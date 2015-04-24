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
#define SMOOTHING_KSIZE 7
#define SMOOTHING_SIGMA 5
#define TAIL_HEAD_JUMP_THRESHOLD 40




/* Function: drawCross
 * -------------------------------
 * Uses OpenCV functions to draw a cross on an image at a specific point in a specific color. 
 * It draws two diagonal lines to create the cross.
 */
void drawCross(Mat *image, Point point, Scalar color) {
	line(*image, Point(point.x - 5, point.y + 5), Point(point.x + 5, point.y - 5), color, 2, 8, 0);
	line(*image, Point(point.x + 5, point.y + 5), Point(point.x - 5, point.y - 5), color, 2, 8, 0);
}

/* Function: imageWithOutputOverlay
 * -------------------------------
 * Draws marks on the features of interest onto the image to be appended to the video stream
 * Returns a new image with the overlays on top of it.
 */

Mat imageWithOutputOverlay(WormOutputData* data, bool allOverlays)
{
	Mat result;
	//bool allOverLays = true;
    
		//Convert to color image
		cvtColor(data->image, result, CV_GRAY2RGB);

		//Create colors to for overlary
		Scalar green(0,255,0);
		Scalar red(0,0,225);
		Scalar blue(225,0,0);
		Scalar white(225,225,255);
	
	if (allOverlays == true){
		//Print CANTILEVER
		circle(result, data->cantilever, 15, green, 2, 8, 0);

		//PRINT SEGMENTS:
		//Step through each segment and draw a line between the points that correspond between each point
		// color is red.
		for (unsigned int i = 0; i < data->segments.size(); i++) {
			line(result, data->wormContour[data->segments[i].first], data->wormContour[data->segments[i].second], red, 1, 8, 0);
		}

		//PRINT CONTOURS
		// Draw a line around the contour that corresponds to the worm.
		vector<Vec4i> hierarchy;
		drawContours(result, data->contours, data->wormContourIndex, blue, 1, 0, hierarchy, 0, Point(0,0));

		//PRINT SKELETON
		//Draw blue lines between each set of skeleton points.
		for (unsigned int i = 0; i < data->skeleton.size() - 1; i++) {
			line(result, data->skeleton[i], data->skeleton[i+1], blue, 1, 8, 0);
		}

		//PRINT TARGET
		drawCross(&result, data->target, red);

		//PRINT POINTS ON CONTOUR NEAR SEGMENT
		circle(result, data->targetSegment1, 4, blue, 2, 8, 0);
		circle(result, data->targetSegment2, 4, blue, 2, 8, 0);

		//PRINT TAIL
		// Tail has small red circle
		circle(result, data->tail, 5, red, 2, 8, 0);

		//PRINT HEAD
		//Head has large red circle.
		circle(result, data->head, 10, red, 2, 8, 0);

		//PRINT FRAME NUMBER, STIM NUMBER, STIM STATUS
		char* frameText = new char[50];
		if (data->stimulusActive == true)
			sprintf(frameText, "Frame #%d, Stim #%d, ON", data->frameNumber,  data->stimulusNumber);
		else 
			sprintf(frameText, "Frame #%d, Stim #%d, OFF", data->frameNumber,  data->stimulusNumber);
		putText(result, frameText, Point(25, 25), FONT_HERSHEY_SIMPLEX, 0.5, red, 2, 8, false);  
		delete[] frameText;
	}
	else {
		//result = data->image;
		//Scalar bright(225);
		//PRINT FRAME NUMBER, STIM NUMBER, STIM STATUS
		char* frameText = new char[50];
		if (data->stimulusActive == true)
			sprintf(frameText, "Frame #%d, Stim #%d, ON", data->frameNumber,  data->stimulusNumber);
		else 
			sprintf(frameText, "Frame #%d, Stim #%d, OFF", data->frameNumber,  data->stimulusNumber);
		putText(result, frameText, Point(25, 25), FONT_HERSHEY_SIMPLEX, 0.5, white, 2, 8, false);  
		delete[] frameText;
	}

    // Return the image with the overlays:
	return result;
}
/* Constructor: Worm
 * ---------------------------------
 * Constucts the worm structure for the current frame using the given experiment parameters.
 * The image is the most recent image grabbed from the camera
 * The target length percentage is the place on the worm we want to track
 * The prevTrail is the point that corresponds to the tail in the previous frame
 * frame is the current frame number for processing.
 * time is the current time according the PC clock.
 * reset is a boolean indicating to reset the tail search to the entire worm contour instead of the search area.
 */

Worm::Worm(Mat image, double targetLengthPercentage, Point prevTail, int frame, SYSTEMTIME time, bool reset)
{
	// Convert constructor arguments to worm constructor:
    frameTime = time;
	frameNumber = frame;
	resetTailFinding = reset;
	images.original = image;
    
    //Downsampe the image to a smaller scale for faster processing:
	Size newSize = Size((int)(images.original.cols*IMAGE_RESIZE_SCALE), (int)(images.original.rows*IMAGE_RESIZE_SCALE));
	resize(images.original, images.resized, newSize, 0, 0, INTER_LINEAR);

    // Find the worm in the image using the previous tail location
	findWorm(prevTail);
    // Find the target on the worm spline:
	target = findTarget(targetLengthPercentage);
}

/* Function: translateTail
 * ----------------------------
 * Translates the point determined to be the tail in the previous frame by the the amount the stage moved between frames.
 * receives the previous point and the stage movement amount.
 * returns the new, translated points.
 */
 
 
Point  Worm::translateTail(Point oldTail, double stageMovement_x, double stageMovement_y){

	Point translatedTail;
    //Shift point by stage movement:
	translatedTail.x = oldTail.x + (int)stageMovement_x*(PIXELS_PER_UM * IMAGE_RESIZE_SCALE);
	translatedTail.y = oldTail.y + (int)stageMovement_y*(PIXELS_PER_UM * IMAGE_RESIZE_SCALE);;
    //Return new point:
	return translatedTail;
}

/* Function: findWorm
 * -----------------------------
 * Highest level function that calls each step of the image processing in sequence.
 */
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
/* Function: findWormConour
 * -----------------------------
 * From a list of contours in the image, finds the contour that is the longest to be the one corresponding to the worm.
 */
void Worm::findWormContour(void)
{
	int largestContourIndex;
	int largestContourSize = 0; // Initialize at zero.
	int thisContourSize;
    // Interate through the contours, get the length of the contour.
	for (unsigned int i = 0; i < contours.size(); i++) {
		thisContourSize = contours[i].size();
        //If this is the longest contour so far, remember the contour index it corresponds to, and the contour size.
		if (thisContourSize > largestContourSize) {
			largestContourIndex = i;
			largestContourSize = thisContourSize;
		}
	}
    // Assign the longest contour index and the contour itself
	wormContourIndex = largestContourIndex;
	wormContour = contours[largestContourIndex];
}
/* Function: findWormTail
 * -----------------------------------------
 * This function searches for the point along the worm contour that corresponds to the worm tail.
 * The tail is found to be the sharpest point on the contour within the specified set of indices.
 * Sharpness at the current point is calculated by looking at the distance between the current point and a point to the left, 
 * the distance between the current point and a point to the right, and the distance between the two peripheral points.
 * In all frames the we only look at points in which the curvature is convex relative to worm by looking at the centroid of all three 
 * points of interest.
 * In all frames but the first one or when the reset is engaged we only look inside a search region based on the location of the previous 
 * tail point.
 */
 
void Worm::findWormTail(Point prevTail)
{
	// The number of contour indices to span in order to calculate sharpness.
    int jump = 7;
	// Number of points on the worm contour:
    int numPoints = wormContour.size();

    //Initialize sharpness
	double maxSharpness = 0;
	int maxSharpnessIndex;

    //Initialize variables for points:
	Point currPoint;
	Point prevPoint;
	Point nextPoint;
	int currPointIndex;
	int prevPointIndex;
	int nextPointIndex;
	double prevNextDist;
	double currPrevDist;
	double currNextDist;
    //Sharpness measure variable:
	double sharpness;
    //Point to correspond to the centroid of between the three points for each sharpness calculation.
	Point centroid;

    // Iterate through all points on centroid:
	for (int i = 0; i < numPoints; i += 1) {
		// Check indices:
        currPointIndex = boundCheck(i, numPoints - 1);
		prevPointIndex = boundCheck(i - jump, numPoints - 1);
		nextPointIndex = boundCheck(i + jump, numPoints - 1);
        
        //Get the current point coordinates:
		currPoint = wormContour[currPointIndex];
        
        // For this point, check three things to decide if we should calculate sharpness. If yes to any, calculate sharpness:
        // 1. Is this the first frame?
        // 2. Has the user specified that the tail location is wrong and needs to be reset?
        // 3. Is the point within the search region based on previous tail location?
		if (frameNumber <= 2 || resetTailFinding == true || pointDistance(currPoint, prevTail) < TAIL_HEAD_JUMP_THRESHOLD ) {
			// Get coordinates of points on either side of the current point.
            prevPoint = wormContour[prevPointIndex];
			nextPoint = wormContour[nextPointIndex];
            // Calculate the centroid of the three point
			centroid.x = int( 0.333*(currPoint.x + prevPoint.x + nextPoint.x));
			centroid.y = int( 0.333*(currPoint.y + prevPoint.y + nextPoint.y));
            // If the centroid correspond to a bright pixel, then it is "inside" the worm and this is a viable point:
			if (images.threshold.ptr<uchar>(centroid.y)[centroid.x] == 1){
                //Calculate distances between points:
                prevNextDist = pointDistance(prevPoint, nextPoint);
				currPrevDist = pointDistance(currPoint, prevPoint);
				currNextDist = pointDistance(currPoint, nextPoint);
                //Calculate sharpness:
				sharpness = 1 - (prevNextDist/(currPrevDist + currNextDist));
                // Is this the sharpest one yet? If yes, save it.
				if (sharpness > maxSharpness) {
					maxSharpness = sharpness;
					maxSharpnessIndex = currPointIndex;
				}
			}

		}
	}
    // Assign tail to be the sharpest point and save the index:
	tail = wormContour[maxSharpnessIndex];
	tailIndex = maxSharpnessIndex;
}
/* Function: findWormHead
 * ------------------------------------------
 * Find the point that corresponds to the head along the worm contour.
 *
 */
void Worm::findWormHead(void)
{
    // The number of contour indices to span in order to calculate sharpness.
	int jump = 7;
    // Number of points on the worm contour:
	int numPoints = wormContour.size();

    // Set up head search area.
    // The search area is the quarter of the worm contour that is opposite the tail:
	int predictedHeadIndex = boundCheck(tailIndex - (int)numPoints/2, numPoints - 1);
	int minSearch = predictedHeadIndex - (numPoints/6);
	int maxSearch = predictedHeadIndex + (numPoints/6);

	//Initialize sharpness
	double maxSharpness = 0;
	int maxSharpnessIndex;
    
    //Initialize variables for points:
	Point currPoint;
	Point prevPoint;
	Point nextPoint;
	int currPointIndex;
	int prevPointIndex;
	int nextPointIndex;
	double prevNextDist;
	double currPrevDist;
	double currNextDist;
    //Sharpness measure variable:
	double sharpness;
    //Point to correspond to the centroid of between the three points for each sharpness calculation.
	Point centroid;

    //Iterate over the specified search area determined above:
	for (int i = minSearch; i < maxSearch - jump; i += jump) {
		// Check Indices:
        currPointIndex = boundCheck(i, numPoints - 1);
		prevPointIndex = boundCheck(i - jump, numPoints - 1);
		nextPointIndex = boundCheck(i + jump, numPoints - 1);
        // Get point coordinates:
		currPoint = wormContour[currPointIndex];
		prevPoint = wormContour[prevPointIndex];
		nextPoint = wormContour[nextPointIndex];
		//Calculate centroid of three points:
		centroid.x = int( 0.333*(currPoint.x + prevPoint.x + nextPoint.x));
		centroid.y = int( 0.333*(currPoint.y + prevPoint.y + nextPoint.y));
        // If the centroid correspond to a bright pixel, then it is "inside" the worm and this is a viable point:
		if (images.threshold.ptr<uchar>(centroid.y)[centroid.x] == 1){
            // Calculate distances for sharpness calculation:
			prevNextDist = pointDistance(prevPoint, nextPoint);
			currPrevDist = pointDistance(currPoint, prevPoint);
			currNextDist = pointDistance(currPoint, nextPoint);
            // Calculate sharpness:
			sharpness = 1 - (prevNextDist/(currPrevDist + currNextDist));
            // If this is the sharpest point so far, save it:
			if (sharpness > maxSharpness) {
				maxSharpness = sharpness;
				maxSharpnessIndex = currPointIndex;
			}
		}
	}
    // Assign head to be the point worm contout with the highest sharpness and save the index:
	head = wormContour[maxSharpnessIndex];
	headIndex = maxSharpnessIndex;
}
/* Function: segmentWorm:
 * ----------------------------------------
 * Finds segments along the body contour, starting at the head and moving towards the tail
 * Segments are stored in a vector of integer pairs which correspond to the segment pair coordinates.
 */
void Worm::segmentWorm(void)
{
	//Variables for segmentiation:
    int segmentNumber = 0; //Counts the number of segments
    int jump = 5; // The number of points along the contour to move between segments
	int numPoints = wormContour.size(); // The number of points on the contour
	int searchRegion = 30; // The number of points to search over on the opposite side of the worm.
    
    // Initialization:
	int currentIndex = headIndex;
	int endIndex = tailIndex;
	int matchingIndex = headIndex;
    int adjustedMatchingIndex;
    // variables for minimization:
    double valueToMinimize;
    double minValue;
    int minValueIndex;
    
	// Finds which index is greater, head or tail.
	// If tail index is greater, direction is positive, indices increase as you move from head to tail.
	// If head index is greater, direction is negative, indices decrease as you move from tail to head.
	int direction = (endIndex - currentIndex)/abs(endIndex - currentIndex);


	//direction is positive, indices increase as you move from head to tail.
	if (direction > 0) {
		while (currentIndex < endIndex - jump) {
			// Move "jump" points down the worm away from the head.
            currentIndex += jump;
            // increment segment counter
			segmentNumber++;
			// For the first two segments, just move the same distance along the worm:
			if (segmentNumber <= 2) {
				matchingIndex = boundCheck(matchingIndex - jump, numPoints - 1);
			// For the segments within searchRegion of the tail, just move the same distance along the worm.
			//} else if(currentIndex+searchRegion*0.5 >= tailIndex){
			} else if(tailIndex-currentIndex < searchRegion){
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
            // Move "jump" points down the worm away from the head.
			currentIndex -= jump;
            // increment segment counter
			segmentNumber++;
			// For the first two segments, just move the same distance along the worm:
			if (segmentNumber <= 2) {
				matchingIndex = boundCheck(matchingIndex + jump, numPoints - 1);
			// For the segments within searchRegion of the tail, just move the same distance along the worm.
			} else if(currentIndex-tailIndex < searchRegion){
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
            // Save segment to segment vector
			segments.push_back(pair<int, int>(currentIndex, matchingIndex));
		}
	}
}
/* Function: findSkeleton
 * ----------------------------------------
 * Constructs a list of points that correspond to the skeleton. The points are the head, the midpoints 
 * of the segments and the tail, in the order.
 */

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

/* Function: addMidpointToSkeleton
 * -----------------------------------
 * Calculates the midpoint of the current segment and adds it to the skeleton
 */

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

/* Function: findTarget
 * ----------------------------------------
 * Finds the point on the skeleton that corresponds to the target, which is defined as a percentage down the body length.
 * Accepts the percent length as an argument and returns the point that corresponds to the target.
 */
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


/* Function: extractWormOutputData
 * -----------------------------------
 * Organizes the parameters of the worm to be written out as data.
 */


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

/////// Lowest Level Functions:

/* Function: pointDistance
 * ----------------------------
 * Returns the absolute distance between two points. Uses the distance formula.
 */
double Worm::pointDistance(Point a, Point b)
{
    // Distance formula = sqrt((x2-x1)^2+(y2-y1)^2)
    return sqrt(pow(double(a.x - b.x), 2) + pow(double(a.y - b.y), 2));
}
/* Function: boundCheck
 * -----------------------------
 * Ensures that the currentIndex is within the range of 0 and the maxIndex.
 * If it is not it returns the correct value of the index, assuming the indexes
 * loop around (the index after maxIndex is 0).
 */
int Worm::boundCheck(int currentIndex, int maxIndex)
{
    // Index cannot be negative
    if (currentIndex < 0) {
        //Return the appropriate index at the end of the list.
        return maxIndex - abs(currentIndex);
        // Index cannot be more than the total number of indices in the curvature
    } else if (currentIndex > maxIndex) {
        //Return the appropriate index at the beginning of the list.
        return currentIndex - maxIndex;
    } else {
        // If inside bounds, just return the argument index.
        return currentIndex;
    }
}