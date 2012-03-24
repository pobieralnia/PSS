// PSS.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include "Config.h"

using namespace PSS;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Load first init
	Config::getInstance().init();

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
