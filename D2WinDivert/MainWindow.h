﻿#pragma once

#include <map>
#include <msclr\marshal_cppstd.h>

namespace D2WinDivert {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWIndow
	/// </summary>

	public ref class MainWindow : public System::Windows::Forms::Form {
	public:
		MainWindow(void) {
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow() {
			if (components) {
				delete components;
			}
		}
	public: std::vector<std::string>* playersID = new std::vector<std::string>;
	public: std::map<std::string, std::string>* playersNames = new std::map<std::string, std::string>;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBoxSteamIDs;
	private: System::Windows::Forms::LinkLabel^ linkLabel1;
	private: System::Windows::Forms::TextBox^ textBoxNames;
	private: System::Windows::Forms::Button^ buttonHelp;
	private: System::Windows::Forms::TextBox^ textBoxThreads;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::CheckBox^ filterCheckBox;
	private: System::Windows::Forms::CheckBox^ scanCheckBox;
	private: System::Windows::Forms::VScrollBar^ vScrollBar1;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxSteamIDs = (gcnew System::Windows::Forms::TextBox());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->textBoxNames = (gcnew System::Windows::Forms::TextBox());
			this->buttonHelp = (gcnew System::Windows::Forms::Button());
			this->textBoxThreads = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->filterCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->scanCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"SteamID:";
			// 
			// textBoxSteamIDs
			// 
			this->textBoxSteamIDs->Location = System::Drawing::Point(12, 25);
			this->textBoxSteamIDs->Multiline = true;
			this->textBoxSteamIDs->Name = L"textBoxSteamIDs";
			this->textBoxSteamIDs->Size = System::Drawing::Size(200, 200);
			this->textBoxSteamIDs->TabIndex = 2;
			this->textBoxSteamIDs->WordWrap = false;
			this->textBoxSteamIDs->TextChanged += gcnew System::EventHandler(this, &MainWindow::textBox_Edit);
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Location = System::Drawing::Point(476, 9);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(40, 13);
			this->linkLabel1->TabIndex = 8;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"GitHub";
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainWindow::linkLabel1_LinkClicked);
			// 
			// textBoxNames
			// 
			this->textBoxNames->Location = System::Drawing::Point(218, 25);
			this->textBoxNames->Multiline = true;
			this->textBoxNames->Name = L"textBoxNames";
			this->textBoxNames->ReadOnly = true;
			this->textBoxNames->Size = System::Drawing::Size(200, 200);
			this->textBoxNames->TabIndex = 9;
			this->textBoxNames->WordWrap = false;
			// 
			// buttonHelp
			// 
			this->buttonHelp->Location = System::Drawing::Point(447, 97);
			this->buttonHelp->Name = L"buttonHelp";
			this->buttonHelp->Size = System::Drawing::Size(69, 23);
			this->buttonHelp->TabIndex = 10;
			this->buttonHelp->Text = L"\?";
			this->buttonHelp->UseVisualStyleBackColor = true;
			this->buttonHelp->Click += gcnew System::EventHandler(this, &MainWindow::buttonHelp_Click);
			// 
			// textBoxThreads
			// 
			this->textBoxThreads->Location = System::Drawing::Point(496, 25);
			this->textBoxThreads->Name = L"textBoxThreads";
			this->textBoxThreads->Size = System::Drawing::Size(20, 20);
			this->textBoxThreads->TabIndex = 12;
			this->textBoxThreads->Text = L"1";
			this->textBoxThreads->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(444, 28);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Threads";
			// 
			// filterCheckBox
			// 
			this->filterCheckBox->AutoSize = true;
			this->filterCheckBox->Location = System::Drawing::Point(447, 51);
			this->filterCheckBox->Name = L"filterCheckBox";
			this->filterCheckBox->Size = System::Drawing::Size(48, 17);
			this->filterCheckBox->TabIndex = 13;
			this->filterCheckBox->Text = L"Filter";
			this->filterCheckBox->UseVisualStyleBackColor = true;
			this->filterCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::filterCheckbox_CheckedChanged);
			// 
			// scanCheckBox
			// 
			this->scanCheckBox->AutoSize = true;
			this->scanCheckBox->Location = System::Drawing::Point(447, 74);
			this->scanCheckBox->Name = L"scanCheckBox";
			this->scanCheckBox->Size = System::Drawing::Size(51, 17);
			this->scanCheckBox->TabIndex = 14;
			this->scanCheckBox->Text = L"Scan";
			this->scanCheckBox->UseVisualStyleBackColor = true;
			this->scanCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::scanCheckBox_CheckedChanged);
			// 
			// vScrollBar1
			// 
			this->vScrollBar1->LargeChange = 1;
			this->vScrollBar1->Location = System::Drawing::Point(421, 25);
			this->vScrollBar1->Maximum = 0;
			this->vScrollBar1->Name = L"vScrollBar1";
			this->vScrollBar1->Size = System::Drawing::Size(20, 200);
			this->vScrollBar1->TabIndex = 15;
			this->vScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MainWindow::vScrollBar1_Scroll);
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(528, 236);
			this->Controls->Add(this->vScrollBar1);
			this->Controls->Add(this->scanCheckBox);
			this->Controls->Add(this->filterCheckBox);
			this->Controls->Add(this->textBoxThreads);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->buttonHelp);
			this->Controls->Add(this->textBoxNames);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->textBoxSteamIDs);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainWindow";
			this->Text = L"D2WinDivert by EugW";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void filterCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void scanCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox_Edit(System::Object^ sender, System::EventArgs^ e);
	private: System::Void SteamIDHandler(System::Object^ sender, System::Net::DownloadStringCompletedEventArgs^ e);
	private: System::Void linkLabel1_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		System::Diagnostics::Process::Start("https://github.com/EugW/D2WinDivert");
	}
	private: System::Void buttonHelp_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::MessageBox::Show(
			"Threads - number of threads that process packets (more is faster, cpu load is bigger)\n\n" +
			"Scan - activate this mode and tell teammates to join fireteam, it will capture their IDs and add them to the list\n\n" +
			"Filter - activate this mode and it will block any connection except that contain ID from the list\n\n" +
			"App works with STEAM, XBOX and PS",
			"Help");
	}
	public: int getThreads() {
		return Convert::ToInt32(textBoxThreads->Text);
	}
	public: std::string getLines() {
		auto str = textBoxSteamIDs->Text;
		msclr::interop::marshal_context context;
		auto res = context.marshal_as<std::string>(str);
		return res;
	}
	private: delegate System::Void threadStateChangeDelegate(int type, int evt);
	public: System::Void threadStateChange(int type, int evt) {
		auto action = gcnew threadStateChangeDelegate(this, &MainWindow::threadStateChangeWorker);
		Invoke(action, type, evt);
	}
	private: System::Void threadStateChangeWorker(int type, int evt) {
		if (evt == 0) {
			if (type == 0) {
				filterCheckBox->Enabled = true;
				scanCheckBox->Enabled = false;
				textBoxThreads->Enabled = false;
			}
			else if (type == 1) {
				filterCheckBox->Enabled = false;
				scanCheckBox->Enabled = true;
				textBoxThreads->Enabled = false;
			}
		}
		else if (evt == 1) {
			filterCheckBox->Enabled = true;
			scanCheckBox->Enabled = true;
			textBoxThreads->Enabled = true;
		}

	}
	private: delegate System::Void appendTextBoxDelegate(System::String^ id);
	public: System::Void appendTextBox(std::string id) {
		auto action = gcnew appendTextBoxDelegate(this, &MainWindow::appendTextBoxWorker);
		Invoke(action, gcnew System::String(id.c_str()));
	}
	private: System::Void appendTextBoxWorker(System::String^ id) {
		textBoxSteamIDs->Text += id;
		textBoxSteamIDs->Text += Environment::NewLine;
	}
	private: System::Void vScrollBar1_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
		auto number = e->NewValue;
		int positionS = 0;
		int positionN = 0;
		for (int i = 0; i < number; i++) {
			positionS += textBoxSteamIDs->Lines[i]->Length + Environment::NewLine->Length;
			positionN += textBoxNames->Lines[i]->Length + Environment::NewLine->Length;
		}
		textBoxNames->SelectionStart = positionN;
		textBoxNames->ScrollToCaret();
		textBoxSteamIDs->SelectionStart = positionS;
		textBoxSteamIDs->ScrollToCaret();
	}
};
}
