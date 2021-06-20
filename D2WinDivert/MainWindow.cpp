#include "Filter.h"
#include <Windows.h>

using namespace D2WinDivert;

Filter* flt;

System::Void MainWindow::filterCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (filterCheckBox->Checked) {
		flt = new Filter(this, 0);
	}
	else {
		flt->closeHandle();
	}
	filterCheckBox->Enabled = false;
	scanCheckBox->Enabled = false;
	textBoxThreads->Enabled = false;
}

System::Void MainWindow::scanCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (scanCheckBox->Checked) {
		flt = new Filter(this, 1);
	}
	else {
		flt->closeHandle();
	}
	filterCheckBox->Enabled = false;
	scanCheckBox->Enabled = false;
	textBoxThreads->Enabled = false;
}

System::Void MainWindow::textBox_Edit(System::Object^ sender, System::EventArgs^ e) {
	auto st = textBoxSteamIDs->SelectionStart;
	textBoxSteamIDs->Text = textBoxSteamIDs->Text->Replace(Environment::NewLine + Environment::NewLine, Environment::NewLine);
	textBoxSteamIDs->SelectionStart = st;
	auto str = textBoxSteamIDs->Lines;
	playersID->clear();
	msclr::interop::marshal_context context;
	for (int i = 0; i < str->Length; i++) {
		if (!String::IsNullOrWhiteSpace(str[i])) {
			std::string a = context.marshal_as<std::string>(str[i]->Replace(Environment::NewLine, "")->Replace(" ", ""));
			playersID->push_back(a);
		}
	}
	if (str->Length != 0) {
		vScrollBar1->Maximum = str->Length - 1;
		vScrollBar1->Value = textBoxSteamIDs->GetLineFromCharIndex(st);
	}
	for (int i = 0; i < playersID->size(); i++) {
		auto wc = gcnew System::Net::WebClient();
		wc->DownloadStringCompleted += gcnew System::Net::DownloadStringCompletedEventHandler(this, &MainWindow::SteamIDHandler);
		wc->DownloadStringAsync(gcnew Uri("https://steamcommunity.com/profiles/" + gcnew String(playersID->at(i).c_str()) + "/?xml=1"));
	}
}

System::Void MainWindow::SteamIDHandler(System::Object^ sender, System::Net::DownloadStringCompletedEventArgs^ e) {
	auto result = e->Result;
	auto sstart = result->IndexOf("<steamID64>") + 11;
	auto send = result->IndexOf("</steamID64>");
	auto nstart = result->IndexOf("<steamID><![CDATA[") + 18;
	auto nend = result->IndexOf("]]></steamID>");
	if (sstart != 10 && send != -1 && nstart != 17 && nend != -1) {
		auto steamid = result->Substring(sstart, send - sstart);
		auto name = result->Substring(nstart, nend - nstart);
		msclr::interop::marshal_context context;
		if (playersNames->count(context.marshal_as<std::string>(steamid)) == 1) {
			playersNames->at(context.marshal_as<std::string>(steamid)) = context.marshal_as<std::string>(name);
		}
		else {
			playersNames->emplace(context.marshal_as<std::string>(steamid), context.marshal_as<std::string>(name));
		}
	}
	textBoxNames->Clear();
	auto def = System::Text::Encoding::Default;
	auto utf8 = System::Text::Encoding::UTF8;
	for (int i = 0; i < playersID->size(); i++) {
		if (playersNames->count(playersID->at(i)) == 1) {
			auto bytes = def->GetBytes(gcnew String(playersNames->at(playersID->at(i)).c_str()));
			textBoxNames->Text += utf8->GetString(bytes);
		}
		textBoxNames->Text += Environment::NewLine;
	}
	auto number = textBoxSteamIDs->GetLineFromCharIndex(textBoxSteamIDs->SelectionStart);
	int positionN = 0;
	for (int i = 0; i < number; i++) {
		positionN += textBoxNames->Lines[i]->Length + Environment::NewLine->Length;
	}
	textBoxNames->SelectionStart = positionN;
	textBoxNames->ScrollToCaret();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainWindow);
	if (flt != nullptr) {
		if (flt->running) {
			flt->closeHandle();
		}
	}
	return 0;
}
