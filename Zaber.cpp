#include "StdAfx.h"
#include "Zaber.h"
#include "ImageControl.h"

#using <System.dll>

// Sets duration to wait for when polling for available bytes to read
#define SLEEP_DURATION_MS	         1
// Some Binary message command numbers
#define CMD_HOME	 	 	 	 	 1
#define CMD_LIMIT_ACTIVE	 	 	 9
#define CMD_MOVE_ABSOLUTE	 	 	 20
#define CMD_MOVE_RELATIVE			 21
#define CMD_UNEXPECTED_POS	 	 	 13
#define CMD_RETURN_CURRENT_POSITION	 60
#define CMD_ERROR	 	 	 	 	 255
#define CMD_RETURN_STATUS			 54

#define STAGE_RESOLUTION            0.15625e-6
#define ACTUATOR_RESOLUTION			0.047625e-6

using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;
using namespace System::Text;

using namespace cv;

Zaber::Zaber()
{
	// Set up serial port
	 port = gcnew SerialPort();
	 port->PortName = "COM6";
	 port->BaudRate = 9600;
	 port->DataBits = 8;
	 port->Parity = Parity::None;
	 port->StopBits = StopBits::One;
	 port->Handshake = Handshake::None;

	 moveUnit = MICROSTEP;
}

int Zaber::openPort(void)
{
	if (port->IsOpen) return -1;
	port->Open();
	return 0;
}

int Zaber::closePort(void)
{
	if(!port->IsOpen) return -1;
	port->Close();
	return 0;
}

Movement determineStageMovement(Point target, Point cantilever)
{
	Movement result;

	result.x = -((double)(cantilever.x - target.x))/(PIXELS_PER_UM * IMAGE_RESIZE_SCALE);
	result.y = ((double)(cantilever.y - target.y))/(PIXELS_PER_UM * IMAGE_RESIZE_SCALE);

	return result;
}

void Zaber::moveStage(Movement move)
{
	microstepsX = (unsigned int)convertToStageMicrosteps(move.x);
	microstepsY = (unsigned int)convertToStageMicrosteps(move.y);

	device = 1;
	command = CMD_MOVE_RELATIVE;
	data = microstepsX;
	sendCommand();

	device = 2;
	command = CMD_MOVE_RELATIVE;
	data = microstepsY;
	sendCommand();
}

void Zaber::moveActuator(double distance)
{
	microstepsZ = (unsigned int)convertToActuatorMicrosteps(distance);

	device = 3;
	command = CMD_MOVE_RELATIVE;
	data = microstepsZ;
	sendCommand();

	waitForReply(3, CMD_MOVE_RELATIVE);
}

void Zaber::moveActuatorToPosition(double position)
{
	device = 3;
	command = CMD_MOVE_ABSOLUTE;
	data = (unsigned int)convertToActuatorMicrosteps(position);
	sendCommand();
}

void Zaber::waitForStaticStage(void)
{
	while (true) { //wait for zaber to stabilize
		int zaberStatus = requestZaberStatus();
		if (zaberStatus == 0) break;
	}
}

int Zaber::requestZaberStatus(void)
{
	device = 1;
	command = CMD_RETURN_STATUS;
	data = 0;
	sendCommand();
	waitForReply(1, CMD_RETURN_STATUS);
	if (data !=0) {
		return 1; //x-axis is moving
	}
	device = 2;
	command = CMD_RETURN_STATUS;
	data = 0;
	sendCommand();
	waitForReply(2, CMD_RETURN_STATUS);
	if (data != 0) {
		return 2; //y-axis is moving
	}
	return 0; //zaber is stable
}

Point2d Zaber::getStagePosition(void)
{
	Point2d position; //placeholder

	// Send command to request x position
	device = 1;
	command = CMD_RETURN_CURRENT_POSITION;
	data = 0;
	sendCommand();

	//Wait for device to reply with x position
	waitForReply(1, CMD_RETURN_CURRENT_POSITION);
	position.x = convertFromStageMicrosteps(data);

	//Send command to request y position.
	device = 2;
	command = CMD_RETURN_CURRENT_POSITION;
	data = 0;
	sendCommand();

	//Wait for device to reply with y position
	waitForReply(2, CMD_RETURN_CURRENT_POSITION);
	position.y = convertFromStageMicrosteps(data);

	return position;
}

void Zaber::receiveReply(void)
{
 while (port->BytesToRead < 6) {
 	 Thread::Sleep(SLEEP_DURATION_MS);
 }
 
 array<Byte>^ packet = gcnew array<Byte>(6);
 port->Read(packet, 0, 6);
 
 device = packet[0];
 command = packet[1];
 data = packet[2] + (packet[3] << 8) + (packet[4] << 16) + (packet[5] << 24);
}

void Zaber::waitForReply(Byte expectDevice, Byte expectCommand)
{
	do {
		receiveReply();
	} while ( ! (device == expectDevice
 	 	 	 && (command == expectCommand
 	 	 	 	 || command == CMD_HOME	 	 	 	 // Auto-home routine has been triggered
 	 	 	 	 || command == CMD_LIMIT_ACTIVE	 	 // Device has reached its travel limit
 	 	 	 	 || command == CMD_UNEXPECTED_POS	 // Device has recently stalled or displaced
 	 	 	 	 || command == CMD_ERROR) ) );	 	 // Device is sending an error reply
}

void Zaber::waitForReplyEitherDevice(Byte expectDevice1, Byte expectCommand1, Byte expectDevice2, Byte expectCommand2)
{
	do {
		receiveReply();
	} while ( !( (device == expectDevice1)  
			&& (command == expectCommand1            // Reply matches device and command 1
                 || command == CMD_HOME              // Auto-home routinehas been triggered
                 || command == CMD_LIMIT_ACTIVE      // Device has reached its travel limit
                 || command == CMD_UNEXPECTED_POS    // Device has recently stalled or displaced
                 || command == CMD_ERROR))           // Device is sending an error reply
          || (device == expectDevice2                // OR reply matches device and command 2
			&& (command == expectCommand2
                 || command == CMD_HOME              // Auto-home routine has been triggered
                 || command == CMD_LIMIT_ACTIVE      // Device has reached its travel limit
                 || command == CMD_UNEXPECTED_POS    // Device has recently stalled or displaced
                 || command == CMD_ERROR)) );        // Device is sending an error reply
}

int Zaber::convertToStageMicrosteps(double distanceInMoveUnit)
{
	int result;

	if (moveUnit == CENTIMETER) {
		result = (int)(distanceInMoveUnit * (1e-2) / STAGE_RESOLUTION);
	} else if (moveUnit == MILLIMETER) {
		result = (int)(distanceInMoveUnit * (1e-3) / STAGE_RESOLUTION);
	} else if (moveUnit == MICROMETER) {
		result = (int)(distanceInMoveUnit * (1e-6) / STAGE_RESOLUTION);
	} else if (moveUnit == MICROSTEP) {
		result = (int)(distanceInMoveUnit);
	}

	return result;
}

double Zaber::convertFromStageMicrosteps(int distanceInMicroSteps)
{
	double result;

	if (moveUnit == CENTIMETER) {
		result = (double)distanceInMicroSteps * (1e2) * STAGE_RESOLUTION;
	} else if (moveUnit == MILLIMETER) {
		result = (double)distanceInMicroSteps * (1e3) * STAGE_RESOLUTION;
	} else if (moveUnit == MICROMETER) {
		result = (double)distanceInMicroSteps * (1e6) * STAGE_RESOLUTION;
	} else if (moveUnit == MICROSTEP) {
		result = (double)distanceInMicroSteps;
	}

	return result;
}

int Zaber::convertToActuatorMicrosteps(double distanceInMoveUnit)
{
	int result;

	if (moveUnit == CENTIMETER) {
		result = (int)(distanceInMoveUnit * (1e-2) / ACTUATOR_RESOLUTION);
	} else if (moveUnit == MILLIMETER) {
		result = (int)(distanceInMoveUnit * (1e-3) / ACTUATOR_RESOLUTION);
	} else if (moveUnit == MICROMETER) {
		result = (int)(distanceInMoveUnit * (1e-6) / ACTUATOR_RESOLUTION);
	} else if (moveUnit == MICROSTEP) {
		result = (int)(distanceInMoveUnit);
	}

	return result;
}

double Zaber::convertFromActuatorMicrosteps(int distanceInMicroSteps)
{
	double result;

	if (moveUnit == CENTIMETER) {
		result = (double)distanceInMicroSteps * (1e2) * ACTUATOR_RESOLUTION;
	} else if (moveUnit == MILLIMETER) {
		result = (double)distanceInMicroSteps * (1e3) * ACTUATOR_RESOLUTION;
	} else if (moveUnit == MICROMETER) {
		result = (double)distanceInMicroSteps * (1e6) * ACTUATOR_RESOLUTION;
	} else if (moveUnit == MICROSTEP) {
		result = (double)distanceInMicroSteps;
	}

	return result;
}

void Zaber::sendCommand(void)
{
	array<Byte>^ packet = gcnew array<Byte>(6);
 
	packet[0] = device;
	packet[1] = command;
 
	packet[2] = data & 0xFF;
	packet[3] = (data >> 8) & 0xFF;
	packet[4] = (data >> 16) & 0xFF;
	packet[5] = (data >> 24) & 0xFF;
 
	port->Write(packet, 0, 6);
}