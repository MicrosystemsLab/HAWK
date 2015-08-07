/* PostExperimentForm.h
 * --------------------
 * Component and event code for the windows form that collects
 * post experiment notes from the user.
 *
 * Created by John Whitworth on 8/26/14.
 * Copyright 2015 Eileen Mazzochette, et al <emazz86@stanford.edu>
 */

#pragma once

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include "Experiment.h"

namespace BehaviorRig20 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for PostExperimentForm
	/// </summary>
	public ref class PostExperimentForm : public System::Windows::Forms::Form
	{
	public:
		PostExperimentForm(Experiment* exp)
		{
			InitializeComponent();
			this->experiment = exp;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PostExperimentForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: Experiment* experiment;
	private: System::Windows::Forms::TextBox^  postExpNotesTextBox;
	private: System::Windows::Forms::Button^  okButton;

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
			this->postExpNotesTextBox = (gcnew System::Windows::Forms::TextBox());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// postExpNotesTextBox
			// 
			this->postExpNotesTextBox->Location = System::Drawing::Point(12, 12);
			this->postExpNotesTextBox->Multiline = true;
			this->postExpNotesTextBox->Name = L"postExpNotesTextBox";
			this->postExpNotesTextBox->Size = System::Drawing::Size(260, 119);
			this->postExpNotesTextBox->TabIndex = 10;
			// 
			// okButton
			// 
			this->okButton->Location = System::Drawing::Point(197, 137);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(75, 23);
			this->okButton->TabIndex = 11;
			this->okButton->Text = L"OK";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &PostExperimentForm::okButton_Click);
			// 
			// PostExperimentForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 166);
			this->ControlBox = false;
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->postExpNotesTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"PostExperimentForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Post Experiment Notes";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:

	/* Function: okButton_Click
	 * ------------------------
	 * Click event handler for okButton. Submits the user's notes to the experiment
	 * and closes the form.
	 */
	System::Void okButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		marshal_context^ context = gcnew marshal_context();
		experiment->postExpNotes = context->marshal_as<string>(postExpNotesTextBox->Text);
		this->DialogResult = Windows::Forms::DialogResult::OK;
		this->Close();
	}

	};
}
