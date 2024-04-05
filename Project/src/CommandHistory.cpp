#include "CommandHistory.h"

void CommandHistory::addNewKeyboardCommand(const int& keyPressed, const int& action)
{
	m_KeyboardCommandHistory.push({ keyPressed, action });
}

void CommandHistory::addNewMouseCommand(const int& buttonPressed, const int& action)
{
	m_MouseCommandHistory.push({ buttonPressed, action });
}

const KeyboardCommand CommandHistory::getNextKeyboardCommand()
{
	const auto& historySize = m_KeyboardCommandHistory.size();

	if (historySize == 0)
		return {};

	const auto latestCommand = m_KeyboardCommandHistory.front();

	m_KeyboardCommandHistory.pop();

	return latestCommand;
}

const MouseCommand CommandHistory::getNextMouseCommand()
{
	const auto& historySize = m_MouseCommandHistory.size();

	if (historySize == 0)
		return {};

	const auto latestCommand = m_MouseCommandHistory.front();

	m_MouseCommandHistory.pop();

	return latestCommand;
}
