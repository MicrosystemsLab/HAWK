/* Zaber.h
 * -------
 * Header file for the Zaber class. This object controls the HAWK stage and
 * z actuator. The header file also contains the Movement structure definition
 * and function to determine the Movement necessary between two points,
 * presumably the target and cantilever.
 *
 * Created by John Whitworth on 8/26/14.
 */

#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#define MICROSTEP  0
#define MICROMETER 1
#define MILLIMETER 2
#define CENTIMETER 3

/* Structure: Movement
 * -------------------
 * Made up of two doubles, each corresponding to a movement
 * in one axis of the xy plane.
 */
struct Movement {
	double x;
	double y;
};

/* Class: Zaber
 * ------------
 * This object controls communication betwwen the HAWK and the Zaber
 * controller. That includes movement in the x, y, and z directions.
 */
public ref class Zaber {
//properties
public:
	//(#defines above) are possible values for this property
	int moveUnit;
	// holds the value for the home, hover, and scan positions of the acutator zaber.
	double homePosition;
	double hoverPosition;
	double scanPosition;
private:
	//port to communicate with Zaber Controller
	System::IO::Ports::SerialPort ^port;
	//device = 1 (x-axis), 2 (y-axis), 3 (z-axis)
	System::Byte device;
	//command to be sent to device (i.e. move absolute)
	System::Byte command;
	//data associated with the comment.
	int data;
	//placeholders for data in microsteps
	unsigned int microstepsX;
	unsigned int microstepsY;
	unsigned int microstepsZ;
	
//prototypes
public:
	/* Function: Zaber
	 * ---------------
	 * Constructor for a Zaber object. Sets up the port and initial moveUnit.
	 */
	Zaber();

	/* Function: openPort
	 * ------------------
	 * If the port is not open, it is opened. Returns 0 if the port was opened, 
	 * returns -1 if the port failed to open.
	 */
	int openPort(void);

	/* Function: closePort
	 * -------------------
	 * If the port is not closed, it is closed. Returns 0 if the port was closed, 
	 * returns -1 if the port failed to close.
	 */
	int closePort(void);

	/* Function: waitForStaticStage
	 * ----------------------------
	 * A while loop keeps going until the stage is not moving
	 */
	void waitForStaticStage(void);

	/* Function: moveStage
	 * -------------------
	 * Takes a Movement as a parameter and directs the stage to move by that much.
	 */
	void moveStage(Movement move);

	/* Function: moveActuator
	 * ----------------------
	 * Takes a double as a parameter and directs the z actuator to move by that much.
	 * Waits for the movement to complete.
	 */
	void moveActuator(double distance);

	/* Function: moveActuatorToPosition
	 * --------------------------------
	 * Takes a double as a parameter and directs the z actuator to move to that
	 * location. Waits for the movement to complete.
	 */
	void moveActuatorToPosition(double position);

	/* Function: moveActuatorHome
	 * --------------------------
	 * Directs the z actuator to move to position 0. This does not wait for the
	 * movement to complete.
	 */
	void moveActuatorHome(void);

	/* Function: getStagePosition
	 * --------------------------
	 * Returns a CV Point_ of two doubles corresponding to the current stage
	 * position in microns.
	 */
	cv::Point2d getStagePosition(void);

	/*Function: get ActuatorPosition
	 * --------------------------
	 * Returns the current position of the zaber holding the actuator
	 */
	double getActuatorPosition(void);

private:

	/* Function: requestZaberStatus
	 * ----------------------------
	 * Calls for and returns the current status of the zaber stage.
	 */
	int requestZaberStatus(void);
	
	/* Function: sendCommand
	 * ---------------------
	 * Transmits whatever command is in the Zaber properties to the
	 * Zaber controller.
	 */
	void sendCommand(void);

	/* Function: sendCommand
	 * ---------------------
	 * Receives whatever command is being sent from the Zaber controller
	 * and stores its information in the properties.
	 */
	void receiveReply(void);

	/* Function: waitForReply
	 * ----------------------
	 * Enters a while loop until a message is received regarding a certain
	 * device and command.
	 */
	void waitForReply(System::Byte expectDevice, System::Byte expectCommand);

	/* Function: waitForReplyEitherDevice
	 * ----------------------------------
	 * Enters a while loop until a message is received regarding either of the 
	 * specified device, command combinations.
	 */
	void waitForReplyEitherDevice(System::Byte expectDevice1, System::Byte expectCommand1, System::Byte expectDevice2, System::Byte expectCommand2);
	
	/* Function: convertToStageMicrosteps
	 * ----------------------------------
	 * Returns the stage microstep value for the double parameter it takes,
	 * assumes that that parameter is in the current MoveUnit
	 */
	int convertToStageMicrosteps(double distanceInMoveUnit);

	/* Function: convertFromStageMicrosteps
	 * ------------------------------------
	 * Returns the move unit value of the stage microstep value given in the parameter.
	 */
	double convertFromStageMicrosteps(int distanceInMicroSteps);

	/* Function: convertToActuatorMicrosteps
	 * -------------------------------------
	 * Returns the z actuator microstep value for the double parameter it takes,
	 * assumes that that parameter is in the current MoveUnit
	 */
	int convertToActuatorMicrosteps(double distanceInMoveUnit);

	/* Function: convertFromStageMicrosteps
	 * ------------------------------------
	 * Returns the move unit value of the z actuator microstep value given in
	 * the parameter.
	 */
	double convertFromActuatorMicrosteps(int distanceInMicroSteps);
};

/* Function: determineStageMovement
 * --------------------------------
 * Takes two opencv Points corresponding to the target and the cantilever and
 * returns the Movement necessary between those points.
 */
Movement determineStageMovement(cv::Point target, cv::Point cantilever);