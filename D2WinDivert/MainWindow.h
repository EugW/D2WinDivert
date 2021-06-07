#pragma once

#include <fstream>
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
			this->textBoxSteamIDs->Size = System::Drawing::Size(272, 170);
			this->textBoxSteamIDs->TabIndex = 2;
			this->textBoxSteamIDs->TextChanged += gcnew System::EventHandler(this, &MainWindow::textBox_Edit);
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Location = System::Drawing::Point(428, 9);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(40, 13);
			this->linkLabel1->TabIndex = 8;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"GitHub";
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainWindow::linkLabel1_LinkClicked);
			// 
			// textBoxNames
			// 
			this->textBoxNames->Location = System::Drawing::Point(290, 25);
			this->textBoxNames->Multiline = true;
			this->textBoxNames->Name = L"textBoxNames";
			this->textBoxNames->ReadOnly = true;
			this->textBoxNames->Size = System::Drawing::Size(100, 170);
			this->textBoxNames->TabIndex = 9;
			// 
			// buttonHelp
			// 
			this->buttonHelp->Location = System::Drawing::Point(399, 98);
			this->buttonHelp->Name = L"buttonHelp";
			this->buttonHelp->Size = System::Drawing::Size(69, 23);
			this->buttonHelp->TabIndex = 10;
			this->buttonHelp->Text = L"\?";
			this->buttonHelp->UseVisualStyleBackColor = true;
			this->buttonHelp->Click += gcnew System::EventHandler(this, &MainWindow::buttonHelp_Click);
			// 
			// textBoxThreads
			// 
			this->textBoxThreads->Location = System::Drawing::Point(448, 25);
			this->textBoxThreads->Name = L"textBoxThreads";
			this->textBoxThreads->Size = System::Drawing::Size(20, 20);
			this->textBoxThreads->TabIndex = 12;
			this->textBoxThreads->Text = L"1";
			this->textBoxThreads->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(396, 28);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Threads";
			// 
			// filterCheckBox
			// 
			this->filterCheckBox->AutoSize = true;
			this->filterCheckBox->Location = System::Drawing::Point(399, 51);
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
			this->scanCheckBox->Location = System::Drawing::Point(399, 75);
			this->scanCheckBox->Name = L"scanCheckBox";
			this->scanCheckBox->Size = System::Drawing::Size(51, 17);
			this->scanCheckBox->TabIndex = 14;
			this->scanCheckBox->Text = L"Scan";
			this->scanCheckBox->UseVisualStyleBackColor = true;
			this->scanCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::scanCheckBox_CheckedChanged);
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(480, 207);
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
			this->Text = L"D2 WinDivert by EugW";
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
		System::Windows::Forms::MessageBox::Show("It's recommended not to change!!!\n\n\n" +
			"Threads - number of threads that process packets" +
			" (more is faster, cpu load is bigger)", "Help");
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
	};
}
