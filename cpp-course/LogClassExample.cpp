#include "LogClassExample.h"
#include <iostream>


void ClassStructure()
{
	LogClassExample logClass;
	//logClass.SetLevel(LogLevelWarning);
	logClass.LogMessage("Error");
	std::cin.get();
}

void LogClassExample::SetLevel(int level)
{
	m_LogLevel = level;
}

void LogClassExample::LogMessage(const char* message)
{
	std::cout << "[" << m_LogLevel << "]" << message << std::endl;
}
