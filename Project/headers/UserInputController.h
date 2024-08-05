#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <deque>

class UserInputSubscriber;

struct KeyPressEvent
{
	int Key = -1;
	int State = -1;
	int Modifiers = -1;

	bool operator==(const KeyPressEvent& rhs) { return Key == rhs.Key && State == rhs.State && Modifiers == rhs.Modifiers; }

	bool isValid() { return Key != -1 && State != -1 && Modifiers != -1; }
};

struct MousePosEvent
{
	glm::vec2 Position;
};

class UserInputController
{
public:

	UserInputController();

	const KeyPressEvent& getLatestKeyEvent() const;

	const MousePosEvent& getLatestMousePosition() const;
	std::vector<MousePosEvent> getLastNMouseEvents(int n) const;

	void updateKeyPressInput(const KeyPressEvent& keyEvent);

	void updateMousePos(glm::vec2 pos);

	void notify() const;
	void addSubscription(UserInputSubscriber* sub);

private:

	std::deque<KeyPressEvent> m_KeyEventQueue;
	std::deque<MousePosEvent> m_MouseEventQueue;

	std::vector<UserInputSubscriber*> m_Subscribers;

};
