#include "StdAfx.h"
#include "ImageControl.h"

#include <opencv2/highgui/highgui.hpp>

using namespace _DSHOWLIB_NAMESPACE;
using namespace cv;
using namespace std;

#define DEVICE_SERIAL 0x30210107

void showImage(cv::Mat image)
{
	namedWindow("Display window", CV_WINDOW_AUTOSIZE);
	imshow("Display window", image);
	cvWaitKey(3);
}

int ImageController::setUpCamera(HWND hwnd)
{
	int result = startCamera();

	if (result == 0) {
		startLive(hwnd);
	}

	return result;
}

void ImageController::closeCamera(void)
{
	stopLive();
}

int ImageController::startCamera(void)
{
	InitLibrary();
	
	sink = FrameHandlerSink::create(DShowLib::eY800, 5);
	sink->setSnapMode(true);

	grabber.setSinkType(sink);
	// Show the device selection dialog
	if (grabber.openDev(DEVICE_SERIAL)) {
		autoExposeOff();
		grabber.getOverlay()->setEnable(true);
		grabber.getOverlay()->setColorMode(OverlayBitmap::eCOLOR);
		grabber.getOverlay()->setDropOutColor(RGB(0,255,255));
	} else return CAMERA_DEVICE_SELECTION_ERROR;

	return 0;
}

void ImageController::startLive(HWND hwnd)
{
	 if (grabber.isDevValid()) {
		grabber.setHWND(hwnd);
		grabber.setDefaultWindowPosition(false);
        grabber.setWindowSize((int)(IMAGE_X_PIXELS * SCREEN_RESIZE_SCALE), (int)(IMAGE_Y_PIXELS * SCREEN_RESIZE_SCALE));
		
		grabber.startLive(true);
		FrameTypeInfo info;
		sink->getOutputFrameType(info);

		image = cvCreateImage(cvSize(info.dim.cx, info.dim.cy), IPL_DEPTH_8U, 1);
		grabber.setExternalTrigger(true);
	 }
}

Mat ImageController::getImage(void)
{
	if (grabber.isDevValid()) {
		// Snap an image and save in memory.
		sink->snapImages(1);
            
		if (grabber.getLastError().isError()) {
			printf("Failed to snap an image");
		} else {
			image.data = (uchar*)sink->getLastAcqMemBuffer()->getPtr();				
		}
	}

	return image;
}

void ImageController::overlayCircle(Point center, int radius)
{
	center.x = (int)(center.x/IMAGE_RESIZE_SCALE);
	center.y = (int)(center.y/IMAGE_RESIZE_SCALE);
	RECT bound;
	bound.left = center.x - radius;
	bound.right = center.x + radius;
	bound.top = center.y - radius;
	bound.bottom = center.y + radius;
	grabber.getOverlay()->drawFrameEllipse(RGB(0,255,0), bound);
}

void ImageController::clearOverlay(void)
{
	grabber.getOverlay()->fill(grabber.getOverlay()->getDropOutColor());
}

void ImageController::stopLive(void)
{
	// Stop the live video
	if (grabber.isLive()) {
		grabber.stopLive();
		ExitLibrary(); // Tidy up memory.
	}
}

void ImageController::autoExposeOn(void)
{
	grabber.setProperty(CameraControl_Exposure, true);
}

void ImageController::autoExposeOff(void)
{
	long val = grabber.getProperty(CameraControl_Exposure);
	tsPropertyRange ExposureRange = grabber.getPropertyRange(CameraControl_Exposure);
	grabber.setProperty(CameraControl_Exposure, false);
	long ExposureValue = -8;
	grabber.setProperty(CameraControl_Exposure,ExposureValue);
}