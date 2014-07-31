#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#define MICROSTEP  0
#define MICROMETER 1
#define MILLIMETER 2
#define CENTIMETER 3

struct Movement {
	double x;
	double y;
};

public ref class Zaber {
//properties
public:
	int moveUnit;
private:
	System::IO::Ports::SerialPort ^port;
	System::Byte device; // 1 = x-axis, 2 = y-axis
	System::Byte command; // command to be sent to device (i.e. move absolute)
	int data; // data associated with the comment.
	unsigned int microstepsX;
	unsigned int microstepsY;
	unsigned int microstepsZ;
	
//prototypes
public:
	Zaber();
	int openPort(void);
	int closePort(void);
	void waitForStaticStage(void);
	void moveStage(Movement move);
	void moveActuator(double distance);
	void moveActuatorToPosition(double position);
	cv::Point2d getStagePosition(void);
private:
	int requestZaberStatus(void);
	void sendCommand(void);
	void receiveReply(void);
	void waitForReply(System::Byte expectDevice, System::Byte expectCommand);
	void waitForReplyEitherDevice(System::Byte expectDevice1, System::Byte expectCommand1, System::Byte expectDevice2, System::Byte expectCommand2);
	int convertToStageMicrosteps(double distanceInMoveUnit);
	double convertFromStageMicrosteps(int distanceInMicroSteps);
	int convertToActuatorMicrosteps(double distanceInMoveUnit);
	double convertFromActuatorMicrosteps(int distanceInMicroSteps);
};

Movement determineStageMovement(cv::Point target, cv::Point cantilever);