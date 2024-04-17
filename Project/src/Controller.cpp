#include "Controller.h"

Controller::Controller()
	:
	m_Camera(Camera()),
	m_Subscribers({})
{
	m_Subscribers.reserve(5);
}

Controller::Controller(const glm::vec3& position, Shader* pShader)
{
	m_Camera.setPosition(position);
	m_Camera.setShader(pShader);

	m_Camera.updateTranform();
}

void Controller::setPosition(const glm::vec3& pos)
{
	m_Camera.setPosition(pos);
}

void Controller::setShader(Shader* pShader)
{
	m_Camera.setShader(pShader);

	m_Camera.updateTranform();
}

const Camera& Controller::getCamera() const
{
	return m_Camera;
}

void Controller::moveCamera(const glm::vec3& delta)
{
	m_Camera.move(delta);
}

void Controller::rotateCamera(const glm::vec3& delta)
{
	m_Camera.rotate(delta);
}

void Controller::tick(const float& deltaTime)
{
	if (!m_Camera.hasChanged())
		return;

	m_Camera.updateTranform();

	UserPositionSubscriber* sub = nullptr;
	for (auto it = m_Subscribers.begin(); it != m_Subscribers.end();)
	{
		sub = *it;

		if (sub)
		{
			sub->userPositionUpdate(m_Camera.getPosition());
			it++;
		}
		else
		{
			m_Subscribers.erase(it);
		}
	}
}

void Controller::AddSubscriber(UserPositionSubscriber& newSub)
{
	if (std::find(m_Subscribers.begin(), m_Subscribers.end(), &newSub) == m_Subscribers.end())
	{
		m_Subscribers.push_back(&newSub);

		newSub.userPositionUpdate(m_Camera.getPosition());
	}
}