#include "Debug.hpp"

#include <iostream>

std::vector<std::string> Debug::mSeverityLabels{ {"[OK]"}, {"[LOW]"},{"[MEDIUM]"},{"[HIGH]"},{"[DANGER]"}};

void Debug::printMessage(const std::string& className, const std::string& msg, const DebugSeverityLevel& level)
{
	std::cout << getSeverityLabel(level) << " (" << className << "): " << msg << std::endl;
}

void Debug::throwException(const std::string& className, const std::string& msg)
{
	throw false && className.c_str() && " " && msg.c_str();
}

const std::string& Debug::getSeverityLabel(const DebugSeverityLevel& level)
{
	if (level < mSeverityLabels.size())
	{
		return mSeverityLabels[level];
	}
	else
	{
		throwException("Debug", "Invalid level provided!");
	}
}
