/* ImageControl.h
 * --------------
 * Header file for the ImageController class. This object manages the camera.
 *
 * Created by John Whitworth on 8/26/14.
 */

#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include "tisudshl.h" 

#define CAMERA_DEVICE_SELECTION_ERROR -1

#define IMAGE_RESIZE_SCALE 0.50
#define SCREEN_RESIZE_SCALE 0.75

#define IMAGE_X_PIXELS 1024
#define IMAGE_Y_PIXELS 768
#define PIXELS_PER_UM 0.567369167

/* Class: ImageController
 * ----------------------
 * ImageController object manages the camera through a grabber
 */
class ImageController {
//properties
private:
	//placeholder for last image
	cv::Mat image;
	//grabber controls getting and updating images from the camera
	_DSHOWLIB_NAMESPACE::Grabber grabber;
	//stores images from the camera
	_DSHOWLIB_NAMESPACE::FrameHandlerSink::tFHSPtr sink;

//prototypes
public:
	/* Function: setUpCamera
	 * ---------------------
	 * Starts the camera and starts the live feed from the camera.
	 */
	int setUpCamera(HWND hwnd);

	/* Function: closeCamera
	 * ---------------------
	 * Stops the live feed from the camera.
	 */
	void closeCamera(void);

	/* Function: getImage
	 * ------------------
	 * Snaps and returns an image.
	 */
	cv::Mat getImage(void);

	/* Function: overlayCircle
	 * -----------------------
	 * Puts a circular overlay at the given point and radius
	 * using the grabber overlay capabilities.
	 */
	void overlayCircle(cv::Point center, int radius);

	/* Function: clearOverlay
	 * ----------------------
	 * Clears any overlays on the image using the grabber
	 * overlay capabilities.
	 */
	void clearOverlay(void);

	/* Function: autoExposeOn
	 * ----------------------
	 * Sets the camera exposure to automatic.
	 */
	void autoExposeOn(void);

	/* Function: autoExposeOn
	 * ----------------------
	 * Sets the camera exposure to a default value.
	 */
	void autoExposeOff(void);

private:
	/* Function: startCamera
	 * ----------------------
	 * Intitializes and sets thte snap mode and enables overlays
	 * for the grabber.
	 */
	int startCamera(void);
	
	/* Function: startLive
	 * -------------------
	 * Starts the live feed from the camera to the giver handler.
	 */
	void startLive(HWND hwnd);

	/* Function: stopLive
	 * ------------------
	 * Stops the live feed and cleans up any memory in use.
	 */
	void stopLive(void);
};

/* Function: showImage
 * -------------------
 * Displays the given image in a seperate dialog.
 */
void showImage(cv::Mat image);