#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include "Experiment.h"
#include "ExcelInterface.h"

namespace BehaviorRig {

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
		SetUpForm(Experiment* exp)
		{
			InitializeComponent();

			this->experiment = exp;
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
	private: System::Windows::Forms::ComboBox^  scaleTypeStimComboBox;
	private: System::Windows::Forms::TextBox^  contactTimeStimTextBox;
	private: System::Windows::Forms::TextBox^  noCyclesStimTextBox;
	private: System::Windows::Forms::TextBox^  magnitudeStimTextBox;
	private: System::Windows::Forms::TextBox^  scaleStimTextBox;
	private: System::Windows::Forms::TextBox^  periodStimTextBox;
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
	private: System::Windows::Forms::TextBox^  sineBiasStimTextBox;
	private: System::Windows::Forms::TextBox^  sineFreqStimTextBox;
	private: System::Windows::Forms::Button^  customStimBrowseButton;
	private: System::Windows::Forms::TextBox^  customStimFileTextBox;
	private: System::Windows::Forms::Label^  customStimFileLabel;
	private: System::Windows::Forms::Label^  contactTimeStimUnitLabel;
	private: System::Windows::Forms::Label^  percentAgarUnitLabel;
	private: System::Windows::Forms::Label^  ambientHumidityUnitLabel;
	private: System::Windows::Forms::Button^  showStimulusButton;
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
			this->saveStimButton = (gcnew System::Windows::Forms::Button());
			this->showStimulusButton = (gcnew System::Windows::Forms::Button());
			this->contactTimeStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->sineBiasStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->sineBiasStimLabel = (gcnew System::Windows::Forms::Label());
			this->sineFreqStimLabel = (gcnew System::Windows::Forms::Label());
			this->sineFreqStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->sineBiasStimTextBox = (gcnew System::Windows::Forms::TextBox());
			this->sineFreqStimTextBox = (gcnew System::Windows::Forms::TextBox());
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
			this->scaleTypeStimComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->contactTimeStimTextBox = (gcnew System::Windows::Forms::TextBox());
			this->noCyclesStimTextBox = (gcnew System::Windows::Forms::TextBox());
			this->magnitudeStimTextBox = (gcnew System::Windows::Forms::TextBox());
			this->scaleStimTextBox = (gcnew System::Windows::Forms::TextBox());
			this->periodStimTextBox = (gcnew System::Windows::Forms::TextBox());
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
			this->stimulusTypeGroupBox->SuspendLayout();
			this->stimulusSignalGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimulusSignalChart))->BeginInit();
			this->dataOutputGroupBox->SuspendLayout();
			this->experimentInfoGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ambientTemperatureNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ambientHumidityNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->percentAgarNumericUpDown))->BeginInit();
			this->cantileverGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverSensitivityNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverStiffnessNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverFrequencyNumericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// clampModeGroupBox
			// 
			this->clampModeGroupBox->Controls->Add(this->dispClampRadioButton);
			this->clampModeGroupBox->Controls->Add(this->forceClampRadioButton);
			this->clampModeGroupBox->Location = System::Drawing::Point(334, 12);
			this->clampModeGroupBox->Name = L"clampModeGroupBox";
			this->clampModeGroupBox->Size = System::Drawing::Size(133, 72);
			this->clampModeGroupBox->TabIndex = 0;
			this->clampModeGroupBox->TabStop = false;
			this->clampModeGroupBox->Text = L"Clamp Mode";
			// 
			// dispClampRadioButton
			// 
			this->dispClampRadioButton->AutoSize = true;
			this->dispClampRadioButton->Location = System::Drawing::Point(7, 44);
			this->dispClampRadioButton->Name = L"dispClampRadioButton";
			this->dispClampRadioButton->Size = System::Drawing::Size(121, 17);
			this->dispClampRadioButton->TabIndex = 1;
			this->dispClampRadioButton->Text = L"Displacement Clamp";
			this->dispClampRadioButton->UseVisualStyleBackColor = true;
			// 
			// forceClampRadioButton
			// 
			this->forceClampRadioButton->AutoSize = true;
			this->forceClampRadioButton->Checked = true;
			this->forceClampRadioButton->Location = System::Drawing::Point(7, 20);
			this->forceClampRadioButton->Name = L"forceClampRadioButton";
			this->forceClampRadioButton->Size = System::Drawing::Size(84, 17);
			this->forceClampRadioButton->TabIndex = 0;
			this->forceClampRadioButton->TabStop = true;
			this->forceClampRadioButton->Text = L"Force Clamp";
			this->forceClampRadioButton->UseVisualStyleBackColor = true;
			// 
			// targetGroupBox
			// 
			this->targetGroupBox->Controls->Add(this->targetTailLabel);
			this->targetGroupBox->Controls->Add(this->targetHeadLabel);
			this->targetGroupBox->Controls->Add(this->targetWormPictureBox);
			this->targetGroupBox->Controls->Add(this->targetNumericUpDown);
			this->targetGroupBox->Controls->Add(this->targetUnitLabel);
			this->targetGroupBox->Controls->Add(this->targetTrackBar);
			this->targetGroupBox->Location = System::Drawing::Point(334, 90);
			this->targetGroupBox->Name = L"targetGroupBox";
			this->targetGroupBox->Size = System::Drawing::Size(133, 285);
			this->targetGroupBox->TabIndex = 2;
			this->targetGroupBox->TabStop = false;
			this->targetGroupBox->Text = L"Target Selection";
			// 
			// targetTailLabel
			// 
			this->targetTailLabel->AutoSize = true;
			this->targetTailLabel->Location = System::Drawing::Point(83, 259);
			this->targetTailLabel->Name = L"targetTailLabel";
			this->targetTailLabel->Size = System::Drawing::Size(31, 13);
			this->targetTailLabel->TabIndex = 27;
			this->targetTailLabel->Text = L"Anus";
			// 
			// targetHeadLabel
			// 
			this->targetHeadLabel->AutoSize = true;
			this->targetHeadLabel->Location = System::Drawing::Point(73, 19);
			this->targetHeadLabel->Name = L"targetHeadLabel";
			this->targetHeadLabel->Size = System::Drawing::Size(45, 13);
			this->targetHeadLabel->TabIndex = 26;
			this->targetHeadLabel->Text = L"Pharynx";
			// 
			// targetWormPictureBox
			// 
			this->targetWormPictureBox->Location = System::Drawing::Point(62, 32);
			this->targetWormPictureBox->Name = L"targetWormPictureBox";
			this->targetWormPictureBox->Size = System::Drawing::Size(67, 224);
			this->targetWormPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->targetWormPictureBox->TabIndex = 17;
			this->targetWormPictureBox->TabStop = false;
			// 
			// targetNumericUpDown
			// 
			this->targetNumericUpDown->Location = System::Drawing::Point(6, 257);
			this->targetNumericUpDown->Name = L"targetNumericUpDown";
			this->targetNumericUpDown->Size = System::Drawing::Size(40, 20);
			this->targetNumericUpDown->TabIndex = 16;
			this->targetNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {50, 0, 0, 0});
			this->targetNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &SetUpForm::targetNumericUpDown_ValueChanged);
			// 
			// targetUnitLabel
			// 
			this->targetUnitLabel->AutoSize = true;
			this->targetUnitLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->targetUnitLabel->Location = System::Drawing::Point(48, 259);
			this->targetUnitLabel->Name = L"targetUnitLabel";
			this->targetUnitLabel->Size = System::Drawing::Size(20, 16);
			this->targetUnitLabel->TabIndex = 15;
			this->targetUnitLabel->Text = L"%";
			// 
			// targetTrackBar
			// 
			this->targetTrackBar->LargeChange = 10;
			this->targetTrackBar->Location = System::Drawing::Point(11, 19);
			this->targetTrackBar->Maximum = 100;
			this->targetTrackBar->Name = L"targetTrackBar";
			this->targetTrackBar->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->targetTrackBar->Size = System::Drawing::Size(45, 237);
			this->targetTrackBar->TabIndex = 0;
			this->targetTrackBar->TickFrequency = 5;
			this->targetTrackBar->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->targetTrackBar->Value = 50;
			this->targetTrackBar->Scroll += gcnew System::EventHandler(this, &SetUpForm::targetTrackBar_Scroll);
			// 
			// stimulusInfoGroupBox
			// 
			this->stimulusInfoGroupBox->Controls->Add(this->saveStimButton);
			this->stimulusInfoGroupBox->Controls->Add(this->showStimulusButton);
			this->stimulusInfoGroupBox->Controls->Add(this->contactTimeStimUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->sineBiasStimUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->sineBiasStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->sineFreqStimLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->sineFreqStimUnitLabel);
			this->stimulusInfoGroupBox->Controls->Add(this->sineBiasStimTextBox);
			this->stimulusInfoGroupBox->Controls->Add(this->sineFreqStimTextBox);
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
			this->stimulusInfoGroupBox->Controls->Add(this->scaleTypeStimComboBox);
			this->stimulusInfoGroupBox->Controls->Add(this->contactTimeStimTextBox);
			this->stimulusInfoGroupBox->Controls->Add(this->noCyclesStimTextBox);
			this->stimulusInfoGroupBox->Controls->Add(this->magnitudeStimTextBox);
			this->stimulusInfoGroupBox->Controls->Add(this->scaleStimTextBox);
			this->stimulusInfoGroupBox->Controls->Add(this->periodStimTextBox);
			this->stimulusInfoGroupBox->Controls->Add(this->stimulusTypeGroupBox);
			this->stimulusInfoGroupBox->Location = System::Drawing::Point(473, 90);
			this->stimulusInfoGroupBox->Name = L"stimulusInfoGroupBox";
			this->stimulusInfoGroupBox->Size = System::Drawing::Size(345, 285);
			this->stimulusInfoGroupBox->TabIndex = 3;
			this->stimulusInfoGroupBox->TabStop = false;
			this->stimulusInfoGroupBox->Text = L"Stimulus Information";
			// 
			// saveStimButton
			// 
			this->saveStimButton->Location = System::Drawing::Point(207, 228);
			this->saveStimButton->Name = L"saveStimButton";
			this->saveStimButton->Size = System::Drawing::Size(132, 23);
			this->saveStimButton->TabIndex = 45;
			this->saveStimButton->Text = L"Save Stimulus";
			this->saveStimButton->UseVisualStyleBackColor = true;
			// 
			// showStimulusButton
			// 
			this->showStimulusButton->Location = System::Drawing::Point(6, 142);
			this->showStimulusButton->Name = L"showStimulusButton";
			this->showStimulusButton->Size = System::Drawing::Size(75, 80);
			this->showStimulusButton->TabIndex = 44;
			this->showStimulusButton->Text = L"Show Stimulus";
			this->showStimulusButton->UseVisualStyleBackColor = true;
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
			// sineBiasStimTextBox
			// 
			this->sineBiasStimTextBox->Location = System::Drawing::Point(207, 202);
			this->sineBiasStimTextBox->Name = L"sineBiasStimTextBox";
			this->sineBiasStimTextBox->Size = System::Drawing::Size(85, 20);
			this->sineBiasStimTextBox->TabIndex = 37;
			// 
			// sineFreqStimTextBox
			// 
			this->sineFreqStimTextBox->Location = System::Drawing::Point(207, 176);
			this->sineFreqStimTextBox->Name = L"sineFreqStimTextBox";
			this->sineFreqStimTextBox->Size = System::Drawing::Size(85, 20);
			this->sineFreqStimTextBox->TabIndex = 36;
			// 
			// customStimBrowseButton
			// 
			this->customStimBrowseButton->Location = System::Drawing::Point(284, 257);
			this->customStimBrowseButton->Name = L"customStimBrowseButton";
			this->customStimBrowseButton->Size = System::Drawing::Size(55, 23);
			this->customStimBrowseButton->TabIndex = 35;
			this->customStimBrowseButton->Text = L"Browse";
			this->customStimBrowseButton->UseVisualStyleBackColor = true;
			// 
			// customStimFileTextBox
			// 
			this->customStimFileTextBox->Location = System::Drawing::Point(7, 259);
			this->customStimFileTextBox->Name = L"customStimFileTextBox";
			this->customStimFileTextBox->Size = System::Drawing::Size(272, 20);
			this->customStimFileTextBox->TabIndex = 34;
			// 
			// customStimFileLabel
			// 
			this->customStimFileLabel->AutoSize = true;
			this->customStimFileLabel->Location = System::Drawing::Point(6, 237);
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
			this->scaleStimLabel->Size = System::Drawing::Size(37, 13);
			this->scaleStimLabel->TabIndex = 29;
			this->scaleStimLabel->Text = L"Scale:";
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
			this->magnitudeStimUnitLabel->Text = L"uN, um";
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
			// scaleTypeStimComboBox
			// 
			this->scaleTypeStimComboBox->FormattingEnabled = true;
			this->scaleTypeStimComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"None", L"Linear", L"Geometric"});
			this->scaleTypeStimComboBox->Location = System::Drawing::Point(207, 149);
			this->scaleTypeStimComboBox->Name = L"scaleTypeStimComboBox";
			this->scaleTypeStimComboBox->Size = System::Drawing::Size(132, 21);
			this->scaleTypeStimComboBox->TabIndex = 14;
			this->scaleTypeStimComboBox->Text = L"None";
			// 
			// contactTimeStimTextBox
			// 
			this->contactTimeStimTextBox->Location = System::Drawing::Point(207, 45);
			this->contactTimeStimTextBox->Name = L"contactTimeStimTextBox";
			this->contactTimeStimTextBox->Size = System::Drawing::Size(85, 20);
			this->contactTimeStimTextBox->TabIndex = 6;
			// 
			// noCyclesStimTextBox
			// 
			this->noCyclesStimTextBox->Location = System::Drawing::Point(207, 71);
			this->noCyclesStimTextBox->Name = L"noCyclesStimTextBox";
			this->noCyclesStimTextBox->Size = System::Drawing::Size(85, 20);
			this->noCyclesStimTextBox->TabIndex = 5;
			// 
			// magnitudeStimTextBox
			// 
			this->magnitudeStimTextBox->Location = System::Drawing::Point(207, 97);
			this->magnitudeStimTextBox->Name = L"magnitudeStimTextBox";
			this->magnitudeStimTextBox->Size = System::Drawing::Size(85, 20);
			this->magnitudeStimTextBox->TabIndex = 4;
			// 
			// scaleStimTextBox
			// 
			this->scaleStimTextBox->Location = System::Drawing::Point(207, 123);
			this->scaleStimTextBox->Name = L"scaleStimTextBox";
			this->scaleStimTextBox->Size = System::Drawing::Size(85, 20);
			this->scaleStimTextBox->TabIndex = 3;
			// 
			// periodStimTextBox
			// 
			this->periodStimTextBox->Location = System::Drawing::Point(207, 19);
			this->periodStimTextBox->Name = L"periodStimTextBox";
			this->periodStimTextBox->Size = System::Drawing::Size(85, 20);
			this->periodStimTextBox->TabIndex = 1;
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
			this->stimulusTypeGroupBox->TabIndex = 0;
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
			this->stimulusSignalGroupBox->Location = System::Drawing::Point(334, 381);
			this->stimulusSignalGroupBox->Name = L"stimulusSignalGroupBox";
			this->stimulusSignalGroupBox->Size = System::Drawing::Size(484, 180);
			this->stimulusSignalGroupBox->TabIndex = 4;
			this->stimulusSignalGroupBox->TabStop = false;
			this->stimulusSignalGroupBox->Text = L"Stimulus Signal";
			// 
			// stimulusSignalChart
			// 
			this->stimulusSignalChart->BackColor = System::Drawing::SystemColors::Control;
			chartArea1->AxisX->Title = L"Time (s)";
			chartArea1->Name = L"ChartArea1";
			this->stimulusSignalChart->ChartAreas->Add(chartArea1);
			this->stimulusSignalChart->Location = System::Drawing::Point(6, 19);
			this->stimulusSignalChart->Name = L"stimulusSignalChart";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Name = L"Series1";
			this->stimulusSignalChart->Series->Add(series1);
			this->stimulusSignalChart->Size = System::Drawing::Size(472, 155);
			this->stimulusSignalChart->TabIndex = 0;
			this->stimulusSignalChart->Text = L"stimulusSignalChart";
			// 
			// dataOutputGroupBox
			// 
			this->dataOutputGroupBox->Controls->Add(this->outputLocationBrowseButton);
			this->dataOutputGroupBox->Controls->Add(this->outputLocationTextBox);
			this->dataOutputGroupBox->Location = System::Drawing::Point(473, 12);
			this->dataOutputGroupBox->Name = L"dataOutputGroupBox";
			this->dataOutputGroupBox->Size = System::Drawing::Size(345, 72);
			this->dataOutputGroupBox->TabIndex = 6;
			this->dataOutputGroupBox->TabStop = false;
			this->dataOutputGroupBox->Text = L"Data Output Location";
			// 
			// outputLocationBrowseButton
			// 
			this->outputLocationBrowseButton->Location = System::Drawing::Point(284, 28);
			this->outputLocationBrowseButton->Name = L"outputLocationBrowseButton";
			this->outputLocationBrowseButton->Size = System::Drawing::Size(55, 23);
			this->outputLocationBrowseButton->TabIndex = 20;
			this->outputLocationBrowseButton->Text = L"Browse";
			this->outputLocationBrowseButton->UseVisualStyleBackColor = true;
			this->outputLocationBrowseButton->Click += gcnew System::EventHandler(this, &SetUpForm::outputLocationBrowseButton_Click);
			// 
			// outputLocationTextBox
			// 
			this->outputLocationTextBox->Location = System::Drawing::Point(6, 30);
			this->outputLocationTextBox->Name = L"outputLocationTextBox";
			this->outputLocationTextBox->Size = System::Drawing::Size(272, 20);
			this->outputLocationTextBox->TabIndex = 1;
			this->outputLocationTextBox->Text = L"C:\\\\Users\\\\Eileen Mazzochette\\\\Desktop\\\\TestFolder\\\\";
			// 
			// cancelSetupButton
			// 
			this->cancelSetupButton->Location = System::Drawing::Point(743, 567);
			this->cancelSetupButton->Name = L"cancelSetupButton";
			this->cancelSetupButton->Size = System::Drawing::Size(75, 23);
			this->cancelSetupButton->TabIndex = 7;
			this->cancelSetupButton->Text = L"Cancel";
			this->cancelSetupButton->UseVisualStyleBackColor = true;
			this->cancelSetupButton->Click += gcnew System::EventHandler(this, &SetUpForm::cancelSetupButton_Click);
			// 
			// finishSetupButton
			// 
			this->finishSetupButton->Location = System::Drawing::Point(662, 567);
			this->finishSetupButton->Name = L"finishSetupButton";
			this->finishSetupButton->Size = System::Drawing::Size(75, 23);
			this->finishSetupButton->TabIndex = 8;
			this->finishSetupButton->Text = L"OK";
			this->finishSetupButton->UseVisualStyleBackColor = true;
			this->finishSetupButton->Click += gcnew System::EventHandler(this, &SetUpForm::finishSetupButton_Click);
			// 
			// customStimOpenFileDialog
			// 
			this->customStimOpenFileDialog->FileName = L"openFileDialog1";
			// 
			// experimentInfoGroupBox
			// 
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
			this->experimentInfoGroupBox->Location = System::Drawing::Point(12, 12);
			this->experimentInfoGroupBox->Name = L"experimentInfoGroupBox";
			this->experimentInfoGroupBox->Size = System::Drawing::Size(316, 363);
			this->experimentInfoGroupBox->TabIndex = 9;
			this->experimentInfoGroupBox->TabStop = false;
			this->experimentInfoGroupBox->Text = L"Experiment Information";
			// 
			// wormFoodStatusComboBox
			// 
			this->wormFoodStatusComboBox->FormattingEnabled = true;
			this->wormFoodStatusComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"on", L"off"});
			this->wormFoodStatusComboBox->Location = System::Drawing::Point(141, 177);
			this->wormFoodStatusComboBox->Name = L"wormFoodStatusComboBox";
			this->wormFoodStatusComboBox->Size = System::Drawing::Size(169, 21);
			this->wormFoodStatusComboBox->TabIndex = 26;
			this->wormFoodStatusComboBox->Text = L"off";
			// 
			// wormFoodStatusLabel
			// 
			this->wormFoodStatusLabel->AutoSize = true;
			this->wormFoodStatusLabel->Location = System::Drawing::Point(6, 180);
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
			this->ambientTemperatureNumericUpDown->TabIndex = 25;
			this->ambientTemperatureNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {22, 0, 0, 0});
			// 
			// ambientHumidityNumericUpDown
			// 
			this->ambientHumidityNumericUpDown->DecimalPlaces = 1;
			this->ambientHumidityNumericUpDown->Location = System::Drawing::Point(141, 204);
			this->ambientHumidityNumericUpDown->Name = L"ambientHumidityNumericUpDown";
			this->ambientHumidityNumericUpDown->Size = System::Drawing::Size(45, 20);
			this->ambientHumidityNumericUpDown->TabIndex = 24;
			this->ambientHumidityNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {25, 0, 0, 0});
			// 
			// percentAgarNumericUpDown
			// 
			this->percentAgarNumericUpDown->Location = System::Drawing::Point(141, 98);
			this->percentAgarNumericUpDown->Name = L"percentAgarNumericUpDown";
			this->percentAgarNumericUpDown->Size = System::Drawing::Size(45, 20);
			this->percentAgarNumericUpDown->TabIndex = 23;
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
			this->otherInfoTextBox->Location = System::Drawing::Point(141, 255);
			this->otherInfoTextBox->Multiline = true;
			this->otherInfoTextBox->Name = L"otherInfoTextBox";
			this->otherInfoTextBox->Size = System::Drawing::Size(169, 102);
			this->otherInfoTextBox->TabIndex = 9;
			this->otherInfoTextBox->Text = L"other info test";
			// 
			// wormGenderComboBox
			// 
			this->wormGenderComboBox->FormattingEnabled = true;
			this->wormGenderComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Male", L"Hermaphradite"});
			this->wormGenderComboBox->Location = System::Drawing::Point(141, 123);
			this->wormGenderComboBox->Name = L"wormGenderComboBox";
			this->wormGenderComboBox->Size = System::Drawing::Size(169, 21);
			this->wormGenderComboBox->TabIndex = 5;
			this->wormGenderComboBox->Text = L"Hermaphradite";
			// 
			// wormTreatmentsTextBox
			// 
			this->wormTreatmentsTextBox->Location = System::Drawing::Point(141, 71);
			this->wormTreatmentsTextBox->Name = L"wormTreatmentsTextBox";
			this->wormTreatmentsTextBox->Size = System::Drawing::Size(169, 20);
			this->wormTreatmentsTextBox->TabIndex = 3;
			this->wormTreatmentsTextBox->Text = L"none";
			// 
			// wormStrainTextBox
			// 
			this->wormStrainTextBox->Location = System::Drawing::Point(141, 45);
			this->wormStrainTextBox->Name = L"wormStrainTextBox";
			this->wormStrainTextBox->Size = System::Drawing::Size(169, 20);
			this->wormStrainTextBox->TabIndex = 2;
			this->wormStrainTextBox->Text = L"N2";
			// 
			// experimentTitleTextBox
			// 
			this->experimentTitleTextBox->Location = System::Drawing::Point(141, 19);
			this->experimentTitleTextBox->Name = L"experimentTitleTextBox";
			this->experimentTitleTextBox->Size = System::Drawing::Size(169, 20);
			this->experimentTitleTextBox->TabIndex = 1;
			this->experimentTitleTextBox->Text = L"TitleTest";
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
			this->otherInfoLabel->Location = System::Drawing::Point(6, 258);
			this->otherInfoLabel->Name = L"otherInfoLabel";
			this->otherInfoLabel->Size = System::Drawing::Size(122, 13);
			this->otherInfoLabel->TabIndex = 8;
			this->otherInfoLabel->Text = L"Other Experiment Notes:";
			// 
			// wormAgeLabel
			// 
			this->wormAgeLabel->AutoSize = true;
			this->wormAgeLabel->Location = System::Drawing::Point(6, 153);
			this->wormAgeLabel->Name = L"wormAgeLabel";
			this->wormAgeLabel->Size = System::Drawing::Size(60, 13);
			this->wormAgeLabel->TabIndex = 7;
			this->wormAgeLabel->Text = L"Worm Age:";
			// 
			// wormGenderLabel
			// 
			this->wormGenderLabel->AutoSize = true;
			this->wormGenderLabel->Location = System::Drawing::Point(6, 126);
			this->wormGenderLabel->Name = L"wormGenderLabel";
			this->wormGenderLabel->Size = System::Drawing::Size(76, 13);
			this->wormGenderLabel->TabIndex = 6;
			this->wormGenderLabel->Text = L"Worm Gender:";
			// 
			// percentAgarLabel
			// 
			this->percentAgarLabel->AutoSize = true;
			this->percentAgarLabel->Location = System::Drawing::Point(6, 100);
			this->percentAgarLabel->Name = L"percentAgarLabel";
			this->percentAgarLabel->Size = System::Drawing::Size(43, 13);
			this->percentAgarLabel->TabIndex = 5;
			this->percentAgarLabel->Text = L"% Agar:";
			// 
			// ambientTemperatureLabel
			// 
			this->ambientTemperatureLabel->AutoSize = true;
			this->ambientTemperatureLabel->Location = System::Drawing::Point(6, 232);
			this->ambientTemperatureLabel->Name = L"ambientTemperatureLabel";
			this->ambientTemperatureLabel->Size = System::Drawing::Size(111, 13);
			this->ambientTemperatureLabel->TabIndex = 4;
			this->ambientTemperatureLabel->Text = L"Ambient Temperature:";
			// 
			// ambientHumidityLabel
			// 
			this->ambientHumidityLabel->AutoSize = true;
			this->ambientHumidityLabel->Location = System::Drawing::Point(6, 206);
			this->ambientHumidityLabel->Name = L"ambientHumidityLabel";
			this->ambientHumidityLabel->Size = System::Drawing::Size(91, 13);
			this->ambientHumidityLabel->TabIndex = 3;
			this->ambientHumidityLabel->Text = L"Ambient Humidity:";
			// 
			// wormTreatmentsLabel
			// 
			this->wormTreatmentsLabel->AutoSize = true;
			this->wormTreatmentsLabel->Location = System::Drawing::Point(6, 74);
			this->wormTreatmentsLabel->Name = L"wormTreatmentsLabel";
			this->wormTreatmentsLabel->Size = System::Drawing::Size(94, 13);
			this->wormTreatmentsLabel->TabIndex = 2;
			this->wormTreatmentsLabel->Text = L"Worm Treatments:";
			// 
			// wormStrainLabel
			// 
			this->wormStrainLabel->AutoSize = true;
			this->wormStrainLabel->Location = System::Drawing::Point(6, 48);
			this->wormStrainLabel->Name = L"wormStrainLabel";
			this->wormStrainLabel->Size = System::Drawing::Size(71, 13);
			this->wormStrainLabel->TabIndex = 1;
			this->wormStrainLabel->Text = L"Worm Strain: ";
			// 
			// experimentTitleLabel
			// 
			this->experimentTitleLabel->AutoSize = true;
			this->experimentTitleLabel->Location = System::Drawing::Point(6, 23);
			this->experimentTitleLabel->Name = L"experimentTitleLabel";
			this->experimentTitleLabel->Size = System::Drawing::Size(85, 13);
			this->experimentTitleLabel->TabIndex = 0;
			this->experimentTitleLabel->Text = L"Experiment Title:";
			// 
			// cantileverGroupBox
			// 
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
			this->cantileverGroupBox->Location = System::Drawing::Point(12, 381);
			this->cantileverGroupBox->Name = L"cantileverGroupBox";
			this->cantileverGroupBox->Size = System::Drawing::Size(316, 180);
			this->cantileverGroupBox->TabIndex = 10;
			this->cantileverGroupBox->TabStop = false;
			this->cantileverGroupBox->Text = L"Cantilever Information";
			// 
			// cantileverSensitivityNumericUpDown
			// 
			this->cantileverSensitivityNumericUpDown->DecimalPlaces = 4;
			this->cantileverSensitivityNumericUpDown->Location = System::Drawing::Point(141, 152);
			this->cantileverSensitivityNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->cantileverSensitivityNumericUpDown->Name = L"cantileverSensitivityNumericUpDown";
			this->cantileverSensitivityNumericUpDown->Size = System::Drawing::Size(135, 20);
			this->cantileverSensitivityNumericUpDown->TabIndex = 28;
			// 
			// cantileverStiffnessNumericUpDown
			// 
			this->cantileverStiffnessNumericUpDown->DecimalPlaces = 4;
			this->cantileverStiffnessNumericUpDown->Location = System::Drawing::Point(141, 126);
			this->cantileverStiffnessNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->cantileverStiffnessNumericUpDown->Name = L"cantileverStiffnessNumericUpDown";
			this->cantileverStiffnessNumericUpDown->Size = System::Drawing::Size(135, 20);
			this->cantileverStiffnessNumericUpDown->TabIndex = 27;
			// 
			// cantileverFrequencyNumericUpDown
			// 
			this->cantileverFrequencyNumericUpDown->DecimalPlaces = 4;
			this->cantileverFrequencyNumericUpDown->Location = System::Drawing::Point(141, 100);
			this->cantileverFrequencyNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->cantileverFrequencyNumericUpDown->Name = L"cantileverFrequencyNumericUpDown";
			this->cantileverFrequencyNumericUpDown->Size = System::Drawing::Size(135, 20);
			this->cantileverFrequencyNumericUpDown->TabIndex = 26;
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
			this->deviceIDTextBox->TabIndex = 13;
			this->deviceIDTextBox->Text = L"1001";
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
			this->cantileverSensitivityUnitLabel->Location = System::Drawing::Point(283, 155);
			this->cantileverSensitivityUnitLabel->Name = L"cantileverSensitivityUnitLabel";
			this->cantileverSensitivityUnitLabel->Size = System::Drawing::Size(27, 13);
			this->cantileverSensitivityUnitLabel->TabIndex = 10;
			this->cantileverSensitivityUnitLabel->Text = L"V/N";
			// 
			// cantileverSensitivityLabel
			// 
			this->cantileverSensitivityLabel->AutoSize = true;
			this->cantileverSensitivityLabel->Location = System::Drawing::Point(6, 155);
			this->cantileverSensitivityLabel->Name = L"cantileverSensitivityLabel";
			this->cantileverSensitivityLabel->Size = System::Drawing::Size(57, 13);
			this->cantileverSensitivityLabel->TabIndex = 8;
			this->cantileverSensitivityLabel->Text = L"Sensitivity:";
			// 
			// cantileverStiffnessUnitLabel
			// 
			this->cantileverStiffnessUnitLabel->AutoSize = true;
			this->cantileverStiffnessUnitLabel->Location = System::Drawing::Point(282, 129);
			this->cantileverStiffnessUnitLabel->Name = L"cantileverStiffnessUnitLabel";
			this->cantileverStiffnessUnitLabel->Size = System::Drawing::Size(28, 13);
			this->cantileverStiffnessUnitLabel->TabIndex = 7;
			this->cantileverStiffnessUnitLabel->Text = L"N/m";
			// 
			// cantileverFreqUnitLabel
			// 
			this->cantileverFreqUnitLabel->AutoSize = true;
			this->cantileverFreqUnitLabel->Location = System::Drawing::Point(282, 103);
			this->cantileverFreqUnitLabel->Name = L"cantileverFreqUnitLabel";
			this->cantileverFreqUnitLabel->Size = System::Drawing::Size(20, 13);
			this->cantileverFreqUnitLabel->TabIndex = 6;
			this->cantileverFreqUnitLabel->Text = L"Hz";
			// 
			// cantileverStiffnessLabel
			// 
			this->cantileverStiffnessLabel->AutoSize = true;
			this->cantileverStiffnessLabel->Location = System::Drawing::Point(6, 129);
			this->cantileverStiffnessLabel->Name = L"cantileverStiffnessLabel";
			this->cantileverStiffnessLabel->Size = System::Drawing::Size(50, 13);
			this->cantileverStiffnessLabel->TabIndex = 3;
			this->cantileverStiffnessLabel->Text = L"Stiffness:";
			// 
			// cantileverFrequencyLabel
			// 
			this->cantileverFrequencyLabel->AutoSize = true;
			this->cantileverFrequencyLabel->Location = System::Drawing::Point(6, 103);
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
			this->waferIDTextBox->TabIndex = 1;
			this->waferIDTextBox->Text = L"EM10A";
			// 
			// cantileverIDSearchButton
			// 
			this->cantileverIDSearchButton->Location = System::Drawing::Point(141, 71);
			this->cantileverIDSearchButton->Name = L"cantileverIDSearchButton";
			this->cantileverIDSearchButton->Size = System::Drawing::Size(169, 23);
			this->cantileverIDSearchButton->TabIndex = 0;
			this->cantileverIDSearchButton->Text = L"Extract From Spreadsheet";
			this->cantileverIDSearchButton->UseVisualStyleBackColor = true;
			this->cantileverIDSearchButton->Click += gcnew System::EventHandler(this, &SetUpForm::cantileverIDSearchButton_Click);
			// 
			// SetUpForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(830, 598);
			this->Controls->Add(this->cantileverGroupBox);
			this->Controls->Add(this->experimentInfoGroupBox);
			this->Controls->Add(this->finishSetupButton);
			this->Controls->Add(this->cancelSetupButton);
			this->Controls->Add(this->stimulusSignalGroupBox);
			this->Controls->Add(this->dataOutputGroupBox);
			this->Controls->Add(this->stimulusInfoGroupBox);
			this->Controls->Add(this->targetGroupBox);
			this->Controls->Add(this->clampModeGroupBox);
			this->Name = L"SetUpForm";
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
			this->stimulusTypeGroupBox->ResumeLayout(false);
			this->stimulusTypeGroupBox->PerformLayout();
			this->stimulusSignalGroupBox->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimulusSignalChart))->EndInit();
			this->dataOutputGroupBox->ResumeLayout(false);
			this->dataOutputGroupBox->PerformLayout();
			this->experimentInfoGroupBox->ResumeLayout(false);
			this->experimentInfoGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ambientTemperatureNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ambientHumidityNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->percentAgarNumericUpDown))->EndInit();
			this->cantileverGroupBox->ResumeLayout(false);
			this->cantileverGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverSensitivityNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverStiffnessNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cantileverFrequencyNumericUpDown))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


private: 
	System::Void finishSetupButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (formIsComplete()) {
			populateExperimentFromForm();
			int dataOutputError = experiment->setUpDataOutput();
			if (dataOutputError == AVI_OPEN_ERROR) {
				MessageBox::Show("There was an error creating a writable AVI file.");
			} else if (dataOutputError == YAML_OPEN_ERROR) {
				MessageBox::Show("There was an error creating a writable YAML file.");
			} else {
				this->DialogResult = Windows::Forms::DialogResult::OK;
				this->Close();
			}
		}
	}

	System::Void cancelSetupButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
		this->Close();
	}

	bool formIsComplete(void)
	{
		if (outputLocationTextBox->Text->Length == 0) {
			
		} else if (experimentTitleTextBox->Text->Length == 0) {
			MessageBox::Show("Please provide a title for the experiment.");
		} else if (wormStrainTextBox->Text->Length == 0) {
			MessageBox::Show("Please specify the worm strain.");
		} else if (wormTreatmentsTextBox->Text->Length == 0) {
			MessageBox::Show("Please specify any worm treatments. Enter none if applicable.");
		} else if (percentAgarNumericUpDown->Value.Equals(Decimal(0))) {
			MessageBox::Show("Please specify the percent agar that the worm is crawling on.");
		} else if (wormGenderComboBox->Text->Length == 0) {
			MessageBox::Show("Please specify the worm gender.");
		} else if (wormFoodStatusComboBox->Text->Length == 0) {
			MessageBox::Show("Please specify the food status of the worm.");
		} else if (ambientTemperatureNumericUpDown->Value.Equals(Decimal(0))) {
			MessageBox::Show("Please specify the current ambient temperature.");
		} else if (ambientHumidityNumericUpDown->Value.Equals(Decimal(0))) {
			MessageBox::Show("Please specify the current ambient humidity.");
		} else if (waferIDTextBox->Text->Length == 0) {
			MessageBox::Show("Please specify the wafer ID for the cantilever in use.");
		} else if (deviceIDTextBox->Text->Length == 0) {
			MessageBox::Show("Please specify the device ID for the cantilever in use.");
		} else if (cantileverFrequencyNumericUpDown->Value.Equals(Decimal(0)) ||
				   cantileverStiffnessNumericUpDown->Value.Equals(Decimal(0)) ||
				   cantileverSensitivityNumericUpDown->Value.Equals(Decimal(0))) {
			MessageBox::Show("Please extract or provide the specifications for the cantilever in use.");
		} else return true;

		return false;
	}

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

		experiment->cantileverProperties.serialNumber = context->marshal_as<string>(System::String::Concat(waferIDTextBox->Text, deviceIDTextBox->Text));
		experiment->cantileverProperties.frequency = Decimal::ToDouble(cantileverFrequencyNumericUpDown->Value);
		experiment->cantileverProperties.stiffness = Decimal::ToDouble(cantileverStiffnessNumericUpDown->Value);
		experiment->cantileverProperties.sensitivity = Decimal::ToDouble(cantileverSensitivityNumericUpDown->Value);

		experiment->experimentMode = (forceClampRadioButton->Checked) ? std::string("Force Clamp") : std::string("Displacement Clamp");
		experiment->targetLocation = Decimal::ToDouble(targetNumericUpDown->Value)/100.0;
	}

	System::Void outputLocationBrowseButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (outputFolderBrowserDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
			outputLocationTextBox->Text = outputFolderBrowserDialog->SelectedPath;
		}
	}

	System::Void targetTrackBar_Scroll(System::Object^  sender, System::EventArgs^  e)
	{
		targetNumericUpDown->Value = Decimal(100 - targetTrackBar->Value);
	}

	System::Void targetNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		targetTrackBar->Value = 100 - Decimal::ToInt32(targetNumericUpDown->Value);
	}

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
		}
	}

};
}
