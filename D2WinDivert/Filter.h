#pragma once

#include "MainWindow.h"
#include "windivert.h"
#include <fstream>
#include <msclr/auto_gcroot.h>

class Filter {
	// Constructor
public: Filter(D2WinDivert::MainWindow^ win, int mode);
	// Public functions
public: void closeHandle() {
	running = false;
	if (!WinDivertClose(handle)) {
		log("error: failed to close handle", GetLastError());
	}
};
	// Private functions
private: static DWORD WINAPI staticFilterStart(LPVOID lpParam) {
	return ((Filter*)lpParam)->filterFunction();
};
private: static DWORD WINAPI staticScanStart(LPVOID lpParam) {
	return ((Filter*)lpParam)->scanFunction();
};
private: DWORD filterFunction();
private: DWORD scanFunction();
private: void log(std::string msg, int code) {
	std::ofstream logfl;
	logfl.open("log_divert.txt", std::ofstream::app);
	logfl << msg << " " << code << std::endl;
	logfl.close();
};
private: void log(std::string msg) {
	log(msg, -1);
};
	// Public fields
public: bool running;
	// Private fiels
private: msclr::auto_gcroot<D2WinDivert::MainWindow^> window;
private: std::vector<std::string>* players;
private: HANDLE handle;
};
