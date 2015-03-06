#include "StdAfx.h"
#include "Worm.h"
#include "ImageControl.h"

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//PARAMETER DEFINES
#define THRESHOLDING_VALUE 75
#define THRESHOLDING_MAX_BINARY 225
#define SMOOTHING_KSIZE 5
#define SMOOTHING_SIGMA 3
#define TAIL_HEAD_JUMP_THRESHOLD 20

double Worm::pointDistance(Point a, Point b)
{
 	return sqrt(pow(double(a.x - b.x), 2) + pow(double(a.y - b.y), 2));
}

int Worm::boundCheck(int currentIndex, int maxIndex)
{
	if (currentIndex < 0) {
        return maxIndex - abs(currentIndex);
	} else if (currentIndex > maxIndex) {
        return currentIndex - maxIndex;
	} else {
        return currentIndex;
	}
}

void drawCross(Mat *image, Point point, Scalar color) {
	line(*image, Point(point.x - 5, point.y + 5), Point(point.x + 5, point.y - 5), color, 2, 8, 0);
	line(*image, Point(point.x + 5, point.y + 5), Point(point.x - 5, point.y - 5), color, 2, 8, 0);
}

Mat imageWithOutputOverlay(WormOutputData* data)
{
	Mat result;

	cvtColor(data->image, result, CV_GRAY2RGB);

	Scalar green(0,255,0);
	Scalar red(0,0,225);
	Scalar blue(225,0,0);

	//Print CANTILEVER
	circle(result, data->cantilever, 15, green, 2, 8, 0);

	//PRINT SEGMENTS:
	for (unsigned int i = 0; i < data->segments.size(); i++) {
		line(result, data->wormContour[data->segments[i].first], data->wormContour[data->segments[i].second], red, 1, 8, 0);
	}

	//PRINT CONTOURS
	vector<Vec4i> hierarchy;
	drawContours(result, data->contours, data->wormContourIndex, blue, 1, 0, hierarchy, 0, Point(0,0));

	//PRINT SKELETON
	for (unsigned int i = 0; i < data->skeleton.size() - 1; i++) {
		line(result, data->skeleton[i], data->skeleton[i+1], blue, 1, 8, 0);
	}

	//PRINT TARGET
	drawCross(&result, data->target, red);

	//PRINT POINTS ON CONTOUR NEAR SEGMENT
	circle(result, data->targetSegment1, 4, blue, 2, 8, 0);
	circle(result, data->targetSegment2, 4, blue, 2, 8, 0);

	//PRINT TAIL
	circle(result, data->tail, 5, red, 2, 8, 0);

	//PRINT HEAD
	circle(result, data->head, 10, red, 2, 8, 0);

	//PRINT FRAME NUMBER

	char* frameText = new char[50];
	if (data->stimulusActive == true)
		sprintf(frameText, "Frame #%d, Stim #%d, ON", data->frameNumber,  data->stimulusNumber);
	else 
		sprintf(frameText, "Frame #%d, Stim #%d, OFF", data->frameNumber,  data->stimulusNumber);
	putText(result, frameText, Point(50, 50), FONT_HERSHEY_SIMPLEX, 0.75, red, 2, 8, false);  
	delete[] frameText;

	return result;
}

Worm::Worm(Mat image, double targetLengthPercentage, Point prevTail, int frame, SYSTEMTIME time)
{
	frameTime = time;
	frameNumber = frame;

	images.original = image;
	Size newSize = Size((int)(images.original.cols*IMAGE_RESIZE_SCALE), (int)(images.original.rows*IMAGE_RESIZE_SCALE));
	resize(images.original, images.resized, newSize, 0, 0, INTER_LINEAR);

	findWorm(prevTail);
	target = findTarget(targetLengthPercentage);
}

void Worm::findWorm(Point prevTail)
{
	//SMOOTH
	GaussianBlur(images.resized, images.smooth, Size(SMOOTHING_KSIZE, SMOOTHING_KSIZE), SMOOTHING_SIGMA, SMOOTHING_SIGMA, BORDER_DEFAULT);
	//THRESHOLD
	threshold(images.smooth, images.threshold, THRESHOLDING_VALUE, THRESHOLDING_MAX_BINARY, THRESH_BINARY + THRESH_OTSU);
	//FIND CONTOURS
	findContours(images.threshold, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0,0));
	//FIND WORM CONTOUR
	findWormContour();
	//FIND TAIL
	findWormTail(prevTail);
	//FIND HEAD
	findWormHead();
	//SEGMENTATION
	segmentWorm();
	//FIND SKELETON
	findSkeleton();
}

void Worm::segmentWorm(void)
{
	int segmentNumber = 0;
	int jump = 5;
	int numPoints = wormContour.size();
	int searchRegion = 30;
	int currentIndex = headIndex;
	int endIndex = tailIndex;
	int matchingIndex = headIndex;

	// Finds which index is great, head or tail. 
	// If tail index is greater, direction is positive, indices increase as you move from head to tail.
	// If head index is greater, direction is negative, indices decrease as you move from tail to head.
	int direction = (endIndex - currentIndex)/abs(endIndex - currentIndex);

	int adjustedMatchingIndex;
	double valueToMinimize;
	double minValue;
	int minValueIndex;

	//direction is positive, indices increase as you move from head to tail.
	if (direction > 0) {
		while (currentIndex < endIndex - jump) {
			currentIndex += jump;

			segmentNumber++;
			// For the first two segments, just move the same distance along the worm:
			if (segmentNumber <= 2) {
				matchingIndex = boundCheck(matchingIndex - jump, numPoints - 1);
			// For the segments within searchRegion of the tail, just move the same distance along the worm.
			} else if(currentIndex+searchRegion*0.5 >= tailIndex){
				matchingIndex  = boundCheck(matchingIndex - jump, numPoints-1);
			// For the next segments, search over region searchRegion points long to find the point closest to current 
			//index on the opposite side of the worm
			} else {
				for (int i = 1; i <= searchRegion; i++) {
					adjustedMatchingIndex = boundCheck(matchingIndex - i, numPoints - 1);
					if (adjustedMatchingIndex > tailIndex || adjustedMatchingIndex < headIndex) {
						valueToMinimize = pow((double)(wormContour[adjustedMatchingIndex].x - wormContour[currentIndex].x), 2) +
										  pow((double)(wormContour[adjustedMatchingIndex].y - wormContour[currentIndex].y), 2);

						if (i == 1) {
							minValue = valueToMinimize;
							minValueIndex = adjustedMatchingIndex;
						} else if (valueToMinimize < minValue) {
							minValue = valueToMinimize;
							minValueIndex = adjustedMatchingIndex;
						}
					}
				}
				matchingIndex = minValueIndex;
			}
			segments.push_back(pair<int, int>(currentIndex, matchingIndex));
		}
	//direction is negative, indices decrease as you move from tail to head.
	} else if (direction < 0) {
		while (currentIndex > endIndex + jump) {
			currentIndex -= jump;

			segmentNumber++;
			// For the first two segments, just move the same distance along the worm:
			if (segmentNumber <= 2) {
				matchingIndex = boundCheck(matchingIndex + jump, numPoints - 1);
			// For the segments within searchRegion of the tail, just move the same distance along the worm.
			} else if(currentIndex - searchRegion*0.5 <= tailIndex){
				matchingIndex  = boundCheck(matchingIndex + jump, numPoints-1);
			// For the next segments, search over region searchRegion points long to find the point closest to current 
			//index on the opposite side of the worm
			} else {
				for (int i = 1; i <= 30; i++) {
					adjustedMatchingIndex = boundCheck(matchingIndex + i, numPoints - 1);
					if (adjustedMatchingIndex > tailIndex || adjustedMatchingIndex < headIndex) {
						valueToMinimize = pow((double)(wormContour[adjustedMatchingIndex].x - wormContour[currentIndex].x), 2) +
										  pow((double)(wormContour[adjustedMatchingIndex].y - wormContour[currentIndex].y), 2);

						if (i == 1) {
							minValue = valueToMinimize;
							minValueIndex = adjustedMatchingIndex;
						} else if (valueToMinimize < minValue) {
							minValue = valueToMinimize;
							minValueIndex = adjustedMatchingIndex;
						}
					}
				}
				matchingIndex = minValueIndex;
			}
			segments.push_back(pair<int, int>(currentIndex, matchingIndex));
		}
	}
}

void Worm::findWormTail(Point prevTail)
{
	int jump = 7;
	int numPoints = wormContour.size();

	double maxSharpness = 0;
	int maxSharpnessIndex;

	Point currPoint;
	Point prevPoint;
	Point nextPoint;
	int currPointIndex;
	int prevPointIndex;
	int nextPointIndex;
	double prevNextDist;
	double currPrevDist;
	double currNextDist;
	double sharpness;

	for (int i = 0; i < numPoints - jump; i += jump) {
		currPointIndex = boundCheck(i, numPoints - 1);
		prevPointIndex = boundCheck(i - jump, numPoints - 1);
		nextPointIndex = boundCheck(i + jump, numPoints - 1);

		currPoint = wormContour[currPointIndex];
		if (frameNumber <= 2 || pointDistance(currPoint, prevTail) < TAIL_HEAD_JUMP_THRESHOLD) {
			prevPoint = wormContour[prevPointIndex];
			nextPoint = wormContour[nextPointIndex];

			prevNextDist = pointDistance(prevPoint, nextPoint);
			currPrevDist = pointDistance(currPoint, prevPoint);
			currNextDist = pointDistance(currPoint, nextPoint);

			sharpness = 1 - (prevNextDist/(currPrevDist + currNextDist));

			if (sharpness > maxSharpness) {
				maxSharpness = sharpness;
				maxSharpnessIndex = currPointIndex;
			}
		}
	}

	tail = wormContour[maxSharpnessIndex];
	tailIndex = maxSharpnessIndex;
}

void Worm::findWormHead(void)
{
	int jump = 7;
	int numPoints = wormContour.size();

	int predictedHeadIndex = boundCheck(tailIndex - (int)numPoints/2, numPoints - 1);
	int minSearch = predictedHeadIndex - (numPoints/8);
	int maxSearch = predictedHeadIndex + (numPoints/8);

	//region specific
	double maxSharpness = 0;
	int maxSharpnessIndex;

	Point currPoint;
	Point prevPoint;
	Point nextPoint;
	int currPointIndex;
	int prevPointIndex;
	int nextPointIndex;
	double prevNextDist;
	double currPrevDist;
	double currNextDist;
	double sharpness;

	for (int i = minSearch; i < maxSearch - jump; i += jump) {
		currPointIndex = boundCheck(i, numPoints - 1);
		prevPointIndex = boundCheck(i - jump, numPoints - 1);
		nextPointIndex = boundCheck(i + jump, numPoints - 1);

		currPoint = wormContour[currPointIndex];
		prevPoint = wormContour[prevPointIndex];
		nextPoint = wormContour[nextPointIndex];
		
		prevNextDist = pointDistance(prevPoint, nextPoint);
		currPrevDist = pointDistance(currPoint, prevPoint);
		currNextDist = pointDistance(currPoint, nextPoint);

		sharpness = 1 - (prevNextDist/(currPrevDist + currNextDist));

		if (sharpness > maxSharpness) {
			maxSharpness = sharpness;
			maxSharpnessIndex = currPointIndex;
		}
	}

	head = wormContour[maxSharpnessIndex];
	headIndex = maxSharpnessIndex;
}

void Worm::findWormContour(void)
{
	int largestContourIndex;
	int largestContourSize = 0;
	int thisContourSize;
	for (unsigned int i = 0; i < contours.size(); i++) {
		thisContourSize = contours[i].size();
		if (thisContourSize > largestContourSize) {
			largestContourIndex = i;
			largestContourSize = thisContourSize;
		}
	}
	wormContourIndex = largestContourIndex;
	wormContour = contours[largestContourIndex];
}

Point Worm::findTarget(double percentLength)
{
    Point result;
    
    //finds the length of the skeleton
    double skeletonLength = 0.0;
    vector<double> skeletonDistances;
    for (unsigned int i = 0; i < skeleton.size() - 1; i++) {
        Point point1 = skeleton[i];
        Point point2 = skeleton[i + 1];
        double distance = pointDistance(point1, point2);
        skeletonDistances.push_back(distance);
        skeletonLength += distance;
    }
    
    //target length from head
    double targetLength = percentLength * skeletonLength;
    
    //finds segment that contains target
    double lengthAlongSkeleton = 0;
    int indexAlongSkeleton = 0;
    while (lengthAlongSkeleton < targetLength) {
        lengthAlongSkeleton += skeletonDistances[indexAlongSkeleton];
        indexAlongSkeleton++;
    }
    
    //find target
    double extraLength = lengthAlongSkeleton - targetLength;
    
    double lastSegmentLength = skeletonDistances[indexAlongSkeleton - 1];
    Point nextPoint = skeleton[indexAlongSkeleton];
    Point prevPoint = skeleton[indexAlongSkeleton - 1];
    
	// Save the points on either side of the contour that coorrespond to the segment closest to the target.
	if (indexAlongSkeleton-1 < segments.size()){
		targetSegment1 = wormContour[segments[indexAlongSkeleton-1].first];
		targetSegment2 = wormContour[segments[indexAlongSkeleton-1].second];
	} else {
		targetSegment1.x = 0;
		targetSegment1.y = 0;
		targetSegment2.x = 0;
		targetSegment2.y = 0;
	}


	// Calculate location of point along the skeleton segment that correpsonds to the target.
    result.x = (int)(nextPoint.x - extraLength * ((nextPoint.x - prevPoint.x)/lastSegmentLength));
    result.y = (int)(nextPoint.y - extraLength * ((nextPoint.y - prevPoint.y)/lastSegmentLength));
    
    return result;
}

void Worm::addMidpointToSkeleton(pair<int, int> segmentIndexes)
{
    //extract points
    Point point1 = wormContour[segmentIndexes.first];
    Point point2 = wormContour[segmentIndexes.second];
    
    //compute midpoint
    Point midpoint;
    midpoint.x = (point1.x + point2.x)/2;
    midpoint.y = (point1.y + point2.y)/2;
    
    //add midpoint to skeleton
    skeleton.push_back(midpoint);
}

void Worm::findSkeleton(void)
{
    //Add head to skeleton
    skeleton.push_back(head);
    
    //Add midpoints to skeleton
    for(unsigned int i = 0; i < segments.size(); i++) {
		addMidpointToSkeleton(segments[i]);
	}

    //Add tail to skeleton
    skeleton.push_back(tail);
}

WormOutputData Worm::extractWormOutputData(Movement stageMovement, Point2d stagePosition, Point cantilever, bool toggled, bool stimulusActive, int stimulusNumber)
{
	WormOutputData result;

	result.cantilever = cantilever;
	result.image = images.resized;
	result.frameNumber = frameNumber;
	result.frameTime = frameTime;
	result.stimulusActive = stimulusActive;
	result.stimulusNumber = stimulusNumber;

	result.stagePosition = stagePosition;
	result.stageMovement = stageMovement;

	result.target = target;
	result.head = head;
	result.tail = tail;
	result.headTailToggled = toggled;
	result.targetSegment1 = targetSegment1;
	result.targetSegment2 = targetSegment2;

	result.contours = contours;
	result.wormContourIndex = wormContourIndex;
	result.wormContour = wormContour;
	result.segments = segments;
	result.skeleton = skeleton;
	
	return result;
}