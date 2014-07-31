#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include "tisudshl.h" 

#define CAMERA_DEVICE_SELECTION_ERROR -1

#define IMAGE_RESIZE_SCALE 0.50
#define IMAGE_X_PIXELS 1024
#define IMAGE_Y_PIXELS 768
#define PIXELS_PER_UM 0.567369167

class ImageController {
//properties
private:
	cv::Mat image; //placeholder
	_DSHOWLIB_NAMESPACE::Grabber grabber;
	_DSHOWLIB_NAMESPACE::FrameHandlerSink::tFHSPtr sink;

//prototypes
public:
	int setUpCamera(HWND hwnd);
	void closeCamera(void);
	cv::Mat getImage(void);
private:
	int startCamera(void);
	void startLive(HWND hwnd);
	void stopLive(void);
};

void showImage(cv::Mat image);