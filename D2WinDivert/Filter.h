#pragma once

#include "windivert.h"
#include "MainWindow.h"
#include "DebugWindow.h"
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
private: static DWORD WINAPI staticStatusUpdateStart(LPVOID lpParam) {
	return ((Filter*)lpParam)->statusUpdateFunction();
};
private: static DWORD WINAPI staticIdAppendStart(LPVOID lpParam) {
	return ((Filter*)lpParam)->idAppendFunction();
};
public: static DWORD WINAPI staticDebugStart(LPVOID lpParam) {
	return ((Filter*)lpParam)->debugFunction();
};
private: DWORD filterFunction();
private: DWORD scanFunction();
private: DWORD statusUpdateFunction();
private: DWORD idAppendFunction();
private: DWORD debugFunction();
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
public: bool debugging;
public: msclr::auto_gcroot<D2WinDivert::DebugWindow^> dbg;
	// Private fiels
private: msclr::auto_gcroot<D2WinDivert::MainWindow^> window;
private: std::vector<std::string>* players;
private: HANDLE handle;
private: int allow;
private: bool updating;
private: int updint;
private: long long time0;
private: std::vector<std::string> pendingId;
};
