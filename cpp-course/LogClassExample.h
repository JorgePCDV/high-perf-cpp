#pragma once

const int LogLevelError = 0;
const int LogLevelWarning = 1;
const int LogLevelInfo = 2;

class LogClassExample
{
private:
	int m_LogLevel = LogLevelInfo;
public:
	void SetLevel(int level);
	void LogMessage(const char* message);
};

void ClassStructure();

