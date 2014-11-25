#include "StdAfx.h"
#include "STM_Communicator.h"

using namespace System;
using namespace System::Runtime::InteropServices;


#pragma region Write Functions

void STM_Communicator::triggerStimulus(void)
{
	if (connected) {
		messageReceivedCount = 0;
		piezoSignalData.clear();
		actuatorPositionData.clear();
		actuatorCommandData.clear();
		desiredSignalData.clear();

		stimulusStarted = true;
		
		CByteArray msgData;
		msgData.SetSize(sizeof(int));
		int one = 1;
		intFlatten(&one, (char*)msgData.GetData());
		CString command("write_Actuate");
		STM.SendMsg(command, &msgData);


	}
}

void STM_Communicator::cancelStimulus(void)
{
	if (connected) {
		CByteArray msgData;
		msgData.SetSize(sizeof(int));
		int zero = 0;
		intFlatten(&zero, (char*)msgData.GetData());
		CString command("write_Actuate");
		STM.SendMsg(command, &msgData);
	}
}

void STM_Communicator::sendActuatorPosition(double position)
{
	if (connected) {
		CByteArray msgData;
		msgData.SetSize(sizeof(double));
		dblFlatten(&position, (char*)msgData.GetData());
		CString command("write_ActuatorManual");
		STM.SendMsg(command, &msgData);
	}
}

void STM_Communicator::sendWaveTable(double *waveTable, int arrSize)
{
	if (connected) {
		CByteArray msgData;
		msgData.SetSize(sizeof(double) * arrSize + sizeof(int));
		dblArrFlatten(waveTable, (char*)msgData.GetData(), arrSize);
		CString command("write_ActuatorWaveTable");
		STM.SendMsg(command, &msgData);
	}
}

void STM_Communicator::sendWaveInterval(int deltaT)
{
	if (connected) {
		CByteArray msgData;
		msgData.SetSize(sizeof(int));
		intFlatten(&deltaT, (char*)msgData.GetData());
		CString command("write_WaveTableInterval");
		STM.SendMsg(command, &msgData);
	}
}

void STM_Communicator::sendAcquisitionInterval(int deltaAcqusitionT)
{
	if (connected) {
		CByteArray msgData;
		msgData.SetSize(sizeof(int));
		intFlatten(&deltaAcqusitionT, (char*)msgData.GetData());
		CString command("write_AcquisitionInterval");
		STM.SendMsg(command, &msgData);
	}
}

void STM_Communicator::sendPIDParameters(double *PIDParameters, int arrSize)
{
	if (connected){
		CByteArray msgData;
		msgData.SetSize(sizeof(double) * arrSize + sizeof(int));
		dblArrFlatten(PIDParameters, (char*)msgData.GetData(), arrSize);
		CString command("write_PIDParameters");
		STM.SendMsg(command, &msgData);
	}
}

void STM_Communicator::sendTriggerMode(int triggerMode)
{
	if (connected){
		CByteArray msgData;
		msgData.SetSize(sizeof(int));
		intFlatten(&triggerMode, (char*)msgData.GetData());
		CString command("write_TriggerMode");
		STM.SendMsg(command, &msgData);
	}
}

void  STM_Communicator::sendClampMode(int clampMode)
{
	if (connected){
		CByteArray msgData;
		msgData.SetSize(sizeof(int));
		intFlatten(&clampMode, (char*)msgData.GetData());
		CString command("write_ClampMode");
		STM.SendMsg(command, &msgData);
	}
}


#pragma endregion

#pragma region Read Functions

/*read_Data: retrieve an array of double composed of four channels: Set Point (V), Actuation Command (V), Actuator Sensor (V), Piezoresistive Signal (V)

read_FPGAStatus: retrieve a boolean about the status of the actuator (actuating:true, idle: false)

*/
void STM_Communicator::OnNewData(CString MetaName, CByteArray *MsgData)
{
	if (MetaName == "read_Data") {
		double* channelData;
		int arrSize;
		channelData = dblArrUnflatten((char*)(MsgData->GetData()), &arrSize);
		messageReceivedCount++;

		for (int i = 0; i < arrSize; i += 4) {
			desiredSignalData.push_back(channelData[i + 0]); // channel 1
			actuatorCommandData.push_back(channelData[i + 1]); // channel 2 
			actuatorPositionData.push_back(channelData[i + 2]); // channel 3
			piezoSignalData.push_back(channelData[i + 3]); // channel 4
		}
	} else if(MetaName == "read_FPGAParameters"){
		double* parameterData;
		int arrSize;
		parameterData = dblArrUnflatten((char*)(MsgData->GetData()), &arrSize);
		int numParameters = 10;
		double oldActuatorMovingParameter;

		for (int i=0; i<arrSize/numParameters; i += numParameters)
		{
			P_Parameter = parameterData[i+0];
			I_Parameter = parameterData[i+1];
			D_Parameter = parameterData[i+2];
			clampModeParameter = parameterData[i+3];
			triggerModeParameter = parameterData[i+4];
			acquisitionFreqParameter = parameterData[i+5];
			actuatorFreqParameter = parameterData[i+ 6];
			fifoMemoryFullParameter = parameterData[i+7]; // should be false, if true, there is a problem with the FPGA, don't trust data
			oldActuatorMovingParameter = actuatorMovingParameter;
			actuatorMovingParameter = parameterData[i+8]; // true if actuator is moving.
			waveTablePresentParameter = parameterData[i+9];
		}

		if(stimulusStarted == true & actuatorMovingParameter == 0 & oldActuatorMovingParameter == 1)
		{
			stimulusCompleted = true;
		}

	}

	STMDispatch::OnNewData(MetaName, MsgData);
}

#pragma endregion

#pragma region Initialization and Open/Close Functions

STM_Communicator::STM_Communicator()
{
	STM.SetDispatch(this);
	connected = false;
	stimulusStarted = false;
	stimulusCompleted = false;
	CString ip("171.64.164.81");
	int port = 55555;
	connect(ip, port);
}

STM_Communicator::~STM_Communicator()
{
	disconnect();
}

void STM_Communicator::connect(CString ip, int port)
{
	if (!connected) {
		int error=STM.Connect(ip, port);
	} else {
		//already connected
	}
}

void STM_Communicator::OnConnect()
{
	connected = true;
	STMDispatch::OnConnect();
}

void STM_Communicator::disconnect(void)
{
	if (connected) {
		int error = STM.Disconnect();
		connected = false;
	} else {
		//already disconnected
	}
}

void STM_Communicator::OnClose()
{
	connected = false;
	STMDispatch::OnClose();
}

#pragma endregion