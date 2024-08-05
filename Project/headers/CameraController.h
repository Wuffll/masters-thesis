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

struct CameraMovementInfo
{
	glm::vec3 Direction = { 0.0f, 0.0f, 0.0f };

	bool CanRotate = false;
	glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
	
	float Speed = 20.0f;
	float RotationSensitivity = 30.0f;
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
	CameraMovementInfo m_CameraMovementInfo;

	InputHistory m_InputHistory;

};