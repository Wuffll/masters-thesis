#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"
#include "UserPositionSubscriber.h"

class Controller
{
public:

	Controller();
	Controller(const glm::vec3& position, Shader* pShader);

	void setPosition(const glm::vec3& pos);
	void setShader(Shader* pShader);

	const Camera& getCamera() const;
	void moveCamera(const glm::vec3& delta);
	void rotateCamera(const glm::vec3& delta);

	void tick(const float& deltaTime);

	void AddSubscriber(UserPositionSubscriber& newSub);

private:

	Camera m_Camera;

	std::vector<UserPositionSubscriber*> m_Subscribers;

};

