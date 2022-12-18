#ifndef LOGGING_FACILITY
#define LOGGING_FACILITY

#include <iostream>
#include <fstream>
#include <string>

#include "process.hpp"

class Log
{
private:
	time_unit occurrenceTime;
	int pid;
	std::string status;

public:
	Log(time_unit occurrenceTime, int pid, std::string status) : occurrenceTime(occurrenceTime), pid(pid), status(status) {}
	std::string toString();
};

inline std::string Log::toString()
{
	std::string log = std::to_string(occurrenceTime) + ", " + std::to_string(pid) + ", " + status;
	return log;
}

class Logger
{
private:
	std::ofstream logFile;

public:
	Logger(std::string logFileName);
	~Logger();
	void log(time_unit occurrenceTime, int pid, std::string status);
};

Logger::Logger(std::string logFileName)
{
	logFile.open(logFileName);
	if (!logFile.is_open())
	{
		std::cout << "Error opening log file\n";
	}
	else
	{
		std::cout << "Log file opened successfully\n";
	}
	logFile << "Time, PID, Status\n";
}

Logger::~Logger()
{
	logFile.close();
}

inline void Logger::log(time_unit occurrenceTime, int pid, std::string status)
{
	Log log(occurrenceTime, pid, status);
	logFile << log.toString() << std::endl;
}

#endif // LOGGING_FACILITY
