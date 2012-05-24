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
#include "Regulator.h"
#include "RegulatorManager.h"
#include "Signal.h"
#include "SingalDecorator.h"
#include "Loop.h"
#include "Save.h"
#include "SaveBase.h"

#include <algorithm>
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
	private: bool m_regulator_selected_flag;
	private: bool m_save_file_flag;
	private: int n;
	private: ARX * arx_object;
	private: Loop * m_loop;
	private: ConfigBase * config_object;
	private: ConfigBase * config_generator;
	private: ConfigBase * m_config_regulator;
	private: Regulator * m_regulator;
	private: SignalBase * m_proces;
	private: Save * m_save;
	private: SaveBase * m_save_file;
	private: ArrayList^ av10;
	private: ArrayList^ av20;
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

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::TabControl^  tabControl2;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	public:
		CPlotSurface2DDemo(void);
		System::Void PlotSincFunction(ArrayList^ managedValues, ArrayList^ uchyb);
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
		this->button10 = (gcnew System::Windows::Forms::Button());
		this->button9 = (gcnew System::Windows::Forms::Button());
		this->label9 = (gcnew System::Windows::Forms::Label());
		this->button8 = (gcnew System::Windows::Forms::Button());
		this->button7 = (gcnew System::Windows::Forms::Button());
		this->button6 = (gcnew System::Windows::Forms::Button());
		this->listBox2 = (gcnew System::Windows::Forms::ListBox());
		this->button5 = (gcnew System::Windows::Forms::Button());
		this->button4 = (gcnew System::Windows::Forms::Button());
		this->listBox1 = (gcnew System::Windows::Forms::ListBox());
		this->button3 = (gcnew System::Windows::Forms::Button());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->button2 = (gcnew System::Windows::Forms::Button());
		this->button1 = (gcnew System::Windows::Forms::Button());
		this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
		this->plikToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->infoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->zamknijToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
		this->tabControl2 = (gcnew System::Windows::Forms::TabControl());
		this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
		this->textBox5 = (gcnew System::Windows::Forms::TextBox());
		this->textBox4 = (gcnew System::Windows::Forms::TextBox());
		this->textBox3 = (gcnew System::Windows::Forms::TextBox());
		this->textBox2 = (gcnew System::Windows::Forms::TextBox());
		this->label8 = (gcnew System::Windows::Forms::Label());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
		this->textBox11 = (gcnew System::Windows::Forms::TextBox());
		this->label16 = (gcnew System::Windows::Forms::Label());
		this->textBox10 = (gcnew System::Windows::Forms::TextBox());
		this->label15 = (gcnew System::Windows::Forms::Label());
		this->textBox9 = (gcnew System::Windows::Forms::TextBox());
		this->label14 = (gcnew System::Windows::Forms::Label());
		this->label13 = (gcnew System::Windows::Forms::Label());
		this->textBox8 = (gcnew System::Windows::Forms::TextBox());
		this->label12 = (gcnew System::Windows::Forms::Label());
		this->textBox7 = (gcnew System::Windows::Forms::TextBox());
		this->label11 = (gcnew System::Windows::Forms::Label());
		this->label10 = (gcnew System::Windows::Forms::Label());
		this->textBox6 = (gcnew System::Windows::Forms::TextBox());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
		this->tabControl1->SuspendLayout();
		this->Wykres->SuspendLayout();
		this->tabPage2->SuspendLayout();
		this->menuStrip1->SuspendLayout();
		this->tabControl2->SuspendLayout();
		this->tabPage1->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
		this->tabPage3->SuspendLayout();
		this->tabPage4->SuspendLayout();
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
		this->plotSurface->Size = System::Drawing::Size(1011, 301);
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
		this->trackBar1->Location = System::Drawing::Point(856, 327);
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
		this->textBox1->Location = System::Drawing::Point(966, 327);
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
		this->tabControl1->Size = System::Drawing::Size(1043, 409);
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
		this->Wykres->Size = System::Drawing::Size(1035, 383);
		this->Wykres->TabIndex = 0;
		this->Wykres->Text = L"Wykres";
		this->Wykres->UseVisualStyleBackColor = true;
		// 
		// tabPage2
		// 
		this->tabPage2->Controls->Add(this->button10);
		this->tabPage2->Controls->Add(this->button9);
		this->tabPage2->Controls->Add(this->label9);
		this->tabPage2->Controls->Add(this->button8);
		this->tabPage2->Controls->Add(this->button7);
		this->tabPage2->Controls->Add(this->button6);
		this->tabPage2->Controls->Add(this->listBox2);
		this->tabPage2->Controls->Add(this->button5);
		this->tabPage2->Controls->Add(this->button4);
		this->tabPage2->Controls->Add(this->listBox1);
		this->tabPage2->Controls->Add(this->button3);
		this->tabPage2->Controls->Add(this->label1);
		this->tabPage2->Controls->Add(this->button2);
		this->tabPage2->Controls->Add(this->button1);
		this->tabPage2->Location = System::Drawing::Point(4, 22);
		this->tabPage2->Name = L"tabPage2";
		this->tabPage2->Padding = System::Windows::Forms::Padding(3);
		this->tabPage2->Size = System::Drawing::Size(1035, 383);
		this->tabPage2->TabIndex = 1;
		this->tabPage2->Text = L"Konfiguracja";
		this->tabPage2->UseVisualStyleBackColor = true;
		// 
		// button10
		// 
		this->button10->Location = System::Drawing::Point(19, 196);
		this->button10->Name = L"button10";
		this->button10->Size = System::Drawing::Size(214, 23);
		this->button10->TabIndex = 13;
		this->button10->Text = L"poka¿ dane";
		this->button10->UseVisualStyleBackColor = true;
		this->button10->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button10_Click);
		// 
		// button9
		// 
		this->button9->Location = System::Drawing::Point(19, 88);
		this->button9->Name = L"button9";
		this->button9->Size = System::Drawing::Size(214, 23);
		this->button9->TabIndex = 12;
		this->button9->Text = L"poka¿ dane";
		this->button9->UseVisualStyleBackColor = true;
		this->button9->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button9_Click);
		// 
		// label9
		// 
		this->label9->AutoSize = true;
		this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F));
		this->label9->Location = System::Drawing::Point(15, 245);
		this->label9->Name = L"label9";
		this->label9->Size = System::Drawing::Size(606, 40);
		this->label9->TabIndex = 11;
		this->label9->Text = L"W celu zapisu danych z symulacji, prosimy w³¹czyæ œledzenie przyciskiem Start\r\nPr" 
			L"zycisk Stop zatrzymuje zapisywanie do pliku.";
		// 
		// button8
		// 
		this->button8->Location = System::Drawing::Point(410, 304);
		this->button8->Name = L"button8";
		this->button8->Size = System::Drawing::Size(120, 63);
		this->button8->TabIndex = 10;
		this->button8->Text = L"STOP";
		this->button8->UseVisualStyleBackColor = true;
		this->button8->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button8_Click);
		// 
		// button7
		// 
		this->button7->BackColor = System::Drawing::Color::Transparent;
		this->button7->Location = System::Drawing::Point(174, 304);
		this->button7->Name = L"button7";
		this->button7->Size = System::Drawing::Size(122, 63);
		this->button7->TabIndex = 9;
		this->button7->Text = L"START";
		this->button7->UseVisualStyleBackColor = false;
		this->button7->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button7_Click);
		// 
		// button6
		// 
		this->button6->Location = System::Drawing::Point(19, 58);
		this->button6->Name = L"button6";
		this->button6->Size = System::Drawing::Size(75, 23);
		this->button6->TabIndex = 8;
		this->button6->Text = L"czyœæ";
		this->button6->UseVisualStyleBackColor = true;
		this->button6->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button6_Click);
		// 
		// listBox2
		// 
		this->listBox2->FormattingEnabled = true;
		this->listBox2->Location = System::Drawing::Point(113, 133);
		this->listBox2->Name = L"listBox2";
		this->listBox2->Size = System::Drawing::Size(120, 56);
		this->listBox2->TabIndex = 7;
		this->listBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::listBox2_SelectedIndexChanged);
		// 
		// button5
		// 
		this->button5->Location = System::Drawing::Point(19, 166);
		this->button5->Name = L"button5";
		this->button5->Size = System::Drawing::Size(75, 23);
		this->button5->TabIndex = 6;
		this->button5->Text = L"czyœæ";
		this->button5->UseVisualStyleBackColor = true;
		this->button5->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button5_Click);
		// 
		// button4
		// 
		this->button4->Location = System::Drawing::Point(19, 133);
		this->button4->Name = L"button4";
		this->button4->Size = System::Drawing::Size(75, 23);
		this->button4->TabIndex = 5;
		this->button4->Text = L"Regulator";
		this->button4->UseVisualStyleBackColor = true;
		this->button4->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::button4_Click);
		// 
		// listBox1
		// 
		this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
		this->listBox1->FormattingEnabled = true;
		this->listBox1->Location = System::Drawing::Point(113, 25);
		this->listBox1->Name = L"listBox1";
		this->listBox1->Size = System::Drawing::Size(120, 56);
		this->listBox1->TabIndex = 4;
		this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::listBox1_SelectedIndexChanged);
		// 
		// button3
		// 
		this->button3->Location = System::Drawing::Point(455, 58);
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
		this->label1->Location = System::Drawing::Point(564, 42);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(101, 17);
		this->label1->TabIndex = 2;
		this->label1->Text = L"Za³adowono: 0";
		// 
		// button2
		// 
		this->button2->Location = System::Drawing::Point(455, 25);
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
		this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->plikToolStripMenuItem});
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(1066, 24);
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
		this->infoToolStripMenuItem->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::infoToolStripMenuItem_Click);
		// 
		// zamknijToolStripMenuItem
		// 
		this->zamknijToolStripMenuItem->Name = L"zamknijToolStripMenuItem";
		this->zamknijToolStripMenuItem->Size = System::Drawing::Size(117, 22);
		this->zamknijToolStripMenuItem->Text = L"Zamknij";
		this->zamknijToolStripMenuItem->Click += gcnew System::EventHandler(this, &CPlotSurface2DDemo::zamknijToolStripMenuItem_Click);
		// 
		// openFileDialog1
		// 
		this->openFileDialog1->FileName = L"openFileDialog1";
		// 
		// tabControl2
		// 
		this->tabControl2->Controls->Add(this->tabPage1);
		this->tabControl2->Controls->Add(this->tabPage3);
		this->tabControl2->Controls->Add(this->tabPage4);
		this->tabControl2->Location = System::Drawing::Point(11, 454);
		this->tabControl2->Name = L"tabControl2";
		this->tabControl2->SelectedIndex = 0;
		this->tabControl2->Size = System::Drawing::Size(1039, 179);
		this->tabControl2->TabIndex = 13;
		// 
		// tabPage1
		// 
		this->tabPage1->Controls->Add(this->label3);
		this->tabPage1->Controls->Add(this->numericUpDown1);
		this->tabPage1->Controls->Add(this->label2);
		this->tabPage1->Enabled = false;
		this->tabPage1->Location = System::Drawing::Point(4, 22);
		this->tabPage1->Name = L"tabPage1";
		this->tabPage1->Padding = System::Windows::Forms::Padding(3);
		this->tabPage1->Size = System::Drawing::Size(1031, 153);
		this->tabPage1->TabIndex = 0;
		this->tabPage1->Text = L"RegulatorP";
		this->tabPage1->UseVisualStyleBackColor = true;
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label3->Location = System::Drawing::Point(182, 100);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(100, 16);
		this->label3->TabIndex = 2;
		this->label3->Text = L"Wzmocnienie K";
		// 
		// numericUpDown1
		// 
		this->numericUpDown1->Location = System::Drawing::Point(327, 100);
		this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {2500, 0, 0, 0});
		this->numericUpDown1->Name = L"numericUpDown1";
		this->numericUpDown1->Size = System::Drawing::Size(120, 20);
		this->numericUpDown1->TabIndex = 1;
		this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::NumericUpDown1_ValueChanged);
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F));
		this->label2->Location = System::Drawing::Point(6, 14);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(530, 40);
		this->label2->TabIndex = 0;
		this->label2->Text = L"Prosimy o wybranie wzmocnienia Regulatora P, wpisuj¹c odpowiedni¹\r\nwartoœæ liczbo" 
			L"w¹ w pole obok.";
		// 
		// tabPage3
		// 
		this->tabPage3->Controls->Add(this->textBox5);
		this->tabPage3->Controls->Add(this->textBox4);
		this->tabPage3->Controls->Add(this->textBox3);
		this->tabPage3->Controls->Add(this->textBox2);
		this->tabPage3->Controls->Add(this->label8);
		this->tabPage3->Controls->Add(this->label7);
		this->tabPage3->Controls->Add(this->label6);
		this->tabPage3->Controls->Add(this->label5);
		this->tabPage3->Controls->Add(this->label4);
		this->tabPage3->Enabled = false;
		this->tabPage3->Location = System::Drawing::Point(4, 22);
		this->tabPage3->Name = L"tabPage3";
		this->tabPage3->Padding = System::Windows::Forms::Padding(3);
		this->tabPage3->Size = System::Drawing::Size(1031, 153);
		this->tabPage3->TabIndex = 1;
		this->tabPage3->Text = L"RegulatorGPC";
		this->tabPage3->UseVisualStyleBackColor = true;
		// 
		// textBox5
		// 
		this->textBox5->Location = System::Drawing::Point(483, 90);
		this->textBox5->Name = L"textBox5";
		this->textBox5->Size = System::Drawing::Size(100, 20);
		this->textBox5->TabIndex = 17;
		this->textBox5->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::RO_TextBox_TextChanged);
		// 
		// textBox4
		// 
		this->textBox4->Location = System::Drawing::Point(483, 54);
		this->textBox4->Name = L"textBox4";
		this->textBox4->Size = System::Drawing::Size(100, 20);
		this->textBox4->TabIndex = 16;
		this->textBox4->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::ALPHA_TextBox_TextChanged);
		// 
		// textBox3
		// 
		this->textBox3->Location = System::Drawing::Point(147, 90);
		this->textBox3->Name = L"textBox3";
		this->textBox3->Size = System::Drawing::Size(100, 20);
		this->textBox3->TabIndex = 15;
		this->textBox3->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::L_TextBox_TextChanged);
		// 
		// textBox2
		// 
		this->textBox2->Location = System::Drawing::Point(147, 54);
		this->textBox2->Name = L"textBox2";
		this->textBox2->Size = System::Drawing::Size(100, 20);
		this->textBox2->TabIndex = 14;
		this->textBox2->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::H_TextBox_TextChanged);
		// 
		// label8
		// 
		this->label8->AutoSize = true;
		this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label8->Location = System::Drawing::Point(398, 95);
		this->label8->Name = L"label8";
		this->label8->Size = System::Drawing::Size(26, 16);
		this->label8->TabIndex = 8;
		this->label8->Text = L"Ro";
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label7->Location = System::Drawing::Point(398, 58);
		this->label7->Name = L"label7";
		this->label7->Size = System::Drawing::Size(43, 16);
		this->label7->TabIndex = 6;
		this->label7->Text = L"Alpha";
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label6->Location = System::Drawing::Point(84, 95);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(15, 16);
		this->label6->TabIndex = 4;
		this->label6->Text = L"L";
		// 
		// label5
		// 
		this->label5->AutoSize = true;
		this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label5->Location = System::Drawing::Point(84, 58);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(18, 16);
		this->label5->TabIndex = 2;
		this->label5->Text = L"H";
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F));
		this->label4->Location = System::Drawing::Point(6, 12);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(503, 20);
		this->label4->TabIndex = 0;
		this->label4->Text = L"Prosimy o ustawienie parametrów Regulatora GPC w polach obok.";
		// 
		// tabPage4
		// 
		this->tabPage4->Controls->Add(this->textBox11);
		this->tabPage4->Controls->Add(this->label16);
		this->tabPage4->Controls->Add(this->textBox10);
		this->tabPage4->Controls->Add(this->label15);
		this->tabPage4->Controls->Add(this->textBox9);
		this->tabPage4->Controls->Add(this->label14);
		this->tabPage4->Controls->Add(this->label13);
		this->tabPage4->Controls->Add(this->textBox8);
		this->tabPage4->Controls->Add(this->label12);
		this->tabPage4->Controls->Add(this->textBox7);
		this->tabPage4->Controls->Add(this->label11);
		this->tabPage4->Controls->Add(this->label10);
		this->tabPage4->Controls->Add(this->textBox6);
		this->tabPage4->Enabled = false;
		this->tabPage4->Location = System::Drawing::Point(4, 22);
		this->tabPage4->Name = L"tabPage4";
		this->tabPage4->Padding = System::Windows::Forms::Padding(3);
		this->tabPage4->Size = System::Drawing::Size(1031, 153);
		this->tabPage4->TabIndex = 2;
		this->tabPage4->Text = L"RegulatorPID";
		this->tabPage4->UseVisualStyleBackColor = true;
		// 
		// textBox11
		// 
		this->textBox11->Location = System::Drawing::Point(521, 98);
		this->textBox11->Name = L"textBox11";
		this->textBox11->Size = System::Drawing::Size(100, 20);
		this->textBox11->TabIndex = 12;
		this->textBox11->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::B_TextBox_TextChanged);
		// 
		// label16
		// 
		this->label16->AutoSize = true;
		this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label16->Location = System::Drawing::Point(485, 102);
		this->label16->Name = L"label16";
		this->label16->Size = System::Drawing::Size(16, 16);
		this->label16->TabIndex = 11;
		this->label16->Text = L"b";
		// 
		// textBox10
		// 
		this->textBox10->Location = System::Drawing::Point(521, 63);
		this->textBox10->Name = L"textBox10";
		this->textBox10->Size = System::Drawing::Size(100, 20);
		this->textBox10->TabIndex = 10;
		this->textBox10->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::TP_TextBox_TextChanged);
		// 
		// label15
		// 
		this->label15->AutoSize = true;
		this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label15->Location = System::Drawing::Point(476, 65);
		this->label15->Name = L"label15";
		this->label15->Size = System::Drawing::Size(25, 16);
		this->label15->TabIndex = 9;
		this->label15->Text = L"Tp";
		// 
		// textBox9
		// 
		this->textBox9->Location = System::Drawing::Point(308, 98);
		this->textBox9->Name = L"textBox9";
		this->textBox9->Size = System::Drawing::Size(98, 20);
		this->textBox9->TabIndex = 8;
		this->textBox9->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::N_TextBox_TextChanged);
		// 
		// label14
		// 
		this->label14->AutoSize = true;
		this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label14->Location = System::Drawing::Point(269, 102);
		this->label14->Name = L"label14";
		this->label14->Size = System::Drawing::Size(18, 16);
		this->label14->TabIndex = 7;
		this->label14->Text = L"N";
		// 
		// label13
		// 
		this->label13->AutoSize = true;
		this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label13->Location = System::Drawing::Point(272, 63);
		this->label13->Name = L"label13";
		this->label13->Size = System::Drawing::Size(15, 16);
		this->label13->TabIndex = 6;
		this->label13->Text = L"k";
		// 
		// textBox8
		// 
		this->textBox8->Location = System::Drawing::Point(308, 63);
		this->textBox8->Name = L"textBox8";
		this->textBox8->Size = System::Drawing::Size(100, 20);
		this->textBox8->TabIndex = 5;
		this->textBox8->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::K_TextBox_TextChanged);
		// 
		// label12
		// 
		this->label12->AutoSize = true;
		this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label12->Location = System::Drawing::Point(69, 102);
		this->label12->Name = L"label12";
		this->label12->Size = System::Drawing::Size(25, 16);
		this->label12->TabIndex = 4;
		this->label12->Text = L"Td";
		// 
		// textBox7
		// 
		this->textBox7->Location = System::Drawing::Point(113, 102);
		this->textBox7->Name = L"textBox7";
		this->textBox7->Size = System::Drawing::Size(100, 20);
		this->textBox7->TabIndex = 3;
		this->textBox7->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::TD_TextBox_TextChanged);
		// 
		// label11
		// 
		this->label11->AutoSize = true;
		this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F));
		this->label11->Location = System::Drawing::Point(6, 13);
		this->label11->Name = L"label11";
		this->label11->Size = System::Drawing::Size(359, 20);
		this->label11->TabIndex = 2;
		this->label11->Text = L"Prosimy o dobranie parametrów regulatora PID";
		// 
		// label10
		// 
		this->label10->AutoSize = true;
		this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
		this->label10->Location = System::Drawing::Point(74, 63);
		this->label10->Name = L"label10";
		this->label10->Size = System::Drawing::Size(20, 16);
		this->label10->TabIndex = 1;
		this->label10->Text = L"Ti";
		// 
		// textBox6
		// 
		this->textBox6->Location = System::Drawing::Point(113, 63);
		this->textBox6->Name = L"textBox6";
		this->textBox6->Size = System::Drawing::Size(100, 20);
		this->textBox6->TabIndex = 0;
		this->textBox6->TextChanged += gcnew System::EventHandler(this, &CPlotSurface2DDemo::TI_TextBox_TextChanged);
		// 
		// CPlotSurface2DDemo
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(1066, 645);
		this->Controls->Add(this->tabControl2);
		this->Controls->Add(this->tabControl1);
		this->Controls->Add(this->menuStrip1);
		this->MainMenuStrip = this->menuStrip1;
		this->Name = L"CPlotSurface2DDemo";
		this->Text = L"PSS 1.9";
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
		this->tabControl1->ResumeLayout(false);
		this->Wykres->ResumeLayout(false);
		this->Wykres->PerformLayout();
		this->tabPage2->ResumeLayout(false);
		this->tabPage2->PerformLayout();
		this->menuStrip1->ResumeLayout(false);
		this->menuStrip1->PerformLayout();
		this->tabControl2->ResumeLayout(false);
		this->tabPage1->ResumeLayout(false);
		this->tabPage1->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
		this->tabPage3->ResumeLayout(false);
		this->tabPage3->PerformLayout();
		this->tabPage4->ResumeLayout(false);
		this->tabPage4->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	 }
#pragma endregion

	// Handle the TrackBar.ValueChanged event by calculating a value for
	// TextBox1 based on the TrackBar value.  
	private: System::Void trackBar1_ValueChanged( Object^ /*sender*/, System::EventArgs^ /*e*/ )
	{
		this->textBox1->Text = String::Concat("", trackBar1->Value );
		this->n = trackBar1->Value * 1000;
	}

	// -------------------------------------------------------------------------------------------------------

	private: System::Void startAsyncButton_Click( System::Object^ /*sender*/, System::EventArgs^ /*e*/ )
	{
		// Check if object was selected
		// ----------------------------------------------------------------------------------------------------------
		if ( listBox1->SelectedIndex != -1 )
		{

			// Check if generator was uploaded
			// ----------------------------------------------------------------------------------------------------------
			if(config_generator->get_size() > 0)
			{
				
				if(m_regulator)		m_regulator->set_setpoint(m_proces);

				m_loop->set_object(arx_object);
				m_loop->set_regulator(m_regulator);

				// Disable the Start button until 
				// the asynchronous operation is done.
				this->startAsyncButton->Enabled = false;

				// Enable the Cancel button while 
				// the asynchronous operation runs.
				this->cancelAsyncButton->Enabled = true;

				// Disable clear button for regulator
				this->button5->Enabled = false;

				// Disable upload and clear button for object config
				this->button1->Enabled = false;
				this->button6->Enabled = false;

				// Disable button for clearing generators
				this->button3->Enabled = false;

				this->listBox1->Enabled = false;

				// Start the asynchronous operation.
				backgroundWorker1->RunWorkerAsync();
			}
			else
			{
				MessageBox::Show("Nie wybrano generatora sygna³ów", "Konfiguracja");
			}
		}
		else
		{
			MessageBox::Show("Obiekt nie zosta³ zaznaczony", "Konfiguracja");
		}
		
	}

	// -------------------------------------------------------------------------------------------------------

	private: System::Void cancelAsyncButton_Click( System::Object^ /*sender*/, System::EventArgs^ /*e*/ )
	{  
		// Cancel the asynchronous operation.
		this->backgroundWorker1->CancelAsync();

		// Enable clear button for regulator
		this->button5->Enabled = true;

		// Enable upload and clear button for object config
		this->button1->Enabled = true;
		this->button6->Enabled = true;

		// Enable clear button for generator
		this->button3->Enabled = true;

		this->listBox1->Enabled = true;

		// Disable the Cancel button.
		cancelAsyncButton->Enabled = false;
	}

	// -------------------------------------------------------------------------------------------------------

	private: System::Void zamknijToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//ToDo
		// check if background process is set then - close it
		CPlotSurface2DDemo::Close();
	}

	// -------------------------------------------------------------------------------------------------------

	/**
	 * Upload object configs, before that all configs for object are removed, listbox is cleared
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// Check if dialog is open correct
		if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				// Clear all selections in the ListBox and clear from app
				listBox1->ClearSelected();
				listBox1->Items->Clear();

				// Create an instance of StreamReader to read from a file.
				StreamReader^ sr = gcnew StreamReader( this->openFileDialog1->FileName );
				try
				{
					// Clear config files
					config_object->clear_all();

					String^ line;
					// Read and display lines from the file until the end of 
					// the file is reached.
					while ( line = sr->ReadLine() )
					{
						config_object->parse_line( msclr::interop::marshal_as< std::string >( line )  );
					}

					// Shutdown the painting of the ListBox as items are added.
					listBox1->BeginUpdate();

					// Loop through and add config to the ListBox.
					for ( int x = 1; x <= config_object->get_size(); x++ )
					{
						listBox1->Items->Add( String::Format( "Obiekt {0}", x ) );

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
	
	// -------------------------------------------------------------------------------------------------------

	/**
	 * Upload generators for controller
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
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

					if(config_generator->get_size() > 0)
					{
						// Create new proces if is NULL
						if(m_proces == NULL)
						{
							m_proces = new Signal;
						}

						// Getting config for Signal generator
						std::vector<std::map<std::string,double>> generator;
						Config::getInstance().get_config_generator(generator);

						// Creating process from all signal in config
						for(auto it = generator.begin() ; it != generator.end() ; it++)
						{
							if( (*it)["name"] == 1 ) // SignalStep
							{
								m_proces = new SignalStep(m_proces, (*it)["val"]);
							}
							else if( (*it)["name"] == 2 ) // SignalRectangle
							{
								m_proces = new SignalRectangle(m_proces, (*it)["amplitude"], static_cast<int>((*it)["period"]), (*it)["fill"]);
							}
							else if( (*it)["name"] == 3 ) // SignalTriangle
							{
								m_proces = new SignalTriangle(m_proces, (*it)["frequency"], (*it)["amplitude"]);
							}
							else if( (*it)["name"] == 4) // SignalSinus
							{
								m_proces = new SignalSinus(m_proces, static_cast<int>((*it)["period"]), (*it)["amplitude"]);
							}
						}
						
					}
				}
				finally
				{
					if ( sr )
					delete (IDisposable^)sr;
					
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
	
	// -------------------------------------------------------------------------------------------------------
	
	/**
	 * Clear all generators
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		config_generator->clear_all();
		if(m_proces)
			delete m_proces;
		m_proces = NULL;
		this->label1->Text =  L"Za³adowano: 0";
	}
	
	// -------------------------------------------------------------------------------------------------------

	/**
	 * Uploading config files for regulator - we clear listbox, and null m_regulator pointer
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// Check if dialog is open correct
		if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				// Clear all selections in the ListBox and clear from app
				listBox2->ClearSelected();
				listBox2->Items->Clear();

				// Create an instance of StreamReader to read from a file.
				StreamReader^ sr = gcnew StreamReader( this->openFileDialog1->FileName );
				try
				{
					// Clear config files
					m_config_regulator->clear_all();

					String^ line;

					// Read and display lines from the file until the end of the file is reached.
					while ( line = sr->ReadLine() )
					{
						m_config_regulator->parse_line( msclr::interop::marshal_as< std::string >( line )  );
					}

					// Shutdown the painting of the ListBox as items are added.
					listBox2->BeginUpdate();

					// Loop through and add config to the ListBox.
					for ( int x = 1; x <= m_config_regulator->get_size(); x++ )
					{
						listBox2->Items->Add( String::Format( "Regulator {0}", x) );
					}
					listBox2->EndUpdate();

				}
				finally
				{
					if ( sr )
					delete (IDisposable^)sr;
					m_regulator_selected_flag = false;
				}

			}
			catch ( Exception^ e ) 
			{
				// Let the user know what went wrong.
				MessageBox::Show( e->Message, "The file could not be read");
			}
				
		}
	}
	
	// -------------------------------------------------------------------------------------------------------

	/**
	 * Event - setting regulator for loop control
	 *
	 * @param		Object^
	 * @param		System::EventArgs^
	 * @return		void
	 */
	private: System::Void listBox2_SelectedIndexChanged( Object^ /*sender*/, System::EventArgs^ /*e*/ )
	{
		if(m_config_regulator->get_size() > 0)
		{
			// Getting config for Signal generator
			std::map<std::string,double> regulator;
			Config::getInstance().get_config_regulator(regulator, listBox2->SelectedIndex);

			RegulatorManager manager;

			try
			{	
				if(regulator["name"] == 1) // Regulator GPC
				{
					m_regulator = manager.get_prototyp("GPC");
					m_regulator->set_parameters(regulator);

					this->tabPage1->Enabled = false; // P page disabled
					this->tabPage4->Enabled = false; // PID page disabled
					this->tabPage3->Enabled = true;
				}
				else if(regulator["name"] == 2) // Regulator PID
				{
					m_regulator = manager.get_prototyp("PID");
					m_regulator->set_parameters(regulator);

					this->tabPage1->Enabled = false; // P page disabled
					this->tabPage4->Enabled = true; // PID page enabled
					this->tabPage3->Enabled = false; // GPC page disabled
				
				}
				else if(regulator["name"] == 3) // Regulator P
				{
					m_regulator = manager.get_prototyp("P");
					m_regulator->set_parameters(regulator);

					this->tabPage1->Enabled = true;
					this->tabPage4->Enabled = false; // P page disabled
					this->tabPage3->Enabled = false; // GPC page disabled
				}

				m_regulator_selected_flag = true;			
			}
			catch(std::string & e)
			{
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "Regulator");
			}
		}
	}

	// -------------------------------------------------------------------------------------------------------

	/**
	 * Event - setting object for loop control
	 *
	 * @param		Object^
	 * @param		System::EventArgs^
	 * @return		void
	 */
	private: System::Void listBox1_SelectedIndexChanged( Object^ /*sender*/, System::EventArgs^ /*e*/ )
	{
		if(config_object->get_size() > 0)
		{
			// Fill loop with object and regulator
			std::tuple <std::map<int,double>, std::map<int,double>, std::map<std::string, double>> m_vector_objects_ptr;

			Config::getInstance().get_config(m_vector_objects_ptr, listBox1->SelectedIndex);

			std::deque<double> m_A;
			std::deque<double> m_B;

			for( auto it =  std::get<0>(m_vector_objects_ptr).begin(); it !=  std::get<0>(m_vector_objects_ptr).end(); it++ )	m_A.push_back( it->second );
			for( auto ite = std::get<1>(m_vector_objects_ptr).begin(); ite != std::get<1>(m_vector_objects_ptr).end(); ite++ )	m_B.push_back( ite->second );
	
			arx_object->set_parameters(m_A, m_B, std::get<2>(m_vector_objects_ptr));
		}
	}

	// -------------------------------------------------------------------------------------------------------

	/**
	 * Clear all regulators and configs for them, we clear also listbox
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// Clear all selections in the ListBox and clear from app
		listBox2->ClearSelected();
		listBox2->Items->Clear();

		// Clear config for regulator
		m_config_regulator->clear_all();

		if(m_regulator)
			delete m_regulator;

		m_regulator =  NULL;
		m_regulator_selected_flag = false;
	}

	// -------------------------------------------------------------------------------------------------------

	/**
	 * Clear all configs for object and delete old object pointer, after that we create new one
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// Clear all selections in the ListBox and clear from app
		listBox1->ClearSelected();
		listBox1->Items->Clear();

		// Clear config for regulator
		config_object->clear_all();

		if(arx_object)
		{
			delete arx_object;
			arx_object = NULL;
		}
		
		if(!arx_object)
			arx_object = new ARX;
	}

	// P
	// -------------------------------------------------------------------------------------------------------

	/**
	 * Event - value for Regulator P - has changed
	 *
	 * @param		Object^
	 * @param		System::EventArgs^
	 * @return		void
	 */
	private: System::Void NumericUpDown1_ValueChanged( Object^ /*sender*/, System::EventArgs^ /*e*/ )
	{
		m_regulator->set_parameters("k", System::Convert::ToDouble( numericUpDown1->Value ));
	}


	// GPC
	// -------------------------------------------------------------------------------------------------------

	/**
	 * Event - value for Regulator GPC - H has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void H_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox2->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("H", Double::Parse(textBox2->Text));
			}
			catch(std::string & e)
			{
				textBox2->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorGPC");
			}
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox2->ForeColor = Color::Red;
        }
    }

	/**
	 * Event - value for Regulator GPC - L has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void L_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox3->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("L", Double::Parse(textBox3->Text));
			}
			catch(std::string & e)
			{
				textBox3->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorGPC");
			}
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox3->ForeColor = Color::Red;
        }
    }

	/**
	 * Event - value for Regulator GPC - Alpha has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void ALPHA_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox4->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("alpha", Double::Parse( textBox4->Text ) );
			}
			catch(std::string & e)
			{
				textBox4->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorGPC");
			}
			 
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox4->ForeColor = Color::Red;
        }
    }

	/**
	 * Event - value for Regulator GPC - Alpha has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void RO_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox5->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("ro", Double::Parse(textBox5->Text));
			}
			catch(std::string & e)
			{
				textBox5->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorGPC");
			}
			 
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox5->ForeColor = Color::Red;
        }
    }
	
	// PID
	// ---------------------------------------------------------------------------------------------------

	/**
	 * Event - value for Regulator PID - TI has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void TI_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox6->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("Ti", Double::Parse(textBox6->Text));
			}
			catch(std::string & e)
			{
				textBox6->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorGPC");
			}
			 
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox6->ForeColor = Color::Red;
        }
    }

	/**
	 * Event - value for Regulator PID - TD has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void TD_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox7->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("Td", Double::Parse(textBox7->Text));
			}
			catch(std::string & e)
			{
				textBox7->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorPID");
			}
			 
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox7->ForeColor = Color::Red;
        }
    }

	/**
	 * Event - value for Regulator PID - K has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void K_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox8->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("k", Double::Parse(textBox8->Text));
			}
			catch(std::string & e)
			{
				textBox8->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorPID");
			}
			 
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox8->ForeColor = Color::Red;
        }
    }

	/**
	 * Event - value for Regulator PID - N has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void N_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox9->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("N", Double::Parse(textBox9->Text));
			}
			catch(std::string & e)
			{
				textBox9->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorPID");
			}
			 
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox9->ForeColor = Color::Red;
        }
    }

	/**
	 * Event - value for Regulator PID - TP has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void TP_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox10->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("Tp", Double::Parse(textBox10->Text));
			}
			catch(std::string & e)
			{
				textBox10->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorPID");
			}
			 
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox10->ForeColor = Color::Red;
        }
    }

	/**
	 * Event - value for Regulator PID - B has changed
	 *
	 * @param		Object^
	 * @param		EventArgs^
	 * @return		void
	 */
	private: System::Void B_TextBox_TextChanged(Object^ /*sender*/, EventArgs^ /*e*/)
	{
        try 
		{
			// If the number is negative, display it in Red.
			textBox11->ForeColor = Color::Green;

			try
			{
				m_regulator->set_parameters("b", Double::Parse(textBox11->Text));
			}
			catch(std::string & e)
			{
				textBox11->ForeColor = Color::Red;
				MessageBox::Show(msclr::interop::marshal_as< String^ >( e ), "RegulatorPID");
			}
			 
        }
		catch (Exception^)
		{
            // If there is an error, display the text using the system colors. Semi coma
            textBox11->ForeColor = Color::Red;
        }
    }

	// ---------------------------------------------------------------------------------------------------

	/**
	 * Open file for saving data from regulation loop
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(!m_save_file)
		{
			m_save_file = m_save->createInstance("file");
		}
		
		if(m_save_file)
		{
			// Open file for saving data
			if(m_save_file->open())
			{
				m_save_file_flag = true;
				this->button7->BackColor = Color::Green;
			}
			else
				MessageBox::Show("Nie otworzono pliku do zapisu", "Zapis");
		}
	}
	
	/**
	 * Close file to disable saving data
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(m_save_file)
			m_save_file->close();

		m_save_file_flag = false;
		this->button7->BackColor = Color::Transparent;
	}

	/**
	 * Displaying data from Regulator
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e)
	{
		 if(m_regulator)
		 {
			 std::map<std::string, double> values;
			 m_regulator->get_parameters(values);

			 std::stringstream ss; //create a stringstream

			 for(auto it = values.begin() ; it != values.end() ; it++)
			 {
				 ss <<  it->first << ": " << it->second << " | ";
			 }

			 MessageBox::Show(msclr::interop::marshal_as< String^ >( ss.str() ), "Regulator");
		 }
		 else
			 MessageBox::Show("Brak zdefiniowanego regulatora", "Regulator");
	}

	/**
	 * Displaying ARX model parameters
	 * 
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(arx_object)
		{
			 std::deque<double> A;
			 std::deque<double> B;
			 std::map<std::string, double> others;
			 arx_object->get_parameters(A,B,others);

			 std::stringstream ss; //create a stringstream

			 for(auto it = others.begin() ; it != others.end() ; it++)
			 {
				 ss <<  it->first << ": " << it->second << " | ";
			 }

			 ss << "A: ";

			 for(auto it = A.begin() ; it != A.end() ; it++)
			 {
				 ss << *it << " | ";
			 }

			 ss << "B: ";

			 for(auto it = B.begin() ; it != B.end() ; it++)
			 {
				 ss << *it << " | ";
			 }

			 MessageBox::Show(msclr::interop::marshal_as< String^ >( ss.str() ), "Obiekt");
		 }
		 else
			 MessageBox::Show("Brak zdefiniowanego obiektu", "Obiekt");
	}

	/**
	 * Info button from Menu
	 *
	 * @param		System::Object^  sender
	 * @param		System::EventArgs^  e
	 * @return		void
	 */
	private: System::Void infoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		MessageBox::Show("Aplikacja PSS, wersja 1.9", "PSS");
	}

}; // END OF CLASS

} // END OF NAMESPACE