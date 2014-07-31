#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include <highgui.h>
#include "SafeQueue.h"
#include "Worm.h"

#define YAML_OPEN_ERROR 23
#define  AVI_OPEN_ERROR 24

class DataManager {
//properties
public:
	cv::FileStorage dataWriter;
	cv::VideoWriter videoWriter;

	SafeQueue<WormOutputData> wormDataBuffer;
private:
	
//prototypes
public:
	int setUpDataWriters(string directory, string filename);
	void appendWormFrameToDisk(WormOutputData data);
	void closeDataWriters(void);

	void writeStringToDisk(string title, string value);
	void writeDoubleToDisk(string title, double value);
	void writeIntToDisk(string title, int value);
	void writePointToDisk(string title, cv::Point value);
	void writePoint2dToDisk(string title, cv::Point2d value);
	void writeMovementToDisk(string title, Movement value);
	void writeTimeToDisk(string title, SYSTEMTIME value);

	void startNode(string nodeTitle);
	void endNode(void);
private:
	string localTimeFilename(SYSTEMTIME now);
	string wormTitle(int frameNumber);
};