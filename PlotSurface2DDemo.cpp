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
#include "PlotSurface2DDemo.h"
#include <algorithm>
#include <stdio.h>

namespace PSS {

	CPlotSurface2DDemo::CPlotSurface2DDemo(void)
	{
		m_regulator_selected_flag = false;
		m_save_file_flag = false;

		this->n = 100;
		InitializeComponent();
		InitializeBackgoundWorker();
		
		plotSurface->Anchor =   
			System::Windows::Forms::AnchorStyles::Left  |
			System::Windows::Forms::AnchorStyles::Right |
			System::Windows::Forms::AnchorStyles::Top   |
			System::Windows::Forms::AnchorStyles::Bottom;

		config_object = NULL;
		config_generator = NULL;
		arx_object = NULL;
		m_regulator = NULL;
		m_config_regulator = NULL;
		m_proces = NULL;
		m_loop = NULL;
		m_save = NULL;
		m_save_file = NULL;

		m_loop = new Loop;
		arx_object = new ARX;
		m_save = new Save;

		av10 = gcnew ArrayList();
		av20 = gcnew ArrayList();
		av30 = gcnew ArrayList();

		// Config
		m_config_regulator = Config::getInstance().create("regulator");
		config_object = Config::getInstance().create("object");
		config_generator = Config::getInstance().create("generator");

		plotSurface->RightMenu = NPlot::Windows::PlotSurface2D::DefaultContextMenu;
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

		if(config_object)
		{
			delete config_object;
		}

		if(arx_object)
		{
			delete arx_object;
		}

		if(m_config_regulator)
		{
			delete m_config_regulator;
		}

		if(m_regulator)
		{
			delete m_regulator;
		}

		if(m_loop)
		{
			delete m_loop;
		}

		if(m_proces)
		{
			delete m_proces;
		}
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
		if(m_regulator_selected_flag)
		{
			m_regulator->set_setpoint(m_proces);
			m_loop->set_regulator(m_regulator);
			m_regulator_selected_flag = false;
		}
		
		// Clear List
		if(av10->Count > 200)
		{
			av10->Clear();
			av20->Clear();
			av30->Clear();
		}

		const double y = m_loop->simulation_step();
		const double error = m_loop->get_error();
		const double setpoint = m_loop->get_setpoint();
		av10->Add( y );
		av20->Add( error );
		av30->Add( setpoint );

		// Saving
		if(m_save_file_flag)
		{
			if(m_save_file)
				m_save_file->save_online(y);
		}

		// Plot
		CPlotSurface2DDemo::PlotSincFunction(av10, av20, av30);

	}
	
	#pragma region PlotSincFunction
	System::Void CPlotSurface2DDemo::PlotSincFunction(ArrayList^ managedValues, ArrayList^ uchyb, ArrayList^ st) 
	{
        plotSurface->Clear(); // clear everything. reset fonts. remove plot components etc.

		Grid^ fineGrid = gcnew Grid();
		fineGrid->VerticalGridType = Grid::GridType::Fine;
	//	fineGrid->HorizontalGridType = Grid::GridType::Fine;
		plotSurface->Add( fineGrid );

		LinePlot^ lp = gcnew LinePlot();
		lp->OrdinateData = managedValues;
		lp->Pen = gcnew Pen( Color::Blue, 2.0f );
		lp->Label = L"OdpowiedŸ obiektu";

		LinePlot^ top = gcnew LinePlot();
		top->OrdinateData = uchyb;
		top->Color = Color::Red;
		top->Pen->Width = 1.0f;
		top->Label = L"Uchyb";

		Marker^ m = gcnew Marker(Marker::MarkerType::Cross1,6,gcnew Pen(Color::Green,1.0F));
		PointPlot^ pp = gcnew PointPlot( m );
		pp->OrdinateData = st;
		pp->Label = L"Wartoœæ zadana";

		plotSurface->Add(lp);
		plotSurface->Add(top);
		plotSurface->Add(pp);

		plotSurface->Title = "Wykres symulacji";
		plotSurface->YAxis1->Label = "Y";
		plotSurface->XAxis1->Label = "Krok symulacji";

		plotSurface->Legend = gcnew Legend();
		plotSurface->Legend->AttachTo( PlotSurface2D::XAxisPosition::Top, PlotSurface2D::YAxisPosition::Left );
		plotSurface->Legend->VerticalEdgePlacement = Legend::Placement::Inside;
		plotSurface->Legend->HorizontalEdgePlacement = Legend::Placement::Inside;
        plotSurface->Legend->YOffset = 8;
		plotSurface->LegendZOrder = 0;

		plotSurface->Title = "Wykres symulacji";
		plotSurface->AddInteraction(gcnew NPlot::Windows::PlotSurface2D::Interactions::RubberBandSelection());

		plotSurface->Refresh();
	}
	#pragma endregion
}
