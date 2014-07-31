#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include "DataManagement.h"
#include "Worm.h"

using namespace std;

class Experiment {
//properties
public:
	double targetLocation;

	string dataOutputLocation;
	string experimentMode;
	string experimentTitle;
	string otherInfo;

	DataManager dataManager;

	struct WormProperties{
		string wormStrain;
		string wormTreatments;
		string wormGender;
		string wormAge;
		int percentAgar;
		string foodStatus;
	} wormProperties;

	struct CantileverProperties{
		string serialNumber;
		//inclue control parameters
		double frequency;
		double stiffness;
		double sensitivity;
		//Point2d positionInRealSpace;
		cv::Point positionInImageSpace; // = (621, 365) with resize adjust
	} cantileverProperties;

	struct AmbientParameters{
		double temperature;
		double humidity;
	} ambientParameters;

private:

//prototypes
public:
	int setUpDataOutput(void);
	void writeFrameToDisk(WormOutputData data);
	void endExperiment(void);
private:

};