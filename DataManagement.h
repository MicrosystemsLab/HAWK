/* DataManagement.h
 * ----------------
 * Header file for the DataManager class. This object handles all the data storage,
 * and writing to disk functionality of the HAWK.
 *
 * Created by John Whitworth on 8/26/14.
  *  Copyright 2015 Eileen Mazzochette, et al <emazz86@stanford.edu>
 */

#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include <highgui.h>
#include "SafeQueue.h"
#include "Worm.h"

#define YAML_OPEN_ERROR 23
#define  AVI_OPEN_ERROR 24

/* Class: DataManager
 * ------------------
 * The DataManager object manages the video and yaml writers. It also houses
 * the SafeQueue of worm data while it is being processed.
 */
class DataManager {
//properties
public:
	//object for writing the YAML file
	cv::FileStorage dataWriter;
	//object for writing to the fpga data file
	cv::FileStorage fpgaWriter;
	//object for writing the AVI file
	cv::VideoWriter videoWriter;
	//threadsafe queue for worm data prior to write out
	SafeQueue<WormOutputData> wormDataBuffer;
	//
	std::string trackDataFileName;
	std::string stimDataFileName;
	std::string aviDataFileName;
	std::string fpgaDataFileName;
private:
	//incremented from 0 as soon as frames are being written
	int writtenWormNumber;
	//time of creation
	SYSTEMTIME now;
//prototypes
public:
	/* Function: setUpDataWriters
	 * --------------------------
	 * Creates the names for the output files, opens up both writers, and
	 * writes the initial header.
	 */
	int setUpDataWriters(string directory, string filename);

	/* Function: appendWormFrameToDisk
	 * -------------------------------
	 * Writes a frame of video to disk and then writes the worm data to the
	 * YAML file.
	 */
	void appendWormFrameToDisk(WormOutputData data, bool printOverlays);



	/* Function: closeDataWriters
	 * --------------------------
	 * Releases both the data writers.
	 */
	void closeDataWriters(void);

	/* Function: writeStimulusDataToDisk
	 * -----------------------------------
	 * Writes the data from the current stimulus to fpga data writer object.
	*/
	void writeStimulusDataToDisk(int stimNum, vector<double> piezoSignalData, vector<double> actuatorPositionData, vector<double> actuatorCommandData, vector<double> desiredSignalData);

	/* Function writefpgaPointToDisk
	 * --------------------------------------
	 * writes a data point from the fpga to the fpga data writer.
	 */

	void writefpgaPointToDisk(string title, double value);

	/* Function: writeStringToDisk
	 * ---------------------------
	 * Outputs the value string with the given title.
	 */
	void writeStringToDisk(string title, string value);

	/* Function: writeDoubleToDisk
	 * ---------------------------
	 * Outputs the value double with the given title.
	 */
	void writeDoubleToDisk(string title, double value);

	/* Function: writeIntToDisk
	 * ------------------------
	 * Outputs the value int with the given title.
	 */
	void writeIntToDisk(string title, int value);

	/* Function: writePointToDisk
	 * --------------------------
	 * Outputs the value Point with the given title.
	 */
	void writePointToDisk(string title, cv::Point value);

	/* Function: writePoint2dToDisk
	 * ----------------------------
	 * Outputs the value Point2d with the given title.
	 */
	void writePoint2dToDisk(string title, cv::Point2d value);

	/* Function: writeMovementToDisk
	 * -----------------------------
	 * Outputs the value Movement with the given title.
	 */
	void writeMovementToDisk(string title, Movement value);

	/* Function: writeTimeToDisk
	 * -------------------------
	 * Outputs the value SYSTEMTIME with the given title.
	 */
	void writeTimeToDisk(string title, SYSTEMTIME value);

	/* Function: startNode
	 * -------------------
	 * Begins a YAML structutre node with the given title.
	 */
	void startNode(string nodeTitle);

	/* Function: endNode
	 * -----------------
	 * Ends a YAML structutre node.
	 */
	void endNode(void);

private:
	/* Function: localTimeFilename
	 * ---------------------------
	 * Returns a string with the local time formatted to be put
	 * in the file name of the output files.
	 */
	string localTimeFilename(SYSTEMTIME now);

	/* Function: wormTitle
	 * -------------------
	 * Returns a string combination of "WormInfo " and the given
	 * integer.
	 */
	string wormTitle(int frameNumber);
};