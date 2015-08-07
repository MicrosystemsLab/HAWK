// BehaviorRig2.0.cpp : main project file.
/*
 *  Copyright 2015 Eileen Mazzochette, et al <emazz86@stanford.edu>
 */
#include "stdafx.h"
//#include <vld.h>
#include "MainForm.h"

using namespace BehaviorRig20;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))  
    {             
        return 1;   
    }   
    AfxGetInstanceHandle();

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew MainForm());
	return 0;
}
