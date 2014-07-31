#include "StdAfx.h"
#include "Experiment.h"

int Experiment::setUpDataOutput(void)
{
	int result = dataManager.setUpDataWriters(dataOutputLocation, experimentTitle);
	if (result == 0) {
		dataManager.writeStringToDisk("Experiment Title", experimentTitle);
		dataManager.writeStringToDisk("Experiment Mode", experimentMode);
		dataManager.writeStringToDisk("Other Experiment Info", otherInfo);

		dataManager.startNode("Worm Properties");
		dataManager.writeStringToDisk("Worm Strain", wormProperties.wormStrain);
		dataManager.writeStringToDisk("Worm Treatments", wormProperties.wormTreatments);
		dataManager.writeStringToDisk("Worm Gender", wormProperties.wormGender);
		dataManager.writeStringToDisk("Worm Age", wormProperties.wormAge);
		dataManager.writeIntToDisk("Percent Agar", wormProperties.percentAgar);
		dataManager.writeStringToDisk("Food Status", wormProperties.foodStatus);
		dataManager.endNode();

		dataManager.startNode("Cantilever Properties");
		dataManager.writeStringToDisk("Serial Number", cantileverProperties.serialNumber);
		dataManager.writeDoubleToDisk("Resonant Frequency", cantileverProperties.frequency);
		dataManager.writeDoubleToDisk("Stiffness", cantileverProperties.stiffness);
		dataManager.writeDoubleToDisk("Sensitivity", cantileverProperties.sensitivity);
		dataManager.endNode();
	
		dataManager.startNode("Ambient Parameters");
		dataManager.writeDoubleToDisk("Temperature", ambientParameters.temperature);
		dataManager.writeDoubleToDisk("Humidity", ambientParameters.humidity);
		dataManager.endNode();
	}
	return result;
}

void Experiment::writeFrameToDisk(WormOutputData data)
{
	dataManager.appendWormFrameToDisk(data);
}

void Experiment::endExperiment(void)
{
	dataManager.writeStringToDisk("Timing Data", TICTOC::timer().generateReport());
	dataManager.closeDataWriters();
}