#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Camera.h"
#include "UserInputSubscriber.h"
#include "UserInputController.h"
#include "CameraSubscriber.h"

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
	void setCameraMoveSpeed(float speed);
	void setCameraRotationSensitivity(float sensitivity);

	const Camera& getCamera() const;
	Camera& getMutableCamera();

	void addSubscriber(CameraSubscriber* newSub);
	void positionNotify();

	void userInputUpdate(const UserInputController& inputController);

private:

	Camera m_Camera;
	CameraMovementInfo m_CameraMovementInfo;

	InputHistory m_InputHistory;

	std::vector<CameraSubscriber*> m_Subscribers;

};