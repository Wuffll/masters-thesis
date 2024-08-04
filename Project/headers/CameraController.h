#pragma once

#include <glm/glm.hpp>

#include "Camera.h"
#include "UserInputSubscriber.h"
#include "UserInputController.h"

struct InputHistory
{
	KeyPressEvent PreviousKeyPressed;
	glm::vec2 PreviousMousePosition;
};

class CameraController : public UserInputSubscriber
{
public:

	CameraController();

	void tick(float deltaTime);

	void setCamera(Camera camera);

	const Camera& getCamera() const;
	Camera& getMutableCamera();

	void userInputUpdate(const UserInputController& inputController);

private:

	Camera m_Camera;

	InputHistory m_InputHistory;

	bool m_RotationActivated;
	glm::vec3 m_Direction;
	glm::vec3 m_Rotation;
	float m_MoveSpeed;

};