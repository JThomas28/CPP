//=================================================================
// Name: Logger.cpp
// Version: 11/19/16
// Authors: Micah Coffman, Jonathan Thomas
// Description: logger.cpp is used to log data to a log file.
//				It is thread safe due to the locking and unlocking 
//				of mutexes in each method
//==================================================================
#include "..\includes\logger.h"
using namespace std;

//logger's constructor. Sets the filename of the log file to the filename passed in
Logger::Logger(std::string filename) {
	this->filename = filename;
}

//logger's destructor
Logger::~Logger() {
}

//open close and clear the log file
void Logger::clearlogfile() {
	std::lock_guard<mutex> lg(m);
	myFile.open(filename, std::fstream::trunc);

	//close file
	if (myFile.is_open())
		myFile.close();
}

//outputs the data passed in to the log file
void Logger::log(std::string data) {
	std::lock_guard<mutex> lg(m);
	myFile.open(filename, std::fstream::app);
	if (!myFile.is_open())
		return;

	std::string myline;

	myFile << data;

	//close file
	if (myFile.is_open())
		myFile.close();
}
