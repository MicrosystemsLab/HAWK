/* STM_Communicator.h
 * ------------------
 * Header file for the STM_Communicator class. This object manages
 * communication with the force clamp via TCP/IP communication.
 *
 * Created by John Whitworth on 8/26/14.
 */

#pragma once

#include "STM Convert.h"
#include "STMDispatch.h"
#include "STMSession.h"

using namespace System;

/* Class: STM_Communicator
 * -----------------------
 * This object inherits from the STMDispatch class and uses STM
 * flatten and unflatten protocols to send and receive packets of
 * data over TCP/IP.
 */
class STM_Communicator : public STMDispatch {
//properties
public:
	//indicates if the HAWK is connected to the force clamp
	bool connected;
	//indicates if an actuation has been completed
	bool stimulusCompleted;
	//indicates if an actuation has started.
	bool stimulusStarted;
	//indicates the curent status of the actuator
	int moving;

	bool dataRead;

	vector<double> piezoSignalData;
	vector<double> actuatorPositionData;
	vector<double> actuatorCommandData;
	vector<double> desiredSignalData;
	int messageReceivedCount;

	double P_Parameter;
	double I_Parameter;
	double D_Parameter;
	double clampModeParameter;
	double triggerModeParameter;
	double acquisitionFreqParameter;
	double actuatorFreqParameter;
	double waveTablePresentParameter;
	double fifoMemoryFullParameter;  // should be false, if true, there is a problem with the FPGA, don't trust data
	double actuatorMovingParameter;


	int reportedStimNum;
	vector<double> reportedPiezoSignalData; 
	vector<double> reportedActuatorPositionData;
	vector<double> reportedActuatorCommandData;
	vector<double> reportedDesiredSignalData;

private:
	//a communication session with the force clamp
	STMSession STM;
//prototypes
public:
	/* Function: STM_Communicator
	 * --------------------------
	 * Constructor for a STM_Communicator object. Sets the dispast for STM to this object,
	 * and connects to the IP and port of the force clamp.
	 */
	STM_Communicator();

	/* Function: ~STM_Communicator
	 * ---------------------------
	 * Deconstructor for a STM_Communicator object. Disconnects before
	 * deconstruction.
	 */
	~STM_Communicator();

	/* Function: triggerStimulus
	 * -------------------------
	 * Writes the write_Actuate command with a 1 argument.
	 */
	bool triggerStimulus(void);

	/* Function: cancelStimulus
	 * ------------------------
	 * Writes the write_Actuate command with a 0 argument.
	 */
	void cancelStimulus(void);

	/* Function: sendActuatorPosition
	 * ------------------------------
	 * Writes the write_ActuatorManual command along with the position to move
	 * the actuator to.
	 */
	void sendActuatorPosition(double position);

	/* Function: sendWaveTable
	 * -----------------------
	 * Writes the write_ActuatorWaveTable command along with the waveTable in the
	 * message data.
	 */
	void sendWaveTable(double *waveTable, int arrSize);

	/* Function: sendWaveInterval
	 * --------------------------
	 * Writes the write_WaveTableInterval command along with the time interval in
	 * microseconds between data points in the wave table. Possible values
	 * are 100, 1000, 10000, 100000, 1000000.
	 */
	void sendWaveInterval(int deltaT);
	
	/* Function: sendAcquisitionInterval
	 * -----------------------
	 * Select the interval (int) between each acquired point in us. Maximum is 100 (10 kHz)
	 */
	void sendAcquisitionInterval(int deltaAcqusitionT);

	/* Function: sendPIDParameters
	 * ---------------------------
	 * Writes the array of PID parameters: update the PID gains with an array of double (Pgain,Intgain,Derivgain,Anti-Windup)
	 */
	void sendPIDParameters(double *PIDParameters, int arrSize);

	/* Function: sendTriggerMode
	 * -------------------------
	 * Select the trigger mode with an int (0:manual mode/no trigger, 1: wave table/1 trigger per table, 2: wave table/1 trigger per point)
	 */
	void sendTriggerMode(int triggerMode);

	/* Function: write_ClampMode
	 *
	 * select the clamp mode with an int (0: open loop, 1: displacement clamp, 2: force clamp)
	 */
	void sendClampMode(int clampMode);

	/* Function: getfpgaData
	 * --------------------------
	 * Get the data from the FPGA to be written to disk.
	 */
	void getfpgaData(int stimNum, vector<double> piezoSignalData, vector<double> actuatorPositionData, vector<double> actuatorCommandData, vector<double> desiredSignalData);

private:
	/* Function: OnConnect
	 * -------------------
	 * Overwrites the OnConnect from STMDispatch. Sets the connected flag to true.
	 */
	void OnConnect();

	/* Function: OnClose
	 * -----------------
	 * Overwrites the OnClose from STMDispatch. Sets the connected flag to false.
	 */
	void OnClose();

	/* Function: OnNewData
	 * -------------------
	 * Overwrites the OnNewData from STMDispatch. Receives commands from the
	 * force clamp and handles them appropriately.
	 */
	void OnNewData(CString MetaName, CByteArray *MsgData);

	/* Function: connect
	 * -----------------
	 * Connects to the force clamp via STM.
	 */
	void connect(CString ip, int port);

	/* Function: disconnect
	 * --------------------
	 * Disconnects to the force clamp via STM.
	 */
	void disconnect(void);
};