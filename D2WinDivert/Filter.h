#pragma once

#include "MainWindow.h"
#include <msclr/auto_gcroot.h>

ref class Filter {
	// Constructor
public: Filter(D2WinDivert::MainWindow^ win, int mode);
	// Public functions
public: void closeHandle();
	// Private functions
private: void filterFunction();
private: void scanFunction();
private: void log(std::string msg, int code);
private: void log(std::string msg);
	// Public fields
public: bool running;
	// Private fiels
private: D2WinDivert::MainWindow^ window;
private: std::vector<std::string>* players;
private: HANDLE handle;
};

