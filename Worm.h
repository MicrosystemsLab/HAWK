#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include "Zaber.h"

using namespace std;

struct WormOutputData {
	cv::Mat image;
	int frameNumber;
	SYSTEMTIME frameTime;
	cv::Point2d stagePosition;
	Movement stageMovement;
	cv::Point target;
	cv::Point head;
	cv::Point tail;
	vector<vector<cv::Point> > contours;
	int wormContourIndex;
	vector<cv::Point> wormContour;
	vector<pair<int, int> > segments;
	vector<cv::Point> skeleton;
};

class Worm {
//properties
public:
	cv::Point target;
	cv::Point tail;
private:
	int frameNumber;
	SYSTEMTIME frameTime;

	vector<vector<cv::Point> > contours;
	int wormContourIndex;
	vector<cv::Point> wormContour;
	cv::Point head;
	int headIndex;
	int tailIndex;
	vector<pair<int, int> > segments;
	vector<cv::Point> skeleton;
	
	struct WormImages {
		cv::Mat original;
		cv::Mat resized;
		cv::Mat smooth;
		cv::Mat threshold;
	} images;

//prototypes
public:
	Worm(cv::Mat image, double targetLengthPercentage, cv::Point prevTail, int frame);
	WormOutputData extractWormOutputData(Movement stageMovement, cv::Point2d stagePosition);
private:
	double pointDistance(cv::Point a, cv::Point b);
	int boundCheck(int, int);
	void findWorm(cv::Point prevTail);
	cv::Point findTarget(double percentLength);
	void findWormContour(void);
	void findWormTail(cv::Point prevTail);
	void findWormHead(void);
	void segmentWorm(void);
	void findSkeleton(void);
	void addMidpointToSkeleton(pair<int, int> segmentIndexes);
};

cv::Mat imageWithOutputOverlay(WormOutputData* data);
void drawCross(cv::Mat *image, cv::Point point, cv::Scalar color);
;