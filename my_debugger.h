#pragma once

#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

using namespace std; // I understand its not advisable.

#define DEBUG_MODE // Debugger activated

class Logger
{
public:
	template<typename... Args>
	static void log(const Args&... args)
	{
		ofstream logfile(msDebugFileName, ios_base::app);
		if (logfile.fail()) {
			cerr << "Unable to open debug file!" << endl;
			return;
		}
		// Use a C++17 unary right fold, see Chapter 22.
		((logfile << args), ...);
		logfile << endl;

		((cout << args), ...);
		cout << endl;
	}

private:
	// static const string msDebugFileName = "debugfile2.txt";
	// static const string Logger::msDebugFileName = "debugfile2.txt";
	static const string msDebugFileName;
};
	
	// const string Logger::msDebugFileName = "debugfile.txt";


#ifdef DEBUG_MODE
	// class Logger
	// {
	// public:
	// 	template<typename... Args>
	// 	static void log(const Args&... args)
	// 	{
	// 		ofstream logfile(msDebugFileName, ios_base::app);
	// 		if (logfile.fail()) {
	// 			cerr << "Unable to open debug file!" << endl;
	// 			return;
	// 		}
	// 		// Use a C++17 unary right fold, see Chapter 22.
	// 		((logfile << args), ...);
	// 		logfile << endl;

    //         ((cout << args), ...);
	// 		cout << endl;
	// 	}

	// private:
	// 	// static const string msDebugFileName = "debugfile2.txt";
	// 	// static const string Logger::msDebugFileName = "debugfile2.txt";
	// 	static const string msDebugFileName;
	// };
	
	// // const string Logger::msDebugFileName = "debugfile.txt";

	#define log(...) Logger::log(__func__, "(): ", __VA_ARGS__)
#else
	#define log(...)
#endif