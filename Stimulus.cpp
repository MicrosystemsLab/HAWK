#include "StdAfx.h"
#include "Stimulus.h"

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

using namespace cv;

#define PI 3.14159265358979323846
#define NO_SCALE      0
#define LINEAR_SCALE  1
#define GEO_SCALE     2




Stimulus::Stimulus()
{

}

Stimulus::Stimulus(double prd, double percentConTime, int noCyc, double mag, double scl, int sclType, double snFreq, double snBias)
{
	period = prd;
	contactTime = percentConTime * prd / 100;
	noCycles = noCyc;
	magnitude = mag;
	scale = scl;
	scaleType = sclType;
	sineFrequency = snFreq;
	sineBias = snBias;

	waveTable.clear();
	voltages.clear();

	totalPointsPerPeriod = (int)(period/DELTA_T);
	activePointsPerPeriod = (int)(contactTime/DELTA_T);
	passivePointsPerPeriod = totalPointsPerPeriod - activePointsPerPeriod;

	if (scaleType == LINEAR_SCALE) {
		linearJump = magnitude * scale;
	} else if (scaleType == GEO_SCALE) {
		geoJump = magnitude;
	}
}

void Stimulus::createSquare(void)
{
	for (int i = 0; i < noCycles; i++) {
		for (int j = 0; j < activePointsPerPeriod; j++) {
			double value = magnitude;
			waveTable.push_back(value);
		}
		for (int j = 0; j < passivePointsPerPeriod; j++) {
			double value = 0;
			waveTable.push_back(value);
		}
		updateMagnitudeToScale();
	}
}

void Stimulus::createTriangle(void)
{
	for (int i = 0; i < noCycles; i++) {
		for (int j = 0; j < activePointsPerPeriod/2; j++) {
			double value = magnitude * j * 2 / activePointsPerPeriod;
			waveTable.push_back(value);
		}
		for (int j = 0; j < activePointsPerPeriod/2; j++) {
			double value = magnitude - (magnitude * j * 2 / activePointsPerPeriod);
			waveTable.push_back(value);
		}
		for (int j = 0; j < passivePointsPerPeriod; j++) {
			double value = 0;
			waveTable.push_back(value);
		}
		updateMagnitudeToScale();
	}
}

void Stimulus::createSine(void)
{
	for (int i = 0; i < noCycles; i++) {
		for (int j = 0; j < activePointsPerPeriod; j++) {
			double value = sineBias + magnitude * sin(sineFrequency * 2 * PI * j * DELTA_T);
			waveTable.push_back(value);
		}
		for (int j = 0; j < passivePointsPerPeriod; j++) {
			double value = 0;
			waveTable.push_back(value);
		}
		updateMagnitudeToScale();
	}
}

void Stimulus::updateMagnitudeToScale(void)
{
	if (scaleType == LINEAR_SCALE) {
		magnitude += linearJump;
	} else if (scaleType == GEO_SCALE) {
		geoJump *= abs(scale);
		int sign = (int)(scale/abs(scale));
		magnitude += sign * geoJump;
	}
}

void Stimulus::createFromYAML(string filePath)
{
	FileStorage stimFile(filePath, FileStorage::READ);
	if (stimFile.isOpened()) {
		FileNode node = stimFile["Magnitudes"];
		if (node.type() != FileNode::SEQ) {
			//handle error
		} else {
			FileNodeIterator it = node.begin(), it_end = node.end();
			for(; it != it_end; ++it) {
				waveTable.push_back((double)*it);
			}
			stimFile.release();
		}
	} else {
		//handle error
	}
}

void Stimulus::saveAsYAML(string filePath)
{
	FileStorage stimFile(filePath, FileStorage::WRITE);
	if (stimFile.isOpened()) {
		stimFile << "Magnitudes" << "[";
		//print rest of data
		for (unsigned int i = 0; i < waveTable.size(); i++) {
			stimFile << waveTable[i];
		}
		stimFile << "]";
		stimFile.release();
	} else {
		//handle error
	}
}

void Stimulus::convertToVoltages(double sensitivity)
{
	for(int i = 0; i < waveTable.size(); i++)
	{
		voltages.push_back(waveTable[i]*sensitivity);
	}

}

void Stimulus::appendZeroPulse(void)
{
	for(int i = 0; i < 2/DELTA_T; i++)
	{
		waveTable.push_back(0);
	}
}

void Stimulus::prependZeroPulse(int numberOfZeros)
{
	for(int i = 0; i < numberOfZeros; i++)
	{
		waveTable.push_back(0);
	}
}
void Stimulus::createCalibrationWaveTable(void){
	for (int i = 0; i < noCycles; i++) {
			for (int j = 0; j < activePointsPerPeriod*3/8; j++) {
				double value = magnitude * j * 8/(3* activePointsPerPeriod);
				waveTable.push_back(value);
			}
			for (int j = 0; j < activePointsPerPeriod*2/8; j++) {
				double value = magnitude;
				waveTable.push_back(value);
			}
			for (int j = 0; j < activePointsPerPeriod*3/8; j++) {
				double value = magnitude - (magnitude * j * 8 / (3*activePointsPerPeriod));
				waveTable.push_back(value);
			}
		}
}