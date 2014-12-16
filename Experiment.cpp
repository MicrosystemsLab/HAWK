#include "StdAfx.h"
#include "Experiment.h"


Experiment::Experiment()
{

}

int Experiment::setUpDataOutput(void)
{
	int result = dataManager.setUpDataWriters(dataOutputLocation, experimentTitle);
	if (result == 0) {
		dataManager.writeStringToDisk("Experiment Title", experimentTitle);
		dataManager.writeStringToDisk("Experiment Mode", experimentMode);
		dataManager.writeDoubleToDisk("Target Location", targetLocation*100);
		dataManager.writeIntToDisk("Slide Number", slideNumber);
		dataManager.writeIntToDisk("Experiment on this slide Number", experimentPerSlideNumber);
		dataManager.writeIntToDisk("Pre-Stimulus Record Time", waitingBufferSize);
		dataManager.writeIntToDisk("Post-Stimulus Record Time", postWaitingBufferSize);
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
		dataManager.writeDoubleToDisk("P Parameter", cantileverProperties.P_parameter);
		dataManager.writeDoubleToDisk("I Parameter", cantileverProperties.I_parameter);
		dataManager.writeDoubleToDisk("D Parameter", cantileverProperties.D_parameter);
		dataManager.endNode();

		dataManager.startNode("Reported FPGA Parameters");
		dataManager.writeDoubleToDisk("P Parameter", reportedFPGAParameters.P_Parameter);
		dataManager.writeDoubleToDisk("I Parameter", reportedFPGAParameters.I_Parameter);
		dataManager.writeDoubleToDisk("D Parameter", reportedFPGAParameters.D_Parameter);
		dataManager.writeDoubleToDisk("Clamp Mode Parameter", reportedFPGAParameters.clampModeParameter);
		dataManager.writeDoubleToDisk("Trigger Mode Parameter", reportedFPGAParameters.triggerModeParameter);
		dataManager.writeDoubleToDisk("Acquisition Frequency", reportedFPGAParameters.acquisitionFreqParameter);
		dataManager.writeDoubleToDisk("Actuator Frequency", reportedFPGAParameters.actuatorFreqParameter);
		dataManager.writeDoubleToDisk("Wave Table Present", reportedFPGAParameters.waveTablePresentParameter);
		dataManager.endNode();
	
		dataManager.startNode("Ambient Parameters");
		dataManager.writeDoubleToDisk("Temperature", ambientParameters.temperature);
		dataManager.writeDoubleToDisk("Humidity", ambientParameters.humidity);
		dataManager.endNode();

		
	}
	
	stim.saveAsYAML(dataManager.stimDataFileName);
	
	return result;
}

void Experiment::writeFrameToDisk(WormOutputData data)
{
	dataManager.appendWormFrameToDisk(data);
}

void Experiment::writefpgaDataToDisk(int stimNum, vector<double> piezoSignalData, vector<double> actuatorPositionData, vector<double> actuatorCommandData, vector<double> desiredSignalData)
{
	dataManager.writeStimulusDataToDisk(stimNum, piezoSignalData,  actuatorPositionData, actuatorCommandData,  desiredSignalData);
}

void Experiment::endExperiment(void)
{
	dataManager.writeIntToDisk("Number Of Stimulus", stimulusNumber-1);
	dataManager.writeStringToDisk("Post Experiment Notes", postExpNotes);
	dataManager.writeStringToDisk("Timing Data", TICTOC::timer().generateReport());

	

	dataManager.closeDataWriters();
}