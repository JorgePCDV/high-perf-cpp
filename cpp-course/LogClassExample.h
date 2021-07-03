#pragma once



class LogClassExample
{
public: 
	const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;
private:
	int m_LogLevel = LogLevelInfo;
public:
	void SetLevel(int level);
	void LogMessage(const char* message);
};

void ClassStructure();

