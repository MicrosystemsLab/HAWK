/* Experiment.h
 * ----------
 * Header file for the Experiment class. The Experiment object handles a single
 * worm behavior experiment.
 *
 * Created by John Whitworth on 8/26/14.
 */

#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include "DataManagement.h"
#include "Stimulus.h"
#include "Worm.h"

using namespace std;

class Experiment {
//properties
public:
	//experiment states:
	bool experimentSetUp;
	bool stimulusReady;
	bool trackingReady;
	bool trackingActive;
	bool stimulusActive;
	bool postStimulusRecording;

	int stimulusNumber;

	//the percentage of body length from the head that should be targeted
	double targetLocation;
	//path to data output location
	string dataOutputLocation;
	//force or displacement clamp
	string experimentMode;
	//user given title for data output
	string experimentTitle;
	//any extra pre-experiment notes
	string otherInfo;
	//any extra post-experiment notes
	string postExpNotes;
	//the DataManager for this experiment
	DataManager dataManager;
	// amount of time to record frames (converts to the number of frames to have in the dataManager's buffer) before stimulus is applied
	int waitingBufferSize;
	// amount of time to record frames (converts to the number of frames) to record after stimulus is applied
	int postWaitingBufferSize;
	// counter for the number of experiments done on a particular slide
	int experimentPerSlideNumber;
	// counter for the number of slides experimented in this session.
	int slideNumber;
	//user defined properties of the worm
	struct WormProperties{
		string wormStrain;
		string wormTreatments;
		string wormGender;
		string wormAge;
		int percentAgar;
		string foodStatus;
	} wormProperties;
	//user defined properties of the cantilever
	struct CantileverProperties{
		string serialNumber;
		//include control parameters
		double frequency;
		double stiffness;
		double sensitivity;
		cv::Point positionInImageSpace;
		double P_parameter;
		double I_parameter;
		double D_parameter;
	} cantileverProperties;
	//stimulus associated with experiment
	Stimulus stim;
	//user defined ambient parameters
	struct AmbientParameters{
		double temperature;
		double humidity;
	} ambientParameters;

	struct ReportedFPGAParameters{
		double P_Parameter;
		double I_Parameter;
		double D_Parameter;
		double clampModeParameter;
		double triggerModeParameter;
		double acquisitionFreqParameter;
		double actuatorFreqParameter;
		double waveTablePresentParameter;
	} reportedFPGAParameters;

//prototypes
public:
	Experiment();

	/* Function: setUpDataOutput
	 * -------------------------
	 * Sets up the data writers and then writes out all the header information for the
	 * experiment.
	 */
	int setUpDataOutput(void);

	/* Function: writeFrameToDisk
	 * --------------------------
	 * Writes a frame of information to disk. This includes raw data on the YAML side and
	 * the video to the AVI file.
	 */
	void writeFrameToDisk(WormOutputData data);

	/* Function: write fpga data to disk
	 * -------------------------------------------
	 * writes the data from the fpga to the data writer in the data manager.
	 */
	void writefpgaDataToDisk(int stimNum, vector<double> piezoSignalData, vector<double> actuatorPositionData, vector<double> actuatorCommandData, vector<double> desiredSignalData);

	/* Function: endExperiment
	 * -----------------------
	 * Writes the post-experiment notes and timing data to disk. Then closes the data
	 * writers.
	 */
	void endExperiment(void);
};