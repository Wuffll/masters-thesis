#pragma once

#include <string>
#include <vector>

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

class Debug
{
public:

	static void printMessage(const std::string& className, const std::string& msg, const DebugSeverityLevel& level);
	static void throwException(const std::string& className, const std::string& msg);

private:

	static const std::string& getSeverityLabel(const DebugSeverityLevel& level);

	static std::vector<std::string> mSeverityLabels;

};