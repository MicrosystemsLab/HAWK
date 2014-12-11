/* MainForm.h
 * ----------
 * Component and event code for the main Windows form of the
 * H.A.W.K. Contains controls for all user processes.
 *
 * Created by John Whitworth on 8/26/14.
 */

#pragma once

#include "CalibrateSensitivityForm.h"
#include "CalibratePIDParameters.h"
#include "SafeQueue.h"
#include "Worm.h"
#include "Experiment.h"
#include "Zaber.h"
#include "ImageControl.h"
#include "SetUpForm.h"
#include "PostExperimentForm.h"
#include "STM_Communicator.h"


#define STAGE_LEFT 34
#define STAGE_RIGHT 35
#define STAGE_UP 36
#define STAGE_DOWN 37

#define RELATIVE_UP_FINE 41
#define RELATIVE_UP_COARSE 42
#define RELATIVE_DOWN_FINE 43
#define RELATIVE_DOWN_COARSE 44
#define ABSOLUTE_USER_DEF 45
#define ABSOLUTE_HOME 46
#define ABSOLUTE_HOVER 47
#define ABSOLUTE_SCAN 48

#define STIM_DONE 38
#define WRITE_FRAME 39

namespace BehaviorRig20 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Timers;

	using namespace cv;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			comm = new STM_Communicator;
				
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			disconnectHardware();
			if (experiment) {
				experiment->endExperiment();
				delete experiment;
			}
			if (comm) {
				delete comm;
			}
			if (components) {
				delete components;
			}
		}

	private: Zaber^ zaber;
	private: Experiment* experiment;
	private: ImageController* imageController;
	private: STM_Communicator* comm;
	private: bool toggleWormEnds;
	//private: bool stimulusActive;
	//private: bool stimulusFinished;
	//private: int stimulusNumber;

#pragma region Components
	private: System::Windows::Forms::Panel^  liveFeedPanel;
	private: System::Windows::Forms::Button^  setUpExpButton;
	private: System::Windows::Forms::GroupBox^  trackingGroupBox;
	private: System::Windows::Forms::Button^  startTrackButton;
	private: System::Windows::Forms::Button^  stopTrackButton;
	private: System::ComponentModel::BackgroundWorker^  trackingBackgroundWorker;
	private: System::Windows::Forms::StatusStrip^  statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusText;
	private: System::Windows::Forms::Button^  moveActuatorButton;
	private: System::Windows::Forms::NumericUpDown^  actuatorPositionNumericUpDown;
	private: System::Windows::Forms::GroupBox^  actuatorMovementGroupBox;
	private: System::Windows::Forms::Button^  lowerActuatorButton;
	private: System::Windows::Forms::Button^  raiseActuatorButton;
	private: System::Windows::Forms::GroupBox^  stageMovementGroupBox;
	private: System::Windows::Forms::Button^  moveStageDownButton;
	private: System::Windows::Forms::Button^  moveStageUpButton;
	private: System::Windows::Forms::Button^  moveStageRightButton;
	private: System::Windows::Forms::Button^  moveStageLeftButton;
	private: System::Windows::Forms::Button^  actuatorHomeButton;
	private: System::Windows::Forms::DomainUpDown^  actuatorResolutionDomainUpDown;
	private: System::Windows::Forms::Label^  actuatorResolutionLabel;
	private: System::ComponentModel::BackgroundWorker^  zaberBackgroundWorker;
	private: System::Windows::Forms::DomainUpDown^  stageSpeedDomainUpDown;
	private: System::Windows::Forms::Label^  stageSpeedLabel;
	private: System::Windows::Forms::GroupBox^  experimentGroupBox;
	private: System::Windows::Forms::Button^  applyStimButton;
	private: System::Windows::Forms::Button^  actuatorScanPosButton;
	private: System::Windows::Forms::Button^  actuatorHovPosButton;
	private: System::Windows::Forms::Button^  toggleHeadTailButton;
	private: System::Windows::Forms::GroupBox^  exposureGroupBox;
	private: System::Windows::Forms::RadioButton^  autoExposeRadioButton;
	private: System::Windows::Forms::RadioButton^  defaultExposeRadioButton;
	private: System::Windows::Forms::Panel^  fpgaConnectionIndicationPanel;
	private: System::Windows::Forms::Label^  fpgaConnectionLabel;
	private: System::ComponentModel::BackgroundWorker^  forceClampBackgroundWorker;
	private: System::Windows::Forms::Button^  endStimulusButton;

	private: System::Windows::Forms::Button^  setScanPositionButton;

	private: System::Windows::Forms::Button^  setHoverPositionButton;
	private: System::ComponentModel::BackgroundWorker^  actuatorBackgroundWorker;
	private: System::Windows::Forms::Label^  hoverPositionLabel;
	private: System::Windows::Forms::Label^  scanPositionLabel;
	private: System::Windows::Forms::Button^  calibrateCantileverButton;
	private: System::Windows::Forms::Button^  calibratePIDButton;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::GroupBox^  calibrationToolsGroupBox;

	private: System::ComponentModel::IContainer^  components;
#pragma endregion

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->setUpExpButton = (gcnew System::Windows::Forms::Button());
			this->startTrackButton = (gcnew System::Windows::Forms::Button());
			this->stopTrackButton = (gcnew System::Windows::Forms::Button());
			this->trackingGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->toggleHeadTailButton = (gcnew System::Windows::Forms::Button());
			this->trackingBackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->liveFeedPanel = (gcnew System::Windows::Forms::Panel());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusText = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->moveActuatorButton = (gcnew System::Windows::Forms::Button());
			this->actuatorPositionNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->actuatorMovementGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->hoverPositionLabel = (gcnew System::Windows::Forms::Label());
			this->scanPositionLabel = (gcnew System::Windows::Forms::Label());
			this->actuatorScanPosButton = (gcnew System::Windows::Forms::Button());
			this->setScanPositionButton = (gcnew System::Windows::Forms::Button());
			this->actuatorHovPosButton = (gcnew System::Windows::Forms::Button());
			this->setHoverPositionButton = (gcnew System::Windows::Forms::Button());
			this->actuatorResolutionDomainUpDown = (gcnew System::Windows::Forms::DomainUpDown());
			this->actuatorResolutionLabel = (gcnew System::Windows::Forms::Label());
			this->actuatorHomeButton = (gcnew System::Windows::Forms::Button());
			this->lowerActuatorButton = (gcnew System::Windows::Forms::Button());
			this->raiseActuatorButton = (gcnew System::Windows::Forms::Button());
			this->stageMovementGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->stageSpeedDomainUpDown = (gcnew System::Windows::Forms::DomainUpDown());
			this->stageSpeedLabel = (gcnew System::Windows::Forms::Label());
			this->moveStageDownButton = (gcnew System::Windows::Forms::Button());
			this->moveStageUpButton = (gcnew System::Windows::Forms::Button());
			this->moveStageRightButton = (gcnew System::Windows::Forms::Button());
			this->moveStageLeftButton = (gcnew System::Windows::Forms::Button());
			this->zaberBackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->experimentGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->endStimulusButton = (gcnew System::Windows::Forms::Button());
			this->applyStimButton = (gcnew System::Windows::Forms::Button());
			this->exposureGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->autoExposeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->defaultExposeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->fpgaConnectionIndicationPanel = (gcnew System::Windows::Forms::Panel());
			this->fpgaConnectionLabel = (gcnew System::Windows::Forms::Label());
			this->forceClampBackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->actuatorBackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->calibrateCantileverButton = (gcnew System::Windows::Forms::Button());
			this->calibratePIDButton = (gcnew System::Windows::Forms::Button());
			this->calibrationToolsGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->trackingGroupBox->SuspendLayout();
			this->liveFeedPanel->SuspendLayout();
			this->statusStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->actuatorPositionNumericUpDown))->BeginInit();
			this->actuatorMovementGroupBox->SuspendLayout();
			this->stageMovementGroupBox->SuspendLayout();
			this->experimentGroupBox->SuspendLayout();
			this->exposureGroupBox->SuspendLayout();
			this->calibrationToolsGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// setUpExpButton
			// 
			this->setUpExpButton->Location = System::Drawing::Point(6, 19);
			this->setUpExpButton->Name = L"setUpExpButton";
			this->setUpExpButton->Size = System::Drawing::Size(97, 23);
			this->setUpExpButton->TabIndex = 0;
			this->setUpExpButton->Text = L"Set Up";
			this->setUpExpButton->UseVisualStyleBackColor = true;
			this->setUpExpButton->Click += gcnew System::EventHandler(this, &MainForm::setUpExpButton_Click);
			// 
			// startTrackButton
			// 
			this->startTrackButton->Enabled = false;
			this->startTrackButton->Location = System::Drawing::Point(6, 19);
			this->startTrackButton->Name = L"startTrackButton";
			this->startTrackButton->Size = System::Drawing::Size(97, 23);
			this->startTrackButton->TabIndex = 9;
			this->startTrackButton->Text = L"Start";
			this->startTrackButton->UseVisualStyleBackColor = true;
			this->startTrackButton->Click += gcnew System::EventHandler(this, &MainForm::startTrackButton_Click);
			// 
			// stopTrackButton
			// 
			this->stopTrackButton->Enabled = false;
			this->stopTrackButton->Location = System::Drawing::Point(6, 48);
			this->stopTrackButton->Name = L"stopTrackButton";
			this->stopTrackButton->Size = System::Drawing::Size(97, 23);
			this->stopTrackButton->TabIndex = 10;
			this->stopTrackButton->Text = L"Stop";
			this->stopTrackButton->UseVisualStyleBackColor = true;
			this->stopTrackButton->Click += gcnew System::EventHandler(this, &MainForm::stopTrackButton_Click);
			// 
			// trackingGroupBox
			// 
			this->trackingGroupBox->Controls->Add(this->toggleHeadTailButton);
			this->trackingGroupBox->Controls->Add(this->startTrackButton);
			this->trackingGroupBox->Controls->Add(this->stopTrackButton);
			this->trackingGroupBox->Location = System::Drawing::Point(12, 12);
			this->trackingGroupBox->Name = L"trackingGroupBox";
			this->trackingGroupBox->Size = System::Drawing::Size(109, 125);
			this->trackingGroupBox->TabIndex = 11;
			this->trackingGroupBox->TabStop = false;
			this->trackingGroupBox->Text = L"Tracking";
			// 
			// toggleHeadTailButton
			// 
			this->toggleHeadTailButton->Enabled = false;
			this->toggleHeadTailButton->Location = System::Drawing::Point(6, 77);
			this->toggleHeadTailButton->Name = L"toggleHeadTailButton";
			this->toggleHeadTailButton->Size = System::Drawing::Size(97, 39);
			this->toggleHeadTailButton->TabIndex = 11;
			this->toggleHeadTailButton->Text = L"Head, Tail Toggle";
			this->toggleHeadTailButton->UseVisualStyleBackColor = true;
			this->toggleHeadTailButton->Click += gcnew System::EventHandler(this, &MainForm::toggleHeadTailButton_Click);
			// 
			// trackingBackgroundWorker
			// 
			this->trackingBackgroundWorker->WorkerReportsProgress = true;
			this->trackingBackgroundWorker->WorkerSupportsCancellation = true;
			this->trackingBackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::trackingBackgroundWorker_TrackWorm);
			this->trackingBackgroundWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MainForm::trackingBackgroundWorker_ProgressChanged);
			this->trackingBackgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::trackingBackgroundWorker_RunWorkerCompleted);
			// 
			// liveFeedPanel
			// 
			this->liveFeedPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->liveFeedPanel->Controls->Add(this->statusStrip1);
			this->liveFeedPanel->Location = System::Drawing::Point(127, 12);
			this->liveFeedPanel->Name = L"liveFeedPanel";
			this->liveFeedPanel->Size = System::Drawing::Size(768, 576);
			this->liveFeedPanel->TabIndex = 18;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Location = System::Drawing::Point(0, 550);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(764, 22);
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripStatusLabel, 
				this->toolStripStatusText});
			this->statusStrip->Location = System::Drawing::Point(0, 597);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(1041, 22);
			this->statusStrip->TabIndex = 19;
			this->statusStrip->Text = L"statusStrip";
			// 
			// toolStripStatusLabel
			// 
			this->toolStripStatusLabel->Name = L"toolStripStatusLabel";
			this->toolStripStatusLabel->Size = System::Drawing::Size(42, 17);
			this->toolStripStatusLabel->Text = L"Status:";
			// 
			// toolStripStatusText
			// 
			this->toolStripStatusText->Name = L"toolStripStatusText";
			this->toolStripStatusText->Size = System::Drawing::Size(0, 17);
			// 
			// moveActuatorButton
			// 
			this->moveActuatorButton->Location = System::Drawing::Point(6, 116);
			this->moveActuatorButton->Name = L"moveActuatorButton";
			this->moveActuatorButton->Size = System::Drawing::Size(97, 23);
			this->moveActuatorButton->TabIndex = 20;
			this->moveActuatorButton->Text = L"Move to Position:";
			this->moveActuatorButton->UseVisualStyleBackColor = true;
			this->moveActuatorButton->UseWaitCursor = true;
			this->moveActuatorButton->Click += gcnew System::EventHandler(this, &MainForm::moveActuatorButton_Click);
			// 
			// actuatorPositionNumericUpDown
			// 
			this->actuatorPositionNumericUpDown->Location = System::Drawing::Point(7, 145);
			this->actuatorPositionNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {50000, 0, 0, 0});
			this->actuatorPositionNumericUpDown->Name = L"actuatorPositionNumericUpDown";
			this->actuatorPositionNumericUpDown->Size = System::Drawing::Size(96, 20);
			this->actuatorPositionNumericUpDown->TabIndex = 21;
			this->actuatorPositionNumericUpDown->UseWaitCursor = true;
			// 
			// actuatorMovementGroupBox
			// 
			this->actuatorMovementGroupBox->Controls->Add(this->hoverPositionLabel);
			this->actuatorMovementGroupBox->Controls->Add(this->scanPositionLabel);
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorScanPosButton);
			this->actuatorMovementGroupBox->Controls->Add(this->setScanPositionButton);
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorHovPosButton);
			this->actuatorMovementGroupBox->Controls->Add(this->setHoverPositionButton);
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorResolutionDomainUpDown);
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorResolutionLabel);
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorPositionNumericUpDown);
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorHomeButton);
			this->actuatorMovementGroupBox->Controls->Add(this->moveActuatorButton);
			this->actuatorMovementGroupBox->Controls->Add(this->lowerActuatorButton);
			this->actuatorMovementGroupBox->Controls->Add(this->raiseActuatorButton);
			this->actuatorMovementGroupBox->Location = System::Drawing::Point(901, 164);
			this->actuatorMovementGroupBox->Name = L"actuatorMovementGroupBox";
			this->actuatorMovementGroupBox->Size = System::Drawing::Size(133, 295);
			this->actuatorMovementGroupBox->TabIndex = 29;
			this->actuatorMovementGroupBox->TabStop = false;
			this->actuatorMovementGroupBox->Text = L"Cantilever Controls";
			this->actuatorMovementGroupBox->UseWaitCursor = true;
			// 
			// hoverPositionLabel
			// 
			this->hoverPositionLabel->AutoSize = true;
			this->hoverPositionLabel->Location = System::Drawing::Point(7, 247);
			this->hoverPositionLabel->Name = L"hoverPositionLabel";
			this->hoverPositionLabel->Size = System::Drawing::Size(79, 13);
			this->hoverPositionLabel->TabIndex = 39;
			this->hoverPositionLabel->Text = L"Hover Position:";
			this->hoverPositionLabel->UseWaitCursor = true;
			// 
			// scanPositionLabel
			// 
			this->scanPositionLabel->AutoSize = true;
			this->scanPositionLabel->Location = System::Drawing::Point(9, 201);
			this->scanPositionLabel->Name = L"scanPositionLabel";
			this->scanPositionLabel->Size = System::Drawing::Size(75, 13);
			this->scanPositionLabel->TabIndex = 38;
			this->scanPositionLabel->Text = L"Scan Position:";
			this->scanPositionLabel->UseWaitCursor = true;
			// 
			// actuatorScanPosButton
			// 
			this->actuatorScanPosButton->Location = System::Drawing::Point(70, 217);
			this->actuatorScanPosButton->Name = L"actuatorScanPosButton";
			this->actuatorScanPosButton->Size = System::Drawing::Size(56, 23);
			this->actuatorScanPosButton->TabIndex = 34;
			this->actuatorScanPosButton->Text = L"Go To ";
			this->actuatorScanPosButton->UseVisualStyleBackColor = true;
			this->actuatorScanPosButton->UseWaitCursor = true;
			this->actuatorScanPosButton->Click += gcnew System::EventHandler(this, &MainForm::actuatorScanPosButton_Click);
			// 
			// setScanPositionButton
			// 
			this->setScanPositionButton->Location = System::Drawing::Point(7, 217);
			this->setScanPositionButton->Name = L"setScanPositionButton";
			this->setScanPositionButton->Size = System::Drawing::Size(57, 23);
			this->setScanPositionButton->TabIndex = 36;
			this->setScanPositionButton->Text = L"Set ";
			this->setScanPositionButton->UseVisualStyleBackColor = true;
			this->setScanPositionButton->UseWaitCursor = true;
			this->setScanPositionButton->Click += gcnew System::EventHandler(this, &MainForm::setScanPositionButton_Click);
			// 
			// actuatorHovPosButton
			// 
			this->actuatorHovPosButton->Location = System::Drawing::Point(70, 263);
			this->actuatorHovPosButton->Name = L"actuatorHovPosButton";
			this->actuatorHovPosButton->Size = System::Drawing::Size(56, 23);
			this->actuatorHovPosButton->TabIndex = 33;
			this->actuatorHovPosButton->Text = L"Go To";
			this->actuatorHovPosButton->UseVisualStyleBackColor = true;
			this->actuatorHovPosButton->UseWaitCursor = true;
			this->actuatorHovPosButton->Click += gcnew System::EventHandler(this, &MainForm::actuatorHovPosButton_Click);
			// 
			// setHoverPositionButton
			// 
			this->setHoverPositionButton->Location = System::Drawing::Point(7, 263);
			this->setHoverPositionButton->Name = L"setHoverPositionButton";
			this->setHoverPositionButton->Size = System::Drawing::Size(57, 23);
			this->setHoverPositionButton->TabIndex = 37;
			this->setHoverPositionButton->Text = L"Set";
			this->setHoverPositionButton->UseVisualStyleBackColor = true;
			this->setHoverPositionButton->UseWaitCursor = true;
			this->setHoverPositionButton->Click += gcnew System::EventHandler(this, &MainForm::setHoverPositionButton_Click);
			// 
			// actuatorResolutionDomainUpDown
			// 
			this->actuatorResolutionDomainUpDown->Items->Add(L"Fine (5um)");
			this->actuatorResolutionDomainUpDown->Items->Add(L"Coarse (50um)");
			this->actuatorResolutionDomainUpDown->Location = System::Drawing::Point(6, 90);
			this->actuatorResolutionDomainUpDown->Name = L"actuatorResolutionDomainUpDown";
			this->actuatorResolutionDomainUpDown->SelectedIndex = 0;
			this->actuatorResolutionDomainUpDown->Size = System::Drawing::Size(97, 20);
			this->actuatorResolutionDomainUpDown->TabIndex = 31;
			this->actuatorResolutionDomainUpDown->Text = L"Fine (5um)";
			this->actuatorResolutionDomainUpDown->UseWaitCursor = true;
			this->actuatorResolutionDomainUpDown->Wrap = true;
			// 
			// actuatorResolutionLabel
			// 
			this->actuatorResolutionLabel->AutoSize = true;
			this->actuatorResolutionLabel->Location = System::Drawing::Point(3, 74);
			this->actuatorResolutionLabel->Name = L"actuatorResolutionLabel";
			this->actuatorResolutionLabel->Size = System::Drawing::Size(60, 13);
			this->actuatorResolutionLabel->TabIndex = 32;
			this->actuatorResolutionLabel->Text = L"Resolution:";
			this->actuatorResolutionLabel->UseWaitCursor = true;
			// 
			// actuatorHomeButton
			// 
			this->actuatorHomeButton->Location = System::Drawing::Point(7, 171);
			this->actuatorHomeButton->Name = L"actuatorHomeButton";
			this->actuatorHomeButton->Size = System::Drawing::Size(120, 23);
			this->actuatorHomeButton->TabIndex = 2;
			this->actuatorHomeButton->Text = L"Go To Home Position";
			this->actuatorHomeButton->UseVisualStyleBackColor = true;
			this->actuatorHomeButton->UseWaitCursor = true;
			this->actuatorHomeButton->Click += gcnew System::EventHandler(this, &MainForm::actuatorHomeButton_Click);
			// 
			// lowerActuatorButton
			// 
			this->lowerActuatorButton->Location = System::Drawing::Point(6, 48);
			this->lowerActuatorButton->Name = L"lowerActuatorButton";
			this->lowerActuatorButton->Size = System::Drawing::Size(97, 23);
			this->lowerActuatorButton->TabIndex = 1;
			this->lowerActuatorButton->Text = L"Lower";
			this->lowerActuatorButton->UseVisualStyleBackColor = true;
			this->lowerActuatorButton->UseWaitCursor = true;
			this->lowerActuatorButton->Click += gcnew System::EventHandler(this, &MainForm::lowerActuatorButton_Click);
			// 
			// raiseActuatorButton
			// 
			this->raiseActuatorButton->Location = System::Drawing::Point(6, 19);
			this->raiseActuatorButton->Name = L"raiseActuatorButton";
			this->raiseActuatorButton->Size = System::Drawing::Size(97, 23);
			this->raiseActuatorButton->TabIndex = 0;
			this->raiseActuatorButton->Text = L"Raise";
			this->raiseActuatorButton->UseVisualStyleBackColor = true;
			this->raiseActuatorButton->UseWaitCursor = true;
			this->raiseActuatorButton->Click += gcnew System::EventHandler(this, &MainForm::raiseActuatorButton_Click);
			// 
			// stageMovementGroupBox
			// 
			this->stageMovementGroupBox->Controls->Add(this->stageSpeedDomainUpDown);
			this->stageMovementGroupBox->Controls->Add(this->stageSpeedLabel);
			this->stageMovementGroupBox->Controls->Add(this->moveStageDownButton);
			this->stageMovementGroupBox->Controls->Add(this->moveStageUpButton);
			this->stageMovementGroupBox->Controls->Add(this->moveStageRightButton);
			this->stageMovementGroupBox->Controls->Add(this->moveStageLeftButton);
			this->stageMovementGroupBox->Location = System::Drawing::Point(901, 12);
			this->stageMovementGroupBox->Name = L"stageMovementGroupBox";
			this->stageMovementGroupBox->Size = System::Drawing::Size(136, 146);
			this->stageMovementGroupBox->TabIndex = 30;
			this->stageMovementGroupBox->TabStop = false;
			this->stageMovementGroupBox->Text = L"Stage Controls";
			// 
			// stageSpeedDomainUpDown
			// 
			this->stageSpeedDomainUpDown->Items->Add(L"Slow");
			this->stageSpeedDomainUpDown->Items->Add(L"Regular");
			this->stageSpeedDomainUpDown->Items->Add(L"Fast");
			this->stageSpeedDomainUpDown->Location = System::Drawing::Point(6, 119);
			this->stageSpeedDomainUpDown->Name = L"stageSpeedDomainUpDown";
			this->stageSpeedDomainUpDown->SelectedIndex = 1;
			this->stageSpeedDomainUpDown->Size = System::Drawing::Size(97, 20);
			this->stageSpeedDomainUpDown->TabIndex = 33;
			this->stageSpeedDomainUpDown->Text = L"Regular";
			this->stageSpeedDomainUpDown->Wrap = true;
			// 
			// stageSpeedLabel
			// 
			this->stageSpeedLabel->AutoSize = true;
			this->stageSpeedLabel->Location = System::Drawing::Point(6, 103);
			this->stageSpeedLabel->Name = L"stageSpeedLabel";
			this->stageSpeedLabel->Size = System::Drawing::Size(41, 13);
			this->stageSpeedLabel->TabIndex = 34;
			this->stageSpeedLabel->Text = L"Speed:";
			// 
			// moveStageDownButton
			// 
			this->moveStageDownButton->Location = System::Drawing::Point(41, 77);
			this->moveStageDownButton->Name = L"moveStageDownButton";
			this->moveStageDownButton->Size = System::Drawing::Size(45, 23);
			this->moveStageDownButton->TabIndex = 3;
			this->moveStageDownButton->Text = L"v";
			this->moveStageDownButton->UseVisualStyleBackColor = true;
			this->moveStageDownButton->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::moveStageDownButton_MouseDown);
			this->moveStageDownButton->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::moveStageDownButton_MouseUp);
			// 
			// moveStageUpButton
			// 
			this->moveStageUpButton->Location = System::Drawing::Point(41, 19);
			this->moveStageUpButton->Name = L"moveStageUpButton";
			this->moveStageUpButton->Size = System::Drawing::Size(45, 23);
			this->moveStageUpButton->TabIndex = 2;
			this->moveStageUpButton->Text = L"^";
			this->moveStageUpButton->UseVisualStyleBackColor = true;
			this->moveStageUpButton->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::moveStageUpButton_MouseDown);
			this->moveStageUpButton->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::moveStageLeftButton_MouseUp);
			// 
			// moveStageRightButton
			// 
			this->moveStageRightButton->Location = System::Drawing::Point(72, 48);
			this->moveStageRightButton->Name = L"moveStageRightButton";
			this->moveStageRightButton->Size = System::Drawing::Size(45, 23);
			this->moveStageRightButton->TabIndex = 1;
			this->moveStageRightButton->Text = L">";
			this->moveStageRightButton->UseVisualStyleBackColor = true;
			this->moveStageRightButton->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::moveStageRightButton_MouseDown);
			this->moveStageRightButton->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::moveStageRightButton_MouseUp);
			// 
			// moveStageLeftButton
			// 
			this->moveStageLeftButton->Location = System::Drawing::Point(6, 48);
			this->moveStageLeftButton->Name = L"moveStageLeftButton";
			this->moveStageLeftButton->Size = System::Drawing::Size(45, 23);
			this->moveStageLeftButton->TabIndex = 0;
			this->moveStageLeftButton->Text = L"<";
			this->moveStageLeftButton->UseVisualStyleBackColor = true;
			this->moveStageLeftButton->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::moveStageLeftButton_MouseDown);
			this->moveStageLeftButton->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::moveStageLeftButton_MouseUp);
			// 
			// zaberBackgroundWorker
			// 
			this->zaberBackgroundWorker->WorkerSupportsCancellation = true;
			this->zaberBackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::zaberBackgroundWorker_MoveStage);
			// 
			// experimentGroupBox
			// 
			this->experimentGroupBox->Controls->Add(this->endStimulusButton);
			this->experimentGroupBox->Controls->Add(this->setUpExpButton);
			this->experimentGroupBox->Controls->Add(this->applyStimButton);
			this->experimentGroupBox->Location = System::Drawing::Point(12, 143);
			this->experimentGroupBox->Name = L"experimentGroupBox";
			this->experimentGroupBox->Size = System::Drawing::Size(109, 105);
			this->experimentGroupBox->TabIndex = 31;
			this->experimentGroupBox->TabStop = false;
			this->experimentGroupBox->Text = L"Experiment";
			// 
			// endStimulusButton
			// 
			this->endStimulusButton->Location = System::Drawing::Point(6, 76);
			this->endStimulusButton->Name = L"endStimulusButton";
			this->endStimulusButton->Size = System::Drawing::Size(97, 23);
			this->endStimulusButton->TabIndex = 36;
			this->endStimulusButton->Text = L"Stop Stimulus";
			this->endStimulusButton->UseVisualStyleBackColor = true;
			this->endStimulusButton->Click += gcnew System::EventHandler(this, &MainForm::endStimulusButton_Click);
			// 
			// applyStimButton
			// 
			this->applyStimButton->Enabled = false;
			this->applyStimButton->Location = System::Drawing::Point(6, 48);
			this->applyStimButton->Name = L"applyStimButton";
			this->applyStimButton->Size = System::Drawing::Size(97, 23);
			this->applyStimButton->TabIndex = 4;
			this->applyStimButton->Text = L"Apply Stimulus";
			this->applyStimButton->UseVisualStyleBackColor = true;
			this->applyStimButton->Click += gcnew System::EventHandler(this, &MainForm::applyStimButton_Click);
			// 
			// exposureGroupBox
			// 
			this->exposureGroupBox->Controls->Add(this->autoExposeRadioButton);
			this->exposureGroupBox->Controls->Add(this->defaultExposeRadioButton);
			this->exposureGroupBox->Location = System::Drawing::Point(12, 254);
			this->exposureGroupBox->Name = L"exposureGroupBox";
			this->exposureGroupBox->Size = System::Drawing::Size(109, 67);
			this->exposureGroupBox->TabIndex = 32;
			this->exposureGroupBox->TabStop = false;
			this->exposureGroupBox->Text = L"Camera Exposure";
			// 
			// autoExposeRadioButton
			// 
			this->autoExposeRadioButton->AutoSize = true;
			this->autoExposeRadioButton->Location = System::Drawing::Point(6, 42);
			this->autoExposeRadioButton->Name = L"autoExposeRadioButton";
			this->autoExposeRadioButton->Size = System::Drawing::Size(72, 17);
			this->autoExposeRadioButton->TabIndex = 1;
			this->autoExposeRadioButton->TabStop = true;
			this->autoExposeRadioButton->Text = L"Automatic";
			this->autoExposeRadioButton->UseVisualStyleBackColor = true;
			this->autoExposeRadioButton->Click += gcnew System::EventHandler(this, &MainForm::autoExposeRadioButton_Click);
			// 
			// defaultExposeRadioButton
			// 
			this->defaultExposeRadioButton->AutoSize = true;
			this->defaultExposeRadioButton->Checked = true;
			this->defaultExposeRadioButton->Location = System::Drawing::Point(7, 19);
			this->defaultExposeRadioButton->Name = L"defaultExposeRadioButton";
			this->defaultExposeRadioButton->Size = System::Drawing::Size(59, 17);
			this->defaultExposeRadioButton->TabIndex = 0;
			this->defaultExposeRadioButton->TabStop = true;
			this->defaultExposeRadioButton->Text = L"Default";
			this->defaultExposeRadioButton->UseVisualStyleBackColor = true;
			this->defaultExposeRadioButton->Click += gcnew System::EventHandler(this, &MainForm::defaultExposeRadioButton_Click);
			// 
			// fpgaConnectionIndicationPanel
			// 
			this->fpgaConnectionIndicationPanel->BackColor = System::Drawing::Color::Red;
			this->fpgaConnectionIndicationPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->fpgaConnectionIndicationPanel->Location = System::Drawing::Point(7, 578);
			this->fpgaConnectionIndicationPanel->Name = L"fpgaConnectionIndicationPanel";
			this->fpgaConnectionIndicationPanel->Size = System::Drawing::Size(10, 10);
			this->fpgaConnectionIndicationPanel->TabIndex = 33;
			// 
			// fpgaConnectionLabel
			// 
			this->fpgaConnectionLabel->AutoSize = true;
			this->fpgaConnectionLabel->Location = System::Drawing::Point(23, 575);
			this->fpgaConnectionLabel->Name = L"fpgaConnectionLabel";
			this->fpgaConnectionLabel->Size = System::Drawing::Size(92, 13);
			this->fpgaConnectionLabel->TabIndex = 35;
			this->fpgaConnectionLabel->Text = L"FPGA Connection";
			// 
			// forceClampBackgroundWorker
			// 
			this->forceClampBackgroundWorker->WorkerSupportsCancellation = true;
			this->forceClampBackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::forceClampBackgroundWorker_CheckStatus);
			// 
			// actuatorBackgroundWorker
			// 
			this->actuatorBackgroundWorker->WorkerSupportsCancellation = true;
			this->actuatorBackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::actuatorBackgroundWorker_MoveActuator);
			// 
			// calibrateCantileverButton
			// 
			this->calibrateCantileverButton->Location = System::Drawing::Point(7, 19);
			this->calibrateCantileverButton->Name = L"calibrateCantileverButton";
			this->calibrateCantileverButton->Size = System::Drawing::Size(97, 54);
			this->calibrateCantileverButton->TabIndex = 36;
			this->calibrateCantileverButton->Text = L"Calibrate Cantliever Sensitivity";
			this->calibrateCantileverButton->UseVisualStyleBackColor = true;
			this->calibrateCantileverButton->Click += gcnew System::EventHandler(this, &MainForm::calibrateCantileverButton_Click);
			// 
			// calibratePIDButton
			// 
			this->calibratePIDButton->Location = System::Drawing::Point(7, 79);
			this->calibratePIDButton->Name = L"calibratePIDButton";
			this->calibratePIDButton->Size = System::Drawing::Size(96, 54);
			this->calibratePIDButton->TabIndex = 37;
			this->calibratePIDButton->Text = L"Calibrate PID Parameters";
			this->calibratePIDButton->UseVisualStyleBackColor = true;
			this->calibratePIDButton->Click += gcnew System::EventHandler(this, &MainForm::calibratePIDButton_Click);
			// 
			// calibrationToolsGroupBox
			// 
			this->calibrationToolsGroupBox->Controls->Add(this->calibrateCantileverButton);
			this->calibrationToolsGroupBox->Controls->Add(this->calibratePIDButton);
			this->calibrationToolsGroupBox->Location = System::Drawing::Point(12, 427);
			this->calibrationToolsGroupBox->Name = L"calibrationToolsGroupBox";
			this->calibrationToolsGroupBox->Size = System::Drawing::Size(109, 145);
			this->calibrationToolsGroupBox->TabIndex = 38;
			this->calibrationToolsGroupBox->TabStop = false;
			this->calibrationToolsGroupBox->Text = L"Calibration Tools";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1041, 619);
			this->Controls->Add(this->fpgaConnectionLabel);
			this->Controls->Add(this->fpgaConnectionIndicationPanel);
			this->Controls->Add(this->exposureGroupBox);
			this->Controls->Add(this->stageMovementGroupBox);
			this->Controls->Add(this->actuatorMovementGroupBox);
			this->Controls->Add(this->experimentGroupBox);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->liveFeedPanel);
			this->Controls->Add(this->trackingGroupBox);
			this->Controls->Add(this->calibrationToolsGroupBox);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"H.A.W.K.";
			this->Closed += gcnew System::EventHandler(this, &MainForm::MainForm_Close);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->trackingGroupBox->ResumeLayout(false);
			this->liveFeedPanel->ResumeLayout(false);
			this->liveFeedPanel->PerformLayout();
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->actuatorPositionNumericUpDown))->EndInit();
			this->actuatorMovementGroupBox->ResumeLayout(false);
			this->actuatorMovementGroupBox->PerformLayout();
			this->stageMovementGroupBox->ResumeLayout(false);
			this->stageMovementGroupBox->PerformLayout();
			this->experimentGroupBox->ResumeLayout(false);
			this->exposureGroupBox->ResumeLayout(false);
			this->exposureGroupBox->PerformLayout();
			this->calibrationToolsGroupBox->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private:
	/* Function: setUpExpButton_Click
	 * ------------------------------
	 * Event handler to set up an experiment. Clears any previously defined experiment
	 * Creates and shows the SetUpForm. If that form has an OK result the process moves
	 * on to user input of the cantilever tip. Otherwise the experiment set up is
	 * canceled.
	 */
	System::Void setUpExpButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->startTrackButton->Enabled = false;
		this->setUpExpButton->Enabled = false;
		if (experiment) {
			experiment->endExperiment();
			delete experiment;
		}
		experiment = new Experiment;

		Form^ setUpForm = gcnew SetUpForm(experiment, comm);
		setUpForm->ShowDialog();

		if (setUpForm->DialogResult == Windows::Forms::DialogResult::OK) {
			if (experiment->experimentMode == std::string("Behavior Mode")){
				// set up point in image space to be tracked to be the center of the screen.
				System::Drawing::Point cursorPoint;
				cursorPoint.X = liveFeedPanel->Size.Width;
				cursorPoint.Y = liveFeedPanel->Size.Height;
				Point cvCursorPoint = Point((int)((cursorPoint.X)/2 * IMAGE_RESIZE_SCALE/SCREEN_RESIZE_SCALE), (int)((cursorPoint.Y)/2 * IMAGE_RESIZE_SCALE/SCREEN_RESIZE_SCALE));
				experiment->cantileverProperties.positionInImageSpace = cvCursorPoint;
				
			}
			else{
				// ask user where the cantilever is in the image. 
				setCantileverPositionManually();
			}
			experiment->stimulusNumber = 0;
			experiment->experimentSetUp = true;
			experiment->trackingReady = true;
			toolStripStatusText->Text = "Experiment Set Up Complete";
			this->setUpExpButton->Enabled = true;
			this->startTrackButton->Enabled = true;
		} else {
			experiment->experimentSetUp = false;
			experiment->endExperiment();
			delete experiment;
			experiment = NULL;
			toolStripStatusText->Text = "Experiment Set Up Canceled";
			this->setUpExpButton->Enabled = true;
		}
	}

	/* Function: calibrateCantileverButton_Click
	 * -----------------------------------------
	 * Event handler to open dialog box to calibrate a cantilever.
	 *
	 */

	private: System::Void calibrateCantileverButton_Click(System::Object^  sender, System::EventArgs^  e) {
			Form^ calibrateSensitivityForm = gcnew CalibrateSensitivityForm(comm);
			calibrateSensitivityForm->ShowDialog();

			if (calibrateSensitivityForm->DialogResult == Windows::Forms::DialogResult::OK) {
			
			} 
		 }

	 private: System::Void calibratePIDButton_Click(System::Object^  sender, System::EventArgs^  e) {
			Form^ calibratePIDParameters = gcnew CalibratePIDParameters(comm);
			calibratePIDParameters->ShowDialog();

			if (calibratePIDParameters->DialogResult == Windows::Forms::DialogResult::OK) {
			
			} 
		 }

	/* Function: startTrackButton_Click
	 * --------------------------------
	 * Event handler called when the startTrackButton is clicked. Instructs the
	 * trackingBackgroundWorker to track for NUM_CYCLES. Updates form abilities.
	 */
	System::Void startTrackButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(experiment->trackingReady){
		
			this->startTrackButton->Enabled = false;
			trackingBackgroundWorker->RunWorkerAsync(nullptr);

			this->applyStimButton->Enabled = true;
			this->toggleHeadTailButton->Enabled = true;
			this->stopTrackButton->Enabled = true;
			this->setUpExpButton->Enabled = false;
		}
		else {
			MessageBox::Show("Tracking not ready");
		}
	}	

	/* Function: stopTrackButton_Click
	 * -------------------------------
	 * Event handler called when the stopTrackButton is clicked. It raises the cancel flag
	 * for the trackingBackgroundWorker.
	 */
	System::Void stopTrackButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		trackingBackgroundWorker->CancelAsync();
	}

	/* Function: zaberBackgroundWorker_MoveStage
	 * -----------------------------------------
	 * Event handler called when the zaberBackgroundWorker does work. Determines distance
	 * and direction to move the stage and then does so.
	 */
	System::Void zaberBackgroundWorker_MoveStage(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
	{
		BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);
		int direction = safe_cast<int>(e->Argument);
		Movement move;
		move.x = 0;
		move.y = 0;
		double distance;
		switch (stageSpeedDomainUpDown->SelectedIndex) {
		case 0: distance = 10;
			break;
		case 1: distance = 50;
			break;
		case 2: distance = 100;
			break;
		}

		switch (direction) {
		case STAGE_LEFT: move.x = (-1 * distance);
			break;
		case STAGE_RIGHT: move.x = distance;
			break;
		case STAGE_UP: move.y = distance;
			break;
		case STAGE_DOWN: move.y = (-1 * distance);
			break;
		}

		zaber->waitForStaticStage();
		while (true) {
			if (worker->CancellationPending) {
				e->Cancel = true;
				break;
			}
			zaber->moveStage(move);
		}
	}
	System::Void actuatorBackgroundWorker_MoveActuator(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
	{
			BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);
			int movementType = safe_cast<int>(e->Argument);
			


			switch (movementType){
			case RELATIVE_UP_FINE: zaber->moveActuator(-5);
				break;
			case RELATIVE_UP_COARSE: zaber->moveActuator(-50);
				break;
			case RELATIVE_DOWN_FINE: zaber->moveActuator(5);
				break;
			case RELATIVE_DOWN_COARSE: zaber->moveActuator(50);
				break;
			case ABSOLUTE_USER_DEF: zaber->moveActuatorToPosition(Decimal::ToInt32(actuatorPositionNumericUpDown->Value));
				break;
			case ABSOLUTE_HOME: zaber->moveActuatorToPosition(zaber->homePosition);
				break;
			case ABSOLUTE_HOVER: zaber->moveActuatorToPosition(zaber->hoverPosition);
				break;
			case ABSOLUTE_SCAN: zaber->moveActuatorToPosition(zaber->scanPosition);
				break;
			}

			

	}

	/* Function: trackingBackgroundWorker_TrackWorm
	 * --------------------------------------------
	 * Event handler called when the trackingBackgroundWorker does work. Enters a tracking loop
	 * each process involves the following steps: waiting for a static stage, taking an image,
	 * fiding the worm in that image, moving the target point to the cantilever, and recording data
	 * if the stimulus is active.
	 */
	System::Void trackingBackgroundWorker_TrackWorm(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
	{
		TICTOC::timer().tic("WholeWormTrackLoop");

		toggleWormEnds = false;
		experiment->stimulusActive = false;
		experiment->postStimulusRecording = false;
		experiment->trackingActive = true;

		BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);
		double targetLocation = experiment->targetLocation;

		//placeholders
		Mat image;
		SYSTEMTIME time;
		Movement stageMovement;
		WormOutputData data;
		bool toggled = false;
		experiment->stimulusNumber = 0;
		int frameCount = 0;

		int stimulusFinishedCountDown = experiment->waitingBufferSize*12; //convert to frames

		Point cantilever = experiment->cantileverProperties.positionInImageSpace;
		Point2d stagePosition = zaber->getStagePosition();
		Point prevTail;

		while (true) {
			TICTOC::timer().tic("SingleWormTrackLoop");

			frameCount++;
			if (worker->CancellationPending) {
				e->Cancel = true;
				break;
			}
			//update status label with frame number
			toolStripStatusText->Text = Convert::ToString(frameCount);
			//wait for stage to stop moving
			TICTOC::timer().tic("WaitForStage");
			zaber->waitForStaticStage();
			TICTOC::timer().toc("WaitForStage");
			//snap and get image
			imageController->clearOverlay();
			TICTOC::timer().tic("ImageAcqusition");
			image = imageController->getImage();
			TICTOC::timer().toc("ImageAcqusition");
			//find worm
			GetLocalTime(&time);
			TICTOC::timer().tic("FindWorm");
			Worm worm(image, targetLocation, prevTail, frameCount, time);
			TICTOC::timer().toc("FindWorm");
			//overlay key points
			imageController->overlayCircle(worm.head, 20);
			imageController->overlayCircle(worm.tail, 10);
			imageController->overlayCircle(worm.target, 5);
			
			//if (experiment->stimulusActive == false){
				//determine stage movement
				stageMovement = determineStageMovement(worm.target, cantilever);
				//move stage
				TICTOC::timer().tic("MoveStage");
				zaber->moveStage(stageMovement);
				TICTOC::timer().toc("MoveStage");
			//} else {
			//	stageMovement.x = 0;
			//	stageMovement.y = 0;
			//}

			
			data = worm.extractWormOutputData(stageMovement, stagePosition, cantilever, toggled, experiment->stimulusActive, experiment->stimulusNumber+1);
			// based on current status of stimulus, do something with data, report status, etc.
			if (experiment->stimulusActive == true){
				//data = worm.extractWormOutputData(stageMovement, stagePosition, cantilever, toggled, experiment->stimulusActive, experiment->stimulusNumber);
				experiment->dataManager.wormDataBuffer.add(data);
				worker->ReportProgress(WRITE_FRAME);
			}
			//need to record frames until countdown is expired.
			else if (experiment->postStimulusRecording == true && experiment->stimulusActive == false){
				//data = worm.extractWormOutputData(stageMovement, stagePosition, cantilever, toggled, experiment->stimulusActive, experiment->stimulusNumber);
				experiment->dataManager.wormDataBuffer.add(data);
				stimulusFinishedCountDown--;
				worker->ReportProgress(WRITE_FRAME);
				// checks if recording 
				if (stimulusFinishedCountDown == 0) {
					stimulusFinishedCountDown = experiment->postWaitingBufferSize*12; //reset countdown buffer, need to convert to frames, assumes 12 fps
					experiment->postStimulusRecording = false;
					experiment->stimulusNumber++;
					worker->ReportProgress(STIM_DONE);
				}
			}
			// if not recording, keep buffer filled with only the most recent frames.
			else if (experiment->postStimulusRecording == false && experiment->stimulusActive == false)
			{
				experiment->dataManager.wormDataBuffer.add(data);
				if (experiment->dataManager.wormDataBuffer.size() > experiment->waitingBufferSize * 12) {
					experiment->dataManager.wormDataBuffer.get();
				}
			}

			toggled = false;



			stagePosition.x += stageMovement.x;
			stagePosition.y += stageMovement.y;

			if (toggleWormEnds) {
				prevTail = worm.head;
				toggleWormEnds = false;
				toggled = true;
			} else {
				prevTail = worm.tail;
			}

			TICTOC::timer().toc("SingleWormTrackLoop");
		}
		imageController->clearOverlay();
		//update status label
		toolStripStatusText->Text = "Finishing Writing Frames to Disk";
		experiment->trackingActive = false;
		TICTOC::timer().toc("WholeWormTrackLoop");
	}

	/* Function: trackingBackgroundWorker_ProgressChanged
	 * --------------------------------------------------
	 * Event handler called when the trackingBackgroundWorker reports progress. A frame of
	 * tracking data is written.
	 */
	System::Void trackingBackgroundWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
	{
		int argument = safe_cast<int>(e->ProgressPercentage);
		if (argument == STIM_DONE) {
			applyStimButton->Enabled = true;
		} else if (argument == WRITE_FRAME) {
			writeAFrameOfDataToDisk();
		}
	}

	/* Function: trackingBackgroundWorker_RunWorkerCompleted
	 * -----------------------------------------------------
	 * Event handler called when the trackingBackgroundWorker is done doing work. If there
	 * was an error that error is posted. If the tracking was stopped by the user the
	 * status indicates as much. If the tracker completed it's cycles on its own the status
	 * shows as "Tracking Completed". Poste Experiment notes are collected using the
	 * PostExperimentForm that is shown.
	 */
	System::Void trackingBackgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
	{
		this->toggleHeadTailButton->Enabled = false;
		this->stopTrackButton->Enabled = false;

		if (e->Error) {
			MessageBox::Show(e->Error->Message->ToString());
		} else if (e->Cancelled) {
			toolStripStatusText->Text = "Tracking Stopped";
			Form^ postExpForm = gcnew PostExperimentForm(experiment);
			postExpForm->ShowDialog();
		} else {
			toolStripStatusText->Text = "Tracking Completed";
			Form^ postExpForm = gcnew PostExperimentForm(experiment);
			postExpForm->ShowDialog();
		}

		experiment->endExperiment();
		delete experiment;
		experiment = NULL;

		this->setUpExpButton->Enabled = true;	
	}

	/* Function: forceClampBackgroundWorker_CheckStatus
	 * ------------------------------------------------
	 * A constantly running event that is checking the status of the force clamp TCP/IP
	 * connection. It updates the form indicator upon connection and disconnection.
	 */
	System::Void forceClampBackgroundWorker_CheckStatus(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
	{
		BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);

		std::clock_t start;
		bool stimStarted = true;

		int stimNum = 0;
		while (true) {
			
			if (worker->CancellationPending) {
				e->Cancel = true;
				break;
			}
			
			if (comm->connected) {
				fpgaConnectionIndicationPanel->BackColor = System::Drawing::Color::Green;
			} else {
				fpgaConnectionIndicationPanel->BackColor = System::Drawing::Color::Red;
			}
			
			if (comm->stimulusCompleted) {
				comm->stimulusCompleted = false;
				comm->stimulusStarted = false;
				experiment->stimulusActive = false;
				experiment->postStimulusRecording = true;
				//stimNum ++;

				// need to append stimulus data to .yaml file
				int size = comm->piezoSignalData.size();
				experiment->writefpgaDataToDisk( experiment->stimulusNumber+1, comm->piezoSignalData,  comm->actuatorPositionData, comm->actuatorCommandData, comm->desiredSignalData);
				comm->messageReceivedCount = 0;
			} 
			 

			if(comm->stimulusStarted){
				if(stimStarted == true){
					start = std::clock();
					stimStarted = false;
				} else { // not sure if this works:
					if (( std::clock() - start ) / (double) CLOCKS_PER_SEC > experiment->stim.totalTime){
						experiment->stimulusActive = false;
						experiment->postStimulusRecording = true;
						stimStarted = true;
					}
				}
			}

			Threading::Thread::Sleep(100);
		}
		
	}


	/* Function: MainForm_Load
	 * -----------------------
	 * When the form loads the camera and zaber controller are connected. The z actuator is
	 * raised all the way and if the FPGA is connected the inidactor is turned green.
	 */
	System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		connectHardware();
		//zaber->moveActuatorToPosition(0);
		forceClampBackgroundWorker->RunWorkerAsync(nullptr);

		actuatorBackgroundWorker->RunWorkerAsync(ABSOLUTE_HOME);
		actuatorPositionNumericUpDown->Value = Decimal(zaber->homePosition);

		experiment->experimentSetUp = false;
		experiment->stimulusReady = false;
		experiment->trackingReady = false;
		experiment->trackingActive = false;
		experiment->stimulusActive = false;
		experiment->postStimulusRecording = false;
	}

	/* Function: MainForm_Close
	 * ------------------------
	 * When the form closes the z actuator is raised completely without any
	 * wait for completion.
	 */
	System::Void MainForm_Close(System::Object^  sender, System::EventArgs^  e)
	{
		trackingBackgroundWorker->CancelAsync();
		forceClampBackgroundWorker->CancelAsync();
		//zaber->moveActuatorHome();
		actuatorBackgroundWorker->RunWorkerAsync(ABSOLUTE_HOME);
		actuatorPositionNumericUpDown->Value = Decimal(zaber->homePosition);
	}

	/* Function: setCantileverPositionManually
	 * ---------------------------------------
	 * The user is prompted to prepare the cantilever for selection. A handler for clicking on
	 * the liveFeedPanel is then added.
	 */
	void setCantileverPositionManually(void)
	{
		MessageBox::Show("Lower the cantilever to Scan Position, center it manually, and click on the tip.");
		liveFeedPanel->MouseDown += gcnew MouseEventHandler(this, &MainForm::liveFeedPanel_MouseDown);
		toolStripStatusText->Text = "ACTION - Click On The Cantilever Tip";
	}

	/* Function: liveFeedPanel_MouseDown
	 * ---------------------------------
	 * Event handler for mousing down anywhere in the liveFeedPanel. The point of the event is found
	 * The user is prompted to confirm their choice. Once they confirm that point is set as the
	 * cantilever posisiton and this event handler is taken away.
	 */
	System::Void liveFeedPanel_MouseDown(System::Object^  sender, MouseEventArgs^  e)
	{
		System::Drawing::Point cursorPoint = liveFeedPanel->PointToClient(Cursor->Position);
		Point cvCursorPoint = Point((int)(cursorPoint.X * IMAGE_RESIZE_SCALE/SCREEN_RESIZE_SCALE), (int)(cursorPoint.Y * IMAGE_RESIZE_SCALE/SCREEN_RESIZE_SCALE));
		imageController->overlayCircle(cvCursorPoint, 10);
		Windows::Forms::DialogResult confirmResult = MessageBox::Show("Did you click accurately on the cantilever tip?", "Confirm Cantilever Position", MessageBoxButtons::YesNo);
		if (confirmResult ==  Windows::Forms::DialogResult::Yes) {
			liveFeedPanel->MouseDown -= gcnew MouseEventHandler(this, &MainForm::liveFeedPanel_MouseDown);
			experiment->cantileverProperties.positionInImageSpace = cvCursorPoint;
			//toolStripStatusText->Text = "Experiment Set Up Complete";
			//this->setUpExpButton->Enabled = true;
			//this->startTrackButton->Enabled = true;
		}
		imageController->clearOverlay();
	}

	/* Function: connectHardware
	 * -------------------------
	 * A new Zaber object is created. It opens up the port to the zaber controller and stes the
	 * moveUnit to microns. Then a new imageController object is created and that is connected
	 * and displayed within the form. The status reflects completetion.
	 */
	void connectHardware(void)
	{
		zaber = gcnew Zaber;
		zaber->moveUnit = MICROMETER;
		int zaberResult = zaber->openPort();

		if (zaberResult != 0) {
			MessageBox::Show("Zaber Connection Failed");
			this->Close();
		} else {
			imageController = new ImageController;
			HWND hwnd = static_cast<HWND>(this->liveFeedPanel->Handle.ToPointer());
			int cameraResult = imageController->setUpCamera(hwnd);

			if (cameraResult == CAMERA_DEVICE_SELECTION_ERROR) {
				MessageBox::Show("Camera Connection Failed");
				this->Close();
			} else {
				toolStripStatusText->Text = "Zaber Controller and Camera Connected";
			}
		}
	}

	/* Function: disconnectHardware
	 * ----------------------------
	 * The zaber controller and camera are closed and their controlling objects are deleted.
	 */
	void disconnectHardware(void)
	{
		if (zaber) {
			zaber->closePort();
			delete zaber;
		}
		if (imageController) {
			imageController->closeCamera();
			delete imageController;
		}
	}

		/* Function: toggleHeadTailButton_Click
	 * ------------------------------------
	 * The global flag for a head/tail toggle is raised.
	  */
	
	System::Void toggleHeadTailButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		toggleWormEnds = true;
	}

	/* Function: toggleHeadTailButton_Click
	 * ------------------------------------
	 * The STM_Communicator triggers the stimulus. The global flag for an active stimulus is raised.
	 * The prestimulus frames are written to disk.
	 */
	System::Void applyStimButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		applyStimButton->Enabled = false;
		experiment->stimulusActive = true;
		int currSize = experiment->dataManager.wormDataBuffer.size();
		comm->triggerStimulus();
		for (int i = 0; i < currSize; i++) {
			writeAFrameOfDataToDisk();
		}
	}

	/* Function: endStimulusButton_Click
	 * ---------------------------------
	 * Click event handler to end a stimulus. It clears the wave table from the fpga and
	 * ends the current stimulus.
	 */
	System::Void endStimulusButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		comm->cancelStimulus();
		comm->stimulusCompleted = true;
		//experiment->stimulusActive = false;
		//experiment->postStimulusRecording = true;
	}

	/* Function: writeAFrameOfDataToDisk
	 * ---------------------------------
	 * A frame of data is removed from the wormDataBuffer in the experiment's dataManager.
	 * That frame is sritten to disk.
	 */
	void writeAFrameOfDataToDisk(void)
	{
		//get wormData from buffer
		WormOutputData data = experiment->dataManager.wormDataBuffer.get();
		//write wormData to disk
		TICTOC::timer().tic("WriteToDisk");
		experiment->writeFrameToDisk(data);
		TICTOC::timer().toc("WriteToDisk");
	}

	/* Function: autoExposeRadioButton_Click
	 * -------------------------------------
	 * Click event handler for autoExposeRadioButton. If it is selected the camera is
	 * set to control its own exposure automatically.
	 */
	System::Void autoExposeRadioButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (autoExposeRadioButton->Checked) {
			imageController->autoExposeOn();
		}
	}

	/* Function: defaultExposeRadioButton_Click
	 * ----------------------------------------
	 * Click event handler for defaultExposeRadioButton. If it is selected the camera has
	 * its exposure set to the program default.
	 */
	System::Void defaultExposeRadioButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (defaultExposeRadioButton->Checked) {
			imageController->autoExposeOff();
		}
	}



	/* Function: moveStageLeftButton_MouseDown
	 * ---------------------------------------
	 * The zaberBackgroundWorker is told to do work with the argument for moving left.
	 */
	System::Void moveStageLeftButton_MouseDown(System::Object^  sender, MouseEventArgs^  e)
	{
		if (!zaberBackgroundWorker->IsBusy) {
			zaberBackgroundWorker->RunWorkerAsync(STAGE_LEFT);
		}
	}

	/* Function: moveStageRightButton_MouseDown
	 * ----------------------------------------
	 * The zaberBackgroundWorker is told to do work with the argument for moving right.
	 */
	System::Void moveStageRightButton_MouseDown(System::Object^  sender, MouseEventArgs^  e)
	{
		if (!zaberBackgroundWorker->IsBusy) {
			zaberBackgroundWorker->RunWorkerAsync(STAGE_RIGHT);
		}
	}

	/* Function: moveStageUpButton_MouseDown
	 * -------------------------------------
	 * The zaberBackgroundWorker is told to do work with the argument for moving up.
	 */
	System::Void moveStageUpButton_MouseDown(System::Object^  sender, MouseEventArgs^  e)
	{
		if (!zaberBackgroundWorker->IsBusy) {
			zaberBackgroundWorker->RunWorkerAsync(STAGE_UP);
		}
	}

	/* Function: moveStageDownButton_MouseDown
	 * ---------------------------------------
	 * The zaberBackgroundWorker is told to do work with the argument for moving down.
	 */
	System::Void moveStageDownButton_MouseDown(System::Object^  sender, MouseEventArgs^  e)
	{
		if (!zaberBackgroundWorker->IsBusy) {
			zaberBackgroundWorker->RunWorkerAsync(STAGE_DOWN);
		}
	}

	/* Function: moveStageLeftButton_MouseUp
	 * -------------------------------------
	 * The cancel flag for zaberBackgroundWorker is raised.
	 */
	System::Void moveStageLeftButton_MouseUp(System::Object^  sender, MouseEventArgs^  e)
	{
		zaberBackgroundWorker->CancelAsync();
	}

	/* Function: moveStageRightButton_MouseUp
	 * --------------------------------------
	 * The cancel flag for zaberBackgroundWorker is raised.
	 */
	System::Void moveStageRightButton_MouseUp(System::Object^  sender, MouseEventArgs^  e)
	{
		zaberBackgroundWorker->CancelAsync();
	}

	/* Function: moveStageUpButton_MouseUp
	 * -----------------------------------
	 * The cancel flag for zaberBackgroundWorker is raised.
	 */
	System::Void moveStageUpButton_MouseUp(System::Object^  sender, MouseEventArgs^  e)
	{
		zaberBackgroundWorker->CancelAsync();
	}

	/* Function: moveStageDownButton_MouseUp
	 * -------------------------------------
	 * The cancel flag for zaberBackgroundWorker is raised.
	 */
	System::Void moveStageDownButton_MouseUp(System::Object^  sender, MouseEventArgs^  e)
	{
		zaberBackgroundWorker->CancelAsync();
	}




	/* Function: moveActuatorButton_Click
	 * ----------------------------------
	 * The zaber controller moves the z actuator to whatever position is in the
	 * corresponding numericUpDown.
	 */
	System::Void moveActuatorButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//zaber->moveActuatorToPosition(Decimal::ToInt32(actuatorPositionNumericUpDown->Value));
		if (!actuatorBackgroundWorker->IsBusy) {
			actuatorBackgroundWorker->RunWorkerAsync(ABSOLUTE_USER_DEF);
		}
	}
	/* Function: raiseActuatorButton_Click
	 * -----------------------------------
	 * Click event handler for the raiseActuatorButton. The z actuator is raised by either
	 * 5 or 50 microns depending on the resolution shown in the actuatorResolutionDomainUpDown.
	 * The actuatorPositionNumericUpDown is updated to show the current position.
	 */
	System::Void raiseActuatorButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		double distance = (actuatorResolutionDomainUpDown->SelectedIndex == 0) ? -5 : -50;
		//zaber->moveActuator(distance);
		Decimal value = Decimal::Add(Decimal(distance), actuatorPositionNumericUpDown->Value);
		if (value >= 0)
			actuatorPositionNumericUpDown->Value = value;
		else 
			actuatorPositionNumericUpDown->Value = 0;

		if (!actuatorBackgroundWorker->IsBusy) {
			if (distance == -5)
				actuatorBackgroundWorker->RunWorkerAsync(RELATIVE_UP_FINE);
			else 
				actuatorBackgroundWorker->RunWorkerAsync(RELATIVE_UP_COARSE);
		}

	}

	/* Function: lowerActuatorButton_Click
	 * -----------------------------------
	 * Click event handler for the lowerActuatorButton. The z actuator is lowered by either
	 * 5 or 50 microns depending on the resolution shown in the actuatorResolutionDomainUpDown.
	 * The actuatorPositionNumericUpDown is updated to show the current position.
	 */
	System::Void lowerActuatorButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//int index = actuatorResolutionDomainUpDown->SelectedIndex;
		double distance = (actuatorResolutionDomainUpDown->SelectedIndex == 0) ? 5 : 50;
		//zaber->moveActuator(distance);
		actuatorPositionNumericUpDown->Value = Decimal::Add(Decimal(distance), actuatorPositionNumericUpDown->Value);
		if (!actuatorBackgroundWorker->IsBusy) {
			if (distance == 5)
				actuatorBackgroundWorker->RunWorkerAsync(RELATIVE_DOWN_FINE);
			else 
				actuatorBackgroundWorker->RunWorkerAsync(RELATIVE_DOWN_COARSE);
		}
	}

	/* Function: actuatorHomeButton_Click
	 * ----------------------------------
	 * Click event handler for the actuatorHomeButton. The z actuator is moved to its home (0)
	 * position. The actuatorPositionNumericUpDown is updated to show the current position.
	 */
	System::Void actuatorHomeButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!actuatorBackgroundWorker->IsBusy) {
			actuatorBackgroundWorker->RunWorkerAsync(ABSOLUTE_HOME);
			actuatorPositionNumericUpDown->Value = Decimal(zaber->homePosition);
		}
		
	}

	/* Function: actuatorHovPosButton_Click
	 * ------------------------------------
	 * Click event handler for the actuatorHovPosButton. The z actuator is moved to the
	 * hover position. The actuatorPositionNumericUpDown is updated to show the current position.
	 */
	System::Void actuatorHovPosButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!actuatorBackgroundWorker->IsBusy) {
			actuatorBackgroundWorker->RunWorkerAsync(ABSOLUTE_HOVER);
			actuatorPositionNumericUpDown->Value = Decimal(zaber->hoverPosition);
		}
		
		
	}

	/* Function: actuatorScanPosButton_Click
	 * -------------------------------------
	 * Click event handler for the actuatorScanPosButton. The z actuator is moved to the
	 * scan position. The actuatorPositionNumericUpDown is updated to show the current position.
	 */
	System::Void actuatorScanPosButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!actuatorBackgroundWorker->IsBusy) {
			actuatorBackgroundWorker->RunWorkerAsync(ABSOLUTE_SCAN);
			actuatorPositionNumericUpDown->Value = Decimal(zaber->scanPosition);
		}
		
		
	}



private: System::Void setScanPositionButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 zaber->scanPosition = Decimal::ToInt32(actuatorPositionNumericUpDown->Value);
			
		 }
private: System::Void setHoverPositionButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 zaber->hoverPosition = Decimal::ToInt32(actuatorPositionNumericUpDown->Value);
		 }


};
}

