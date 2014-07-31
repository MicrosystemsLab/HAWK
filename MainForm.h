#pragma once

#include "SafeQueue.h"
#include "Worm.h"
#include "Experiment.h"
#include "Zaber.h"
#include "ImageControl.h"
#include "SetUpForm.h"

#define NUM_CYCLES 1500

namespace BehaviorRig {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;

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

			if (components) {
				delete components;
			}
		}

	private: Zaber^ zaber;
	private: Experiment* experiment;
	private: ImageController* imageController;

#pragma region Components
	private: System::Windows::Forms::Panel^  liveFeedPanel;
	private: System::Windows::Forms::Button^  setUpExpButton;
	private: System::Windows::Forms::GroupBox^  trackingGroupBox;
	private: System::Windows::Forms::Button^  startTrackButton;
	private: System::Windows::Forms::Button^  stopTrackButton;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker;
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
	private: System::Windows::Forms::DomainUpDown^  stageResolutionDomainUpDown;
	private: System::Windows::Forms::Label^  stageResolutionLabel;
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
			this->setUpExpButton = (gcnew System::Windows::Forms::Button());
			this->startTrackButton = (gcnew System::Windows::Forms::Button());
			this->stopTrackButton = (gcnew System::Windows::Forms::Button());
			this->trackingGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->liveFeedPanel = (gcnew System::Windows::Forms::Panel());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusText = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->moveActuatorButton = (gcnew System::Windows::Forms::Button());
			this->actuatorPositionNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->actuatorMovementGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->actuatorResolutionDomainUpDown = (gcnew System::Windows::Forms::DomainUpDown());
			this->actuatorResolutionLabel = (gcnew System::Windows::Forms::Label());
			this->actuatorHomeButton = (gcnew System::Windows::Forms::Button());
			this->lowerActuatorButton = (gcnew System::Windows::Forms::Button());
			this->raiseActuatorButton = (gcnew System::Windows::Forms::Button());
			this->stageMovementGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->stageResolutionDomainUpDown = (gcnew System::Windows::Forms::DomainUpDown());
			this->stageResolutionLabel = (gcnew System::Windows::Forms::Label());
			this->moveStageDownButton = (gcnew System::Windows::Forms::Button());
			this->moveStageUpButton = (gcnew System::Windows::Forms::Button());
			this->moveStageRightButton = (gcnew System::Windows::Forms::Button());
			this->moveStageLeftButton = (gcnew System::Windows::Forms::Button());
			this->trackingGroupBox->SuspendLayout();
			this->statusStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->actuatorPositionNumericUpDown))->BeginInit();
			this->actuatorMovementGroupBox->SuspendLayout();
			this->stageMovementGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// setUpExpButton
			// 
			this->setUpExpButton->Location = System::Drawing::Point(12, 12);
			this->setUpExpButton->Name = L"setUpExpButton";
			this->setUpExpButton->Size = System::Drawing::Size(109, 23);
			this->setUpExpButton->TabIndex = 0;
			this->setUpExpButton->Text = L"Set Up Experiment";
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
			this->startTrackButton->Text = L"Commence";
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
			this->stopTrackButton->Text = L"Force Stop";
			this->stopTrackButton->UseVisualStyleBackColor = true;
			this->stopTrackButton->Click += gcnew System::EventHandler(this, &MainForm::stopTrackButton_Click);
			// 
			// trackingGroupBox
			// 
			this->trackingGroupBox->Controls->Add(this->startTrackButton);
			this->trackingGroupBox->Controls->Add(this->stopTrackButton);
			this->trackingGroupBox->Location = System::Drawing::Point(12, 41);
			this->trackingGroupBox->Name = L"trackingGroupBox";
			this->trackingGroupBox->Size = System::Drawing::Size(109, 77);
			this->trackingGroupBox->TabIndex = 11;
			this->trackingGroupBox->TabStop = false;
			this->trackingGroupBox->Text = L"Tracking";
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->WorkerReportsProgress = true;
			this->backgroundWorker->WorkerSupportsCancellation = true;
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker_TrackWorm);
			this->backgroundWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MainForm::backgroundWorker_ProgressChanged);
			this->backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorker_RunWorkerCompleted);
			// 
			// liveFeedPanel
			// 
			this->liveFeedPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->liveFeedPanel->Location = System::Drawing::Point(127, 12);
			this->liveFeedPanel->Name = L"liveFeedPanel";
			this->liveFeedPanel->Size = System::Drawing::Size(768, 576);
			this->liveFeedPanel->TabIndex = 18;
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripStatusLabel, 
				this->toolStripStatusText});
			this->statusStrip->Location = System::Drawing::Point(0, 597);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(908, 22);
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
			this->moveActuatorButton->Location = System::Drawing::Point(6, 145);
			this->moveActuatorButton->Name = L"moveActuatorButton";
			this->moveActuatorButton->Size = System::Drawing::Size(97, 23);
			this->moveActuatorButton->TabIndex = 20;
			this->moveActuatorButton->Text = L"Move to Positon:";
			this->moveActuatorButton->UseVisualStyleBackColor = true;
			this->moveActuatorButton->Click += gcnew System::EventHandler(this, &MainForm::moveActuatorButton_Click);
			// 
			// actuatorPositionNumericUpDown
			// 
			this->actuatorPositionNumericUpDown->Location = System::Drawing::Point(7, 174);
			this->actuatorPositionNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {50000, 0, 0, 0});
			this->actuatorPositionNumericUpDown->Name = L"actuatorPositionNumericUpDown";
			this->actuatorPositionNumericUpDown->Size = System::Drawing::Size(96, 20);
			this->actuatorPositionNumericUpDown->TabIndex = 21;
			// 
			// actuatorMovementGroupBox
			// 
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorResolutionDomainUpDown);
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorResolutionLabel);
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorPositionNumericUpDown);
			this->actuatorMovementGroupBox->Controls->Add(this->actuatorHomeButton);
			this->actuatorMovementGroupBox->Controls->Add(this->moveActuatorButton);
			this->actuatorMovementGroupBox->Controls->Add(this->lowerActuatorButton);
			this->actuatorMovementGroupBox->Controls->Add(this->raiseActuatorButton);
			this->actuatorMovementGroupBox->Location = System::Drawing::Point(12, 276);
			this->actuatorMovementGroupBox->Name = L"actuatorMovementGroupBox";
			this->actuatorMovementGroupBox->Size = System::Drawing::Size(109, 202);
			this->actuatorMovementGroupBox->TabIndex = 29;
			this->actuatorMovementGroupBox->TabStop = false;
			this->actuatorMovementGroupBox->Text = L"Actuator";
			// 
			// actuatorResolutionDomainUpDown
			// 
			this->actuatorResolutionDomainUpDown->Items->Add(L"Fine");
			this->actuatorResolutionDomainUpDown->Items->Add(L"Coarse");
			this->actuatorResolutionDomainUpDown->Location = System::Drawing::Point(6, 119);
			this->actuatorResolutionDomainUpDown->Name = L"actuatorResolutionDomainUpDown";
			this->actuatorResolutionDomainUpDown->SelectedIndex = 0;
			this->actuatorResolutionDomainUpDown->Size = System::Drawing::Size(97, 20);
			this->actuatorResolutionDomainUpDown->TabIndex = 31;
			this->actuatorResolutionDomainUpDown->Text = L"Fine";
			// 
			// actuatorResolutionLabel
			// 
			this->actuatorResolutionLabel->AutoSize = true;
			this->actuatorResolutionLabel->Location = System::Drawing::Point(6, 103);
			this->actuatorResolutionLabel->Name = L"actuatorResolutionLabel";
			this->actuatorResolutionLabel->Size = System::Drawing::Size(60, 13);
			this->actuatorResolutionLabel->TabIndex = 32;
			this->actuatorResolutionLabel->Text = L"Resolution:";
			// 
			// actuatorHomeButton
			// 
			this->actuatorHomeButton->Location = System::Drawing::Point(6, 19);
			this->actuatorHomeButton->Name = L"actuatorHomeButton";
			this->actuatorHomeButton->Size = System::Drawing::Size(97, 23);
			this->actuatorHomeButton->TabIndex = 2;
			this->actuatorHomeButton->Text = L"Home Position";
			this->actuatorHomeButton->UseVisualStyleBackColor = true;
			this->actuatorHomeButton->Click += gcnew System::EventHandler(this, &MainForm::actuatorHomeButton_Click);
			// 
			// lowerActuatorButton
			// 
			this->lowerActuatorButton->Location = System::Drawing::Point(6, 77);
			this->lowerActuatorButton->Name = L"lowerActuatorButton";
			this->lowerActuatorButton->Size = System::Drawing::Size(97, 23);
			this->lowerActuatorButton->TabIndex = 1;
			this->lowerActuatorButton->Text = L"Lower";
			this->lowerActuatorButton->UseVisualStyleBackColor = true;
			this->lowerActuatorButton->Click += gcnew System::EventHandler(this, &MainForm::lowerActuatorButton_Click);
			// 
			// raiseActuatorButton
			// 
			this->raiseActuatorButton->Location = System::Drawing::Point(6, 48);
			this->raiseActuatorButton->Name = L"raiseActuatorButton";
			this->raiseActuatorButton->Size = System::Drawing::Size(97, 23);
			this->raiseActuatorButton->TabIndex = 0;
			this->raiseActuatorButton->Text = L"Raise";
			this->raiseActuatorButton->UseVisualStyleBackColor = true;
			this->raiseActuatorButton->Click += gcnew System::EventHandler(this, &MainForm::raiseActuatorButton_Click);
			// 
			// stageMovementGroupBox
			// 
			this->stageMovementGroupBox->Controls->Add(this->stageResolutionDomainUpDown);
			this->stageMovementGroupBox->Controls->Add(this->stageResolutionLabel);
			this->stageMovementGroupBox->Controls->Add(this->moveStageDownButton);
			this->stageMovementGroupBox->Controls->Add(this->moveStageUpButton);
			this->stageMovementGroupBox->Controls->Add(this->moveStageRightButton);
			this->stageMovementGroupBox->Controls->Add(this->moveStageLeftButton);
			this->stageMovementGroupBox->Location = System::Drawing::Point(12, 124);
			this->stageMovementGroupBox->Name = L"stageMovementGroupBox";
			this->stageMovementGroupBox->Size = System::Drawing::Size(109, 146);
			this->stageMovementGroupBox->TabIndex = 30;
			this->stageMovementGroupBox->TabStop = false;
			this->stageMovementGroupBox->Text = L"Stage";
			// 
			// stageResolutionDomainUpDown
			// 
			this->stageResolutionDomainUpDown->Items->Add(L"Fine");
			this->stageResolutionDomainUpDown->Items->Add(L"Coarse");
			this->stageResolutionDomainUpDown->Location = System::Drawing::Point(6, 119);
			this->stageResolutionDomainUpDown->Name = L"stageResolutionDomainUpDown";
			this->stageResolutionDomainUpDown->SelectedIndex = 0;
			this->stageResolutionDomainUpDown->Size = System::Drawing::Size(97, 20);
			this->stageResolutionDomainUpDown->TabIndex = 33;
			this->stageResolutionDomainUpDown->Text = L"Fine";
			// 
			// stageResolutionLabel
			// 
			this->stageResolutionLabel->AutoSize = true;
			this->stageResolutionLabel->Location = System::Drawing::Point(6, 103);
			this->stageResolutionLabel->Name = L"stageResolutionLabel";
			this->stageResolutionLabel->Size = System::Drawing::Size(60, 13);
			this->stageResolutionLabel->TabIndex = 34;
			this->stageResolutionLabel->Text = L"Resolution:";
			// 
			// moveStageDownButton
			// 
			this->moveStageDownButton->Location = System::Drawing::Point(31, 77);
			this->moveStageDownButton->Name = L"moveStageDownButton";
			this->moveStageDownButton->Size = System::Drawing::Size(45, 23);
			this->moveStageDownButton->TabIndex = 3;
			this->moveStageDownButton->Text = L"v";
			this->moveStageDownButton->UseVisualStyleBackColor = true;
			this->moveStageDownButton->Click += gcnew System::EventHandler(this, &MainForm::moveStageDownButton_Click);
			// 
			// moveStageUpButton
			// 
			this->moveStageUpButton->Location = System::Drawing::Point(31, 19);
			this->moveStageUpButton->Name = L"moveStageUpButton";
			this->moveStageUpButton->Size = System::Drawing::Size(45, 23);
			this->moveStageUpButton->TabIndex = 2;
			this->moveStageUpButton->Text = L"^";
			this->moveStageUpButton->UseVisualStyleBackColor = true;
			this->moveStageUpButton->Click += gcnew System::EventHandler(this, &MainForm::moveStageUpButton_Click);
			// 
			// moveStageRightButton
			// 
			this->moveStageRightButton->Location = System::Drawing::Point(58, 48);
			this->moveStageRightButton->Name = L"moveStageRightButton";
			this->moveStageRightButton->Size = System::Drawing::Size(45, 23);
			this->moveStageRightButton->TabIndex = 1;
			this->moveStageRightButton->Text = L">";
			this->moveStageRightButton->UseVisualStyleBackColor = true;
			this->moveStageRightButton->Click += gcnew System::EventHandler(this, &MainForm::moveStageRightButton_Click);
			// 
			// moveStageLeftButton
			// 
			this->moveStageLeftButton->Location = System::Drawing::Point(6, 48);
			this->moveStageLeftButton->Name = L"moveStageLeftButton";
			this->moveStageLeftButton->Size = System::Drawing::Size(45, 23);
			this->moveStageLeftButton->TabIndex = 0;
			this->moveStageLeftButton->Text = L"<";
			this->moveStageLeftButton->UseVisualStyleBackColor = true;
			this->moveStageLeftButton->Click += gcnew System::EventHandler(this, &MainForm::moveStageLeftButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(908, 619);
			this->Controls->Add(this->stageMovementGroupBox);
			this->Controls->Add(this->actuatorMovementGroupBox);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->liveFeedPanel);
			this->Controls->Add(this->trackingGroupBox);
			this->Controls->Add(this->setUpExpButton);
			this->Name = L"MainForm";
			this->Text = L"H.A.W.K.";
			this->Closed += gcnew System::EventHandler(this, &MainForm::MainForm_Close);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->trackingGroupBox->ResumeLayout(false);
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->actuatorPositionNumericUpDown))->EndInit();
			this->actuatorMovementGroupBox->ResumeLayout(false);
			this->actuatorMovementGroupBox->PerformLayout();
			this->stageMovementGroupBox->ResumeLayout(false);
			this->stageMovementGroupBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private:
	System::Void setUpExpButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (experiment) {
			experiment->endExperiment();
			delete experiment;
		}
		experiment = new Experiment;

		Form^ setUpForm = gcnew SetUpForm(experiment);
		setUpForm->ShowDialog();

		if (setUpForm->DialogResult == Windows::Forms::DialogResult::OK) {
			experiment->cantileverProperties.positionInImageSpace = Point((int)(CANTILEVER_X_PIXEL * IMAGE_RESIZE_SCALE), (int)(CANTILEVER_Y_PIXEL * IMAGE_RESIZE_SCALE));
			toolStripStatusText->Text = "Experiment Set Up Complete";
			this->startTrackButton->Enabled = true;
		} else if (setUpForm->DialogResult == Windows::Forms::DialogResult::Cancel) {
			experiment->endExperiment();
			delete experiment;
			experiment = NULL;
			toolStripStatusText->Text = "Experiment Set Up Canceled";
		}
	}

	System::Void startTrackButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->startTrackButton->Enabled = false;
		
		backgroundWorker->RunWorkerAsync(NUM_CYCLES);

		this->stopTrackButton->Enabled = true;
		this->setUpExpButton->Enabled = false;
	}	

	System::Void stopTrackButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		backgroundWorker->CancelAsync();
	}

	System::Void backgroundWorker_TrackWorm(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
	{
		TICTOC::timer().tic("WholeWormTrackLoop");

		BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);
		int nframes = safe_cast<int>(e->Argument);
		double targetLocation = experiment->targetLocation;

		//placeholders
		Mat image;
		Movement stageMovement;
		WormOutputData data;

		Point2d stagePosition = zaber->getStagePosition();
		Point prevTail;

		for (int i = 0; i < nframes; i++) {
			TICTOC::timer().tic("SingleWormTrackLoop");

			if (worker->CancellationPending) {
				e->Cancel = true;
				break;
			}

			//wait for stage to stop moving
			TICTOC::timer().tic("WaitForStage");
			zaber->waitForStaticStage();
			TICTOC::timer().toc("WaitForStage");
			//snap and get image
			TICTOC::timer().tic("ImageAcqusition");
			image = imageController->getImage();
			TICTOC::timer().toc("ImageAcqusition");
			//find worm
			TICTOC::timer().tic("FindWorm");
			Worm worm(image, targetLocation, prevTail, i + 1);
			TICTOC::timer().toc("FindWorm");
			//determine stage movement
			stageMovement = determineStageMovement(worm.target, experiment->cantileverProperties.positionInImageSpace);
			//move stage
			TICTOC::timer().tic("MoveStage");
			zaber->moveStage(stageMovement);
			TICTOC::timer().toc("MoveStage");

			//put worm data in buffer
			data = worm.extractWormOutputData(stageMovement, stagePosition);
			experiment->dataManager.wormDataBuffer.add(data);

			worker->ReportProgress(NULL);

			stagePosition.x += stageMovement.x;
			stagePosition.y += stageMovement.y;

			prevTail = worm.tail;

			TICTOC::timer().toc("SingleWormTrackLoop");
		}
		TICTOC::timer().toc("WholeWormTrackLoop");
	}

	System::Void backgroundWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
	{
		//get wormData from buffer
		WormOutputData data = experiment->dataManager.wormDataBuffer.get();
		//update status label
		toolStripStatusText->Text = Convert::ToString(data.frameNumber);
		//write wormData to disk
		TICTOC::timer().tic("WriteToDisk");
		experiment->writeFrameToDisk(data);
		TICTOC::timer().toc("WriteToDisk");
	}

	System::Void backgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
	{
		this->stopTrackButton->Enabled = false;

		if (e->Error) {
			MessageBox::Show(e->Error->Message->ToString());
		} else if (e->Cancelled) {
			toolStripStatusText->Text = "Cancelled";
		} else {
			toolStripStatusText->Text = "Complete";
		}

		experiment->endExperiment();
		delete experiment;
		experiment = NULL;

		this->setUpExpButton->Enabled = true;	
	}

	System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		connectHardware();
		zaber->moveActuatorToPosition(0);
	}

	System::Void MainForm_Close(System::Object^  sender, System::EventArgs^  e)
	{
		zaber->moveActuatorToPosition(0);
	}

	void connectHardware(void)
	{
		zaber = gcnew Zaber;
		zaber->openPort();
		zaber->moveUnit = MICROMETER;
	
		imageController = new ImageController;
		HWND hwnd = static_cast<HWND>(this->liveFeedPanel->Handle.ToPointer());
		int cameraResult = imageController->setUpCamera(hwnd);

		if (cameraResult == CAMERA_DEVICE_SELECTION_ERROR) {
			MessageBox::Show("Camera Connection Failed");
			this->Close();
		} else {
			toolStripStatusText->Text = "Hardware Connected";
		}
	}

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

	System::Void moveActuatorButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		zaber->moveActuatorToPosition(Decimal::ToInt32(actuatorPositionNumericUpDown->Value));
	}

	System::Void moveStageLeftButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Movement move;
		move.x = (stageResolutionDomainUpDown->SelectedIndex == 0) ? -50 : -500;
		move.y = 0;
		zaber->moveStage(move);
	}

	System::Void moveStageRightButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Movement move;
		move.x = (stageResolutionDomainUpDown->SelectedIndex == 0) ? 50 : 500;
		move.y = 0;
		zaber->moveStage(move);
	}

	System::Void moveStageUpButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Movement move;
		move.x = 0;
		move.y = (stageResolutionDomainUpDown->SelectedIndex == 0) ? 50 : 500;
		zaber->moveStage(move);
	}

	System::Void moveStageDownButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Movement move;
		move.x = 0;
		move.y = (stageResolutionDomainUpDown->SelectedIndex == 0) ? -50 : -500;
		zaber->moveStage(move);
	}

	System::Void raiseActuatorButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		double distance = (actuatorResolutionDomainUpDown->SelectedIndex == 0) ? -5 : -50;
		zaber->moveActuator(distance);
	}

	System::Void lowerActuatorButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		int index = actuatorResolutionDomainUpDown->SelectedIndex;
		double distance = (actuatorResolutionDomainUpDown->SelectedIndex == 0) ? 5 : 50;
		zaber->moveActuator(distance);
	}

	System::Void actuatorHomeButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		zaber->moveActuatorToPosition(0);
	}
};
}

