#pragma once

// This file provides a number of useful conversion functions that are generally required to use STM.
// Note that not all possible data types are implemented.  If you need a data type that isn't available,
// use the provided functions as a guide and the help topic/URL provided below for the data format.

/*---------------------------------------------------------------------------*/
/* Flatten/Unflatten Functions                                               */
/*---------------------------------------------------------------------------*/
/*  Flattening and unflattening is the process of taking generic data 
	(i.e. interger, booleans, arrays) and repectivly encoding/decoding to a 
	string so that it can be sent through TCP.  These functions are based on 
	their LabVIEW counterpart.  The LabVIEW STM VIs Flatten data in Big-Endian
	format by default.

	For more information on the format of flattened data, view the Flattned Data
	topic in the LabVIEW Help or at the following URL (LV 8.6):
	http://zone.ni.com/reference/en-XX/help/371361E-01/lvconcepts/flattened_data/
*/

// Clusters are often unflattened to structures.
// This struct corresponds to the example of unflattening a cluster below.
struct TargetStatus
{
	BOOL AnalogError;
	BOOL DigitalError;
	BOOL RTTO;
	BOOL DMATO;
};

	// Flatten Functions
	int intFlatten(int *intpntr, char *charpntr);
	int uintFlatten(unsigned int * uintpntr, char *charpntr);
	int shortFlatten(short * shortpntr, char *charpntr);
	int ushortFlatten(unsigned short *ushortpntr, char *charpntr);
	int dblFlatten(double *dblpntr, char *charpntr);

	// Unflatten Functions
	int intUnflatten(char * charpntr);
	unsigned int uintUnflatten(char * charpntr);
	short shortUnflatten(char * charpntr);
	unsigned short ushortUnflatten(char * charpntr);
	double dblUnflatten(char * charpntr);
	float sglUnflatten(char * charpntr);
	char* stringUnflatten(char * charpntr);

	// Array Flatten Functions
	// charpntr must have a memory block of size (sizeof(int) * arrsize + sizeof(int))
	int intArrFlatten(int *intpntr, char *charpntr, int arrsize);
	// charpntr must have a memory block of size (sizeof(unsigned int) * arrsize + sizeof(int))
	int uintArrFlatten(unsigned int * uintpntr, char *charpntr, int arrsize);
	// charpntr must have a memory block of size (sizeof(short) * arrsize + sizeof(int))
	int shortArrFlatten(short * shortpntr, char *charpntr, int arrsize);
	// charpntr must have a memory block of size (sizeof(unsigned short) * arrsize + sizeof(int))
	int ushortArrFlatten(unsigned short *ushortpntr, char *charpntr, int arrsize);
	// charpntr must have a memory block of size (sizeof(double) * arrsize + sizeof(int))
	int dblArrFlatten(double *dblpntr, char *charpntr, int arrsize);


	// Array Un-Flatten Functions
	// With any of these functions you must free the returned pointer when done
	int * intArrUnflatten(char * charpntr, int* arrsize);
	unsigned int * uintArrUnflatten(char * charpntr, int* arrsize);
	short * shortArrUnflatten(char * charpntr, int* arrsize);
	unsigned short * ushortArrUnflatten(char * charpntr, int* arrsize);
	double * dblArrUnflatten(char * charpntr, int* arrsize);
	float * sglArrUnflatten(char * charpntr, int* arrsize);

	// 2D Array Un-Flatten Functions
	// With any of these functions you must free xsize arrays under the returned pointer and then free the pointer
	double ** dbl2dArrUnflatten(char * charpntr, int* xsize, int* ysize);
	float ** sgl2dArrUnflatten(char * charpntr, int* xsize, int* ysize);

	// Cluster Un-Flatten Functions
	// This is an example of a cluster unflatten, you must create a function for each cluster you want
	// to handle.
	struct TargetStatus statusUnflatten(char* charpntr);