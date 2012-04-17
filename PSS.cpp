// PSS.cpp : main project file.

#include "stdafx.h"
#include "PlotSurface2DDemo.h"

using namespace PSS;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew CPlotSurface2DDemo());
	return 0;
}
