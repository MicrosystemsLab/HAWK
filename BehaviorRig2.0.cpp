// BehaviorRig2.0.cpp : main project file.

#include "stdafx.h"
//#include <vld.h>
#include "MainForm.h"

using namespace BehaviorRig;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew MainForm());
	return 0;
}
