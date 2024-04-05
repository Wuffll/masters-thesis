#pragma once

#include <queue>

struct KeyboardCommand
{
	int keyPressed = -1;
	int action = -1;
};

struct MouseCommand
{
	int buttonPressed = -1;
	int action = -1;
};

class CommandHistory
{
public:

	CommandHistory() = default;

	void addNewKeyboardCommand(const int& keyPressed, const int& action);
	void addNewMouseCommand(const int& buttonPressed, const int& action);

	const KeyboardCommand getNextKeyboardCommand();
	const MouseCommand getNextMouseCommand();

private:

	std::queue<KeyboardCommand> m_KeyboardCommandHistory{};
	std::queue<MouseCommand> m_MouseCommandHistory{};

};