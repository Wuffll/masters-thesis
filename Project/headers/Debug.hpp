#pragma once

#include <string>
#include <vector>

#include "Utility.hpp"

enum DebugSeverityLevel
{
	OK = 0,
	LOW = 1,
	MEDIUM = 2,
	HIGH = 3,
	DANGER = 4
};

// Possible modifications for later:
// - Adding stack trace for debugging
// - Saving app state for easier debugging

// Problem is now two functions are generated for each type T every time functions printMessage and throwException are called (could get pretty large)

class Debug
{
public:

	template<typename T>
	static void printMessage(const T& instance, const std::string& msg, const DebugSeverityLevel& level);
	
	template<typename T>
	static void throwException(const T& instance, const std::string& msg);
	
	template<typename T>
	static std::string getClassName(const T& instance);

	template<typename T>
	static void glmPrint(const T& variable);

private:

	static const std::string& getSeverityLabel(const DebugSeverityLevel& level);

	static std::vector<std::string> mSeverityLabels;

};

template<typename T>
void Debug::printMessage(const T& instance, const std::string& msg, const DebugSeverityLevel& level)
{
	std::cout << getSeverityLabel(level) << " (" << getClassName(instance) << "): " << msg << std::endl;
}

template<typename T>
void Debug::throwException(const T& instance, const std::string& msg)
{
	throw false && getClassName(instance).c_str() && " " && msg.c_str();
}

template<typename T>
inline std::string Debug::getClassName(const T& instance)
{
	return typeid(instance).name();
}

template<typename T>
inline void Debug::glmPrint(const T& variable)
{
	std::cout << ">> " << GLM_TOSTRING(variable) << std::endl;
}
