#pragma once

#include <comdef.h>
#include <windows.h>

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

#include "Stimulus.h"
#include "STM_Communicator.h"

namespace BehaviorRig20 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Windows::Forms::DataVisualization::Charting;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for CalibrateSensitivityForm
	/// </summary>
	public ref class CalibrateSensitivityForm : public System::Windows::Forms::Form
	{
	public:
		CalibrateSensitivityForm(STM_Communicator* comm)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->comm = comm;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CalibrateSensitivityForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private: STM_Communicator* comm;

	private: System::Windows::Forms::Button^  cancelCalibrationButton;

	private: System::Windows::Forms::Button^  finishCalibrationButton;
	private: System::Windows::Forms::Button^  calibrateButton;
	private: System::Windows::Forms::Button^  createCalibrationProfileButton;
	private: System::Windows::Forms::NumericUpDown^  maxProfileNumericUpDown;
	private: System::Windows::Forms::Label^  maxStimLabel;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  cantileverSignalChart;


	private: System::Windows::Forms::DataVisualization::Charting::Chart^  actuatorPositionChart;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  stimulusProfileChart;
	private: System::Windows::Forms::Button^  getCalibrationDataButton;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  sensitivityChart;









	private: System::Windows::Forms::TextBox^  cantileverIDTextBox;
	private: System::Windows::Forms::Label^  cantileverIDLabel;
	private: System::Windows::Forms::CheckBox^  recordDataCheckBox;
	private: System::Windows::Forms::TextBox^  dataCommentsTextBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->cancelCalibrationButton = (gcnew System::Windows::Forms::Button());
			this->finishCalibrationButton = (gcnew System::Windows::Forms::Button());
			this->calibrateButton = (gcnew System::Windows::Forms::Button());
			this->createCalibrationProfileButton = (gcnew System::Windows::Forms::Button());
			this->maxProfileNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->maxStimLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverSignalChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->actuatorPositionChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->stimulusProfileChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->getCalibrationDataButton = (gcnew System::Windows::Forms::Button());
			this->sensitivityChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->cantileverIDTextBox = (gcnew System::Windows::Forms::TextBox());
			this->cantileverIDLabel = (gcnew System::Windows::Forms::Label());
			this->recordDataCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->dataCommentsTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxProfileNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverSignalChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->actuatorPositionChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimulusProfileChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->sensitivityChart))->BeginInit();
			this->SuspendLayout();
			// 
			// cancelCalibrationButton
			// 
			this->cancelCalibrationButton->Location = System::Drawing::Point(934, 672);
			this->cancelCalibrationButton->Name = L"cancelCalibrationButton";
			this->cancelCalibrationButton->Size = System::Drawing::Size(75, 23);
			this->cancelCalibrationButton->TabIndex = 0;
			this->cancelCalibrationButton->Text = L"Cancel";
			this->cancelCalibrationButton->UseVisualStyleBackColor = true;
			this->cancelCalibrationButton->Click += gcnew System::EventHandler(this, &CalibrateSensitivityForm::cancelCalibrationButton_Click);
			// 
			// finishCalibrationButton
			// 
			this->finishCalibrationButton->Location = System::Drawing::Point(852, 672);
			this->finishCalibrationButton->Name = L"finishCalibrationButton";
			this->finishCalibrationButton->Size = System::Drawing::Size(75, 23);
			this->finishCalibrationButton->TabIndex = 1;
			this->finishCalibrationButton->Text = L"OK";
			this->finishCalibrationButton->UseVisualStyleBackColor = true;
			this->finishCalibrationButton->Click += gcnew System::EventHandler(this, &CalibrateSensitivityForm::finishCalibrationButton_Click);
			// 
			// calibrateButton
			// 
			this->calibrateButton->Location = System::Drawing::Point(853, 213);
			this->calibrateButton->Name = L"calibrateButton";
			this->calibrateButton->Size = System::Drawing::Size(156, 23);
			this->calibrateButton->TabIndex = 2;
			this->calibrateButton->Text = L"Calibrate";
			this->calibrateButton->UseVisualStyleBackColor = true;
			this->calibrateButton->Click += gcnew System::EventHandler(this, &CalibrateSensitivityForm::calibrateButton_Click);
			// 
			// createCalibrationProfileButton
			// 
			this->createCalibrationProfileButton->Location = System::Drawing::Point(853, 184);
			this->createCalibrationProfileButton->Name = L"createCalibrationProfileButton";
			this->createCalibrationProfileButton->Size = System::Drawing::Size(156, 23);
			this->createCalibrationProfileButton->TabIndex = 3;
			this->createCalibrationProfileButton->Text = L"Create Calibration Profile";
			this->createCalibrationProfileButton->UseVisualStyleBackColor = true;
			this->createCalibrationProfileButton->Click += gcnew System::EventHandler(this, &CalibrateSensitivityForm::createCalibrationProfileButton_Click);
			// 
			// maxProfileNumericUpDown
			// 
			this->maxProfileNumericUpDown->Location = System::Drawing::Point(853, 158);
			this->maxProfileNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {250, 0, 0, 0});
			this->maxProfileNumericUpDown->Name = L"maxProfileNumericUpDown";
			this->maxProfileNumericUpDown->Size = System::Drawing::Size(129, 20);
			this->maxProfileNumericUpDown->TabIndex = 4;
			// 
			// maxStimLabel
			// 
			this->maxStimLabel->AutoSize = true;
			this->maxStimLabel->Location = System::Drawing::Point(850, 142);
			this->maxStimLabel->Name = L"maxStimLabel";
			this->maxStimLabel->Size = System::Drawing::Size(146, 13);
			this->maxStimLabel->TabIndex = 5;
			this->maxStimLabel->Text = L"Enter maximum displacement:";
			// 
			// cantileverSignalChart
			// 
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisX->Title = L"Time (s)";
			chartArea1->AxisY->Title = L"Voltage (V)";
			chartArea1->Name = L"ChartArea1";
			this->cantileverSignalChart->ChartAreas->Add(chartArea1);
			this->cantileverSignalChart->Location = System::Drawing::Point(12, 361);
			this->cantileverSignalChart->Name = L"cantileverSignalChart";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Name = L"Cantilever";
			this->cantileverSignalChart->Series->Add(series1);
			this->cantileverSignalChart->Size = System::Drawing::Size(807, 165);
			this->cantileverSignalChart->TabIndex = 6;
			this->cantileverSignalChart->Text = L"Cantilever Signal";
			title1->Name = L"Title1";
			title1->Text = L"Cantilever Signal";
			this->cantileverSignalChart->Titles->Add(title1);
			// 
			// actuatorPositionChart
			// 
			chartArea2->AxisX->Minimum = 0;
			chartArea2->AxisX->Title = L"Time (s)";
			chartArea2->AxisY->Title = L"Voltage (V)";
			chartArea2->Name = L"ChartArea1";
			this->actuatorPositionChart->ChartAreas->Add(chartArea2);
			this->actuatorPositionChart->Location = System::Drawing::Point(12, 184);
			this->actuatorPositionChart->Name = L"actuatorPositionChart";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Name = L"Actuator";
			this->actuatorPositionChart->Series->Add(series2);
			this->actuatorPositionChart->Size = System::Drawing::Size(807, 171);
			this->actuatorPositionChart->TabIndex = 7;
			this->actuatorPositionChart->Text = L"chart2";
			title2->Name = L"Title1";
			title2->Text = L"Actuator Signal";
			this->actuatorPositionChart->Titles->Add(title2);
			// 
			// stimulusProfileChart
			// 
			chartArea3->AxisX->Minimum = 0;
			chartArea3->AxisX->Title = L"Time (s)";
			chartArea3->AxisY->Title = L"Stimulus (um)";
			chartArea3->Name = L"ChartArea1";
			this->stimulusProfileChart->ChartAreas->Add(chartArea3);
			this->stimulusProfileChart->Location = System::Drawing::Point(12, 7);
			this->stimulusProfileChart->Name = L"stimulusProfileChart";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Name = L"Stimulus";
			this->stimulusProfileChart->Series->Add(series3);
			this->stimulusProfileChart->Size = System::Drawing::Size(807, 171);
			this->stimulusProfileChart->TabIndex = 8;
			this->stimulusProfileChart->Text = L"chart3";
			title3->Name = L"Title1";
			title3->Text = L"Desired Stimulus";
			this->stimulusProfileChart->Titles->Add(title3);
			// 
			// getCalibrationDataButton
			// 
			this->getCalibrationDataButton->Location = System::Drawing::Point(852, 243);
			this->getCalibrationDataButton->Name = L"getCalibrationDataButton";
			this->getCalibrationDataButton->Size = System::Drawing::Size(157, 23);
			this->getCalibrationDataButton->TabIndex = 9;
			this->getCalibrationDataButton->Text = L"Get Data";
			this->getCalibrationDataButton->UseVisualStyleBackColor = true;
			this->getCalibrationDataButton->Click += gcnew System::EventHandler(this, &CalibrateSensitivityForm::getCalibrationDataButton_Click);
			// 
			// sensitivityChart
			// 
			chartArea4->AxisX->Minimum = 0;
			chartArea4->AxisX->Title = L"Time (s)";
			chartArea4->AxisY->Title = L" um/V";
			chartArea4->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea4->Name = L"ChartArea1";
			this->sensitivityChart->ChartAreas->Add(chartArea4);
			this->sensitivityChart->Location = System::Drawing::Point(12, 532);
			this->sensitivityChart->Name = L"sensitivityChart";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Name = L"Sensitivity";
			this->sensitivityChart->Series->Add(series4);
			this->sensitivityChart->Size = System::Drawing::Size(807, 165);
			this->sensitivityChart->TabIndex = 10;
			this->sensitivityChart->Text = L"Sensitivity";
			title4->Name = L"Title1";
			title4->Text = L"Sensitivity";
			this->sensitivityChart->Titles->Add(title4);
			// 
			// cantileverIDTextBox
			// 
			this->cantileverIDTextBox->Location = System::Drawing::Point(852, 119);
			this->cantileverIDTextBox->Name = L"cantileverIDTextBox";
			this->cantileverIDTextBox->Size = System::Drawing::Size(157, 20);
			this->cantileverIDTextBox->TabIndex = 19;
			// 
			// cantileverIDLabel
			// 
			this->cantileverIDLabel->AutoSize = true;
			this->cantileverIDLabel->Location = System::Drawing::Point(852, 100);
			this->cantileverIDLabel->Name = L"cantileverIDLabel";
			this->cantileverIDLabel->Size = System::Drawing::Size(71, 13);
			this->cantileverIDLabel->TabIndex = 20;
			this->cantileverIDLabel->Text = L"Cantilever ID:";
			// 
			// recordDataCheckBox
			// 
			this->recordDataCheckBox->AutoSize = true;
			this->recordDataCheckBox->Location = System::Drawing::Point(857, 273);
			this->recordDataCheckBox->Name = L"recordDataCheckBox";
			this->recordDataCheckBox->Size = System::Drawing::Size(87, 17);
			this->recordDataCheckBox->TabIndex = 21;
			this->recordDataCheckBox->Text = L"Record Data";
			this->recordDataCheckBox->UseVisualStyleBackColor = true;
			// 
			// dataCommentsTextBox
			// 
			this->dataCommentsTextBox->Location = System::Drawing::Point(852, 311);
			this->dataCommentsTextBox->Multiline = true;
			this->dataCommentsTextBox->Name = L"dataCommentsTextBox";
			this->dataCommentsTextBox->Size = System::Drawing::Size(157, 85);
			this->dataCommentsTextBox->TabIndex = 22;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(853, 292);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(131, 13);
			this->label1->TabIndex = 23;
			this->label1->Text = L"Comments for output data:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(988, 160);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(21, 13);
			this->label2->TabIndex = 24;
			this->label2->Text = L"um";
			// 
			// CalibrateSensitivityForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1021, 707);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dataCommentsTextBox);
			this->Controls->Add(this->recordDataCheckBox);
			this->Controls->Add(this->cantileverIDLabel);
			this->Controls->Add(this->cantileverIDTextBox);
			this->Controls->Add(this->sensitivityChart);
			this->Controls->Add(this->getCalibrationDataButton);
			this->Controls->Add(this->stimulusProfileChart);
			this->Controls->Add(this->actuatorPositionChart);
			this->Controls->Add(this->cantileverSignalChart);
			this->Controls->Add(this->maxStimLabel);
			this->Controls->Add(this->maxProfileNumericUpDown);
			this->Controls->Add(this->createCalibrationProfileButton);
			this->Controls->Add(this->calibrateButton);
			this->Controls->Add(this->finishCalibrationButton);
			this->Controls->Add(this->cancelCalibrationButton);
			this->Name = L"CalibrateSensitivityForm";
			this->Text = L"CalibrateSensitivityForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxProfileNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverSignalChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->actuatorPositionChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimulusProfileChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->sensitivityChart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void finishCalibrationButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->DialogResult = Windows::Forms::DialogResult::OK;
				this->Close();
			 }
private: System::Void cancelCalibrationButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->DialogResult = Windows::Forms::DialogResult::Cancel;
				this->Close();
		 }
private: System::Void createCalibrationProfileButton_Click(System::Object^  sender, System::EventArgs^  e) {
		Stimulus stim = createStimulus();

		stimulusProfileChart->Series["Stimulus"]->Points->Clear();

		vector<double> waveTable = stim.waveTable;
		int size = waveTable.size();

				//plot on chart
		for (int i = 0; i < size; i++) {
			double value = waveTable[i];
			stimulusProfileChart->Series["Stimulus"]->Points->AddXY(i * DELTA_T, value);
		}

		//covert to an array of voltage doubles
		double* stimVoltages = new double[size];
		for (int i = 0; i < size; i++) {
			double value = stim.voltages[i] ;
			stimVoltages[i] = value;
		}

		comm->sendWaveTable(stimVoltages, size);
		delete stimVoltages;

		stim.totalPoints = waveTable.size();
		stim.totalTime = stim.totalPoints/DELTA_T;

		// send all the data to the FPGA:
		//Wave interval - spacing between points on wave table
		comm->sendWaveInterval((int)(DELTA_T*1000000)); // need to convert from s to us for this
		Threading::Thread::Sleep(500);

		//Send PID parameters:
		int numParams = 4;
		double* parameters = new double[numParams];
		parameters[0] = 0.3;
		parameters[1] = 50;
		parameters[2] = 0.00001;
		parameters[3] = 4; //need to make sure this parameter is OK.
		comm->sendPIDParameters(parameters, numParams);
		Threading::Thread::Sleep(500);
		//Send Clamp Mode: Displacement Clamp
		comm->sendClampMode(1);
		Threading::Thread::Sleep(500);


		//Send all the data to FPGA, request info back
		//Send trigger mode
		comm->sendTriggerMode(1);
		//Send data acquisition parameter
		Threading::Thread::Sleep(500);
		comm->sendAcquisitionInterval(1000); // number of us between two points "1000" = 1kHz sampling, min value this can be is 100 ("100" = 10 kHz)

		 }

	Stimulus createStimulus(void)
	{
		double maxSignal = Decimal::ToDouble(maxProfileNumericUpDown->Value);
		double contactTime = 100;
		double period = 8;
		int noCycles = 1;
		double scale = 0;
		double magnitude = maxSignal;
		int scaleType = 0;
		double sineFreq = 0;
		double sineBias = 0;
		double zeroPulse = 2;

		Stimulus stim(period, contactTime, noCycles, magnitude, scale, scaleType, sineFreq, sineBias, zeroPulse );
		
		stim.createCalibrationWaveTable();
				
		stim.appendZeroPulse(zeroPulse);

		stim.convertToVoltages(1/ACTUATOR_SENSITIVITY);
		


		return stim;
	}
private: System::Void calibrateButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Trigger stimulus
			 comm->triggerStimulus();

	 }
private: System::Void getCalibrationDataButton_Click(System::Object^  sender, System::EventArgs^  e) {

			  //gather data, write to plots:
			actuatorPositionChart->Series["Actuator"]->Points->Clear();
			cantileverSignalChart->Series["Cantilever"]->Points->Clear();
			sensitivityChart->Series["Sensitivity"]->Points->Clear();
			vector<double> actuatorSensorSignal = comm->actuatorPositionData;
			vector<double> cantileverSignal = comm->piezoSignalData;
			//vector<double> actuatorCommandSignal;
			vector<double> sensitivity;
			sensitivity.clear();
			int sizeActuator = actuatorSensorSignal.size();
			int sizeCantilever = cantileverSignal.size();

			//plot on chart
			for (int i = 0; i < sizeActuator; i++) {
				double value = actuatorSensorSignal[i];
				//actuatorCommandSignal.push_back(value*ACTUATOR_SENSITIVITY);
				actuatorPositionChart->Series["Actuator"]->Points->AddXY(i * DELTA_T, value);
			}
			for (int i = 0; i < sizeCantilever; i++) {
				double value = cantileverSignal[i];
				cantileverSignalChart->Series["Cantilever"]->Points->AddXY(i * DELTA_T, value);
			}
			
			/*for (int i = 0; i<sizeCantilever; i++){
				if (cantileverSignal[i] > 0.5 )
					sensitivity.push_back((actuatorSensorSignal[i]*ACTUATOR_SENSITIVITY)/(cantileverSignal[i]));
				else 
					sensitivity.push_back(0);

				sensitivityChart->Series["Sensitivity"]->Points->AddXY(i * DELTA_T, sensitivity[i]);
			}*/
			if (recordDataCheckBox->Checked){
				marshal_context^ context = gcnew marshal_context();
				string cantileverID = context->marshal_as<string>(cantileverIDTextBox->Text);
				string commentsForData = context->marshal_as<string>(dataCommentsTextBox->Text);
			
				writeCalibrationDataToDisk( actuatorSensorSignal,  cantileverSignal, cantileverID, commentsForData);
			}

		 

			 
		 }



		 
private: void writeCalibrationDataToDisk(vector<double> actuatorPositions, vector<double> cantileverSignal, string cantileverID, string commentsForData){
			cv::FileStorage dataWriter;
			 
			 SYSTEMTIME now;
			GetLocalTime(&now);

			string time;
			char* cTime = new char[50];
			sprintf(cTime, "%04d_%02d_%02d__%02d_%02d_%02d__", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
			time = string(cTime);
			delete cTime;

			

			string directory = string("C:\\\\Users\\\\HAWK\\\\Documents\\\\CantileverCalibrationData\\\\SensitivityData\\\\"); // + cantileverID + string("\\\\");
			CreateDirectoryA((directory + cantileverID + string("\\\\")).c_str(), NULL);
			string fileName =  time + string("_") + cantileverID + string("_sensitivityData.yaml");
			string fullfile = directory + cantileverID + string("\\\\") + fileName;

			dataWriter.open(fullfile, cv::FileStorage::WRITE);

			dataWriter << string("Time") << time;
			dataWriter << string("Cantilever") << cantileverID;
			dataWriter << string("Comments") << commentsForData;

			string nodeTitle;
			char* title = new char[50];
			//Write actuator position:
			dataWriter << "Actuator Positions" << "{";
			//print rest of data
			for (unsigned int i = 0; i < actuatorPositions.size(); i++) {
				sprintf(title, "Point %d", i);
				nodeTitle = string(title);
				dataWriter << nodeTitle <<  actuatorPositions[i];
			}
			dataWriter << "}";
			//Write cantilever signal:
			dataWriter << "Cantilever Signal" << "{";
			//print rest of data
			for (unsigned int i = 0; i < cantileverSignal.size(); i++) {
				sprintf(title, "Point %d", i);
				nodeTitle = string(title);
				dataWriter << nodeTitle <<  cantileverSignal[i];
			}
			dataWriter << "}";


			dataWriter.release();
		}


};
}
