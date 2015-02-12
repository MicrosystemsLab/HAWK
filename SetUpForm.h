/* SetUpForm.h
 * ----------
 * Component and event code for the experiemnt set up
 * Windows form. Contains controls for all user processes.
 * Requires an Experiemnt and STM_Communicator object to be
 * initialized.
 *
 * Created by John Whitworth on 8/26/14.
 */

#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include "Experiment.h"
#include "ExcelInterface.h"
#include "Stimulus.h"
#include "STM_Communicator.h"

namespace BehaviorRig20 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for SetUpForm
	/// </summary>
	public ref class SetUpForm : public System::Windows::Forms::Form
	{
	public:
		SetUpForm(Experiment* exp, STM_Communicator* comm)
		{
			InitializeComponent();
			this->experiment = exp;
			this->comm = comm;
			this->stimulusSubmitted = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SetUpForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: Experiment* experiment;
	private: STM_Communicator* comm;
	private: bool stimulusSubmitted;

#pragma region Components
	private: System::Windows::Forms::GroupBox^  clampModeGroupBox;
	private: System::Windows::Forms::RadioButton^  dispClampRadioButton;
	private: System::Windows::Forms::RadioButton^  forceClampRadioButton;
	private: System::Windows::Forms::GroupBox^  targetGroupBox;
	private: System::Windows::Forms::GroupBox^  stimulusInfoGroupBox;
	private: System::Windows::Forms::GroupBox^  stimulusSignalGroupBox;
	private: System::Windows::Forms::GroupBox^  dataOutputGroupBox;
	private: System::Windows::Forms::TextBox^  outputLocationTextBox;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  stimulusSignalChart;
	private: System::Windows::Forms::Button^  outputLocationBrowseButton;
	private: System::Windows::Forms::Button^  cancelSetupButton;
	private: System::Windows::Forms::Button^  finishSetupButton;
	private: System::Windows::Forms::Label^  targetTailLabel;
	private: System::Windows::Forms::Label^  targetHeadLabel;
	private: System::Windows::Forms::PictureBox^  targetWormPictureBox;
	private: System::Windows::Forms::NumericUpDown^  targetNumericUpDown;
	private: System::Windows::Forms::Label^  targetUnitLabel;
	private: System::Windows::Forms::TrackBar^  targetTrackBar;
	private: System::Windows::Forms::FolderBrowserDialog^  outputFolderBrowserDialog;
	private: System::Windows::Forms::OpenFileDialog^  customStimOpenFileDialog;
	private: System::Windows::Forms::Label^  scaleTypeStimLabel;
	private: System::Windows::Forms::Label^  scaleStimLabel;
	private: System::Windows::Forms::Label^  magnitudeStimLabel;
	private: System::Windows::Forms::Label^  noCyclesStimLabel;
	private: System::Windows::Forms::Label^  contactTimeStimLabel;
	private: System::Windows::Forms::Label^  periodStimLabel;
	private: System::Windows::Forms::Label^  magnitudeStimUnitLabel;
	private: System::Windows::Forms::Label^  noCyclesStimUnitLabel;
	private: System::Windows::Forms::Label^  periodStimUnitLabel;
	private: System::Windows::Forms::GroupBox^  stimulusTypeGroupBox;
	private: System::Windows::Forms::RadioButton^  customTypeRadioButton;
	private: System::Windows::Forms::RadioButton^  sineTypeRadioButton;
	private: System::Windows::Forms::RadioButton^  triangleTypeRadioButton;
	private: System::Windows::Forms::RadioButton^  squareTypeRadioButton;
	private: System::Windows::Forms::GroupBox^  experimentInfoGroupBox;
	private: System::Windows::Forms::Label^  ambientTemperatureUnitLabel;
	private: System::Windows::Forms::TextBox^  otherInfoTextBox;
	private: System::Windows::Forms::ComboBox^  wormGenderComboBox;
	private: System::Windows::Forms::TextBox^  wormTreatmentsTextBox;
	private: System::Windows::Forms::TextBox^  wormStrainTextBox;
	private: System::Windows::Forms::TextBox^  experimentTitleTextBox;
	private: System::Windows::Forms::ComboBox^  wormAgeComboBox;
	private: System::Windows::Forms::Label^  otherInfoLabel;
	private: System::Windows::Forms::Label^  wormAgeLabel;
	private: System::Windows::Forms::Label^  wormGenderLabel;
	private: System::Windows::Forms::Label^  percentAgarLabel;
	private: System::Windows::Forms::Label^  ambientTemperatureLabel;
	private: System::Windows::Forms::Label^  ambientHumidityLabel;
	private: System::Windows::Forms::Label^  wormTreatmentsLabel;
	private: System::Windows::Forms::Label^  wormStrainLabel;
	private: System::Windows::Forms::Label^  experimentTitleLabel;
	private: System::Windows::Forms::GroupBox^  cantileverGroupBox;
	private: System::Windows::Forms::Label^  deviceIDExampleLabel;
	private: System::Windows::Forms::Label^  waferIDExampleLabel;
	private: System::Windows::Forms::Label^  deviceIDLabel;
	private: System::Windows::Forms::TextBox^  deviceIDTextBox;
	private: System::Windows::Forms::Label^  cantileverSpecLabel;
	private: System::Windows::Forms::Label^  waferIDLabel;
	private: System::Windows::Forms::Label^  cantileverSensitivityUnitLabel;
	private: System::Windows::Forms::Label^  cantileverSensitivityLabel;
	private: System::Windows::Forms::Label^  cantileverStiffnessUnitLabel;
	private: System::Windows::Forms::Label^  cantileverFreqUnitLabel;
	private: System::Windows::Forms::Label^  cantileverStiffnessLabel;
	private: System::Windows::Forms::Label^  cantileverFrequencyLabel;
	private: System::Windows::Forms::TextBox^  waferIDTextBox;
	private: System::Windows::Forms::Button^  cantileverIDSearchButton;
	private: System::Windows::Forms::Label^  sineBiasStimUnitLabel;
	private: System::Windows::Forms::Label^  sineBiasStimLabel;
	private: System::Windows::Forms::Label^  sineFreqStimLabel;
	private: System::Windows::Forms::Label^  sineFreqStimUnitLabel;
	private: System::Windows::Forms::Button^  customStimBrowseButton;
	private: System::Windows::Forms::TextBox^  customStimFileTextBox;
	private: System::Windows::Forms::Label^  customStimFileLabel;
	private: System::Windows::Forms::Label^  contactTimeStimUnitLabel;
	private: System::Windows::Forms::Label^  percentAgarUnitLabel;
	private: System::Windows::Forms::Label^  ambientHumidityUnitLabel;
	private: System::Windows::Forms::Button^  submitStimulusButton;
	private: System::Windows::Forms::Button^  saveStimButton;
	private: System::Windows::Forms::SaveFileDialog^  saveStimFileDialog;
	private: System::Windows::Forms::NumericUpDown^  ambientTemperatureNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  ambientHumidityNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  percentAgarNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  cantileverSensitivityNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  cantileverStiffnessNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  cantileverFrequencyNumericUpDown;
	private: System::Windows::Forms::ComboBox^  wormFoodStatusComboBox;
	private: System::Windows::Forms::Label^  wormFoodStatusLabel;
	private: System::Windows::Forms::NumericUpDown^  stimSineBiasNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  stimSineFreqNumericUpDown;
	private: System::Windows::Forms::DomainUpDown^  stimScaleTypeDomainUpDown;
	private: System::Windows::Forms::NumericUpDown^  stimScaleNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  stimMagnitudeNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  stimNoCyclesNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  stimContactTimeNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  stimPeriodNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  preStimRecordTimeNumericUpDown;
	private: System::Windows::Forms::Label^  preStimRecordTimeUnitLabel;
	private: System::Windows::Forms::Label^  preStimRecordTimeLabel;
private: System::Windows::Forms::RadioButton^  openLoopClampRadioButton;
private: System::Windows::Forms::Label^  dParameterLabel;
private: System::Windows::Forms::Label^  iParameterLabel;
private: System::Windows::Forms::Label^  pParameterLabel;
private: System::Windows::Forms::Label^  controlParametersLabel;
private: System::Windows::Forms::NumericUpDown^  dParameterNumericUpDown;

private: System::Windows::Forms::NumericUpDown^  iParameterNumericUpDown;

private: System::Windows::Forms::NumericUpDown^  pParameterNumericUpDown;
private: System::Windows::Forms::RadioButton^  behaviorModeRadioButton;
private: System::Windows::Forms::NumericUpDown^  experimentNumericUpDown;

private: System::Windows::Forms::NumericUpDown^  slideNumberNumericUpDown;

private: System::Windows::Forms::NumericUpDown^  postStimRecordTimeNumericUpDown;
private: System::Windows::Forms::Label^  postStimRecordTimeUnitLabel;

private: System::Windows::Forms::Label^  experimentNumberLabel;
private: System::Windows::Forms::Label^  slideNumberLabel;
private: System::Windows::Forms::Label^  postStimRecordTimeLabel;
private: System::Windows::Forms::Label^  postStimZerlPulseUnitLabel;
private: System::Windows::Forms::Label^  postStimZeroPulseLabel;
private: System::Windows::Forms::NumericUpDown^  postStimZeroPulseNumericUpDown;





#pragma endregion

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(SetUpForm::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->clampModeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->behaviorModeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->openLoopClampRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->dispClampRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->forceClampRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->targetGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->targetTailLabel = (gcnew System::Windows::Forms::Label());
			this->targetHeadLabel = (gcnew System::Windows::Forms::Label());
			this->targetWormPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->targetNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->targetUnitLabel = (gcnew System::Windows::Forms::Label());
			this->targetTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->stimulusInfoGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->postStimZerlPulseUnitLabel = (gcnew System::Windows::Forms::Label());
			this->postStimZeroPulseLabel = (gcnew System::Windows::Forms::Label());
			this->postStimZeroPulseNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->stimSineBiasNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->stimSineFreqNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->stimScaleTypeDomainUpDown = (gcnew System::Windows::Forms::DomainUpDown());
			this->stimScaleNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->stimMagnitudeNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->stimNoCyclesNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->stimContactTimeNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->stimPeriodNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->saveStimButton = (gcnew System::Windows::Forms::Button());
			this->submitStimulusButton = (gcnew System::Windows::Forms::Button());
			this->contactTimeStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->sineBiasStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->sineBiasStimLabel = (gcnew System::Windows::Forms::Label());
			this->sineFreqStimLabel = (gcnew System::Windows::Forms::Label());
			this->sineFreqStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->customStimBrowseButton = (gcnew System::Windows::Forms::Button());
			this->customStimFileTextBox = (gcnew System::Windows::Forms::TextBox());
			this->customStimFileLabel = (gcnew System::Windows::Forms::Label());
			this->scaleTypeStimLabel = (gcnew System::Windows::Forms::Label());
			this->scaleStimLabel = (gcnew System::Windows::Forms::Label());
			this->magnitudeStimLabel = (gcnew System::Windows::Forms::Label());
			this->noCyclesStimLabel = (gcnew System::Windows::Forms::Label());
			this->contactTimeStimLabel = (gcnew System::Windows::Forms::Label());
			this->periodStimLabel = (gcnew System::Windows::Forms::Label());
			this->magnitudeStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->noCyclesStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->periodStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->stimulusTypeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->customTypeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->sineTypeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->triangleTypeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->squareTypeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->stimulusSignalGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->stimulusSignalChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->dataOutputGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->outputLocationBrowseButton = (gcnew System::Windows::Forms::Button());
			this->outputLocationTextBox = (gcnew System::Windows::Forms::TextBox());
			this->cancelSetupButton = (gcnew System::Windows::Forms::Button());
			this->finishSetupButton = (gcnew System::Windows::Forms::Button());
			this->outputFolderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->customStimOpenFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->experimentInfoGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->postStimRecordTimeUnitLabel = (gcnew System::Windows::Forms::Label());
			this->experimentNumberLabel = (gcnew System::Windows::Forms::Label());
			this->slideNumberLabel = (gcnew System::Windows::Forms::Label());
			this->postStimRecordTimeLabel = (gcnew System::Windows::Forms::Label());
			this->experimentNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->slideNumberNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->postStimRecordTimeNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->preStimRecordTimeNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->preStimRecordTimeUnitLabel = (gcnew System::Windows::Forms::Label());
			this->preStimRecordTimeLabel = (gcnew System::Windows::Forms::Label());
			this->wormFoodStatusComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->wormFoodStatusLabel = (gcnew System::Windows::Forms::Label());
			this->ambientTemperatureNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->ambientHumidityNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->percentAgarNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->percentAgarUnitLabel = (gcnew System::Windows::Forms::Label());
			this->ambientHumidityUnitLabel = (gcnew System::Windows::Forms::Label());
			this->ambientTemperatureUnitLabel = (gcnew System::Windows::Forms::Label());
			this->otherInfoTextBox = (gcnew System::Windows::Forms::TextBox());
			this->wormGenderComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->wormTreatmentsTextBox = (gcnew System::Windows::Forms::TextBox());
			this->wormStrainTextBox = (gcnew System::Windows::Forms::TextBox());
			this->experimentTitleTextBox = (gcnew System::Windows::Forms::TextBox());
			this->wormAgeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->otherInfoLabel = (gcnew System::Windows::Forms::Label());
			this->wormAgeLabel = (gcnew System::Windows::Forms::Label());
			this->wormGenderLabel = (gcnew System::Windows::Forms::Label());
			this->percentAgarLabel = (gcnew System::Windows::Forms::Label());
			this->ambientTemperatureLabel = (gcnew System::Windows::Forms::Label());
			this->ambientHumidityLabel = (gcnew System::Windows::Forms::Label());
			this->wormTreatmentsLabel = (gcnew System::Windows::Forms::Label());
			this->wormStrainLabel = (gcnew System::Windows::Forms::Label());
			this->experimentTitleLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->dParameterLabel = (gcnew System::Windows::Forms::Label());
			this->iParameterLabel = (gcnew System::Windows::Forms::Label());
			this->pParameterLabel = (gcnew System::Windows::Forms::Label());
			this->controlParametersLabel = (gcnew System::Windows::Forms::Label());
			this->dParameterNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->iParameterNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->pParameterNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->cantileverSensitivityNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->cantileverStiffnessNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->cantileverFrequencyNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->deviceIDExampleLabel = (gcnew System::Windows::Forms::Label());
			this->waferIDExampleLabel = (gcnew System::Windows::Forms::Label());
			this->deviceIDLabel = (gcnew System::Windows::Forms::Label());
			this->deviceIDTextBox = (gcnew System::Windows::Forms::TextBox());
			this->cantileverSpecLabel = (gcnew System::Windows::Forms::Label());
			this->waferIDLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverSensitivityUnitLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverSensitivityLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverStiffnessUnitLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverFreqUnitLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverStiffnessLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverFrequencyLabel = (gcnew System::Windows::Forms::Label());
			this->waferIDTextBox = (gcnew System::Windows::Forms::TextBox());
			this->cantileverIDSearchButton = (gcnew System::Windows::Forms::Button());
			this->saveStimFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->clampModeGroupBox->SuspendLayout();
			this->targetGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->targetWormPictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->targetNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->targetTrackBar))->BeginInit();
			this->stimulusInfoGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->postStimZeroPulseNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimSineBiasNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimSineFreqNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimScaleNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimMagnitudeNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimNoCyclesNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimContactTimeNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimPeriodNumericUpDown))->BeginInit();
			this->stimulusTypeGroupBox->SuspendLayout();
			this->stimulusSignalGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimulusSignalChart))->BeginInit();
			this->dataOutputGroupBox->SuspendLayout();
			this->experimentInfoGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->experimentNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->slideNumberNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->postStimRecordTimeNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->preStimRecordTimeNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ambientTemperatureNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ambientHumidityNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->percentAgarNumericUpDown))->BeginInit();
			this->cantileverGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dParameterNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->iParameterNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pParameterNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverSensitivityNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverStiffnessNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverFrequencyNumericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// clampModeGroupBox
			// 
			this->clampModeGroupBox->Controls->Add(this->behaviorModeRadioButton);
			this->clampModeGroupBox->Controls->Add(this->openLoopClampRadioButton);
			this->clampModeGroupBox->Controls->Add(this->dispClampRadioButton);
			this->clampModeGroupBox->Controls->Add(this->forceClampRadioButton);
			this->clampModeGroupBox->Location = System::Drawing::Point(334, 12);
			this->clampModeGroupBox->Name = L"clampModeGroupBox";
			this->clampModeGroupBox->Size = System::Drawing::Size(133, 112);
			this->clampModeGroupBox->TabIndex = 12;
			this->clampModeGroupBox->TabStop = false;
			this->clampModeGroupBox->Text = L"Clamp Mode";
			// 
			// behaviorModeRadioButton
			// 
			this->behaviorModeRadioButton->AutoSize = true;
			this->behaviorModeRadioButton->Location = System::Drawing::Point(7, 90);
			this->behaviorModeRadioButton->Name = L"behaviorModeRadioButton";
			this->behaviorModeRadioButton->Size = System::Drawing::Size(67, 17);
			this->behaviorModeRadioButton->TabIndex = 15;
			this->behaviorModeRadioButton->Text = L"Behavior";
			this->behaviorModeRadioButton->UseVisualStyleBackColor = true;
			this->behaviorModeRadioButton->CheckedChanged += gcnew System::EventHandler(this, &SetUpForm::behaviorModeRadioButton_CheckedChanged);
			// 
			// openLoopClampRadioButton
			// 
			this->openLoopClampRadioButton->AutoSize = true;
			this->openLoopClampRadioButton->Location = System::Drawing::Point(7, 67);
			this->openLoopClampRadioButton->Name = L"openLoopClampRadioButton";
			this->openLoopClampRadioButton->Size = System::Drawing::Size(78, 17);
			this->openLoopClampRadioButton->TabIndex = 14;
			this->openLoopClampRadioButton->Text = L"Open Loop";
			this->openLoopClampRadioButton->UseVisualStyleBackColor = true;
			this->openLoopClampRadioButton->CheckedChanged += gcnew System::EventHandler(this, &SetUpForm::openLoopClampRadioButton_CheckedChanged);
			// 
			// dispClampRadioButton
			// 
			this->dispClampRadioButton->AutoSize = true;
			this->dispClampRadioButton->Location = System::Drawing::Point(7, 43);
			this->dispClampRadioButton->Name = L"dispClampRadioButton";
			this->dispClampRadioButton->Size = System::Drawing::Size(121, 17);
			this->dispClampRadioButton->TabIndex = 13;
			this->dispClampRadioButton->Text = L"Displacement Clamp";
			this->dispClampRadioButton->UseVisualStyleBackColor = true;
			this->dispClampRadioButton->CheckedChanged += gcnew System::EventHandler(this, &SetUpForm::dispClampRadioButton_CheckedChanged);
			// 
			// forceClampRadioButton
			// 
			this->forceClampRadioButton->AutoSize = true;
			this->forceClampRadioButton->Location = System::Drawing::Point(7, 20);
			this->forceClampRadioButton->Name = L"forceClampRadioButton";
			this->forceClampRadioButton->Size = System::Drawing::Size(84, 17);
			this->forceClampRadioButton->TabIndex = 12;
			this->forceClampRadioButton->Text = L"Force Clamp";
			this->forceClampRadioButton->UseVisualStyleBackColor = true;
			this->forceClampRadioButton->CheckedChanged += gcnew System::EventHandler(this, &SetUpForm::forceClampRadioButton_CheckedChanged);
			// 
			// targetGroupBox
			// 
			this->targetGroupBox->Controls->Add(this->targetTailLabel);
			this->targetGroupBox->Controls->Add(this->targetHeadLabel);
			this->targetGroupBox->Controls->Add(this->targetWormPictureBox);
			this->targetGroupBox->Controls->Add(this->targetNumericUpDown);
			this->targetGroupBox->Controls->Add(this->targetUnitLabel);
			this->targetGroupBox->Controls->Add(this->targetTrackBar);
			this->targetGroupBox->Enabled = false;
			this->targetGroupBox->Location = System::Drawing::Point(334, 130);
			this->targetGroupBox->Name = L"targetGroupBox";
			this->targetGroupBox->Size = System::Drawing::Size(133, 284);
			this->targetGroupBox->TabIndex = 2;
			this->targetGroupBox->TabStop = false;
			this->targetGroupBox->Text = L"Target Selection";
			// 
			// targetTailLabel
			// 
			this->targetTailLabel->AutoSize = true;
			this->targetTailLabel->Location = System::Drawing::Point(91, 257);
			this->targetTailLabel->Name = L"targetTailLabel";
			this->targetTailLabel->Size = System::Drawing::Size(31, 13);
			this->targetTailLabel->TabIndex = 27;
			this->targetTailLabel->Text = L"Anus";
			// 
			// targetHeadLabel
			// 
			this->targetHeadLabel->AutoSize = true;
			this->targetHeadLabel->Location = System::Drawing::Point(77, 13);
			this->targetHeadLabel->Name = L"targetHeadLabel";
			this->targetHeadLabel->Size = System::Drawing::Size(45, 13);
			this->targetHeadLabel->TabIndex = 26;
			this->targetHeadLabel->Text = L"Pharynx";
			// 
			// targetWormPictureBox
			// 
			this->targetWormPictureBox->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"targetWormPictureBox.Image")));
			this->targetWormPictureBox->Location = System::Drawing::Point(58, 28);
			this->targetWormPictureBox->Name = L"targetWormPictureBox";
			this->targetWormPictureBox->Size = System::Drawing::Size(71, 226);
			this->targetWormPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->targetWormPictureBox->TabIndex = 17;
			this->targetWormPictureBox->TabStop = false;
			// 
			// targetNumericUpDown
			// 
			this->targetNumericUpDown->Location = System::Drawing::Point(7, 254);
			this->targetNumericUpDown->Name = L"targetNumericUpDown";
			this->targetNumericUpDown->Size = System::Drawing::Size(40, 20);
			this->targetNumericUpDown->TabIndex = 14;
			this->targetNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {50, 0, 0, 0});
			this->targetNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &SetUpForm::targetNumericUpDown_ValueChanged);
			// 
			// targetUnitLabel
			// 
			this->targetUnitLabel->AutoSize = true;
			this->targetUnitLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->targetUnitLabel->Location = System::Drawing::Point(51, 258);
			this->targetUnitLabel->Name = L"targetUnitLabel";
			this->targetUnitLabel->Size = System::Drawing::Size(20, 16);
			this->targetUnitLabel->TabIndex = 15;
			this->targetUnitLabel->Text = L"%";
			// 
			// targetTrackBar
			// 
			this->targetTrackBar->LargeChange = 10;
			this->targetTrackBar->Location = System::Drawing::Point(7, 19);
			this->targetTrackBar->Maximum = 100;
			this->targetTrackBar->Name = L"targetTrackBar";
			this->targetTrackBar->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->targetTrackBar->Size = System::Drawing::Size(45, 235);
			this->targetTrackBar->TabIndex = 13;
			this->targetTrackBar->TickFrequency = 5;
			this->targetTrackBar->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->targetTrackBar->Value = 50;
			this->targetTrackBar->Scroll += gcnew System::EventHandler(this, &SetUpForm::targetTrackBar_Scroll);
			// 
			// stimulusInfoGroupBox
			// 
			this->stimulusInfoGroupBox->Controls->Add(this->postStimZerlPulseUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->postStimZeroPulseLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->postStimZeroPulseNumericUpDown);
			this->stimulusInfoGroupBox->Controls->Add(this->stimSineBiasNumericUpDown);
			this->stimulusInfoGroupBox->Controls->Add(this->stimSineFreqNumericUpDown);
			this->stimulusInfoGroupBox->Controls->Add(this->stimScaleTypeDomainUpDown);
			this->stimulusInfoGroupBox->Controls->Add(this->stimScaleNumericUpDown);
			this->stimulusInfoGroupBox->Controls->Add(this->stimMagnitudeNumericUpDown);
			this->stimulusInfoGroupBox->Controls->Add(this->stimNoCyclesNumericUpDown);
			this->stimulusInfoGroupBox->Controls->Add(this->stimContactTimeNumericUpDown);
			this->stimulusInfoGroupBox->Controls->Add(this->stimPeriodNumericUpDown);
			this->stimulusInfoGroupBox->Controls->Add(this->saveStimButton);
			this->stimulusInfoGroupBox->Controls->Add(this->submitStimulusButton);
			this->stimulusInfoGroupBox->Controls->Add(this->contactTimeStimUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->sineBiasStimUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->sineBiasStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->sineFreqStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->sineFreqStimUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->customStimBrowseButton);
			this->stimulusInfoGroupBox->Controls->Add(this->customStimFileTextBox);
			this->stimulusInfoGroupBox->Controls->Add(this->customStimFileLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->scaleTypeStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->scaleStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->magnitudeStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->noCyclesStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->contactTimeStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->periodStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->magnitudeStimUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->noCyclesStimUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->periodStimUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->stimulusTypeGroupBox);
			this->stimulusInfoGroupBox->Enabled = false;
			this->stimulusInfoGroupBox->Location = System::Drawing::Point(795, 12);
			this->stimulusInfoGroupBox->Name = L"stimulusInfoGroupBox";
			this->stimulusInfoGroupBox->Size = System::Drawing::Size(345, 310);
			this->stimulusInfoGroupBox->TabIndex = 3;
			this->stimulusInfoGroupBox->TabStop = false;
			this->stimulusInfoGroupBox->Text = L"Stimulus Information";
			// 
			// postStimZerlPulseUnitLabel
			// 
			this->postStimZerlPulseUnitLabel->AutoEllipsis = true;
			this->postStimZerlPulseUnitLabel->AutoSize = true;
			this->postStimZerlPulseUnitLabel->Location = System::Drawing::Point(300, 232);
			this->postStimZerlPulseUnitLabel->Name = L"postStimZerlPulseUnitLabel";
			this->postStimZerlPulseUnitLabel->Size = System::Drawing::Size(12, 13);
			this->postStimZerlPulseUnitLabel->TabIndex = 48;
			this->postStimZerlPulseUnitLabel->Text = L"s";
			// 
			// postStimZeroPulseLabel
			// 
			this->postStimZeroPulseLabel->AutoSize = true;
			this->postStimZeroPulseLabel->Location = System::Drawing::Point(87, 230);
			this->postStimZeroPulseLabel->Name = L"postStimZeroPulseLabel";
			this->postStimZeroPulseLabel->Size = System::Drawing::Size(124, 13);
			this->postStimZeroPulseLabel->TabIndex = 47;
			this->postStimZeroPulseLabel->Text = L"Post-Stimulus Zero Time:";
			// 
			// postStimZeroPulseNumericUpDown
			// 
			this->postStimZeroPulseNumericUpDown->Location = System::Drawing::Point(211, 228);
			this->postStimZeroPulseNumericUpDown->Name = L"postStimZeroPulseNumericUpDown";
			this->postStimZeroPulseNumericUpDown->Size = System::Drawing::Size(85, 20);
			this->postStimZeroPulseNumericUpDown->TabIndex = 46;
			// 
			// stimSineBiasNumericUpDown
			// 
			this->stimSineBiasNumericUpDown->DecimalPlaces = 2;
			this->stimSineBiasNumericUpDown->Location = System::Drawing::Point(211, 202);
			this->stimSineBiasNumericUpDown->Name = L"stimSineBiasNumericUpDown";
			this->stimSineBiasNumericUpDown->Size = System::Drawing::Size(85, 20);
			this->stimSineBiasNumericUpDown->TabIndex = 34;
			// 
			// stimSineFreqNumericUpDown
			// 
			this->stimSineFreqNumericUpDown->DecimalPlaces = 2;
			this->stimSineFreqNumericUpDown->Location = System::Drawing::Point(211, 176);
			this->stimSineFreqNumericUpDown->Name = L"stimSineFreqNumericUpDown";
			this->stimSineFreqNumericUpDown->Size = System::Drawing::Size(85, 20);
			this->stimSineFreqNumericUpDown->TabIndex = 33;
			// 
			// stimScaleTypeDomainUpDown
			// 
			this->stimScaleTypeDomainUpDown->Items->Add(L"None");
			this->stimScaleTypeDomainUpDown->Items->Add(L"Linear");
			this->stimScaleTypeDomainUpDown->Items->Add(L"Geometric");
			this->stimScaleTypeDomainUpDown->Location = System::Drawing::Point(211, 150);
			this->stimScaleTypeDomainUpDown->Name = L"stimScaleTypeDomainUpDown";
			this->stimScaleTypeDomainUpDown->SelectedIndex = 0;
			this->stimScaleTypeDomainUpDown->Size = System::Drawing::Size(107, 20);
			this->stimScaleTypeDomainUpDown->TabIndex = 32;
			this->stimScaleTypeDomainUpDown->Text = L"None";
			this->stimScaleTypeDomainUpDown->Wrap = true;
			// 
			// stimScaleNumericUpDown
			// 
			this->stimScaleNumericUpDown->DecimalPlaces = 2;
			this->stimScaleNumericUpDown->Location = System::Drawing::Point(211, 123);
			this->stimScaleNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, System::Int32::MinValue});
			this->stimScaleNumericUpDown->Name = L"stimScaleNumericUpDown";
			this->stimScaleNumericUpDown->Size = System::Drawing::Size(85, 20);
			this->stimScaleNumericUpDown->TabIndex = 31;
			// 
			// stimMagnitudeNumericUpDown
			// 
			this->stimMagnitudeNumericUpDown->DecimalPlaces = 2;
			this->stimMagnitudeNumericUpDown->Location = System::Drawing::Point(211, 97);
			this->stimMagnitudeNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10000, 0, 0, 0});
			this->stimMagnitudeNumericUpDown->Name = L"stimMagnitudeNumericUpDown";
			this->stimMagnitudeNumericUpDown->Size = System::Drawing::Size(85, 20);
			this->stimMagnitudeNumericUpDown->TabIndex = 30;
			// 
			// stimNoCyclesNumericUpDown
			// 
			this->stimNoCyclesNumericUpDown->Location = System::Drawing::Point(211, 71);
			this->stimNoCyclesNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->stimNoCyclesNumericUpDown->Name = L"stimNoCyclesNumericUpDown";
			this->stimNoCyclesNumericUpDown->Size = System::Drawing::Size(85, 20);
			this->stimNoCyclesNumericUpDown->TabIndex = 29;
			// 
			// stimContactTimeNumericUpDown
			// 
			this->stimContactTimeNumericUpDown->DecimalPlaces = 2;
			this->stimContactTimeNumericUpDown->Location = System::Drawing::Point(211, 45);
			this->stimContactTimeNumericUpDown->Name = L"stimContactTimeNumericUpDown";
			this->stimContactTimeNumericUpDown->Size = System::Drawing::Size(85, 20);
			this->stimContactTimeNumericUpDown->TabIndex = 28;
			// 
			// stimPeriodNumericUpDown
			// 
			this->stimPeriodNumericUpDown->DecimalPlaces = 2;
			this->stimPeriodNumericUpDown->Location = System::Drawing::Point(211, 19);
			this->stimPeriodNumericUpDown->Name = L"stimPeriodNumericUpDown";
			this->stimPeriodNumericUpDown->Size = System::Drawing::Size(85, 20);
			this->stimPeriodNumericUpDown->TabIndex = 27;
			// 
			// saveStimButton
			// 
			this->saveStimButton->Location = System::Drawing::Point(7, 196);
			this->saveStimButton->Name = L"saveStimButton";
			this->saveStimButton->Size = System::Drawing::Size(74, 48);
			this->saveStimButton->TabIndex = 45;
			this->saveStimButton->Text = L"Save Stimulus";
			this->saveStimButton->UseVisualStyleBackColor = true;
			this->saveStimButton->Click += gcnew System::EventHandler(this, &SetUpForm::saveStimButton_Click);
			// 
			// submitStimulusButton
			// 
			this->submitStimulusButton->Location = System::Drawing::Point(6, 142);
			this->submitStimulusButton->Name = L"submitStimulusButton";
			this->submitStimulusButton->Size = System::Drawing::Size(75, 50);
			this->submitStimulusButton->TabIndex = 35;
			this->submitStimulusButton->Text = L"Submit Stimulus";
			this->submitStimulusButton->UseVisualStyleBackColor = true;
			this->submitStimulusButton->Click += gcnew System::EventHandler(this, &SetUpForm::submitStimulusButton_Click);
			// 
			// contactTimeStimUnitLabel
			// 
			this->contactTimeStimUnitLabel->AutoSize = true;
			this->contactTimeStimUnitLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->contactTimeStimUnitLabel->Location = System::Drawing::Point(298, 46);
			this->contactTimeStimUnitLabel->Name = L"contactTimeStimUnitLabel";
			this->contactTimeStimUnitLabel->Size = System::Drawing::Size(20, 16);
			this->contactTimeStimUnitLabel->TabIndex = 43;
			this->contactTimeStimUnitLabel->Text = L"%";
			// 
			// sineBiasStimUnitLabel
			// 
			this->sineBiasStimUnitLabel->AutoSize = true;
			this->sineBiasStimUnitLabel->Location = System::Drawing::Point(298, 205);
			this->sineBiasStimUnitLabel->Name = L"sineBiasStimUnitLabel";
			this->sineBiasStimUnitLabel->Size = System::Drawing::Size(41, 13);
			this->sineBiasStimUnitLabel->TabIndex = 42;
			this->sineBiasStimUnitLabel->Text = L"uN, um";
			// 
			// sineBiasStimLabel
			// 
			this->sineBiasStimLabel->AutoSize = true;
			this->sineBiasStimLabel->Location = System::Drawing::Point(87, 205);
			this->sineBiasStimLabel->Name = L"sineBiasStimLabel";
			this->sineBiasStimLabel->Size = System::Drawing::Size(54, 13);
			this->sineBiasStimLabel->TabIndex = 41;
			this->sineBiasStimLabel->Text = L"Sine Bias:";
			// 
			// sineFreqStimLabel
			// 
			this->sineFreqStimLabel->AutoSize = true;
			this->sineFreqStimLabel->Location = System::Drawing::Point(87, 179);
			this->sineFreqStimLabel->Name = L"sineFreqStimLabel";
			this->sineFreqStimLabel->Size = System::Drawing::Size(84, 13);
			this->sineFreqStimLabel->TabIndex = 40;
			this->sineFreqStimLabel->Text = L"Sine Frequency:";
			// 
			// sineFreqStimUnitLabel
			// 
			this->sineFreqStimUnitLabel->AutoSize = true;
			this->sineFreqStimUnitLabel->Location = System::Drawing::Point(298, 179);
			this->sineFreqStimUnitLabel->Name = L"sineFreqStimUnitLabel";
			this->sineFreqStimUnitLabel->Size = System::Drawing::Size(20, 13);
			this->sineFreqStimUnitLabel->TabIndex = 38;
			this->sineFreqStimUnitLabel->Text = L"Hz";
			// 
			// customStimBrowseButton
			// 
			this->customStimBrowseButton->Location = System::Drawing::Point(284, 271);
			this->customStimBrowseButton->Name = L"customStimBrowseButton";
			this->customStimBrowseButton->Size = System::Drawing::Size(55, 23);
			this->customStimBrowseButton->TabIndex = 35;
			this->customStimBrowseButton->Text = L"Browse";
			this->customStimBrowseButton->UseVisualStyleBackColor = true;
			this->customStimBrowseButton->Click += gcnew System::EventHandler(this, &SetUpForm::customStimBrowseButton_Click);
			// 
			// customStimFileTextBox
			// 
			this->customStimFileTextBox->Location = System::Drawing::Point(7, 273);
			this->customStimFileTextBox->Name = L"customStimFileTextBox";
			this->customStimFileTextBox->Size = System::Drawing::Size(272, 20);
			this->customStimFileTextBox->TabIndex = 34;
			// 
			// customStimFileLabel
			// 
			this->customStimFileLabel->AutoSize = true;
			this->customStimFileLabel->Location = System::Drawing::Point(6, 251);
			this->customStimFileLabel->Name = L"customStimFileLabel";
			this->customStimFileLabel->Size = System::Drawing::Size(106, 13);
			this->customStimFileLabel->TabIndex = 33;
			this->customStimFileLabel->Text = L"Custom Stimulus File:";
			// 
			// scaleTypeStimLabel
			// 
			this->scaleTypeStimLabel->AutoSize = true;
			this->scaleTypeStimLabel->Location = System::Drawing::Point(87, 152);
			this->scaleTypeStimLabel->Name = L"scaleTypeStimLabel";
			this->scaleTypeStimLabel->Size = System::Drawing::Size(64, 13);
			this->scaleTypeStimLabel->TabIndex = 30;
			this->scaleTypeStimLabel->Text = L"Scale Type:";
			// 
			// scaleStimLabel
			// 
			this->scaleStimLabel->AutoSize = true;
			this->scaleStimLabel->Location = System::Drawing::Point(87, 126);
			this->scaleStimLabel->Name = L"scaleStimLabel";
			this->scaleStimLabel->Size = System::Drawing::Size(70, 13);
			this->scaleStimLabel->TabIndex = 29;
			this->scaleStimLabel->Text = L"Scale Factor:";
			// 
			// magnitudeStimLabel
			// 
			this->magnitudeStimLabel->AutoSize = true;
			this->magnitudeStimLabel->Location = System::Drawing::Point(87, 102);
			this->magnitudeStimLabel->Name = L"magnitudeStimLabel";
			this->magnitudeStimLabel->Size = System::Drawing::Size(60, 13);
			this->magnitudeStimLabel->TabIndex = 28;
			this->magnitudeStimLabel->Text = L"Magnitude:";
			// 
			// noCyclesStimLabel
			// 
			this->noCyclesStimLabel->AutoSize = true;
			this->noCyclesStimLabel->Location = System::Drawing::Point(87, 74);
			this->noCyclesStimLabel->Name = L"noCyclesStimLabel";
			this->noCyclesStimLabel->Size = System::Drawing::Size(73, 13);
			this->noCyclesStimLabel->TabIndex = 27;
			this->noCyclesStimLabel->Text = L"No. of Cycles:";
			// 
			// contactTimeStimLabel
			// 
			this->contactTimeStimLabel->AutoSize = true;
			this->contactTimeStimLabel->Location = System::Drawing::Point(87, 48);
			this->contactTimeStimLabel->Name = L"contactTimeStimLabel";
			this->contactTimeStimLabel->Size = System::Drawing::Size(95, 13);
			this->contactTimeStimLabel->TabIndex = 26;
			this->contactTimeStimLabel->Text = L"% Time in Contact:";
			// 
			// periodStimLabel
			// 
			this->periodStimLabel->AutoSize = true;
			this->periodStimLabel->Location = System::Drawing::Point(87, 22);
			this->periodStimLabel->Name = L"periodStimLabel";
			this->periodStimLabel->Size = System::Drawing::Size(40, 13);
			this->periodStimLabel->TabIndex = 25;
			this->periodStimLabel->Text = L"Period:";
			// 
			// magnitudeStimUnitLabel
			// 
			this->magnitudeStimUnitLabel->AutoSize = true;
			this->magnitudeStimUnitLabel->Location = System::Drawing::Point(298, 102);
			this->magnitudeStimUnitLabel->Name = L"magnitudeStimUnitLabel";
			this->magnitudeStimUnitLabel->Size = System::Drawing::Size(41, 13);
			this->magnitudeStimUnitLabel->TabIndex = 24;
			this->magnitudeStimUnitLabel->Text = L"nN, um";
			// 
			// noCyclesStimUnitLabel
			// 
			this->noCyclesStimUnitLabel->AutoSize = true;
			this->noCyclesStimUnitLabel->Location = System::Drawing::Point(298, 74);
			this->noCyclesStimUnitLabel->Name = L"noCyclesStimUnitLabel";
			this->noCyclesStimUnitLabel->Size = System::Drawing::Size(37, 13);
			this->noCyclesStimUnitLabel->TabIndex = 23;
			this->noCyclesStimUnitLabel->Text = L"cycles";
			// 
			// periodStimUnitLabel
			// 
			this->periodStimUnitLabel->AutoSize = true;
			this->periodStimUnitLabel->Location = System::Drawing::Point(298, 22);
			this->periodStimUnitLabel->Name = L"periodStimUnitLabel";
			this->periodStimUnitLabel->Size = System::Drawing::Size(12, 13);
			this->periodStimUnitLabel->TabIndex = 21;
			this->periodStimUnitLabel->Text = L"s";
			// 
			// stimulusTypeGroupBox
			// 
			this->stimulusTypeGroupBox->Controls->Add(this->customTypeRadioButton);
			this->stimulusTypeGroupBox->Controls->Add(this->sineTypeRadioButton);
			this->stimulusTypeGroupBox->Controls->Add(this->triangleTypeRadioButton);
			this->stimulusTypeGroupBox->Controls->Add(this->squareTypeRadioButton);
			this->stimulusTypeGroupBox->Location = System::Drawing::Point(7, 20);
			this->stimulusTypeGroupBox->Name = L"stimulusTypeGroupBox";
			this->stimulusTypeGroupBox->Size = System::Drawing::Size(74, 115);
			this->stimulusTypeGroupBox->TabIndex = 26;
			this->stimulusTypeGroupBox->TabStop = false;
			this->stimulusTypeGroupBox->Text = L"Type";
			// 
			// customTypeRadioButton
			// 
			this->customTypeRadioButton->AutoSize = true;
			this->customTypeRadioButton->Location = System::Drawing::Point(7, 92);
			this->customTypeRadioButton->Name = L"customTypeRadioButton";
			this->customTypeRadioButton->Size = System::Drawing::Size(60, 17);
			this->customTypeRadioButton->TabIndex = 3;
			this->customTypeRadioButton->Text = L"Custom";
			this->customTypeRadioButton->UseVisualStyleBackColor = true;
			// 
			// sineTypeRadioButton
			// 
			this->sineTypeRadioButton->AutoSize = true;
			this->sineTypeRadioButton->Location = System::Drawing::Point(7, 68);
			this->sineTypeRadioButton->Name = L"sineTypeRadioButton";
			this->sineTypeRadioButton->Size = System::Drawing::Size(46, 17);
			this->sineTypeRadioButton->TabIndex = 2;
			this->sineTypeRadioButton->Text = L"Sine";
			this->sineTypeRadioButton->UseVisualStyleBackColor = true;
			// 
			// triangleTypeRadioButton
			// 
			this->triangleTypeRadioButton->AutoSize = true;
			this->triangleTypeRadioButton->Location = System::Drawing::Point(7, 44);
			this->triangleTypeRadioButton->Name = L"triangleTypeRadioButton";
			this->triangleTypeRadioButton->Size = System::Drawing::Size(63, 17);
			this->triangleTypeRadioButton->TabIndex = 1;
			this->triangleTypeRadioButton->Text = L"Triangle";
			this->triangleTypeRadioButton->UseVisualStyleBackColor = true;
			// 
			// squareTypeRadioButton
			// 
			this->squareTypeRadioButton->AutoSize = true;
			this->squareTypeRadioButton->Checked = true;
			this->squareTypeRadioButton->Location = System::Drawing::Point(7, 20);
			this->squareTypeRadioButton->Name = L"squareTypeRadioButton";
			this->squareTypeRadioButton->Size = System::Drawing::Size(59, 17);
			this->squareTypeRadioButton->TabIndex = 0;
			this->squareTypeRadioButton->TabStop = true;
			this->squareTypeRadioButton->Text = L"Square";
			this->squareTypeRadioButton->UseVisualStyleBackColor = true;
			// 
			// stimulusSignalGroupBox
			// 
			this->stimulusSignalGroupBox->Controls->Add(this->stimulusSignalChart);
			this->stimulusSignalGroupBox->Location = System::Drawing::Point(473, 328);
			this->stimulusSignalGroupBox->Name = L"stimulusSignalGroupBox";
			this->stimulusSignalGroupBox->Size = System::Drawing::Size(667, 200);
			this->stimulusSignalGroupBox->TabIndex = 4;
			this->stimulusSignalGroupBox->TabStop = false;
			this->stimulusSignalGroupBox->Text = L"Stimulus Signal";
			// 
			// stimulusSignalChart
			// 
			this->stimulusSignalChart->BackColor = System::Drawing::SystemColors::Control;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisX->Title = L"Time (s)";
			chartArea1->Name = L"ChartArea1";
			this->stimulusSignalChart->ChartAreas->Add(chartArea1);
			this->stimulusSignalChart->Location = System::Drawing::Point(6, 19);
			this->stimulusSignalChart->Name = L"stimulusSignalChart";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Name = L"Stimulus";
			this->stimulusSignalChart->Series->Add(series1);
			this->stimulusSignalChart->Size = System::Drawing::Size(655, 175);
			this->stimulusSignalChart->TabIndex = 0;
			this->stimulusSignalChart->Text = L"stimulusSignalChart";
			// 
			// dataOutputGroupBox
			// 
			this->dataOutputGroupBox->Controls->Add(this->outputLocationBrowseButton);
			this->dataOutputGroupBox->Controls->Add(this->outputLocationTextBox);
			this->dataOutputGroupBox->Location = System::Drawing::Point(473, 12);
			this->dataOutputGroupBox->Name = L"dataOutputGroupBox";
			this->dataOutputGroupBox->Size = System::Drawing::Size(316, 84);
			this->dataOutputGroupBox->TabIndex = 6;
			this->dataOutputGroupBox->TabStop = false;
			this->dataOutputGroupBox->Text = L"Data Output Location";
			// 
			// outputLocationBrowseButton
			// 
			this->outputLocationBrowseButton->Location = System::Drawing::Point(248, 55);
			this->outputLocationBrowseButton->Name = L"outputLocationBrowseButton";
			this->outputLocationBrowseButton->Size = System::Drawing::Size(55, 23);
			this->outputLocationBrowseButton->TabIndex = 16;
			this->outputLocationBrowseButton->Text = L"Browse";
			this->outputLocationBrowseButton->UseVisualStyleBackColor = true;
			this->outputLocationBrowseButton->Click += gcnew System::EventHandler(this, &SetUpForm::outputLocationBrowseButton_Click);
			// 
			// outputLocationTextBox
			// 
			this->outputLocationTextBox->Location = System::Drawing::Point(6, 30);
			this->outputLocationTextBox->Name = L"outputLocationTextBox";
			this->outputLocationTextBox->Size = System::Drawing::Size(297, 20);
			this->outputLocationTextBox->TabIndex = 15;
			this->outputLocationTextBox->Text = L"C:\\\\Users\\\\HAWK\\\\Documents\\\\HAWKData";
			// 
			// cancelSetupButton
			// 
			this->cancelSetupButton->Location = System::Drawing::Point(1065, 534);
			this->cancelSetupButton->Name = L"cancelSetupButton";
			this->cancelSetupButton->Size = System::Drawing::Size(75, 23);
			this->cancelSetupButton->TabIndex = 37;
			this->cancelSetupButton->Text = L"Cancel";
			this->cancelSetupButton->UseVisualStyleBackColor = true;
			this->cancelSetupButton->Click += gcnew System::EventHandler(this, &SetUpForm::cancelSetupButton_Click);
			// 
			// finishSetupButton
			// 
			this->finishSetupButton->Location = System::Drawing::Point(984, 534);
			this->finishSetupButton->Name = L"finishSetupButton";
			this->finishSetupButton->Size = System::Drawing::Size(75, 23);
			this->finishSetupButton->TabIndex = 36;
			this->finishSetupButton->Text = L"OK";
			this->finishSetupButton->UseVisualStyleBackColor = true;
			this->finishSetupButton->Click += gcnew System::EventHandler(this, &SetUpForm::finishSetupButton_Click);
			// 
			// customStimOpenFileDialog
			// 
			this->customStimOpenFileDialog->InitialDirectory = L"C:\\Users\\Eileen Mazzochette\\Desktop\\Saved Stimuli";
			// 
			// experimentInfoGroupBox
			// 
			this->experimentInfoGroupBox->Controls->Add(this->postStimRecordTimeUnitLabel);
			this->experimentInfoGroupBox->Controls->Add(this->experimentNumberLabel);
			this->experimentInfoGroupBox->Controls->Add(this->slideNumberLabel);
			this->experimentInfoGroupBox->Controls->Add(this->postStimRecordTimeLabel);
			this->experimentInfoGroupBox->Controls->Add(this->experimentNumericUpDown);
			this->experimentInfoGroupBox->Controls->Add(this->slideNumberNumericUpDown);
			this->experimentInfoGroupBox->Controls->Add(this->postStimRecordTimeNumericUpDown);
			this->experimentInfoGroupBox->Controls->Add(this->preStimRecordTimeNumericUpDown);
			this->experimentInfoGroupBox->Controls->Add(this->preStimRecordTimeUnitLabel);
			this->experimentInfoGroupBox->Controls->Add(this->preStimRecordTimeLabel);
			this->experimentInfoGroupBox->Controls->Add(this->wormFoodStatusComboBox);
			this->experimentInfoGroupBox->Controls->Add(this->wormFoodStatusLabel);
			this->experimentInfoGroupBox->Controls->Add(this->ambientTemperatureNumericUpDown);
			this->experimentInfoGroupBox->Controls->Add(this->ambientHumidityNumericUpDown);
			this->experimentInfoGroupBox->Controls->Add(this->percentAgarNumericUpDown);
			this->experimentInfoGroupBox->Controls->Add(this->percentAgarUnitLabel);
			this->experimentInfoGroupBox->Controls->Add(this->ambientHumidityUnitLabel);
			this->experimentInfoGroupBox->Controls->Add(this->ambientTemperatureUnitLabel);
			this->experimentInfoGroupBox->Controls->Add(this->otherInfoTextBox);
			this->experimentInfoGroupBox->Controls->Add(this->wormGenderComboBox);
			this->experimentInfoGroupBox->Controls->Add(this->wormTreatmentsTextBox);
			this->experimentInfoGroupBox->Controls->Add(this->wormStrainTextBox);
			this->experimentInfoGroupBox->Controls->Add(this->experimentTitleTextBox);
			this->experimentInfoGroupBox->Controls->Add(this->wormAgeComboBox);
			this->experimentInfoGroupBox->Controls->Add(this->otherInfoLabel);
			this->experimentInfoGroupBox->Controls->Add(this->wormAgeLabel);
			this->experimentInfoGroupBox->Controls->Add(this->wormGenderLabel);
			this->experimentInfoGroupBox->Controls->Add(this->percentAgarLabel);
			this->experimentInfoGroupBox->Controls->Add(this->ambientTemperatureLabel);
			this->experimentInfoGroupBox->Controls->Add(this->ambientHumidityLabel);
			this->experimentInfoGroupBox->Controls->Add(this->wormTreatmentsLabel);
			this->experimentInfoGroupBox->Controls->Add(this->wormStrainLabel);
			this->experimentInfoGroupBox->Controls->Add(this->experimentTitleLabel);
			this->experimentInfoGroupBox->Location = System::Drawing::Point(4, 12);
			this->experimentInfoGroupBox->Name = L"experimentInfoGroupBox";
			this->experimentInfoGroupBox->Size = System::Drawing::Size(324, 483);
			this->experimentInfoGroupBox->TabIndex = 9;
			this->experimentInfoGroupBox->TabStop = false;
			this->experimentInfoGroupBox->Text = L"Experiment Information";
			// 
			// postStimRecordTimeUnitLabel
			// 
			this->postStimRecordTimeUnitLabel->AutoSize = true;
			this->postStimRecordTimeUnitLabel->Location = System::Drawing::Point(192, 287);
			this->postStimRecordTimeUnitLabel->Name = L"postStimRecordTimeUnitLabel";
			this->postStimRecordTimeUnitLabel->Size = System::Drawing::Size(97, 13);
			this->postStimRecordTimeUnitLabel->TabIndex = 36;
			this->postStimRecordTimeUnitLabel->Text = L"s - assuming 12 fps";
			// 
			// experimentNumberLabel
			// 
			this->experimentNumberLabel->AutoSize = true;
			this->experimentNumberLabel->Location = System::Drawing::Point(4, 334);
			this->experimentNumberLabel->Name = L"experimentNumberLabel";
			this->experimentNumberLabel->Size = System::Drawing::Size(102, 26);
			this->experimentNumberLabel->TabIndex = 35;
			this->experimentNumberLabel->Text = L"Experiment Number \r\non this Slide:";
			// 
			// slideNumberLabel
			// 
			this->slideNumberLabel->AutoSize = true;
			this->slideNumberLabel->Location = System::Drawing::Point(4, 313);
			this->slideNumberLabel->Name = L"slideNumberLabel";
			this->slideNumberLabel->Size = System::Drawing::Size(73, 13);
			this->slideNumberLabel->TabIndex = 34;
			this->slideNumberLabel->Text = L"Slide Number:";
			// 
			// postStimRecordTimeLabel
			// 
			this->postStimRecordTimeLabel->AutoSize = true;
			this->postStimRecordTimeLabel->Location = System::Drawing::Point(4, 286);
			this->postStimRecordTimeLabel->Name = L"postStimRecordTimeLabel";
			this->postStimRecordTimeLabel->Size = System::Drawing::Size(137, 13);
			this->postStimRecordTimeLabel->TabIndex = 33;
			this->postStimRecordTimeLabel->Text = L"Post-Stimulus Record Time:";
			// 
			// experimentNumericUpDown
			// 
			this->experimentNumericUpDown->Location = System::Drawing::Point(141, 337);
			this->experimentNumericUpDown->Name = L"experimentNumericUpDown";
			this->experimentNumericUpDown->Size = System::Drawing::Size(45, 20);
			this->experimentNumericUpDown->TabIndex = 32;
			// 
			// slideNumberNumericUpDown
			// 
			this->slideNumberNumericUpDown->Location = System::Drawing::Point(141, 311);
			this->slideNumberNumericUpDown->Name = L"slideNumberNumericUpDown";
			this->slideNumberNumericUpDown->Size = System::Drawing::Size(45, 20);
			this->slideNumberNumericUpDown->TabIndex = 31;
			// 
			// postStimRecordTimeNumericUpDown
			// 
			this->postStimRecordTimeNumericUpDown->Location = System::Drawing::Point(141, 284);
			this->postStimRecordTimeNumericUpDown->Name = L"postStimRecordTimeNumericUpDown";
			this->postStimRecordTimeNumericUpDown->Size = System::Drawing::Size(45, 20);
			this->postStimRecordTimeNumericUpDown->TabIndex = 30;
			this->postStimRecordTimeNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			// 
			// preStimRecordTimeNumericUpDown
			// 
			this->preStimRecordTimeNumericUpDown->Location = System::Drawing::Point(141, 257);
			this->preStimRecordTimeNumericUpDown->Name = L"preStimRecordTimeNumericUpDown";
			this->preStimRecordTimeNumericUpDown->Size = System::Drawing::Size(45, 20);
			this->preStimRecordTimeNumericUpDown->TabIndex = 10;
			this->preStimRecordTimeNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			// 
			// preStimRecordTimeUnitLabel
			// 
			this->preStimRecordTimeUnitLabel->AutoSize = true;
			this->preStimRecordTimeUnitLabel->Location = System::Drawing::Point(192, 259);
			this->preStimRecordTimeUnitLabel->Name = L"preStimRecordTimeUnitLabel";
			this->preStimRecordTimeUnitLabel->Size = System::Drawing::Size(97, 13);
			this->preStimRecordTimeUnitLabel->TabIndex = 29;
			this->preStimRecordTimeUnitLabel->Text = L"s - assuming 12 fps";
			// 
			// preStimRecordTimeLabel
			// 
			this->preStimRecordTimeLabel->AutoSize = true;
			this->preStimRecordTimeLabel->Location = System::Drawing::Point(5, 259);
			this->preStimRecordTimeLabel->Name = L"preStimRecordTimeLabel";
			this->preStimRecordTimeLabel->Size = System::Drawing::Size(132, 13);
			this->preStimRecordTimeLabel->TabIndex = 28;
			this->preStimRecordTimeLabel->Text = L"Pre-Stimulus Record Time:";
			// 
			// wormFoodStatusComboBox
			// 
			this->wormFoodStatusComboBox->FormattingEnabled = true;
			this->wormFoodStatusComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"On", L"Off", L"See Notes"});
			this->wormFoodStatusComboBox->Location = System::Drawing::Point(141, 177);
			this->wormFoodStatusComboBox->Name = L"wormFoodStatusComboBox";
			this->wormFoodStatusComboBox->Size = System::Drawing::Size(169, 21);
			this->wormFoodStatusComboBox->TabIndex = 7;
			this->wormFoodStatusComboBox->Text = L"Off";
			// 
			// wormFoodStatusLabel
			// 
			this->wormFoodStatusLabel->AutoSize = true;
			this->wormFoodStatusLabel->Location = System::Drawing::Point(4, 180);
			this->wormFoodStatusLabel->Name = L"wormFoodStatusLabel";
			this->wormFoodStatusLabel->Size = System::Drawing::Size(98, 13);
			this->wormFoodStatusLabel->TabIndex = 27;
			this->wormFoodStatusLabel->Text = L"Worm Food Status:";
			// 
			// ambientTemperatureNumericUpDown
			// 
			this->ambientTemperatureNumericUpDown->DecimalPlaces = 1;
			this->ambientTemperatureNumericUpDown->Location = System::Drawing::Point(141, 230);
			this->ambientTemperatureNumericUpDown->Name = L"ambientTemperatureNumericUpDown";
			this->ambientTemperatureNumericUpDown->Size = System::Drawing::Size(45, 20);
			this->ambientTemperatureNumericUpDown->TabIndex = 9;
			this->ambientTemperatureNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {22, 0, 0, 0});
			// 
			// ambientHumidityNumericUpDown
			// 
			this->ambientHumidityNumericUpDown->DecimalPlaces = 1;
			this->ambientHumidityNumericUpDown->Location = System::Drawing::Point(141, 204);
			this->ambientHumidityNumericUpDown->Name = L"ambientHumidityNumericUpDown";
			this->ambientHumidityNumericUpDown->Size = System::Drawing::Size(45, 20);
			this->ambientHumidityNumericUpDown->TabIndex = 8;
			this->ambientHumidityNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {25, 0, 0, 0});
			// 
			// percentAgarNumericUpDown
			// 
			this->percentAgarNumericUpDown->Location = System::Drawing::Point(141, 98);
			this->percentAgarNumericUpDown->Name = L"percentAgarNumericUpDown";
			this->percentAgarNumericUpDown->Size = System::Drawing::Size(45, 20);
			this->percentAgarNumericUpDown->TabIndex = 4;
			this->percentAgarNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			// 
			// percentAgarUnitLabel
			// 
			this->percentAgarUnitLabel->AutoSize = true;
			this->percentAgarUnitLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->percentAgarUnitLabel->Location = System::Drawing::Point(192, 98);
			this->percentAgarUnitLabel->Name = L"percentAgarUnitLabel";
			this->percentAgarUnitLabel->Size = System::Drawing::Size(20, 16);
			this->percentAgarUnitLabel->TabIndex = 22;
			this->percentAgarUnitLabel->Text = L"%";
			// 
			// ambientHumidityUnitLabel
			// 
			this->ambientHumidityUnitLabel->AutoSize = true;
			this->ambientHumidityUnitLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ambientHumidityUnitLabel->Location = System::Drawing::Point(192, 204);
			this->ambientHumidityUnitLabel->Name = L"ambientHumidityUnitLabel";
			this->ambientHumidityUnitLabel->Size = System::Drawing::Size(20, 16);
			this->ambientHumidityUnitLabel->TabIndex = 21;
			this->ambientHumidityUnitLabel->Text = L"%";
			// 
			// ambientTemperatureUnitLabel
			// 
			this->ambientTemperatureUnitLabel->AutoSize = true;
			this->ambientTemperatureUnitLabel->Location = System::Drawing::Point(192, 232);
			this->ambientTemperatureUnitLabel->Name = L"ambientTemperatureUnitLabel";
			this->ambientTemperatureUnitLabel->Size = System::Drawing::Size(55, 13);
			this->ambientTemperatureUnitLabel->TabIndex = 20;
			this->ambientTemperatureUnitLabel->Text = L"degrees C";
			// 
			// otherInfoTextBox
			// 
			this->otherInfoTextBox->Location = System::Drawing::Point(141, 375);
			this->otherInfoTextBox->Multiline = true;
			this->otherInfoTextBox->Name = L"otherInfoTextBox";
			this->otherInfoTextBox->Size = System::Drawing::Size(169, 96);
			this->otherInfoTextBox->TabIndex = 11;
			// 
			// wormGenderComboBox
			// 
			this->wormGenderComboBox->FormattingEnabled = true;
			this->wormGenderComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Male", L"Hermaphrodite"});
			this->wormGenderComboBox->Location = System::Drawing::Point(141, 123);
			this->wormGenderComboBox->Name = L"wormGenderComboBox";
			this->wormGenderComboBox->Size = System::Drawing::Size(169, 21);
			this->wormGenderComboBox->TabIndex = 5;
			this->wormGenderComboBox->Text = L"Hermaphrodite";
			// 
			// wormTreatmentsTextBox
			// 
			this->wormTreatmentsTextBox->Location = System::Drawing::Point(141, 71);
			this->wormTreatmentsTextBox->Name = L"wormTreatmentsTextBox";
			this->wormTreatmentsTextBox->Size = System::Drawing::Size(169, 20);
			this->wormTreatmentsTextBox->TabIndex = 3;
			// 
			// wormStrainTextBox
			// 
			this->wormStrainTextBox->Location = System::Drawing::Point(141, 45);
			this->wormStrainTextBox->Name = L"wormStrainTextBox";
			this->wormStrainTextBox->Size = System::Drawing::Size(169, 20);
			this->wormStrainTextBox->TabIndex = 2;
			// 
			// experimentTitleTextBox
			// 
			this->experimentTitleTextBox->Location = System::Drawing::Point(141, 19);
			this->experimentTitleTextBox->Name = L"experimentTitleTextBox";
			this->experimentTitleTextBox->Size = System::Drawing::Size(169, 20);
			this->experimentTitleTextBox->TabIndex = 1;
			// 
			// wormAgeComboBox
			// 
			this->wormAgeComboBox->FormattingEnabled = true;
			this->wormAgeComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"L1", L"L2", L"L3", L"L4", L"Adult"});
			this->wormAgeComboBox->Location = System::Drawing::Point(141, 150);
			this->wormAgeComboBox->Name = L"wormAgeComboBox";
			this->wormAgeComboBox->Size = System::Drawing::Size(169, 21);
			this->wormAgeComboBox->TabIndex = 6;
			this->wormAgeComboBox->Text = L"L4";
			// 
			// otherInfoLabel
			// 
			this->otherInfoLabel->AutoSize = true;
			this->otherInfoLabel->Location = System::Drawing::Point(4, 375);
			this->otherInfoLabel->Name = L"otherInfoLabel";
			this->otherInfoLabel->Size = System::Drawing::Size(122, 13);
			this->otherInfoLabel->TabIndex = 8;
			this->otherInfoLabel->Text = L"Other Experiment Notes:";
			// 
			// wormAgeLabel
			// 
			this->wormAgeLabel->AutoSize = true;
			this->wormAgeLabel->Location = System::Drawing::Point(4, 153);
			this->wormAgeLabel->Name = L"wormAgeLabel";
			this->wormAgeLabel->Size = System::Drawing::Size(60, 13);
			this->wormAgeLabel->TabIndex = 7;
			this->wormAgeLabel->Text = L"Worm Age:";
			// 
			// wormGenderLabel
			// 
			this->wormGenderLabel->AutoSize = true;
			this->wormGenderLabel->Location = System::Drawing::Point(5, 125);
			this->wormGenderLabel->Name = L"wormGenderLabel";
			this->wormGenderLabel->Size = System::Drawing::Size(76, 13);
			this->wormGenderLabel->TabIndex = 6;
			this->wormGenderLabel->Text = L"Worm Gender:";
			// 
			// percentAgarLabel
			// 
			this->percentAgarLabel->AutoSize = true;
			this->percentAgarLabel->Location = System::Drawing::Point(4, 101);
			this->percentAgarLabel->Name = L"percentAgarLabel";
			this->percentAgarLabel->Size = System::Drawing::Size(43, 13);
			this->percentAgarLabel->TabIndex = 5;
			this->percentAgarLabel->Text = L"% Agar:";
			// 
			// ambientTemperatureLabel
			// 
			this->ambientTemperatureLabel->AutoSize = true;
			this->ambientTemperatureLabel->Location = System::Drawing::Point(4, 233);
			this->ambientTemperatureLabel->Name = L"ambientTemperatureLabel";
			this->ambientTemperatureLabel->Size = System::Drawing::Size(111, 13);
			this->ambientTemperatureLabel->TabIndex = 4;
			this->ambientTemperatureLabel->Text = L"Ambient Temperature:";
			// 
			// ambientHumidityLabel
			// 
			this->ambientHumidityLabel->AutoSize = true;
			this->ambientHumidityLabel->Location = System::Drawing::Point(4, 206);
			this->ambientHumidityLabel->Name = L"ambientHumidityLabel";
			this->ambientHumidityLabel->Size = System::Drawing::Size(91, 13);
			this->ambientHumidityLabel->TabIndex = 3;
			this->ambientHumidityLabel->Text = L"Ambient Humidity:";
			// 
			// wormTreatmentsLabel
			// 
			this->wormTreatmentsLabel->AutoSize = true;
			this->wormTreatmentsLabel->Location = System::Drawing::Point(4, 73);
			this->wormTreatmentsLabel->Name = L"wormTreatmentsLabel";
			this->wormTreatmentsLabel->Size = System::Drawing::Size(94, 13);
			this->wormTreatmentsLabel->TabIndex = 2;
			this->wormTreatmentsLabel->Text = L"Worm Treatments:";
			// 
			// wormStrainLabel
			// 
			this->wormStrainLabel->AutoSize = true;
			this->wormStrainLabel->Location = System::Drawing::Point(4, 49);
			this->wormStrainLabel->Name = L"wormStrainLabel";
			this->wormStrainLabel->Size = System::Drawing::Size(71, 13);
			this->wormStrainLabel->TabIndex = 1;
			this->wormStrainLabel->Text = L"Worm Strain: ";
			// 
			// experimentTitleLabel
			// 
			this->experimentTitleLabel->AutoSize = true;
			this->experimentTitleLabel->Location = System::Drawing::Point(4, 22);
			this->experimentTitleLabel->Name = L"experimentTitleLabel";
			this->experimentTitleLabel->Size = System::Drawing::Size(85, 13);
			this->experimentTitleLabel->TabIndex = 0;
			this->experimentTitleLabel->Text = L"Experiment Title:";
			// 
			// cantileverGroupBox
			// 
			this->cantileverGroupBox->Controls->Add(this->dParameterLabel);
			this->cantileverGroupBox->Controls->Add(this->iParameterLabel);
			this->cantileverGroupBox->Controls->Add(this->pParameterLabel);
			this->cantileverGroupBox->Controls->Add(this->controlParametersLabel);
			this->cantileverGroupBox->Controls->Add(this->dParameterNumericUpDown);
			this->cantileverGroupBox->Controls->Add(this->iParameterNumericUpDown);
			this->cantileverGroupBox->Controls->Add(this->pParameterNumericUpDown);
			this->cantileverGroupBox->Controls->Add(this->cantileverSensitivityNumericUpDown);
			this->cantileverGroupBox->Controls->Add(this->cantileverStiffnessNumericUpDown);
			this->cantileverGroupBox->Controls->Add(this->cantileverFrequencyNumericUpDown);
			this->cantileverGroupBox->Controls->Add(this->deviceIDExampleLabel);
			this->cantileverGroupBox->Controls->Add(this->waferIDExampleLabel);
			this->cantileverGroupBox->Controls->Add(this->deviceIDLabel);
			this->cantileverGroupBox->Controls->Add(this->deviceIDTextBox);
			this->cantileverGroupBox->Controls->Add(this->cantileverSpecLabel);
			this->cantileverGroupBox->Controls->Add(this->waferIDLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverSensitivityUnitLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverSensitivityLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverStiffnessUnitLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverFreqUnitLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverStiffnessLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverFrequencyLabel);
			this->cantileverGroupBox->Controls->Add(this->waferIDTextBox);
			this->cantileverGroupBox->Controls->Add(this->cantileverIDSearchButton);
			this->cantileverGroupBox->Enabled = false;
			this->cantileverGroupBox->Location = System::Drawing::Point(473, 101);
			this->cantileverGroupBox->Name = L"cantileverGroupBox";
			this->cantileverGroupBox->Size = System::Drawing::Size(316, 222);
			this->cantileverGroupBox->TabIndex = 10;
			this->cantileverGroupBox->TabStop = false;
			this->cantileverGroupBox->Text = L"Cantilever Information";
			// 
			// dParameterLabel
			// 
			this->dParameterLabel->AutoSize = true;
			this->dParameterLabel->Location = System::Drawing::Point(207, 178);
			this->dParameterLabel->Name = L"dParameterLabel";
			this->dParameterLabel->Size = System::Drawing::Size(18, 13);
			this->dParameterLabel->TabIndex = 35;
			this->dParameterLabel->Text = L"D:";
			// 
			// iParameterLabel
			// 
			this->iParameterLabel->AutoSize = true;
			this->iParameterLabel->Location = System::Drawing::Point(207, 151);
			this->iParameterLabel->Name = L"iParameterLabel";
			this->iParameterLabel->Size = System::Drawing::Size(13, 13);
			this->iParameterLabel->TabIndex = 34;
			this->iParameterLabel->Text = L"I:";
			// 
			// pParameterLabel
			// 
			this->pParameterLabel->AutoSize = true;
			this->pParameterLabel->Location = System::Drawing::Point(207, 126);
			this->pParameterLabel->Name = L"pParameterLabel";
			this->pParameterLabel->Size = System::Drawing::Size(17, 13);
			this->pParameterLabel->TabIndex = 33;
			this->pParameterLabel->Text = L"P:";
			// 
			// controlParametersLabel
			// 
			this->controlParametersLabel->AutoSize = true;
			this->controlParametersLabel->Location = System::Drawing::Point(204, 102);
			this->controlParametersLabel->Name = L"controlParametersLabel";
			this->controlParametersLabel->Size = System::Drawing::Size(99, 13);
			this->controlParametersLabel->TabIndex = 32;
			this->controlParametersLabel->Text = L"Control Parameters:";
			// 
			// dParameterNumericUpDown
			// 
			this->dParameterNumericUpDown->DecimalPlaces = 5;
			this->dParameterNumericUpDown->Location = System::Drawing::Point(230, 175);
			this->dParameterNumericUpDown->Name = L"dParameterNumericUpDown";
			this->dParameterNumericUpDown->Size = System::Drawing::Size(73, 20);
			this->dParameterNumericUpDown->TabIndex = 25;
			// 
			// iParameterNumericUpDown
			// 
			this->iParameterNumericUpDown->DecimalPlaces = 5;
			this->iParameterNumericUpDown->Location = System::Drawing::Point(230, 149);
			this->iParameterNumericUpDown->Name = L"iParameterNumericUpDown";
			this->iParameterNumericUpDown->Size = System::Drawing::Size(73, 20);
			this->iParameterNumericUpDown->TabIndex = 24;
			// 
			// pParameterNumericUpDown
			// 
			this->pParameterNumericUpDown->DecimalPlaces = 5;
			this->pParameterNumericUpDown->Location = System::Drawing::Point(230, 123);
			this->pParameterNumericUpDown->Name = L"pParameterNumericUpDown";
			this->pParameterNumericUpDown->Size = System::Drawing::Size(73, 20);
			this->pParameterNumericUpDown->TabIndex = 23;
			// 
			// cantileverSensitivityNumericUpDown
			// 
			this->cantileverSensitivityNumericUpDown->DecimalPlaces = 5;
			this->cantileverSensitivityNumericUpDown->Location = System::Drawing::Point(66, 175);
			this->cantileverSensitivityNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
			this->cantileverSensitivityNumericUpDown->Name = L"cantileverSensitivityNumericUpDown";
			this->cantileverSensitivityNumericUpDown->Size = System::Drawing::Size(80, 20);
			this->cantileverSensitivityNumericUpDown->TabIndex = 22;
			// 
			// cantileverStiffnessNumericUpDown
			// 
			this->cantileverStiffnessNumericUpDown->DecimalPlaces = 5;
			this->cantileverStiffnessNumericUpDown->Location = System::Drawing::Point(66, 149);
			this->cantileverStiffnessNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->cantileverStiffnessNumericUpDown->Name = L"cantileverStiffnessNumericUpDown";
			this->cantileverStiffnessNumericUpDown->Size = System::Drawing::Size(80, 20);
			this->cantileverStiffnessNumericUpDown->TabIndex = 21;
			// 
			// cantileverFrequencyNumericUpDown
			// 
			this->cantileverFrequencyNumericUpDown->DecimalPlaces = 4;
			this->cantileverFrequencyNumericUpDown->Location = System::Drawing::Point(66, 123);
			this->cantileverFrequencyNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
			this->cantileverFrequencyNumericUpDown->Name = L"cantileverFrequencyNumericUpDown";
			this->cantileverFrequencyNumericUpDown->Size = System::Drawing::Size(80, 20);
			this->cantileverFrequencyNumericUpDown->TabIndex = 20;
			// 
			// deviceIDExampleLabel
			// 
			this->deviceIDExampleLabel->AutoSize = true;
			this->deviceIDExampleLabel->Location = System::Drawing::Point(262, 48);
			this->deviceIDExampleLabel->Name = L"deviceIDExampleLabel";
			this->deviceIDExampleLabel->Size = System::Drawing::Size(41, 13);
			this->deviceIDExampleLabel->TabIndex = 16;
			this->deviceIDExampleLabel->Text = L"(####)";
			// 
			// waferIDExampleLabel
			// 
			this->waferIDExampleLabel->AutoSize = true;
			this->waferIDExampleLabel->Location = System::Drawing::Point(262, 22);
			this->waferIDExampleLabel->Name = L"waferIDExampleLabel";
			this->waferIDExampleLabel->Size = System::Drawing::Size(48, 13);
			this->waferIDExampleLabel->TabIndex = 15;
			this->waferIDExampleLabel->Text = L"(AA##A)";
			// 
			// deviceIDLabel
			// 
			this->deviceIDLabel->AutoSize = true;
			this->deviceIDLabel->Location = System::Drawing::Point(6, 48);
			this->deviceIDLabel->Name = L"deviceIDLabel";
			this->deviceIDLabel->Size = System::Drawing::Size(58, 13);
			this->deviceIDLabel->TabIndex = 14;
			this->deviceIDLabel->Text = L"Device ID:";
			// 
			// deviceIDTextBox
			// 
			this->deviceIDTextBox->Location = System::Drawing::Point(141, 45);
			this->deviceIDTextBox->Name = L"deviceIDTextBox";
			this->deviceIDTextBox->Size = System::Drawing::Size(115, 20);
			this->deviceIDTextBox->TabIndex = 18;
			// 
			// cantileverSpecLabel
			// 
			this->cantileverSpecLabel->AutoSize = true;
			this->cantileverSpecLabel->Location = System::Drawing::Point(6, 76);
			this->cantileverSpecLabel->Name = L"cantileverSpecLabel";
			this->cantileverSpecLabel->Size = System::Drawing::Size(126, 13);
			this->cantileverSpecLabel->TabIndex = 12;
			this->cantileverSpecLabel->Text = L"Cantliever Specifications:";
			// 
			// waferIDLabel
			// 
			this->waferIDLabel->AutoSize = true;
			this->waferIDLabel->Location = System::Drawing::Point(6, 22);
			this->waferIDLabel->Name = L"waferIDLabel";
			this->waferIDLabel->Size = System::Drawing::Size(53, 13);
			this->waferIDLabel->TabIndex = 11;
			this->waferIDLabel->Text = L"Wafer ID:";
			// 
			// cantileverSensitivityUnitLabel
			// 
			this->cantileverSensitivityUnitLabel->AutoSize = true;
			this->cantileverSensitivityUnitLabel->Location = System::Drawing::Point(148, 178);
			this->cantileverSensitivityUnitLabel->Name = L"cantileverSensitivityUnitLabel";
			this->cantileverSensitivityUnitLabel->Size = System::Drawing::Size(33, 13);
			this->cantileverSensitivityUnitLabel->TabIndex = 10;
			this->cantileverSensitivityUnitLabel->Text = L"um/V";
			// 
			// cantileverSensitivityLabel
			// 
			this->cantileverSensitivityLabel->AutoSize = true;
			this->cantileverSensitivityLabel->Location = System::Drawing::Point(6, 178);
			this->cantileverSensitivityLabel->Name = L"cantileverSensitivityLabel";
			this->cantileverSensitivityLabel->Size = System::Drawing::Size(57, 13);
			this->cantileverSensitivityLabel->TabIndex = 8;
			this->cantileverSensitivityLabel->Text = L"Sensitivity:";
			// 
			// cantileverStiffnessUnitLabel
			// 
			this->cantileverStiffnessUnitLabel->AutoSize = true;
			this->cantileverStiffnessUnitLabel->Location = System::Drawing::Point(147, 152);
			this->cantileverStiffnessUnitLabel->Name = L"cantileverStiffnessUnitLabel";
			this->cantileverStiffnessUnitLabel->Size = System::Drawing::Size(28, 13);
			this->cantileverStiffnessUnitLabel->TabIndex = 7;
			this->cantileverStiffnessUnitLabel->Text = L"N/m";
			// 
			// cantileverFreqUnitLabel
			// 
			this->cantileverFreqUnitLabel->AutoSize = true;
			this->cantileverFreqUnitLabel->Location = System::Drawing::Point(147, 126);
			this->cantileverFreqUnitLabel->Name = L"cantileverFreqUnitLabel";
			this->cantileverFreqUnitLabel->Size = System::Drawing::Size(26, 13);
			this->cantileverFreqUnitLabel->TabIndex = 6;
			this->cantileverFreqUnitLabel->Text = L"kHz";
			// 
			// cantileverStiffnessLabel
			// 
			this->cantileverStiffnessLabel->AutoSize = true;
			this->cantileverStiffnessLabel->Location = System::Drawing::Point(6, 152);
			this->cantileverStiffnessLabel->Name = L"cantileverStiffnessLabel";
			this->cantileverStiffnessLabel->Size = System::Drawing::Size(50, 13);
			this->cantileverStiffnessLabel->TabIndex = 3;
			this->cantileverStiffnessLabel->Text = L"Stiffness:";
			// 
			// cantileverFrequencyLabel
			// 
			this->cantileverFrequencyLabel->AutoSize = true;
			this->cantileverFrequencyLabel->Location = System::Drawing::Point(6, 126);
			this->cantileverFrequencyLabel->Name = L"cantileverFrequencyLabel";
			this->cantileverFrequencyLabel->Size = System::Drawing::Size(60, 13);
			this->cantileverFrequencyLabel->TabIndex = 2;
			this->cantileverFrequencyLabel->Text = L"Frequency:";
			// 
			// waferIDTextBox
			// 
			this->waferIDTextBox->Location = System::Drawing::Point(141, 19);
			this->waferIDTextBox->Name = L"waferIDTextBox";
			this->waferIDTextBox->Size = System::Drawing::Size(115, 20);
			this->waferIDTextBox->TabIndex = 17;
			// 
			// cantileverIDSearchButton
			// 
			this->cantileverIDSearchButton->Location = System::Drawing::Point(141, 71);
			this->cantileverIDSearchButton->Name = L"cantileverIDSearchButton";
			this->cantileverIDSearchButton->Size = System::Drawing::Size(169, 23);
			this->cantileverIDSearchButton->TabIndex = 19;
			this->cantileverIDSearchButton->Text = L"Extract From Spreadsheet";
			this->cantileverIDSearchButton->UseVisualStyleBackColor = true;
			this->cantileverIDSearchButton->Click += gcnew System::EventHandler(this, &SetUpForm::cantileverIDSearchButton_Click);
			// 
			// saveStimFileDialog
			// 
			this->saveStimFileDialog->InitialDirectory = L"C:\\Users\\HAWK\\Documents\\HAWKData";
			// 
			// SetUpForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1150, 564);
			this->Controls->Add(this->cantileverGroupBox);
			this->Controls->Add(this->experimentInfoGroupBox);
			this->Controls->Add(this->finishSetupButton);
			this->Controls->Add(this->cancelSetupButton);
			this->Controls->Add(this->stimulusSignalGroupBox);
			this->Controls->Add(this->dataOutputGroupBox);
			this->Controls->Add(this->stimulusInfoGroupBox);
			this->Controls->Add(this->targetGroupBox);
			this->Controls->Add(this->clampModeGroupBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"SetUpForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Experiment Set Up";
			this->clampModeGroupBox->ResumeLayout(false);
			this->clampModeGroupBox->PerformLayout();
			this->targetGroupBox->ResumeLayout(false);
			this->targetGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->targetWormPictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->targetNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->targetTrackBar))->EndInit();
			this->stimulusInfoGroupBox->ResumeLayout(false);
			this->stimulusInfoGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->postStimZeroPulseNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimSineBiasNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimSineFreqNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimScaleNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimMagnitudeNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimNoCyclesNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimContactTimeNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimPeriodNumericUpDown))->EndInit();
			this->stimulusTypeGroupBox->ResumeLayout(false);
			this->stimulusTypeGroupBox->PerformLayout();
			this->stimulusSignalGroupBox->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimulusSignalChart))->EndInit();
			this->dataOutputGroupBox->ResumeLayout(false);
			this->dataOutputGroupBox->PerformLayout();
			this->experimentInfoGroupBox->ResumeLayout(false);
			this->experimentInfoGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->experimentNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->slideNumberNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->postStimRecordTimeNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->preStimRecordTimeNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ambientTemperatureNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ambientHumidityNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->percentAgarNumericUpDown))->EndInit();
			this->cantileverGroupBox->ResumeLayout(false);
			this->cantileverGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dParameterNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->iParameterNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pParameterNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverSensitivityNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverStiffnessNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverFrequencyNumericUpDown))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


private:
	/* Function: finishSetupButton_Click
	 * ---------------------------------
	 * Click event handler to finish setting up the experiment. If the form is
	 * complete the contained data is output to the experiment object. The YAML
	 * and Video data writers are set up.
	 */
	System::Void finishSetupButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (formIsComplete()) {
			populateExperimentFromForm();
			
			//retrieve info from FPGA and display to user:
			String^ fpgaData = "Current Parameters Stored in the FPGA: " + System::Environment::NewLine;
			fpgaData = String::Concat(fpgaData,"P Parameter: ", (gcnew System::Double(comm->P_Parameter))->ToString()) + System::Environment::NewLine;
			fpgaData = String::Concat(fpgaData, "I Parameter: ", (gcnew System::Double(comm->I_Parameter))->ToString()) + System::Environment::NewLine;
			fpgaData = String::Concat(fpgaData, "D Parameter: ", (gcnew System::Double(comm->D_Parameter))->ToString()) + System::Environment::NewLine;
			if (comm->clampModeParameter == 2)
				fpgaData = String::Concat(fpgaData, "Clamp Mode: Force clamp") + System::Environment::NewLine;
			else if (comm->clampModeParameter == 1)
				fpgaData = String::Concat(fpgaData, "Clamp Mode: Displacement clamp") + System::Environment::NewLine;
			else 
				fpgaData = String::Concat(fpgaData, "Clamp Mode: Open Loop") + System::Environment::NewLine;

			//fpgaData = String::Concat(fpgaData, "Clamp Mode: ", (gcnew System::Double(comm->clampModeParameter))->ToString()) + System::Environment::NewLine;
			fpgaData = String::Concat(fpgaData, "Trigger Mode: ", (gcnew System::Double(comm->triggerModeParameter))->ToString()) + System::Environment::NewLine;
			fpgaData = String::Concat(fpgaData, "Acquisition Frequency: ", (gcnew System::Double(comm->acquisitionFreqParameter))->ToString()) + System::Environment::NewLine;
			fpgaData = String::Concat(fpgaData, "Actuator Frequency: ", (gcnew System::Double(comm->actuatorFreqParameter))->ToString()) + System::Environment::NewLine;
			if (comm->waveTablePresentParameter == 1)
				fpgaData = String::Concat(fpgaData, "Wave Table Present: Yes") + System::Environment::NewLine;
			else 
				fpgaData = String::Concat(fpgaData, "Wave Table Present: No") + System::Environment::NewLine;
			//fpgaData = String::Concat(fpgaData, "Wave Table Present: ", (gcnew System::Double(comm->waveTablePresentParameter))->ToString()) + System::Environment::NewLine;
			MessageBox::Show(fpgaData);
			

			//int dataOutputError = experiment->setUpDataOutput();
			//if (dataOutputError == AVI_OPEN_ERROR) {
			//	MessageBox::Show("There was an error creating a writable AVI file.");
			//} else if (dataOutputError == YAML_OPEN_ERROR) {
			//	MessageBox::Show("There was an error creating a writable YAML file.");
			//} else {
				this->DialogResult = Windows::Forms::DialogResult::OK;
				this->Close();
			//}
		}



	}

	/* Function: cancelSetupButton_Click
	 * ---------------------------------
	 * Click event handler to cancel setting up the experiment. The form
	 * result is set to cancel and the form is closed.
	 */
	System::Void cancelSetupButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
		this->Close();
	}

	/* Function: formIsComplete
	 * ------------------------
	 * Returns true is all neccessary parts of the form are completed. Provides
	 * dialogs indicating those that are not.
	 */
	bool formIsComplete(void)
	{
		//First check all parameters
		if (outputLocationTextBox->Text->Length == 0) {
			MessageBox::Show("Please provide an output location for the experiment data.");
			return false;
		} else if (experimentTitleTextBox->Text->Length == 0) {
			MessageBox::Show("Please provide a title for the experiment.");
			return false;
		} else if (wormStrainTextBox->Text->Length == 0) {
			MessageBox::Show("Please specify the worm strain.");
			return false;
		} else if (wormTreatmentsTextBox->Text->Length == 0) {
			MessageBox::Show("Please specify any worm treatments. Enter none if applicable.");
			return false;
		} else if (percentAgarNumericUpDown->Value.Equals(Decimal(0))) {
			MessageBox::Show("Please specify the percent agar that the worm is crawling on.");
			return false;
		} else if (wormGenderComboBox->Text->Length == 0) {
			MessageBox::Show("Please specify the worm gender.");
			return false;
		} else if (wormFoodStatusComboBox->Text->Length == 0) {
			MessageBox::Show("Please specify the food status of the worm.");
			return false;
		} else if (ambientTemperatureNumericUpDown->Value.Equals(Decimal(0))) {
			MessageBox::Show("Please specify the current ambient temperature.");
			return false;
		} else if (ambientHumidityNumericUpDown->Value.Equals(Decimal(0))) {
			MessageBox::Show("Please specify the current ambient humidity.");
			return false;
		} else if (stimulusSubmitted == false) {
				MessageBox::Show("Please submit a stimulus profile.");
				return false;
		} 
		

		// next check based on operating mode
		if (dispClampRadioButton-> Checked || openLoopClampRadioButton->Checked || forceClampRadioButton->Checked){
			// these must all be true if not in behavior mode
			if (waferIDTextBox->Text->Length == 0){
				MessageBox::Show("Please specify the wafer ID for the cantilever in use.");
				return false;
			} else if (deviceIDTextBox->Text->Length == 0) {
				MessageBox::Show("Please specify the device ID for the cantilever in use.");
				return false;
			} else if(forceClampRadioButton->Checked){
				if (cantileverFrequencyNumericUpDown->Value.Equals(Decimal(0)) ||
				   cantileverStiffnessNumericUpDown->Value.Equals(Decimal(0)) ||
				   cantileverSensitivityNumericUpDown->Value.Equals(Decimal(0))) {
					MessageBox::Show("Please extract or provide the specifications for the cantilever in use.");
					return false;
				} else if (pParameterNumericUpDown->Value.Equals(Decimal(0)) ||
				   iParameterNumericUpDown->Value.Equals(Decimal(0)) ||
				   dParameterNumericUpDown->Value.Equals(Decimal(0))) {
					MessageBox::Show("Please extract or provide the specifications for the PID control.");
					return false;
				}
			} else return true;
			
		} else return true;

		return true;

	}

	/* Function: populateExperimentFromForm
	 * ------------------------------------
	 * Stores all the data from the form in the properties of the experiment.
	 */
	void populateExperimentFromForm(void)
	{
		marshal_context^ context = gcnew marshal_context();

		experiment->dataOutputLocation = context->marshal_as<string>(outputLocationTextBox->Text);

		experiment->experimentTitle = context->marshal_as<string>(experimentTitleTextBox->Text);
		experiment->wormProperties.wormStrain = context->marshal_as<string>(wormStrainTextBox->Text);
		experiment->wormProperties.wormTreatments = context->marshal_as<string>(wormTreatmentsTextBox->Text);
		experiment->wormProperties.percentAgar = Decimal::ToInt32(percentAgarNumericUpDown->Value);
		experiment->wormProperties.wormGender = context->marshal_as<string>(wormGenderComboBox->Text);
		experiment->wormProperties.wormAge = context->marshal_as<string>(wormAgeComboBox->Text);
		experiment->wormProperties.foodStatus = context->marshal_as<string>(wormFoodStatusComboBox->Text);
		experiment->ambientParameters.temperature = Decimal::ToDouble(ambientTemperatureNumericUpDown->Value);
		experiment->ambientParameters.humidity = Decimal::ToDouble(ambientHumidityNumericUpDown->Value);
		experiment->otherInfo = context->marshal_as<string>(otherInfoTextBox->Text);
		
		experiment->waitingBufferSize = Decimal::ToInt32(preStimRecordTimeNumericUpDown->Value); // unit: seconds
		experiment->postWaitingBufferSize = Decimal::ToInt32(postStimRecordTimeNumericUpDown->Value); // unit: seconds
		experiment->experimentPerSlideNumber = Decimal::ToInt32(experimentNumericUpDown->Value);
		experiment->slideNumber = Decimal::ToInt32(slideNumberNumericUpDown->Value);


		experiment->cantileverProperties.serialNumber = context->marshal_as<string>(System::String::Concat(waferIDTextBox->Text, deviceIDTextBox->Text));
		experiment->cantileverProperties.frequency = Decimal::ToDouble(cantileverFrequencyNumericUpDown->Value);
		experiment->cantileverProperties.stiffness = Decimal::ToDouble(cantileverStiffnessNumericUpDown->Value);
		experiment->cantileverProperties.sensitivity = Decimal::ToDouble(cantileverSensitivityNumericUpDown->Value);
		experiment->cantileverProperties.P_parameter = Decimal::ToDouble(pParameterNumericUpDown->Value);
		experiment->cantileverProperties.I_parameter = Decimal::ToDouble(iParameterNumericUpDown->Value);
		experiment->cantileverProperties.D_parameter = Decimal::ToDouble(dParameterNumericUpDown->Value);
		experiment->targetLocation = Decimal::ToDouble(targetNumericUpDown->Value)/100.0;

		if (forceClampRadioButton->Checked)
			experiment->experimentMode = std::string("Force Clamp");
		else if(dispClampRadioButton->Checked)
			experiment->experimentMode = std::string("Displacement Clamp");
		else if(openLoopClampRadioButton->Checked)
			experiment->experimentMode = std::string("Open Loop");
		else 
			experiment->experimentMode = std::string("Behavior Mode");

		experiment->reportedFPGAParameters.P_Parameter = comm->P_Parameter;
		experiment->reportedFPGAParameters.I_Parameter = comm->I_Parameter;
		experiment->reportedFPGAParameters.D_Parameter = comm->D_Parameter;
		experiment->reportedFPGAParameters.clampModeParameter = comm->clampModeParameter;
		experiment->reportedFPGAParameters.triggerModeParameter = comm->triggerModeParameter;
		experiment->reportedFPGAParameters.acquisitionFreqParameter = comm->acquisitionFreqParameter;
		experiment->reportedFPGAParameters.actuatorFreqParameter = comm->actuatorFreqParameter;
		experiment->reportedFPGAParameters.waveTablePresentParameter = comm->waveTablePresentParameter;
		
	}

	/* Function: outputLocationBrowseButton_Click
	 * ------------------------------------------
	 * Click event handler that opens up a browser dialog for setting the output
	 * location of the data files.
	 */
	System::Void outputLocationBrowseButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (outputFolderBrowserDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
			outputLocationTextBox->Text = outputFolderBrowserDialog->SelectedPath;
		}
	}

	/* Function: targetTrackBar_Scroll
	 * -------------------------------
	 * Scroll event handler to keep the target track bar and the target numeric
	 * up down in sych with one another.
	 */
	System::Void targetTrackBar_Scroll(System::Object^  sender, System::EventArgs^  e)
	{
		targetNumericUpDown->Value = Decimal(100 - targetTrackBar->Value);
	}

	/* Function: targetNumericUpDown_ValueChanged
	 * ------------------------------------------
	 * Value changed event handler to keep the target track bar and the target numeric
	 * up down in sych with one another.
	 */
	System::Void targetNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		targetTrackBar->Value = 100 - Decimal::ToInt32(targetNumericUpDown->Value);
	}

	/* Function: cantileverIDSearchButton_Click
	 * ----------------------------------------
	 * Click event handler to get the cantilever properties from the excel spreadsheet
	 * and into the form.
	 */
	System::Void cantileverIDSearchButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		System::String^ waferID = waferIDTextBox->Text;
		System::String^ deviceID = deviceIDTextBox->Text;

		marshal_context^ context = gcnew marshal_context();
		const char* cWaferID = context->marshal_as<const char*>(waferID);
		const char* cDeviceID = context->marshal_as<const char*>(deviceID);

		vector<double> cantileverSpecs = lookUpDevice(cWaferID, cDeviceID);

		if (cantileverSpecs[0] == -1) {
			MessageBox::Show("Please enter a valid WaferID");
		} else if (cantileverSpecs[0] == -2) {
			MessageBox::Show("Please enter a valid DeviceID");
		} else {
			cantileverFrequencyNumericUpDown->Value = Decimal(cantileverSpecs[0]);
			cantileverStiffnessNumericUpDown->Value = Decimal(cantileverSpecs[1]);
			cantileverSensitivityNumericUpDown->Value = Decimal(cantileverSpecs[2]);
			/*Not implemented yet: need to modify the look up specs function.*/
			pParameterNumericUpDown->Value = Decimal(cantileverSpecs[3]);
			iParameterNumericUpDown->Value = Decimal(cantileverSpecs[4]);
			dParameterNumericUpDown->Value = Decimal(cantileverSpecs[5]);
			
		}
	}

	/* Function: submitStimulusButton_Click
	 * ------------------------------------
	 * Click event handler to create a Stimulus object from the information in the
	 * form, plot that stimulus, and send the wave table to the force clamp.
	 */
	System::Void submitStimulusButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		
		// TO DO: Check that you have all the info necessary to create stimulus!
		if (behaviorModeRadioButton->Checked == false && confirmAllStimInfo() == false){
			return;
		}  

		Stimulus stim = createStimulus();
		
		stimulusSignalChart->Series["Stimulus"]->Points->Clear();

		vector<double> waveTable = stim.waveTable;
		int size = waveTable.size();

		//plot on chart
		for (int i = 0; i < size; i++) {
			double value = waveTable[i];
			stimulusSignalChart->Series["Stimulus"]->Points->AddXY(i * DELTA_T, value);
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
		stim.totalTime = stim.totalPoints*DELTA_T; // convert to seconds

		experiment->stim = stim;

		// send all the data to the FPGA:
		//Wave interval - spacing between points on wave table
		comm->sendWaveInterval((int)(DELTA_T*1000000)); // need to convert from s to us for this
		Threading::Thread::Sleep(500);
		//PID parameters:
		int numParams = 4;
		double* parameters = new double[numParams];
		if (forceClampRadioButton->Checked){
			//Send PID parameters:
			parameters[0] = Decimal::ToDouble(pParameterNumericUpDown->Value);
			parameters[1] = Decimal::ToDouble(iParameterNumericUpDown->Value);
			parameters[2] = Decimal::ToDouble(dParameterNumericUpDown->Value);
			parameters[3] = 5; //need to make sure this parameter is OK.
			comm->sendPIDParameters(parameters, numParams);
			Threading::Thread::Sleep(500);
			comm->sendClampMode(2);
		}
		else if(dispClampRadioButton->Checked){
			//Send PID parameters:
			parameters[0] = 0.3;
			parameters[1] = 50;
			parameters[2] = 0.00001;
			parameters[3] = 4; //need to make sure this parameter is OK.
			comm->sendPIDParameters(parameters, numParams);
			Threading::Thread::Sleep(500);
			comm->sendClampMode(1);
		}
		else // in open loop or behavior mode:
			comm->sendClampMode(0);

		Threading::Thread::Sleep(500);

		//Send all the data to FPGA, request info back
		//Send trigger mode
		comm->sendTriggerMode(1);
		//Send data acquisition parameter
		Threading::Thread::Sleep(500);
		comm->sendAcquisitionInterval(1000); // number of us between two points "1000" = 1kHz sampling, min value this can be is 100 ("100" = 10 kHz)
		stimulusSubmitted = true;
	}

	/* Function: customStimBrowseButton_Click
	 * --------------------------------------
	 * Click event handler that opens up a browser dialog for setting the location
	 * of the custom stimulus file to open.
	 */
	System::Void customStimBrowseButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (customStimOpenFileDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
			customStimFileTextBox->Text = customStimOpenFileDialog->FileName;
		}
	}

	/* Function: saveStimButton_Click
	 * ------------------------------
	 * Click event handler that opens up a browser dialog for setting the location
	 * of where to save a stimulus. The current Stimulus is then saved in a YAML format.
	 */
	System::Void saveStimButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (saveStimFileDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
			Stimulus stim = createStimulus();
			marshal_context^ context = gcnew marshal_context();
			stim.saveAsYAML(context->marshal_as<string>(saveStimFileDialog->FileName) + string(".yaml"));
		}
	}

	/* Function: createStimulus
	 * ------------------------
	 * A Stimulus is returned with the wave table of what is currently in the form fields.
	 */
	Stimulus createStimulus(void)
	{
		double period = Decimal::ToDouble(stimPeriodNumericUpDown->Value);
		double contactTime = Decimal::ToDouble(stimContactTimeNumericUpDown->Value);
		int noCycles = Decimal::ToInt32(stimNoCyclesNumericUpDown->Value);
		double magnitude = Decimal::ToDouble(stimMagnitudeNumericUpDown->Value);
		double scale = Decimal::ToDouble(stimScaleNumericUpDown->Value);
		int scaleType = stimScaleTypeDomainUpDown->SelectedIndex;
		double sineFreq = Decimal::ToDouble(stimSineFreqNumericUpDown->Value);
		double sineBias = Decimal::ToDouble(stimSineBiasNumericUpDown->Value);
		double zeroPulse = Decimal::ToDouble(postStimZeroPulseNumericUpDown->Value);

		if(behaviorModeRadioButton->Checked){
			contactTime = 100;
			noCycles = 1;
			magnitude = 1;
			scale = 0;
			scaleType = 0;
			sineFreq = 0;
			sineBias = 0;
		} 
		
		Stimulus stim(period, contactTime, noCycles, magnitude, scale, scaleType, sineFreq, sineBias, zeroPulse);
		
		if (squareTypeRadioButton->Checked) {
			stim.createSquare();
		} else if (triangleTypeRadioButton->Checked) {
			stim.createTriangle();
		} else if (sineTypeRadioButton->Checked) {
			stim.createSine();
		} else if (customTypeRadioButton->Checked) {
			marshal_context^ context = gcnew marshal_context();
			stim.createFromYAML(context->marshal_as<string>(customStimFileTextBox->Text));
		}

		stim.appendZeroPulse(zeroPulse);

		if (forceClampRadioButton->Checked)
			stim.convertToVoltages(1/(Decimal::ToDouble(cantileverSensitivityNumericUpDown->Value) * Decimal::ToDouble(cantileverStiffnessNumericUpDown->Value) * 1000));
		else if(dispClampRadioButton->Checked)
			stim.convertToVoltages(1/ACTUATOR_SENSITIVITY);
		else if(openLoopClampRadioButton->Checked)
			stim.convertToVoltages(1);
		else if (behaviorModeRadioButton->Checked)
			stim.convertToVoltages(1);


		return stim;
	}

	bool confirmAllStimInfo(void){

		// check all necessary stim parameters:
		if (customTypeRadioButton->Checked && customStimFileTextBox->Text->Length <= 0 ){
			MessageBox::Show("Enter a file for a custom stimulus");
			return false;
		}
		else {
			if (stimPeriodNumericUpDown->Value <= 0){
				MessageBox::Show("Please enter the length of the stimulus period");
				return false;
			}
			else if (stimContactTimeNumericUpDown->Value <= 0){
				MessageBox::Show("The amount of time in contact with the worm must be greater than 0.");
				return false;
			}
			else if (stimNoCyclesNumericUpDown->Value < 1){
				MessageBox::Show("Please select at least one stimulus cycle");
				return false;
			}
			else if (stimMagnitudeNumericUpDown->Value <= 0){
				MessageBox::Show("Please enter a magnitude value greater than one");
				return false;
			}
		}

		//check displacment clamp setting
		if(forceClampRadioButton->Checked == false &&
			dispClampRadioButton->Checked == false && 
			openLoopClampRadioButton->Checked == false && 
			behaviorModeRadioButton->Checked == false){
				MessageBox::Show("Please select a clamp mode");
				return false;
		}
		//if in force clamp mode:
		else if (forceClampRadioButton->Checked == true){	
			//check PID parameters
			if(pParameterNumericUpDown->Value.Equals(Decimal(0)) ||
				   iParameterNumericUpDown->Value.Equals(Decimal(0)) ||
				   dParameterNumericUpDown->Value.Equals(Decimal(0))) {
				MessageBox::Show("For force clamp mode, please extract or provide the specifications for the PID control.");
				return false;
			} 
			//check cantilever parameters
			if(cantileverStiffnessNumericUpDown->Value.Equals(Decimal(0)) || 
				cantileverSensitivityNumericUpDown->Value.Equals(Decimal(0))) {
				MessageBox::Show("For force clamp mode, please extract or provide the sensitivity and stiffness of the cantilever.");
				return false;
			} 
		
		} 
		
	
		return true;
	
	}




private: System::Void forceClampRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (forceClampRadioButton->Checked){
				 cantileverGroupBox->Enabled = true;
				 stimulusInfoGroupBox->Enabled = true;
				 targetGroupBox->Enabled = true;
			 }
			  if (forceClampRadioButton->Checked == false){
				 cantileverGroupBox->Enabled = false;
				 stimulusInfoGroupBox->Enabled = false;
				 targetGroupBox->Enabled = false;
			 }

		 }
private: System::Void dispClampRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (dispClampRadioButton->Checked){
				 cantileverGroupBox->Enabled = true;
				 stimulusInfoGroupBox->Enabled = true;
				 targetGroupBox->Enabled = true;
			 }
			 if (dispClampRadioButton->Checked == false){
				 cantileverGroupBox->Enabled = false;
				 stimulusInfoGroupBox->Enabled = false;
				 targetGroupBox->Enabled = false;
			 }
		 }
private: System::Void openLoopClampRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (openLoopClampRadioButton->Checked){
				 cantileverGroupBox->Enabled = true;
				 stimulusInfoGroupBox->Enabled = true;
				 targetGroupBox->Enabled = true;
			 }
			 if (openLoopClampRadioButton->Checked == false){
				 cantileverGroupBox->Enabled = false;
				 stimulusInfoGroupBox->Enabled = false;
				 targetGroupBox->Enabled = false;
			 }
		 }
private: System::Void behaviorModeRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (behaviorModeRadioButton->Checked){
				 cantileverGroupBox->Enabled = false;
				 stimulusInfoGroupBox->Enabled = true;
				 targetGroupBox->Enabled = false;
			 }
			 if (behaviorModeRadioButton->Checked == false){
				 cantileverGroupBox->Enabled = false;
				 stimulusInfoGroupBox->Enabled = false;
				 targetGroupBox->Enabled = false;
			 }
		 }
};
}
