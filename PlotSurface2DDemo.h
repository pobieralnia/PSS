/*
 * NPlot - A charting library for .NET
 * 
 * PlotSurface2DDemo.cs
 * Copyright (C) 2003-2006 Jamie McQuay.
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
#pragma once

#include "Config.h"
#include "ARX.h"

#include <sstream>
#include <tuple>
#include <map>
#include <string>
#include <vector>
#include <msclr/marshal_cppstd.h> // String ^ to std:string conversion

namespace PSS {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;
	using namespace NPlot;

	/**
	 * @class	CPlotSurface2DDemo CPlotSurface2DDemo.h
	 * @brief	Ploting is used with background worker
	 */
	public ref class CPlotSurface2DDemo : public System::Windows::Forms::Form
	{
	private: int simulate_counter;
	private: int n;
	private: ARX * arx_object;
	private: ConfigBase * config_object;
	private: ConfigBase * config_generator;
	//private: Signal * s_signal;
	private: System::Windows::Forms::Button^  startAsyncButton;
	private: System::Windows::Forms::Button^  cancelAsyncButton;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  Wykres;

	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  plikToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  infoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  zamknijToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pomocToolStripMenuItem;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::ListBox^  listBox1;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	public:
		CPlotSurface2DDemo(void);
		System::Void PlotSincFunction(array<double>^ managedValues, array<double>^ uchyb);
		~CPlotSurface2DDemo();

	// Note that a NPlot.Windows.PlotSurface2D class
	// is used here. This has exactly the same 
	// functionality as the NPlot.PlotSurface2D 
	// class, except that it is derived from Forms.UserControl
	// and automatically paints itself in a windows.forms
	// application. Windows.PlotSurface2D can also paint itself
	// to other arbitrary Drawing.Graphics drawing surfaces
	// using the Draw method. (see printing later).

	private: NPlot::Windows::PlotSurface2D^  plotSurface;
	private: System::ComponentModel::IContainer^  components;

	// -------------------------- BACKGROUND WORKER -----------------------------------------------------------

	private: void InitializeBackgoundWorker();
	private: void backgroundWorker1_DoWork( Object^ sender, DoWorkEventArgs^ e );
	private: void backgroundWorker1_RunWorkerCompleted( Object^ /*sender*/, RunWorkerCompletedEventArgs^ e );
	private: void backgroundWorker1_ProgressChanged( Object^ /*sender*/, ProgressChangedEventArgs^ e );
	
	// -------------------------- END BACKGROUND WORKER -------------------------------------------------------

#pragma region Windows Form Designer generated code
	/** 
	 * Required method for Designer support - do not modify
	 * the contents of this method with the code editor.
	 * 
	 * @return	void
	 */
	private: void InitializeComponent(void)
	{
		this->startAsyncButton = (gcnew System::Windows::Forms::Button());
		this->cancelAsyncButton = (gcnew System::Windows::Forms::Button());
		this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
		this->plotSurface = (gcnew NPlot::Windows::PlotSurface2D());
		this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
		this->textBox1 = (gcnew System::Windows::Forms::TextBox());
		this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
		this->Wykres = (gcnew System::Windows::Forms::TabPage());
		this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
		this->button3 = (gcnew System::Windows::Forms::Button());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->button2 = (gcnew System::Windows::Forms::Button());
		this->button1 = (gcnew System::Windows::Forms::Button());
		this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
		this->plikToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->infoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->zamknijToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->pomocToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
		this->listBox1 = (gcnew System::Windows::Forms::ListBox());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
		this->tabControl1->SuspendLayout();
		this->Wykres->SuspendLayout();
		this->tabPage2->SuspendLayout();
		this->menuStrip1->SuspendLayout();
		this->SuspendLayout();
		// 
		// startAsyncButton
		// 
		this->startAsyncButton->Location = System::Drawing::Point(6, 327);
		this->startAsyncButton->Name = L"startAsyncButton";
		this->startAsyncButton->Size = System::Drawing::Size(75, 23);
		this->startAsyncButton->TabIndex = 7;
		this->startAsyncButton->Text = L"start";
		this->startAsyncButton->UseVisualStyleBackColor = true;
		this->startAsyncButton->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::startAsyncButton_Click);
		// 
		// cancelAsyncButton
		// 
		this->cancelAsyncButton->Location = System::Drawing::Point(87, 327);
		this->cancelAsyncButton->Name = L"cancelAsyncButton";
		this->cancelAsyncButton->Size = System::Drawing::Size(75, 23);
		this->cancelAsyncButton->TabIndex = 8;
		this->cancelAsyncButton->Text = L"cancel";
		this->cancelAsyncButton->UseVisualStyleBackColor = true;
		this->cancelAsyncButton->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::cancelAsyncButton_Click);
		// 
		// backgroundWorker1
		// 
		this->backgroundWorker1->WorkerReportsProgress = true;
		this->backgroundWorker1->WorkerSupportsCancellation = true;
		// 
		// plotSurface
		// 
		this->plotSurface->AutoScaleAutoGeneratedAxes = false;
		this->plotSurface->AutoScaleTitle = false;
		this->plotSurface->BackColor = System::Drawing::SystemColors::ControlLight;
		this->plotSurface->DateTimeToolTip = false;
		this->plotSurface->Legend = nullptr;
		this->plotSurface->LegendZOrder = 1;
		this->plotSurface->Location = System::Drawing::Point(6, 6);
		this->plotSurface->Name = L"plotSurface";
		this->plotSurface->RightMenu = nullptr;
		this->plotSurface->ShowCoordinates = true;
		this->plotSurface->Size = System::Drawing::Size(689, 301);
		this->plotSurface->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::None;
		this->plotSurface->TabIndex = 0;
		this->plotSurface->Text = L"plotSurface2D1";
		this->plotSurface->Title = L"";
		this->plotSurface->TitleFont = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel));
		this->plotSurface->XAxis1 = nullptr;
		this->plotSurface->XAxis2 = nullptr;
		this->plotSurface->YAxis1 = nullptr;
		this->plotSurface->YAxis2 = nullptr;
		// 
		// trackBar1
		// 
		this->trackBar1->AccessibleName = L"";
		this->trackBar1->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->trackBar1->Location = System::Drawing::Point(534, 327);
		this->trackBar1->Maximum = 5;
		this->trackBar1->Minimum = 1;
		this->trackBar1->Name = L"trackBar1";
		this->trackBar1->Size = System::Drawing::Size(104, 45);
		this->trackBar1->TabIndex = 9;
		this->trackBar1->Value = 1;
		this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::trackBar1_ValueChanged);
		// 
		// textBox1
		// 
		this->textBox1->Location = System::Drawing::Point(644, 329);
		this->textBox1->Name = L"textBox1";
		this->textBox1->Size = System::Drawing::Size(51, 20);
		this->textBox1->TabIndex = 10;
		// 
		// tabControl1
		// 
		this->tabControl1->Controls->Add(this->Wykres);
		this->tabControl1->Controls->Add(this->tabPage2);
		this->tabControl1->Location = System::Drawing::Point(11, 28);
		this->tabControl1->Name = L"tabControl1";
		this->tabControl1->SelectedIndex = 0;
		this->tabControl1->Size = System::Drawing::Size(709, 409);
		this->tabControl1->TabIndex = 11;
		// 
		// Wykres
		// 
		this->Wykres->Controls->Add(this->plotSurface);
		this->Wykres->Controls->Add(this->textBox1);
		this->Wykres->Controls->Add(this->startAsyncButton);
		this->Wykres->Controls->Add(this->trackBar1);
		this->Wykres->Controls->Add(this->cancelAsyncButton);
		this->Wykres->Location = System::Drawing::Point(4, 22);
		this->Wykres->Name = L"Wykres";
		this->Wykres->Padding = System::Windows::Forms::Padding(3);
		this->Wykres->Size = System::Drawing::Size(701, 383);
		this->Wykres->TabIndex = 0;
		this->Wykres->Text = L"Wykres";
		this->Wykres->UseVisualStyleBackColor = true;
		// 
		// tabPage2
		// 
		this->tabPage2->Controls->Add(this->listBox1);
		this->tabPage2->Controls->Add(this->button3);
		this->tabPage2->Controls->Add(this->label1);
		this->tabPage2->Controls->Add(this->button2);
		this->tabPage2->Controls->Add(this->button1);
		this->tabPage2->Location = System::Drawing::Point(4, 22);
		this->tabPage2->Name = L"tabPage2";
		this->tabPage2->Padding = System::Windows::Forms::Padding(3);
		this->tabPage2->Size = System::Drawing::Size(701, 383);
		this->tabPage2->TabIndex = 1;
		this->tabPage2->Text = L"Konfiguracja";
		this->tabPage2->UseVisualStyleBackColor = true;
		// 
		// button3
		// 
		this->button3->Location = System::Drawing::Point(19, 100);
		this->button3->Name = L"button3";
		this->button3->Size = System::Drawing::Size(75, 23);
		this->button3->TabIndex = 3;
		this->button3->Text = L"czyœæ tablicê";
		this->button3->UseVisualStyleBackColor = true;
		this->button3->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button3_Click);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
		this->label1->Location = System::Drawing::Point(110, 87);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(101, 17);
		this->label1->TabIndex = 2;
		this->label1->Text = L"Za³adowono: 0";
		// 
		// button2
		// 
		this->button2->Location = System::Drawing::Point(19, 71);
		this->button2->Name = L"button2";
		this->button2->Size = System::Drawing::Size(75, 23);
		this->button2->TabIndex = 1;
		this->button2->Text = L"Generator";
		this->button2->UseVisualStyleBackColor = true;
		this->button2->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button2_Click);
		// 
		// button1
		// 
		this->button1->Location = System::Drawing::Point(19, 25);
		this->button1->Name = L"button1";
		this->button1->Size = System::Drawing::Size(75, 23);
		this->button1->TabIndex = 0;
		this->button1->Text = L"Obiekt konfig";
		this->button1->UseVisualStyleBackColor = true;
		this->button1->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button1_Click);
		// 
		// menuStrip1
		// 
		this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->plikToolStripMenuItem, 
			this->pomocToolStripMenuItem});
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(732, 24);
		this->menuStrip1->TabIndex = 12;
		this->menuStrip1->Text = L"menuStrip1";
		// 
		// plikToolStripMenuItem
		// 
		this->plikToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->infoToolStripMenuItem, 
			this->zamknijToolStripMenuItem});
		this->plikToolStripMenuItem->Name = L"plikToolStripMenuItem";
		this->plikToolStripMenuItem->Size = System::Drawing::Size(38, 20);
		this->plikToolStripMenuItem->Text = L"Plik";
		// 
		// infoToolStripMenuItem
		// 
		this->infoToolStripMenuItem->Name = L"infoToolStripMenuItem";
		this->infoToolStripMenuItem->Size = System::Drawing::Size(117, 22);
		this->infoToolStripMenuItem->Text = L"Info";
		// 
		// zamknijToolStripMenuItem
		// 
		this->zamknijToolStripMenuItem->Name = L"zamknijToolStripMenuItem";
		this->zamknijToolStripMenuItem->Size = System::Drawing::Size(117, 22);
		this->zamknijToolStripMenuItem->Text = L"Zamknij";
		this->zamknijToolStripMenuItem->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::zamknijToolStripMenuItem_Click);
		// 
		// pomocToolStripMenuItem
		// 
		this->pomocToolStripMenuItem->Name = L"pomocToolStripMenuItem";
		this->pomocToolStripMenuItem->Size = System::Drawing::Size(57, 20);
		this->pomocToolStripMenuItem->Text = L"Pomoc";
		// 
		// openFileDialog1
		// 
		this->openFileDialog1->FileName = L"openFileDialog1";
		// 
		// listBox1
		// 
		this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
		this->listBox1->FormattingEnabled = true;
		this->listBox1->ItemHeight = 17;
		listBox1->Items->Add( String::Format( "Dodaj obiekt", 1 ) );
	//	this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(1) {L"Alo"});
		this->listBox1->Location = System::Drawing::Point(113, 25);
		this->listBox1->Name = L"listBox1";
		this->listBox1->Size = System::Drawing::Size(120, 21);
		this->listBox1->TabIndex = 4;
		// 
		// CPlotSurface2DDemo
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(732, 449);
		this->Controls->Add(this->tabControl1);
		this->Controls->Add(this->menuStrip1);
		this->MainMenuStrip = this->menuStrip1;
		this->Name = L"CPlotSurface2DDemo";
		this->Text = L"PSS 1.0";
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
		this->tabControl1->ResumeLayout(false);
		this->Wykres->ResumeLayout(false);
		this->Wykres->PerformLayout();
		this->tabPage2->ResumeLayout(false);
		this->tabPage2->PerformLayout();
		this->menuStrip1->ResumeLayout(false);
		this->menuStrip1->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

			 }
#pragma endregion

	// Handle the TrackBar.ValueChanged event by calculating a value for
	// TextBox1 based on the TrackBar value.  
	private: System::Void trackBar1_ValueChanged( Object^ /*sender*/, System::EventArgs^ /*e*/ )
	{
		this->textBox1->Text = String::Concat( "", trackBar1->Value );
		this->n = trackBar1->Value * 1000;
	}

	private: System::Void startAsyncButton_Click( System::Object^ /*sender*/, System::EventArgs^ /*e*/ )
	{
		// Disable the Start button until 
		// the asynchronous operation is done.
		this->startAsyncButton->Enabled = false;

		// Enable the Cancel button while 
		// the asynchronous operation runs.
		this->cancelAsyncButton->Enabled = true;

		// Start the asynchronous operation.
		backgroundWorker1->RunWorkerAsync();
	}

	private: System::Void cancelAsyncButton_Click( System::Object^ /*sender*/, System::EventArgs^ /*e*/ )
	{  
		// Cancel the asynchronous operation.
		this->backgroundWorker1->CancelAsync();

		// Disable the Cancel button.
		cancelAsyncButton->Enabled = false;
	}

	private: System::Void zamknijToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//ToDo
		// check if background process is set then - close it
		CPlotSurface2DDemo::Close();
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// Check if dialog is open correct
		if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				// Create an instance of StreamReader to read from a file.
				StreamReader^ sr = gcnew StreamReader( this->openFileDialog1->FileName );
				try
				{
					String^ line;
					// Read and display lines from the file until the end of 
					// the file is reached.
					while ( line = sr->ReadLine() )
					{
						config_object->parse_line( msclr::interop::marshal_as< std::string >( line )  );
					}

					// Shutdown the painting of the ListBox as items are added.
					listBox1->BeginUpdate();

					// Loop through and add 50 items to the ListBox.
					for ( int x = 1; x <= 50; x++ )
					{
						listBox1->Items->Add( String::Format( "Item {0}", x ) );

					}
					listBox1->EndUpdate();

				}
				finally
				{
					if ( sr )
					delete (IDisposable^)sr;
				}

			}
			catch ( Exception^ e ) 
			{
				// Let the user know what went wrong.
				MessageBox::Show( e->Message, "The file could not be read");
			}
				
		}
		
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// Check if dialog is open correct
		if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				// Create an instance of StreamReader to read from a file.
				StreamReader^ sr = gcnew StreamReader( this->openFileDialog1->FileName );
				try
				{
					String^ line;
					// Read and display lines from the file until the end of 
					// the file is reached.
					while ( line = sr->ReadLine() )
					{
						config_generator->parse_line( msclr::interop::marshal_as< std::string >( line )  );
					}

				}
				finally
				{
					if ( sr )
					delete (IDisposable^)sr;

				//	std::vector<std::map<std::string,double> > m_vector_regulator;
				//	Config::getInstance().get_configg(m_vector_regulator);
					
				//	std::stringstream ss; //create a stringstream
				//	ss << m_vector_regulator.size();
					//std::string aa = m_vector_regulator.size();
					//MessageBox::Show( msclr::interop::marshal_as< String ^ >( ss.str() ) );
					
					this->label1->Text =  L"Za³adowano: " + msclr::interop::marshal_as< String ^ >( config_generator->get_size(1) );
				}

			}
			catch ( Exception^ e ) 
			{
				// Let the user know what went wrong.
				MessageBox::Show( e->Message, "The file could not be read");
			}
		}
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		config_generator->clear_all();
		this->label1->Text =  L"Za³adowano: 0";
	//	int b = listBox1->SelectedValue->ToString();
		 if ( listBox1->SelectedIndex != -1 )
			MessageBox::Show( listBox1->SelectedValue->ToString(), "The file could not be read");
	}
			 
}; // END OF CLASS

} // END OF NAMESPACE