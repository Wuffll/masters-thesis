#include "Debug.h"

#include <iostream>

std::vector<std::string> Debug::mSeverityLabels{ {"[OK]"}, {"[LOW]"},{"[MEDIUM]"},{"[HIGH]"},{"[DANGER]"}};

const std::string& Debug::getSeverityLabel(const DebugSeverityLevel& level)
{
	if (level < mSeverityLabels.size())
	{
		return mSeverityLabels[level];
	}
	else
	{
		throwException(Debug(), "Invalid level provided!");
	}
}
