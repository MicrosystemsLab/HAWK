/* Worm.h
 * ------
 * Header file for the Worm class, WormOutputData structure, and
 * imageWithOutputOverlay function. The Worm object corresponds to
 * a frame of tracked data.
 *
 * Created by John Whitworth on 8/26/14.
 */

#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include "Zaber.h"

using namespace std;


/* Structure: WormOutputData
 * -------------------------
 * Made up of all the data that will be recorded from each from of
 * tracking data.
 */
struct WormOutputData {
	cv::Mat image;
	int frameNumber;
	SYSTEMTIME frameTime;
	bool stimulusActive;
	int stimulusNumber;
	cv::Point2d stagePosition;
	Movement stageMovement;
	cv::Point cantilever;
	cv::Point target;
	cv::Point head;
	cv::Point tail;
	cv::Point targetSegment1;
	cv::Point targetSegment2;
	bool headTailToggled;
	vector<vector<cv::Point> > contours;
	int wormContourIndex;
	vector<cv::Point> wormContour;
	vector<pair<int, int> > segments;
	vector<cv::Point> skeleton;
};

/* Class: Worm
 * -----------
 * Object corresponding to a frame of tracking data. All the info on the worm
 * in the image captured.
 */
class Worm {
//properties
public:
	//location point in image space of target
	cv::Point target;
	//location point in image space of tail
	cv::Point tail;
	//location point in image space of head
	cv::Point head;
	//Location of contour points for along the skeleton closest to the target, used for measuring width
	cv::Point targetSegment1;
	cv::Point targetSegment2;

private:
	//processed frame number
	int frameNumber;
	//time of frame capture
	SYSTEMTIME frameTime;
	//boolean flags whether or not to use the search radius to find tail
	bool resetTailFinding;
	//all the contours in the image
	vector<vector<cv::Point> > contours;
	//the index corresponding to the worm's contour in the contours vector
	int wormContourIndex;
	//the worm's contour
	vector<cv::Point> wormContour;
	//the index corresponding to the head point in the wormContour vector
	int headIndex;
	//the index corresponding to the tail point in the wormContour vector
	int tailIndex;
	//all the pairs of indexes which indicate the indexes of segment points in wormContour
	vector<pair<int, int> > segments;
	//all the points along the worm's skeleton, starting at the head
	vector<cv::Point> skeleton;
	//all images along the processing steps
	struct WormImages {
		//original image
		cv::Mat original;
		//resized image
		cv::Mat resized;
		//image with gaussian blur
		cv::Mat smooth;
		//image with OTSU's method thresholding
		cv::Mat threshold;
	} images;

//prototypes
public:
	/* Function: Worm
	 * --------------
	 * Constructor for a Worm object. Resizes the image, finds the worm, and updates the target
	 * property. 1st parameter is the original image, 2nd parameter is the percentage of total
	 * length along the worm to target, 3rd parameter is the tail location from the previously
	 * processed worm (used for tracking), 4th and 5th parameters are frame info.
	 */
	Worm(cv::Mat image, double targetLengthPercentage, cv::Point prevTail, int frame, SYSTEMTIME time, bool reset);

	cv::Point translateTail(cv::Point oldTail, double stageMovement_x, double stageMovement_y);

	/* Function: extractWormOutputData
	 * -------------------------------
	 * Extracts all the data that needs to be output from the worm and returns it in the form of
	 * a WormOutputData structure. Parameters are extra info pieces to be stored and output.
	 */
	WormOutputData extractWormOutputData(Movement stageMovement, cv::Point2d stagePosition, cv::Point cantilever, bool toggled, bool stimulusActive, int stimulusNumber);
private:

	

	/* Function: findWorm
	 * ------------------
	 * Smooths the image, thresholds the image, finds all the contous in the image,
	 * finds the worm contour, finds the tail, then the head, segments the worm, then
	 * finds the skeleton and target.
	 */
	void findWorm(cv::Point prevTail);

	/* Function: findTarget
	 * --------------------
	 * Caclulates the target length from the head, moves along the skeleton until the
	 * length is greater than the target length and then interpolates back along the
	 * previous skeleton part to find the exact target point.
	 */
	cv::Point findTarget(double percentLength);

	/* Function: findWormContour
	 * -------------------------
	 * Finds the worm contour by looking for the largest (most points in the vector) contour
	 * in the list of all contours.
	 */
	void findWormContour(void);

	/* Function: findWormTail
	 * ----------------------
	 * Finds the sharpest point along the worm contour. If this isn't the first frame
	 * only points within a certain range of the previous tail are checked.
	 */
	void findWormTail(cv::Point prevTail);

	/* Function: findWormHead
	 * ----------------------
	 * Finds the sharpest point on the other side of the worm from the tail.
	 */
	void findWormHead(void);

	/* Function: segmentWorm
	 * ---------------------
	 * Segments the worm by moving along one side of the worm by a set increment and
	 * then find the closest point on the other side of the worm.
	 */
	void segmentWorm(void);

	/* Function: findSkeleton
	 * ----------------------
	 * Connects the head, all the midpoints of the segments, and the tail to be the skelton.
	 * Updates the target property.
	 */
	void findSkeleton(void);

	/* Function: addMidpointToSkeleton
	 * -------------------------------
	 * Takes a pair of indexes corresponding to segment endpoints along the wormContour, finds
	 * the midpoint of the segment and adds it to the skeleton.
	 */
	void addMidpointToSkeleton(pair<int, int> segmentIndexes);
    
    /* Function: pointDistance
     * -----------------------
     * Returns the absolute distance between two points. Uses the distance formula.
     */
    double pointDistance(cv::Point a, cv::Point b);
    
    /* Function: boundCheck
     * --------------------
     * Ensures that the currentIndex is within the range of 0 and the maxIndex.
     * If it is not it returns the correct value of the index, assuming the indexes
     * loop around (the index after maxIndex is 0).
     */
    int boundCheck(int currentIndex, int maxIndex);
};

/* Function: imageWithOutputOverlay
 * --------------------------------
 * Returns an the image from data paramter with overlays for all the important worm parts.
 */
cv::Mat imageWithOutputOverlay(WormOutputData* data);

/* Function: drawCross
 * -------------------
 * Draws a cross overlay on the image at the specified point in the specified color.
 */
void drawCross(cv::Mat *image, cv::Point point, cv::Scalar color);