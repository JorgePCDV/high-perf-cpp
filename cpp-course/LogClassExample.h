#pragma once



class LogClassExample
{
public:
	enum Level 
	{
		Error= 0, Warn, Info
	};
public:
	void SetLevel(Level level);
	void ErrorMessage(const char* message);
	void WarnMessage(const char* message);
	void InfoMessage(const char* message);
private:
	Level m_LogLevel = Info;
};

void ClassStructure();

