#include "UserInputController.h"

#include "UserInputSubscriber.h"

constexpr size_t QUEUE_MAX_SIZE = 8;

UserInputController::UserInputController()
	:
	m_KeyEventQueue({}),
	m_MouseEventQueue({})
{
}

const KeyPressEvent& UserInputController::getLatestKeyEvent() const
{
	if (m_KeyEventQueue.size() == 0)
	{
		return { -1, -1, -1 };
	}

	return m_KeyEventQueue.front();
}

const MousePosEvent& UserInputController::getLatestMousePosition() const
{
	if (m_MouseEventQueue.size() == 0)
	{
		return {{}};
	}

	return m_MouseEventQueue.front();
}

std::vector<MousePosEvent> UserInputController::getLastNMouseEvents(int n) const
{
	if (n <= 0)
		return {};

	const size_t numMouseEvents = m_MouseEventQueue.size();

	std::vector<MousePosEvent> output;
	output.reserve(n);

	for (int i = 0; i < numMouseEvents; i++)
	{
		const auto& mouseEvent = m_MouseEventQueue[i];
		output.push_back(mouseEvent);

		if (output.size() >= n)
			break;
	}

	return output;
}

void UserInputController::updateKeyPressInput(const KeyPressEvent& keyEvent)
{
	if (m_KeyEventQueue.size() >= QUEUE_MAX_SIZE)
	{
		m_KeyEventQueue.pop_back();
	}

	m_KeyEventQueue.push_front(keyEvent);

	notify();
}

void UserInputController::updateMousePos(glm::vec2 pos)
{
	if (m_KeyEventQueue.size() >= QUEUE_MAX_SIZE)
	{
		m_KeyEventQueue.pop_back();
	}

	m_MouseEventQueue.push_front({pos});

	notify();
}

void UserInputController::notify() const
{
	for (auto sub : m_Subscribers)
	{
		sub->userInputUpdate(*this);
	}
}

void UserInputController::addSubscription(UserInputSubscriber* sub)
{
	m_Subscribers.push_back(sub);
}
