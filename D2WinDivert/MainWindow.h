#pragma once

#include "util.h"
#include <fstream>
#include <msclr\marshal_cppstd.h>

std::vector<std::string>* playersID;

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
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBoxSteamIDs;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBoxPriority;
	private: System::Windows::Forms::TextBox^ textBoxBatch;
	private: System::Windows::Forms::TextBox^ textBoxThreads;
	private: System::Windows::Forms::Button^ buttonStart;
	private: System::Windows::Forms::Button^ buttonApply;

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
			this->textBoxPriority = (gcnew System::Windows::Forms::TextBox());
			this->textBoxBatch = (gcnew System::Windows::Forms::TextBox());
			this->textBoxThreads = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->buttonApply = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(110, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"SteamID тиммейтов:";
			// 
			// textBoxSteamIDs
			// 
			this->textBoxSteamIDs->Location = System::Drawing::Point(15, 25);
			this->textBoxSteamIDs->Multiline = true;
			this->textBoxSteamIDs->Name = L"textBoxSteamIDs";
			this->textBoxSteamIDs->Size = System::Drawing::Size(140, 170);
			this->textBoxSteamIDs->TabIndex = 2;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBoxPriority);
			this->groupBox1->Controls->Add(this->textBoxBatch);
			this->groupBox1->Controls->Add(this->textBoxThreads);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Location = System::Drawing::Point(161, 95);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(120, 100);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Сложные приколы";
			// 
			// textBoxPriority
			// 
			this->textBoxPriority->Location = System::Drawing::Point(91, 69);
			this->textBoxPriority->Name = L"textBoxPriority";
			this->textBoxPriority->Size = System::Drawing::Size(23, 20);
			this->textBoxPriority->TabIndex = 5;
			this->textBoxPriority->Text = L"0";
			this->textBoxPriority->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBoxBatch
			// 
			this->textBoxBatch->Location = System::Drawing::Point(91, 43);
			this->textBoxBatch->Name = L"textBoxBatch";
			this->textBoxBatch->Size = System::Drawing::Size(23, 20);
			this->textBoxBatch->TabIndex = 4;
			this->textBoxBatch->Text = L"1";
			this->textBoxBatch->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBoxThreads
			// 
			this->textBoxThreads->Location = System::Drawing::Point(91, 16);
			this->textBoxThreads->Name = L"textBoxThreads";
			this->textBoxThreads->Size = System::Drawing::Size(23, 20);
			this->textBoxThreads->TabIndex = 3;
			this->textBoxThreads->Text = L"1";
			this->textBoxThreads->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 73);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(38, 13);
			this->label4->TabIndex = 2;
			this->label4->Text = L"Priority";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 46);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(56, 13);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Batch size";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Threads";
			// 
			// buttonStart
			// 
			this->buttonStart->Location = System::Drawing::Point(161, 24);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(120, 30);
			this->buttonStart->TabIndex = 4;
			this->buttonStart->Text = L"Начать";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &MainWindow::buttonStart_Click);
			// 
			// buttonApply
			// 
			this->buttonApply->Enabled = false;
			this->buttonApply->Location = System::Drawing::Point(161, 59);
			this->buttonApply->Name = L"buttonApply";
			this->buttonApply->Size = System::Drawing::Size(120, 30);
			this->buttonApply->TabIndex = 6;
			this->buttonApply->Text = L"Применить";
			this->buttonApply->UseVisualStyleBackColor = true;
			this->buttonApply->Click += gcnew System::EventHandler(this, &MainWindow::buttonApply_Click);
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(295, 204);
			this->Controls->Add(this->buttonApply);
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
		auto str = this->textBoxSteamIDs->Text->Split('\n');
		if (playersID == nullptr) {
			playersID = new std::vector<std::string>;
		}
		else {
			playersID->clear();
		}
		for (int i = 0; i < str->Length; i++) {
			if (!String::IsNullOrWhiteSpace(str[i])) {
				msclr::interop::marshal_context context;
				std::string a = context.marshal_as<std::string>(str[i]);
				if (a[a.length() - 1] == '\n' || a[a.length() - 1] == '\r') {
					a.pop_back();
				}
				if (a[a.length() - 1] == '\n' || a[a.length() - 1] == '\r') {
					a.pop_back();
				}
				playersID->push_back(a);
			}
		}
		filter(Convert::ToInt32(this->textBoxThreads->Text), 
			Convert::ToInt32(this->textBoxBatch->Text), 
			Convert::ToInt32(this->textBoxPriority->Text), playersID);
		this->buttonStart->Enabled = false;
		this->buttonApply->Enabled = true;
	}
	private: System::Void buttonApply_Click(System::Object^ sender, System::EventArgs^ e) {
		auto str = this->textBoxSteamIDs->Text->Split('\n');
		if (playersID == nullptr) {
			playersID = new std::vector<std::string>;
		}
		else {
			playersID->clear();
		}
		for (int i = 0; i < str->Length; i++) {
			if (!String::IsNullOrWhiteSpace(str[i])) {
				msclr::interop::marshal_context context;
				std::string a = context.marshal_as<std::string>(str[i]);
				if (a[a.length() - 1] == '\n' || a[a.length() - 1] == '\r') {
					a.pop_back();
				}
				if (a[a.length() - 1] == '\n' || a[a.length() - 1] == '\r') {
					a.pop_back();
				}
				playersID->push_back(a);
			}
		}
	}
};
}
