#pragma once

#include "util.h"
#include <fstream>
#include <map>
#include <msclr\marshal_cppstd.h>

std::vector<std::string>* playersID;
std::map<std::string, std::string> playersNames;

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
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBoxSteamIDs;
	private: System::Windows::Forms::GroupBox^ groupBox1;

	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::TextBox^ textBoxThreads;
	private: System::Windows::Forms::Button^ buttonStart;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::LinkLabel^ linkLabel1;
	private: System::Windows::Forms::TextBox^ textBoxNames;
	private: System::Windows::Forms::Button^ buttonHelp;

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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxThreads = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->textBoxNames = (gcnew System::Windows::Forms::TextBox());
			this->buttonHelp = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
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
			this->textBoxSteamIDs->Size = System::Drawing::Size(140, 170);
			this->textBoxSteamIDs->TabIndex = 2;
			this->textBoxSteamIDs->TextChanged += gcnew System::EventHandler(this, &MainWindow::textBox_Edit);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBoxThreads);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Location = System::Drawing::Point(264, 150);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(120, 45);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Advanced";
			// 
			// textBoxThreads
			// 
			this->textBoxThreads->Location = System::Drawing::Point(94, 19);
			this->textBoxThreads->Name = L"textBoxThreads";
			this->textBoxThreads->Size = System::Drawing::Size(20, 20);
			this->textBoxThreads->TabIndex = 3;
			this->textBoxThreads->Text = L"1";
			this->textBoxThreads->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Threads";
			// 
			// buttonStart
			// 
			this->buttonStart->Location = System::Drawing::Point(264, 25);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(120, 64);
			this->buttonStart->TabIndex = 4;
			this->buttonStart->Text = L"Start";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &MainWindow::buttonStart_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(145, 9);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(73, 13);
			this->label5->TabIndex = 7;
			this->label5->Text = L"D2 PRIVATE:";
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Location = System::Drawing::Point(224, 9);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(160, 13);
			this->linkLabel1->TabIndex = 8;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"https://discord.gg/8vSmKJFgp7";
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainWindow::linkLabel1_LinkClicked);
			// 
			// textBoxNames
			// 
			this->textBoxNames->Location = System::Drawing::Point(158, 25);
			this->textBoxNames->Multiline = true;
			this->textBoxNames->Name = L"textBoxNames";
			this->textBoxNames->ReadOnly = true;
			this->textBoxNames->Size = System::Drawing::Size(100, 170);
			this->textBoxNames->TabIndex = 9;
			// 
			// buttonHelp
			// 
			this->buttonHelp->Location = System::Drawing::Point(264, 95);
			this->buttonHelp->Name = L"buttonHelp";
			this->buttonHelp->Size = System::Drawing::Size(120, 49);
			this->buttonHelp->TabIndex = 10;
			this->buttonHelp->Text = L"\?";
			this->buttonHelp->UseVisualStyleBackColor = true;
			this->buttonHelp->Click += gcnew System::EventHandler(this, &MainWindow::buttonHelp_Click);
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(396, 207);
			this->Controls->Add(this->buttonHelp);
			this->Controls->Add(this->textBoxNames);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->buttonStart);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->textBoxSteamIDs);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainWindow";
			this->Text = L"D2 WinDivert by EugW";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonStart_Click(System::Object^ sender, System::EventArgs^ e) {
		if (playersID == nullptr)
			playersID = new std::vector<std::string>;
		filter(Convert::ToInt32(this->textBoxThreads->Text), playersID);
		this->buttonStart->Enabled = false;
		this->textBoxThreads->Enabled = false;
	}
	private: System::Void textBox_Edit(System::Object^ sender, System::EventArgs^ e) {
		auto st = this->textBoxSteamIDs->SelectionStart;
		auto le = this->textBoxSteamIDs->SelectionLength;
		this->textBoxSteamIDs->Text = this->textBoxSteamIDs->Text->Replace(Environment::NewLine + Environment::NewLine,
			Environment::NewLine);
		this->textBoxSteamIDs->Select(st, le);
		auto str = this->textBoxSteamIDs->Lines;
		if (playersID == nullptr)
			playersID = new std::vector<std::string>;
		else
			playersID->clear();
		msclr::interop::marshal_context context;
		for (int i = 0; i < str->Length; i++)
			if (!String::IsNullOrWhiteSpace(str[i])) {
				std::string a = context.marshal_as<std::string>(str[i]->Replace(Environment::NewLine, "")
					->Replace(" ", ""));
				playersID->push_back(a);
			}
		for (int i = 0; i < playersID->size(); i++) {
			System::Net::WebClient^ wc = gcnew System::Net::WebClient();
			wc->DownloadStringCompleted += gcnew System::Net::DownloadStringCompletedEventHandler(this, &MainWindow::SteamIDHandler);
			wc->DownloadStringAsync(gcnew Uri("https://steamcommunity.com/profiles/" +
				gcnew String(playersID->at(i).c_str()) + "/?xml=1"));
		}

	}
	public: System::Void SteamIDHandler(System::Object^ sender, System::Net::DownloadStringCompletedEventArgs^ e) {
		auto result = e->Result;
		auto sstart = result->IndexOf("<steamID64>") + 11;
		auto send = result->IndexOf("</steamID64>");
		auto nstart = result->IndexOf("<steamID><![CDATA[") + 18;
		auto nend = result->IndexOf("]]></steamID>");
		if (sstart != 10 && send != -1 && nstart != 17 && nend != -1) {
			auto steamid = result->Substring(sstart, send - sstart);
			auto name = result->Substring(nstart, nend - nstart);
			msclr::interop::marshal_context context;
			if (playersNames.count(context.marshal_as<std::string>(steamid)) == 1)
				playersNames.at(context.marshal_as<std::string>(steamid)) =
				context.marshal_as<std::string>(name);
			else
				playersNames.emplace(context.marshal_as<std::string>(steamid),
					context.marshal_as<std::string>(name));
		}
		this->textBoxNames->Clear();
		for (int i = 0; i < playersID->size(); i++) {
			if (playersNames.count(playersID->at(i)) == 1) {
				auto def = System::Text::Encoding::Default;
				auto utf8 = System::Text::Encoding::UTF8;
				auto bytes = def->GetBytes(gcnew String(playersNames.at(playersID->at(i)).c_str()));
				this->textBoxNames->Text += utf8->GetString(bytes);
				this->textBoxNames->Text += Environment::NewLine;
			}
			else
				this->textBoxNames->Text += Environment::NewLine;
		}
	}
	private: System::Void linkLabel1_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		System::Diagnostics::Process::Start("https://discord.gg/8vSmKJFgp7");
	}
	private: System::Void buttonHelp_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::MessageBox::Show("It's recommended not to change!!!\n\n\n" +
			"Threads - number of threads that process packets" +
			" (more is faster, cpu load is bigger)", "Help");
	}
	};
}
