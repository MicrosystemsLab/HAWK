#include "StdAfx.h"
#include "DataManagement.h"

#include "ImageControl.h"
#include "Worm.h"

using namespace cv;
using namespace std;

string DataManager::localTimeFilename(SYSTEMTIME now)
{
	string result;

	char* cTime = new char[50];
	sprintf(cTime, "%04d_%02d_%02d__%02d_%02d_%02d__", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
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

void DataManager::writeStimulusDataToDisk(int stimNum, vector<double> piezoSignalData, vector<double> actuatorPositionData, vector<double> actuatorCommandData, vector<double> desiredSignalData)
{
	string nodeTitle;
	char* title = new char[50];
	sprintf(title, "Stimulus %d", stimNum);
	nodeTitle = string(title);

	fpgaWriter << nodeTitle << "{";
	fpgaWriter << "Piezo Signal Magnitudes" << "{";
	//print rest of data
	for (unsigned int i = 0; i < piezoSignalData.size(); i++) {
		sprintf(title, "Point %d", i);
		nodeTitle = string(title);
		fpgaWriter << nodeTitle << piezoSignalData[i];
	}
	fpgaWriter << "}";

	fpgaWriter << "Actuator Position Magnitudes" << "{";
	//print rest of data
	for (unsigned int i = 0; i < actuatorPositionData.size(); i++) {
		sprintf(title, "Point %d", i);
		nodeTitle = string(title);
		fpgaWriter << nodeTitle << actuatorPositionData[i];
	}
	fpgaWriter << "}";

		fpgaWriter << "Actuator Command Magnitudes" << "{";
	//print rest of data
	for (unsigned int i = 0; i < actuatorCommandData.size(); i++) {
		sprintf(title, "Point %d", i);
		nodeTitle = string(title);
		fpgaWriter << nodeTitle << actuatorCommandData[i];
	}
	fpgaWriter << "}";

	fpgaWriter << "Desired Signal Magnitudes" << "{";
	//print rest of data
	for (unsigned int i = 0; i < desiredSignalData.size(); i++) {
		sprintf(title, "Point %d", i);
		nodeTitle = string(title);
		fpgaWriter << nodeTitle << desiredSignalData[i];
	}
	fpgaWriter << "}";

	//end this stimulus node:
	fpgaWriter << "}";
		
}

void DataManager::writefpgaPointToDisk(string title, double value)
{
	fpgaWriter << title << value;
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

	writeIntToDisk("x", (int)(value.x / IMAGE_RESIZE_SCALE));
	writeIntToDisk("y", (int)(value.y / IMAGE_RESIZE_SCALE));

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
	sprintf(cTime, "%02d/%02d/%04d %02d:%02d:%02d.%03d", value.wMonth, value.wDay, value.wYear, value.wHour, value.wMinute, value.wSecond, value.wMilliseconds);
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
	writtenWormNumber = 1;

	SYSTEMTIME now;
	GetLocalTime(&now);

	string fileTimeStamp = localTimeFilename(now);

	CreateDirectoryA((directory + string("\\\\") + fileTimeStamp + filename).c_str(), NULL);

	trackDataFileName = directory + string("\\\\") + fileTimeStamp + filename + string("\\\\") + fileTimeStamp + filename + string("_tracking") + string(".yaml");
	stimDataFileName = directory + string("\\\\") + fileTimeStamp + filename + string("\\\\") + fileTimeStamp + filename + string("_stimulus") + string(".yaml");
	aviDataFileName = directory + string("\\\\") + fileTimeStamp + filename + string("\\\\") + fileTimeStamp + filename + string("_video") + string(".avi");
	fpgaDataFileName = directory + string("\\\\") + fileTimeStamp + filename + string("\\\\") + fileTimeStamp + filename + string("_FPGAdata") + string(".yaml");


	//open AVI Data File for writing
	Size frameSize = Size((int)(IMAGE_X_PIXELS * IMAGE_RESIZE_SCALE), (int)(IMAGE_Y_PIXELS * IMAGE_RESIZE_SCALE));
	videoWriter.open(aviDataFileName, 0, 12, frameSize, true);
	if (!videoWriter.isOpened()) {
		return AVI_OPEN_ERROR;
	}
	//open YAML Data File for writing
	dataWriter.open(trackDataFileName, FileStorage::WRITE);
	if (!dataWriter.isOpened()) {
		return YAML_OPEN_ERROR;
	}

	//open YAML file for writing FPGA data
	fpgaWriter.open(fpgaDataFileName, FileStorage::WRITE);

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
	startNode(wormTitle(writtenWormNumber++));

	writeTimeToDisk("Time",  data.frameTime);
	writeIntToDisk("Processed Frame Number", data.frameNumber);
	if (data.stimulusActive) {
		writeIntToDisk("Stimulus Active", 1);
	} else {
		writeIntToDisk("Stimulus Active", 0);
	}
	writeIntToDisk("Stimulus Number", data.stimulusNumber);
	
	writeMovementToDisk("Stage Movement", data.stageMovement);
	writePoint2dToDisk("Stage Position", data.stagePosition);

	writePointToDisk("Target", data.target);
	writePointToDisk("Head", data.head);
	writePointToDisk("Tail", data.tail);
	writePointToDisk("Target Segment 1", data.targetSegment1);
	writePointToDisk("Target Segment 2", data.targetSegment2);
	if (data.headTailToggled) {
		writeIntToDisk("Toggled", 1);
	} else {
		writeIntToDisk("Toggled", 0);
	}

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
	fpgaWriter.release();
}