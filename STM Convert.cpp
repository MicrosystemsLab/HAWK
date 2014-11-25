#include "StdAfx.h"
#include "STM Convert.h"

////////////////////////////////////////////////////////
// Conversion Functions
////////////////////////////////////////////////////////

// Flattens an int so that it can be read back in LabVIEW
int intFlatten(int *intpntr, char *charpntr)
{
	int x;
	char *temppntr;
	
	temppntr=(char *)intpntr;
	for(x=sizeof(int)-1;x>=0;x--)
	{
		charpntr[(sizeof(int)-1)-x]=*(temppntr+x);
	}
	return 0;
}

// Flattens an unsigned short so that it can be read back in LabVIEW
int ushortFlatten(unsigned short *ushortpntr, char *charpntr)
{
	int x;
	char *temppntr;
	
	temppntr=(char *)ushortpntr;
	for(x=sizeof(unsigned short)-1;x>=0;x--)
	{
		charpntr[(sizeof(unsigned short)-1)-x]=*(temppntr+x);
	}
	return 0;
}

// Flattens a double so that it can be read back in LabVIEW
int dblFlatten(double *dblpntr, char *charpntr)
{
	int x;
	char *temppntr;
	
	temppntr=(char *)dblpntr;
	for(x=sizeof(double)-1;x>=0;x--)
	{
		charpntr[(sizeof(double)-1)-x]=*(temppntr+x);
	}
	return 0;
}

//Flattens a short so that it can be read back in LabVIEW
int shortFlatten(short * shortpntr, char *charpntr)
{
	int x;
	char *temppntr;
	
	temppntr=(char *)shortpntr;
	for(x=sizeof(short)-1;x>=0;x--)
	{
		charpntr[(sizeof(short)-1)-x]=*(temppntr+x);
	}
	return 0;
}

//Flattens a short so that it can be read back in LabVIEW
int uintFlatten(unsigned int * uintpntr, char *charpntr)
{
	int x;
	char *temppntr;
	
	temppntr=(char *)uintpntr;
	for(x=sizeof(unsigned int)-1;x>=0;x--)
	{
		charpntr[(sizeof(unsigned int)-1)-x]=*(temppntr+x);
	}
	return 0;
}

//Unflattens an int.  Typically sent from LabVIEW
int intUnflatten(char * charpntr)
{
 	int data = 0;
	int x;
	char reverse[4]={'\0','\0','\0','\0'};
	
	for(x=0;x<(sizeof(reverse));x++)
		reverse[x]=*(charpntr+((sizeof(reverse)-1)-x));
	
	data=*(int *)reverse;
	return data;
}

// Unflattens an unsigned short typically sent from LabVIEW
unsigned short ushortUnflatten(char * charpntr)
{
 	unsigned short data = 0;
	int x;
	char reverse[2]={'\0','\0'};
	
	for(x=0;x<(sizeof(reverse));x++)
		reverse[x]=*(charpntr+((sizeof(reverse)-1)-x));
	
	data=*(unsigned short *)reverse;
	return data;
}

// Unflattens an unsigned int typically sent from LabVIEW
double dblUnflatten(char * charpntr)
{
 	double data = 0;
	int x;
	char reverse[8]={'\0','\0','\0','\0','\0','\0','\0','\0'};
	
	for(x=0;x<(sizeof(reverse));x++)
		reverse[x]=*(charpntr+((sizeof(reverse)-1)-x));
	
	data=*(double *)reverse;
	return data;
}

// Unflattens a single (float) typically sent from LabVIEW
float sglUnflatten(char * charpntr)
{
 	float data = 0;
	int x;
	char reverse[4]={'\0','\0','\0','\0'};
	
	for(x=0;x<(sizeof(reverse));x++)
		reverse[x]=*(charpntr+((sizeof(reverse)-1)-x));
	
	data=*(float *)reverse;
	return data;
}

// Unflattens a short typically sent from LabVIEW
short shortUnflatten(char * charpntr)
{
 	short data = 0;
	int x;
	char reverse[2]={'\0','\0'};
	
	for(x=0;x<(sizeof(reverse));x++)
		reverse[x]=*(charpntr+((sizeof(reverse)-1)-x));
	
	data=*(short *)reverse;
	return data;
}

// Unflattens an unsigned int typically sent from LabVIEW
unsigned int uintUnflatten(char * charpntr)
{
 	unsigned int data = 0;
	int x;
	char reverse[4]={'\0','\0','\0','\0'};
	
	for(x=0;x<(sizeof(reverse));x++)
		reverse[x]=*(charpntr+((sizeof(reverse)-1)-x));
	
	data=*(unsigned int *)reverse;
	return data;
}

///////////////////////////////////////////////////
// Array Flatten Functions
///////////////////////////////////////////////////

// charpntr must have a memory block of size (sizeof(int) * arrsize + sizeof(int))
int intArrFlatten(int *intpntr, char *charpntr, int arrsize)
{
	// Flattens an int array so that it can be read back in LabVIEW
	int x;
	
	// Array size is always an int
	intFlatten(&arrsize, charpntr);
	
	for (x = 0; x < arrsize; x++)
	{
		intFlatten((intpntr + x), (char *)(charpntr + (sizeof(int) * (x+1))));
	}
	return 0;
}

// charpntr must have a memory block of size (sizeof(unsigned short) * arrsize + sizeof(int))
int ushortArrFlatten(unsigned short *ushortpntr, char *charpntr, int arrsize)
{
	// Flattens an unsigned short array so that it can be read back in LabVIEW
	int x;
	
	// Array size is always an int
	intFlatten(&arrsize, charpntr);
	
	for (x = 0; x < arrsize; x++)
	{
		ushortFlatten((ushortpntr + x), (char *)(charpntr + (sizeof(unsigned short) * (x+1))));
	}
	return 0;
}

// charpntr must have a memory block of stringobj.GetLength()+4 bytes
int cStringFlatten(CString stringobj, char *charpntr)
{
	int size = stringobj.GetLength();
	intFlatten(&size, charpntr);
	memcpy(charpntr+4, stringobj.GetBuffer(), size);
	return 0;
}

// charpntr must have a memory block of size (sizeof(double) * arrsize + sizeof(int))
int dblArrFlatten(double *dblpntr, char *charpntr, int arrsize)
{
	// Flattens a double array so that it can be read back in LabVIEW
	int x;
	
	// Array size is always an int
	intFlatten(&arrsize, charpntr);
	
	for (x = 0; x < arrsize; x++)
	{
		dblFlatten((dblpntr + x), (char *)(sizeof(int) + charpntr + (sizeof(double) * x)));
	}
	return 0;
}

// charpntr must have a memory block of size (sizeof(short) * arrsize + sizeof(int))
int shortArrFlatten(short * shortpntr, char *charpntr, int arrsize)
{
	// Flattens a short array so that it can be read back in LabVIEW
	int x;
	
	// Array size is always an int
	intFlatten(&arrsize, charpntr);
	
	for (x = 0; x < arrsize; x++)
	{
		shortFlatten((shortpntr + x), (char *)(charpntr + (sizeof(short) * (x+1))));
	}
	return 0;
}

// charpntr must have a memory block of size (sizeof(unsigned int) * arrsize + sizeof(int))
int uintArrFlatten(unsigned int * uintpntr, char *charpntr, int arrsize)
{
	// Flattens an unsigned int array so that it can be read back in LabVIEW
	int x;
	
	// Array size is always an int
	intFlatten(&arrsize, charpntr);
	
	for (x = 0; x < arrsize; x++)
	{
		uintFlatten((uintpntr + x), (char *)(charpntr + (sizeof(unsigned int) * (x+1))));
	}
	return 0;
}


///////////////////////////////////////////////////
// Array Un-Flatten Functions
///////////////////////////////////////////////////

// You must free the returned pointer when you are finished with it.
int * intArrUnflatten(char * charpntr, int* arrsize)
{
 	int x;
	int * data;
	
	*arrsize = intUnflatten(charpntr);
	
	data = new int[*arrsize];
	
	for (x = 0; x < *arrsize; x++)
	{
		data[x] = intUnflatten(sizeof(int) + charpntr + (sizeof(int) * x));
	}
		 
	return data;
}

// You must free the returned pointer when you are finished with it.
unsigned int * uintArrUnflatten(char * charpntr, int* arrsize)
{
 	int x;
	unsigned int * data;
	
	*arrsize = uintUnflatten(charpntr);
	
	data = new unsigned int[*arrsize];
	
	for (x = 0; x < *arrsize; x++)
	{
		data[x] = uintUnflatten(sizeof(int) + charpntr + (sizeof(unsigned int) * x));
	}
		 
	return data;
}

// You must free the returned pointer when you are finished with it.
short * shortArrUnflatten(char * charpntr, int* arrsize)
{
 	int x;
	short * data;
	
	*arrsize = intUnflatten(charpntr);
	
	data = new short[*arrsize];
	
	for (x = 0; x < *arrsize; x++)
	{
		data[x] = ushortUnflatten(sizeof(int) + charpntr + (sizeof(short) * x));
	}
		 
	return data;
}

// You must free the returned pointer when you are finished with it.
unsigned short * ushortArrUnflatten(char * charpntr, int* arrsize)
{
 	int x;
	unsigned short * data;
	
	*arrsize = intUnflatten(charpntr);
	
	data = new unsigned short[*arrsize];
	
	for (x = 0; x < *arrsize; x++)
	{
		data[x] = ushortUnflatten(sizeof(int) + charpntr + (sizeof(unsigned short) * x));
	}
		 
	return data;
}

// You must free the returned pointer when you are finished with it.
double * dblArrUnflatten(char * charpntr, int* arrsize)
{
 	int x;
	double * data;
	
	*arrsize = intUnflatten(charpntr);
	
	data = new double[*arrsize];
	
	for (x = 0; x < *arrsize; x++)
	{
		data[x] = dblUnflatten(sizeof(int) + charpntr + (sizeof(double) * x));
	}
		 
	return data;
}

// You must free the returned pointer when you are finished with it.
float * sglArrUnflatten(char * charpntr, int* arrsize)
{
 	int x;
	float * data;
	
	*arrsize = intUnflatten(charpntr);
	
	data = new float[*arrsize];
	
	for (x = 0; x < *arrsize; x++)
	{
		data[x] = (float)dblUnflatten(sizeof(int) + charpntr + (sizeof(float) * x));
	}
		 
	return data;
}

// You must free xsize arrays pointed to by the returned pointer and then free the returned pointer
// when you are finished with it.
double ** dbl2dArrUnflatten(char * charpntr, int* xsize, int* ysize)
{
	int x, y;
	double **data;
	
	*xsize = uintUnflatten (charpntr);
	*ysize = uintUnflatten (charpntr+sizeof(unsigned int));
	data = new double*[*xsize];
	for (x = 0; x < *xsize; x++)
	{
		data[x] = new double[*ysize];
		for(y = 0; y < *ysize; y++)
		{
			data[x][y] = dblUnflatten(sizeof(unsigned int)*2 + charpntr + (sizeof(double)* ((x*(*ysize))+y)));
		}
	}
	return data;
}

// You must free xsize arrays pointed to by the returned pointer and then free the returned pointer
// when you are finished with it.
float ** sgl2dArrUnflatten(char * charpntr, int* xsize, int* ysize)
{
	int x, y;
	float **data;
	float tmpflt;
	CString tempstr;
	
	*xsize = uintUnflatten (charpntr);
	*ysize = uintUnflatten (charpntr+sizeof(unsigned int));
	data = new float*[*xsize];
	for (x = 0; x < *xsize; x++)
	{
		data[x] = new float[*ysize];
		for(y = 0; y < *ysize; y++)
		{
			tmpflt = sglUnflatten(sizeof(unsigned int) + sizeof(unsigned int) + charpntr + (sizeof(float)* ((x*(*ysize))+y)));
			//tempstr.Format("%f ", tmpflt);
			//OutputDebugString(tempstr);
			data[x][y] = tmpflt;
		}
	}
	return data;
}

// Example of unflattening a cluster
TargetStatus statusUnflatten(char* charpntr)
{
	struct TargetStatus temp;
	//Clusters are the concatenation of their elements, and bools are U8s.
	temp.AnalogError = charpntr[0];
	temp.DigitalError = charpntr[1];
	temp.RTTO = charpntr[2];
	temp.DMATO = charpntr[3];
	return temp;
}