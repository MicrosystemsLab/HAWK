/* Stimulus.h
 * ----------
 * Header file for the Stimulus class. The Stimulus object handles
 * the creation of a waveTable from a set of parameters.
 *
 * Created by John Whitworth on 8/26/14.
 * Copyright 2015 Eileen Mazzochette, et al <emazz86@stanford.edu>
 */

#pragma once

using namespace std;

#define DELTA_T 0.001 //one millisecond
#define ACTUATOR_SENSITIVITY 26.04  // um/V

class Stimulus {
//properties
public:
	//the waveTable constructed from the other properties
	vector<double> waveTable;
	vector<double> voltages;
	double totalPoints;
	double totalTime;
private:
	//the length of time of one cycle
	double period;
	//the amount of time at the begining of the period in which there is a non-zero magnitude
	double contactTime;
	//number of cycles
	double noCycles;
	//magnitude of the wave with no scale
	double magnitude;
	//scaling factor
	double scale;
	//none, linear, or geometric
	int scaleType;
	//the frequency of the sine wave within the contactTime
	double sineFrequency;
	//a bias applied to the sine wave
	double sineBias;
	//append this length of zeros to the end of the stimulus waveform.
	double zeroPulseDuration;

	//the calculated count of number of points in a period
	int totalPointsPerPeriod;
	//the calculated count of number of points in a contactTime
	int activePointsPerPeriod;
	//the calculated count of number of points in a period but not in a contactTime
	int passivePointsPerPeriod;

	

	//the magnitude jump for a linear scale
	double linearJump;
	//the magnitude jump for a geometric scale
	double geoJump;
//prototypes
public:
	/* Function: Stimulus
	 * ------------------
	 * Constructors for a Stimulus object. Sets up the properties from the given parameters.
	 */
	Stimulus();
	Stimulus(double prd, double percentConTime, int noCyc, double mag, double scl, int sclType, double snFreq, double snBias, double zeroPulse);

	/* Function: createSquare
	 * ----------------------
	 * Populates the waveTable with magnitudes along a square wave created from the properties
	 */
	void createSquare(void);

	/* Function: createTriangle
	 * ------------------------
	 * Populates the waveTable with magnitudes along a triangle wave created from the properties
	 */
	void createTriangle(void);

	/* Function: createSine
	 * --------------------
	 * Populates the waveTable with magnitudes along a sine wave created from the properties
	 */
	void createSine(void);

	/* Function: createFromYAML
	 * ------------------------
	 * Populates the waveTable with magnitudes along a custom wave accessed through a YAML file.
	 */
	void createFromYAML(string filePath);

	/* Function: saveAsYAML
	 * --------------------
	 * Saves the waveTable to disk in a YAML sequence format.
	 */
	void saveAsYAML(string filePath);

	/* Function: convertToVoltages
	 * --------------------------------
	 * converts the magnitude of the simulus into voltages for the FPGA 
	 */ 
	void convertToVoltages(double sensitivity);

	/* Function: appendZeroPulse
	 * ----------------------------
	 * appends a 2 s zero pulse to the wave table.
	 */
	void appendZeroPulse(double secondsToAppend);

	/* Function: prepend ZeroPulse
	 * ----------------------------
	 * prepends 5 zeros to the wave table.
	 */
	void prependZeroPulse(int numberOfZeros);

	/* Funtion: createCalibrationWaveTable
	 * -------------------------------------------
	 * creates waveform specifically for calibrating the sensitivity of the cantilevers
	 */
	void createCalibrationWaveTable(void);

private:
	/* Function: updateMagnitudeToScale
	 * --------------------------------
	 * updates the magnitude property with the corresponding scale jump.
	 */
	void updateMagnitudeToScale(void);
};