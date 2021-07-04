#include "LogClassExample.h"
#include <iostream>


void ClassStructure()
{
	LogClassExample logClass;
	logClass.SetLevel(logClass.Info);
	logClass.ErrorMessage("Error");
	logClass.WarnMessage("Warn");
	logClass.InfoMessage("Info");
	std::cin.get();
}

void LogClassExample::SetLevel(LogClassExample::Level level)
{
	m_LogLevel = level;
}

void LogClassExample::ErrorMessage(const char* message)
{
	if(m_LogLevel >= LogClassExample::Error)
		std::cout << "[ERROR]:" << message << std::endl;
}

void LogClassExample::WarnMessage(const char* message)
{
	if(m_LogLevel >= LogClassExample::Warn)
		std::cout << "[WARN]:" << message << std::endl;
}

void LogClassExample::InfoMessage(const char* message)
{
	if(m_LogLevel >= LogClassExample::Info)
		std::cout << "[INFO]:" << message << std::endl;
}


