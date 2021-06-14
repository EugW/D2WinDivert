#pragma once

#include "MainWindow.h"
#include <msclr/auto_gcroot.h>

class Filter {
	// Constructor
public: Filter(D2WinDivert::MainWindow^ win, int mode);
	// Public functions
public: void closeHandle();
	// Private functions
private: static DWORD WINAPI staticFilterStart(LPVOID lpParam);
private: static DWORD WINAPI staticScanStart(LPVOID lpParam);
private: DWORD filterFunction();
private: DWORD scanFunction();
private: void log(std::string msg, int code);
private: void log(std::string msg);
	// Public fields
public: bool running;
	// Private fiels
private: msclr::auto_gcroot<D2WinDivert::MainWindow^> window;
private: std::vector<std::string>* players;
private: HANDLE handle;
};
