#pragma once
#include <chrono>
namespace D2WinDivert {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DebugWindow
	/// </summary>
	public ref class DebugWindow : public System::Windows::Forms::Form
	{
	public:
		DebugWindow(void)
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
		~DebugWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^ checkBoxDebug;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
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
			this->checkBoxDebug = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// checkBoxDebug
			// 
			this->checkBoxDebug->AutoSize = true;
			this->checkBoxDebug->Location = System::Drawing::Point(13, 13);
			this->checkBoxDebug->Name = L"checkBoxDebug";
			this->checkBoxDebug->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->checkBoxDebug->Size = System::Drawing::Size(92, 17);
			this->checkBoxDebug->TabIndex = 0;
			this->checkBoxDebug->Text = L"Enable debug";
			this->checkBoxDebug->UseVisualStyleBackColor = true;
			this->checkBoxDebug->CheckedChanged += gcnew System::EventHandler(this, &DebugWindow::checkBoxDebug_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(13, 37);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(154, 46);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Timers";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(43, 13);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(31, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Total";
			// 
			// DebugWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->checkBoxDebug);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"DebugWindow";
			this->Text = L"DebugWindow";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void checkBoxDebug_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: delegate System::Void debugTimeDelegate(int type, long long time);
	public: System::Void debugTime(int type, long long time) {
		try {
			auto action = gcnew debugTimeDelegate(this, &DebugWindow::debugTimeWorker);
			Invoke(action, type, time);
		}
		catch (...) {}
	}
	private: System::Void debugTimeWorker(int type, long long time) {
		switch (type) {
		case 0:
			textBox1->Text = time.ToString();
			break;
		}
	}
	};
}
