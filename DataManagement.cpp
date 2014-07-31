#include "StdAfx.h"
#include "DataManagement.h"

#include "ImageControl.h"
#include "Worm.h"

using namespace cv;
using namespace std;

#define VIDEO_FPS 5
#define VIDEO_CODEC -1

string DataManager::localTimeFilename(SYSTEMTIME now)
{
	string result;

	char* cTime = new char[50];
	sprintf(cTime, "%04d%02d%02d_%02d%02d%02d_", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
	result = string(cTime);
	delete cTime;

	return result;
}

string DataManager::wormTitle(int frameNumber)
{
	string result;

	char* title = new char[50];
	sprintf(title, "WormInfo %d", frameNumber);
	result = string(title);
	delete[] title;

	return result;
}

void DataManager::writeStringToDisk(string title, string value)
{
	dataWriter << title << value;
}

void DataManager::writeDoubleToDisk(string title, double value)
{
	dataWriter << title << value;
}

void DataManager::writeIntToDisk(string title, int value)
{
	dataWriter << title << value;
}

void DataManager::writePointToDisk(string title, Point value)
{
	startNode(title);

	writeIntToDisk("x", value.x);
	writeIntToDisk("y", value.y);

	endNode();
}

void DataManager::writePoint2dToDisk(string title, Point2d value)
{
	startNode(title);

	writeDoubleToDisk("x", value.x);
	writeDoubleToDisk("y", value.y);

	endNode();
}

void DataManager::writeMovementToDisk(string title, Movement value)
{
	startNode(title);

	writeDoubleToDisk("x-axis", value.x);
	writeDoubleToDisk("y-axis", value.y);

	endNode();
}

void DataManager::writeTimeToDisk(string title, SYSTEMTIME value)
{
	string time;
	char* cTime = new char[50];
	sprintf(cTime, "%02d/%02d/%04d %02d:%02d:%02d.%d", value.wMonth, value.wDay, value.wYear, value.wHour, value.wMinute, value.wSecond, value.wMilliseconds);
	time = string(cTime);
	delete cTime;

	writeStringToDisk(title, time);
}

void DataManager::startNode(string nodeTitle)
{
	dataWriter << nodeTitle << "{";
}

void DataManager::endNode(void){
	dataWriter << "}";
}

int DataManager::setUpDataWriters(string directory, string filename)
{
	SYSTEMTIME now;
	GetLocalTime(&now);

	string fileTimeStamp = localTimeFilename(now);
	string yamlDataFileName = directory + fileTimeStamp + filename + string(".yaml");
	string  aviDataFileName = directory + fileTimeStamp + filename + string(".avi");

	//open AVI Data File for writing
	Size frameSize = Size((int)(IMAGE_X_PIXELS * IMAGE_RESIZE_SCALE), (int)(IMAGE_Y_PIXELS * IMAGE_RESIZE_SCALE));
	videoWriter.open(aviDataFileName, VIDEO_CODEC, VIDEO_FPS, frameSize, true);
	if (!videoWriter.isOpened()) {
		return AVI_OPEN_ERROR;
	}
	//open YAML Data File for writing
	dataWriter.open(yamlDataFileName, FileStorage::WRITE);
	if (!dataWriter.isOpened()) {
		return YAML_OPEN_ERROR;
	}

	writeStringToDisk("Raptor", "HAWK");
	writeIntToDisk("Microsystems Lab Stanford University", 2014);

	writeTimeToDisk("Experiment Time", now);

	return 0;
}

void DataManager::appendWormFrameToDisk(WormOutputData data)
{
	//write to AVI
	videoWriter << imageWithOutputOverlay(&data);

	//write to YAML
	startNode(wormTitle(data.frameNumber));

	writeTimeToDisk("Time",  data.frameTime);
	writeIntToDisk("Processed Frame Number", data.frameNumber);
	
	writeMovementToDisk("Stage Movement", data.stageMovement);
	writePoint2dToDisk("Stage Position", data.stagePosition);

	writePointToDisk("Target", data.target);
	writePointToDisk("Head", data.head);
	writePointToDisk("Tail", data.tail);

	startNode("Skeleton");

	char* skeletonPoint = new char[50];
	for (unsigned int i = 0; i < data.skeleton.size(); i++) {
		sprintf(skeletonPoint, "Point %d", i);
		writePointToDisk(skeletonPoint, data.skeleton[i]);
	}
	delete[] skeletonPoint;

	endNode();

	endNode();
}

void DataManager::closeDataWriters(void)
{
	dataWriter.release();
	videoWriter.release();
}