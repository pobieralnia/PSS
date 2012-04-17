/*
 * NPlot - A charting library for .NET
 * 
 * PlotSurface2DDemo.cs
 * Copyright (C) 2003-2006 Matt Howlett, Jamie McQuay.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of NPlot nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "StdAfx.h"
#include "Config.h"
#include "PlotSurface2DDemo.h"
#include "ARX.h"

#include <algorithm>
#include <vector>

namespace PSS {

	CPlotSurface2DDemo::CPlotSurface2DDemo(void)
	{
		this->n = 1000;
		InitializeComponent();
		InitializeBackgoundWorker();
		
		plotSurface->Anchor =   
			System::Windows::Forms::AnchorStyles::Left  |
			System::Windows::Forms::AnchorStyles::Right |
			System::Windows::Forms::AnchorStyles::Top   |
			System::Windows::Forms::AnchorStyles::Bottom;

		config_object = NULL;
		arx_object = NULL;

		arx_object = new ARX();
		config_object = Config::getInstance().create("object");
	}

	/**
	 * Destructor
	 * Clean up any resources being used.
	 *
	 * @return	void
	 */
	CPlotSurface2DDemo::~CPlotSurface2DDemo()
	{
		if (components)
		{
			delete components;
		}

		delete config_object;
		delete arx_object;
	}

	/**
	 * Set up the BackgroundWorker object by
	 * attaching event handlers.
	 * 
	 * @return	void
	 */
	void CPlotSurface2DDemo::InitializeBackgoundWorker()
	{
		backgroundWorker1->DoWork += gcnew DoWorkEventHandler( this, &CPlotSurface2DDemo::backgroundWorker1_DoWork );
		backgroundWorker1->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &CPlotSurface2DDemo::backgroundWorker1_RunWorkerCompleted );
		backgroundWorker1->ProgressChanged += gcnew ProgressChangedEventHandler( this, &CPlotSurface2DDemo::backgroundWorker1_ProgressChanged );
	}

	/**
	 * This event handler is where the actual,
	 * potentially time-consuming work is done.
	 *
	 * @param	Object^ sender
	 * @param	DoWorkEventArgs^ e
	 * @return	void
	 */
	void CPlotSurface2DDemo::backgroundWorker1_DoWork( Object^ sender, DoWorkEventArgs^ e )
	{
		// Get the BackgroundWorker that raised this event.
		BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);
		
		// Assign the result of the computation
		// to the Result property of the DoWorkEventArgs
		// object. This is will be available to the 
		// RunWorkerCompleted eventhandler.
		   
		while( worker->CancellationPending == false )
		{
			Thread::Sleep(this->n); //10 seconds
			worker->ReportProgress( 1 );
		}

		if(worker->CancellationPending)
		{
			e->Cancel = true;
		}
	}

	/**
	 * This event handler deals with the results of the
	 * background operation.
	 *
	 * @param	Object^
	 * @param	RunWorkerCompletedEventArgs^ e
	 * @return	void
	 */
	void CPlotSurface2DDemo::backgroundWorker1_RunWorkerCompleted( Object^ /* sender */, RunWorkerCompletedEventArgs^ e )
	{

		// First, handle the case where an exception was thrown.
		if ( e->Error != nullptr )
		{
			MessageBox::Show( e->Error->Message );
		}
		else
		{
			if ( e->Cancelled )
			{
				
				// Next, handle the case where the user cancelled 
				// the operation.
				// Note that due to a race condition in 
				// the DoWork event handler, the Cancelled
				// flag may not have been set, even though
				// CancelAsync was called.
			// resultLabel->Text = "Cancelled";
			}
			else
			{
				// Finally, handle the case where the operation 
				// succeeded.
			//   resultLabel->Text = e->Result->ToString();
			}

			// Enable the Start button.
			startAsyncButton->Enabled = true;

			// Disable the Cancel button.
			cancelAsyncButton->Enabled = false;
		}
	}

	/**
	 * This event handler updates the progress bar.
	 *
	 * @param	Object^
	 * @param	ProgressChangedEventArgs^ e
	 * @return	void
	 */
	void CPlotSurface2DDemo::backgroundWorker1_ProgressChanged( Object^ /*sender*/, ProgressChangedEventArgs^ e )
	{
		// Create config object driver
		std::vector<std::tuple <std::map<int,double>, std::map<int,double>, std::map<std::string, double>>> m_vector_objects_ptr;	// container for all configs
		Config::getInstance().get_config(m_vector_objects_ptr,Config::getInstance().OBJECT);


		std::deque<double> m_A;
		std::deque<double> m_B;

		for( auto it =  std::get<0>(m_vector_objects_ptr[0]).begin(); it !=  std::get<0>(m_vector_objects_ptr[0]).end(); ++it ) {
			   m_A.push_back( it->second );
		}

		for( auto ite = std::get<1>(m_vector_objects_ptr[0]).begin(); ite != std::get<1>(m_vector_objects_ptr[0]).end(); ++ite ) {
			m_B.push_back( ite->second );
		}

		int m_delay = std::get<2>(m_vector_objects_ptr[0])["k"];
		int m_stat = std::get<2>(m_vector_objects_ptr[0])["stationary"];

		arx_object->get_parameters("name", m_A, m_B, m_delay, m_stat);
			
		Config::getInstance().m_ARX.push_back(arx_object->simulate(4));
			
		//arx_object->get_parameters("name", std::get<0>(m_vector_objects_ptr[0]), std::get<1>(m_vector_objects_ptr[0]), std::get<2>(m_vector_objects_ptr[0]));

		array<double>^ managedValues = gcnew array<double>(Config::getInstance().m_ARX.size());
	
		// cast to managed object type IntPtr representing an object pointer.
		System::IntPtr ptr = (System::IntPtr)&Config::getInstance().m_ARX[0];

		// copy data to managed array using System::Runtime::Interopservices namespace
		Marshal::Copy(ptr, managedValues, 0, Config::getInstance().m_ARX.size());

		CPlotSurface2DDemo::PlotSincFunction(managedValues);
		
	}
	
	#pragma region PlotSincFunction
	System::Void CPlotSurface2DDemo::PlotSincFunction(array<double>^ managedValues) 
	{
		int n = 1000;
        plotSurface->Clear(); // clear everything. reset fonts. remove plot components etc.

		Grid^ fineGrid = gcnew Grid();
		fineGrid->VerticalGridType = Grid::GridType::Fine;
		fineGrid->HorizontalGridType = Grid::GridType::Fine;
		plotSurface->Add( fineGrid );

		System::Random^ r = gcnew Random();
		array<double>^ b = gcnew array<double>(100);
		
		const int npt = 101;
		array<float>^ x = gcnew array<float>(npt);
		array<float>^ y = gcnew array<float>(npt);
		float step = 0.1f;
		for (int i=0; i<npt; ++i)
		{
			//x[i] = i*step - 5.0f;
			//y[i] = (float)Math::Pow( 10.0, x[i] );
		}

		
		//float xmin = x[0];
		//float xmax = x[npt-1];
		//float ymin = (float)Math::Pow( 10.0, xmin );
		//float ymax = (float)Math::Pow( 10.0, xmax );

		LinePlot^ lp = gcnew LinePlot();
		lp->OrdinateData = managedValues;
		//lp->AbscissaData = gcnew StartStep( -500.0, 10.0 );
		//lp->AbscissaData = gcnew StartStep( min_x, max_x );
		lp->Pen = gcnew Pen( Color::Blue, 1.0f );
		plotSurface->Add(lp);

		plotSurface->Title = "Wykres symulacji";
		plotSurface->YAxis1->Label = "Y";
		plotSurface->XAxis1->Label = "Krok symulacji";

		Legend^ legend = gcnew Legend();
		legend->AttachTo( PlotSurface2D::XAxisPosition::Top, PlotSurface2D::YAxisPosition::Left );
		legend->VerticalEdgePlacement = Legend::Placement::Inside;
		legend->HorizontalEdgePlacement = Legend::Placement::Inside;
        legend->YOffset = 8;

        plotSurface->Legend = legend;
		plotSurface->LegendZOrder = 1; // default zorder for adding idrawables is 0, so this puts legend on top.

		plotSurface->Refresh();
	}
	#pragma endregion
}
