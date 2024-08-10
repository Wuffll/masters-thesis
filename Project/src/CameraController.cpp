#include "CameraController.h"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

static constexpr float MIN_MOVE_SPEED = 5.0f;
static constexpr float MIN_ROTATION_SENS = 15.0f;

CameraController::CameraController()
	:
	m_Camera({}),
	m_CameraMovementInfo({}),
	m_InputHistory({})
{
}

void CameraController::tick(float deltaTime)
{
	const auto& direction = m_CameraMovementInfo.Direction;
	if (glm::length(direction) > 0.0f)
	{
		const auto& speed = m_CameraMovementInfo.Speed;
		if (direction.x != 0.0f)
		{
			const auto& right = m_Camera.getRightVector();

			m_Camera.move(direction.x * right * speed * deltaTime);
		}

		if (direction.y != 0.0f)
		{
			const auto& forward = m_Camera.getForwardVector();

			m_Camera.move(direction.y * forward * speed * deltaTime);
		}

		positionNotify();
	}

	if (m_CameraMovementInfo.CanRotate)
	{
		auto& rotation = m_CameraMovementInfo.Rotation;
		const auto& rotationSens = m_CameraMovementInfo.RotationSensitivity;
		m_Camera.rotate(rotation * rotationSens * deltaTime);

		// printf("Rotation for: %f %f %f\n", m_Rotation.x, m_Rotation.y, m_Rotation.z);

		rotation = {};
	}

	glm::vec3 position = m_Camera.getPosition();


	// printf("Camera position: %f %f %f\n", position.x, position.y, position.z);

	m_Camera.updateTranform();
}

void CameraController::setCamera(Camera camera)
{
	m_Camera = std::move(camera);
}

void CameraController::setCameraPosition(glm::vec3 newPosition)
{
	m_Camera.setPosition(newPosition);

	positionNotify();
}

void CameraController::setCameraMoveSpeed(float speed)
{
	if (speed < MIN_MOVE_SPEED)
		return;

	m_CameraMovementInfo.Speed = speed;
}

void CameraController::setCameraRotationSensitivity(float sensitivity)
{
	if (sensitivity < MIN_ROTATION_SENS)
		return;

	m_CameraMovementInfo.RotationSensitivity = sensitivity;
}

const Camera& CameraController::getCamera() const
{
	return m_Camera;
}

Camera& CameraController::getMutableCamera()
{
	return m_Camera;
}

void CameraController::addSubscriber(CameraSubscriber* newSub)
{
	m_Subscribers.push_back(newSub);

	newSub->cameraPositionUpdate(m_Camera.getPosition());
}

void CameraController::positionNotify()
{
	for (auto& sub : m_Subscribers)
	{
		sub->cameraPositionUpdate(m_Camera.getPosition());
	}
}

void CameraController::userInputUpdate(const UserInputController& inputController)
{
	// printf("Processing user input in CameraController\n");

	// key/button press processing
	const auto& keyEvent = inputController.getLatestKeyEvent();

	if (keyEvent != m_InputHistory.PreviousKeyPressed)
	{
		auto& direction = m_CameraMovementInfo.Direction;
		auto& canRotate = m_CameraMovementInfo.CanRotate;
		auto& rotation = m_CameraMovementInfo.Rotation;

		const auto& key = keyEvent.Key;

		if (keyEvent.State == GLFW_PRESS)
		{
			switch (key) {
			case GLFW_KEY_W:	direction.y += 1.0f; break;
			case GLFW_KEY_S:	direction.y -= 1.0f; break;
			case GLFW_KEY_A:	direction.x -= 1.0f; break;
			case GLFW_KEY_D:	direction.x += 1.0f; break;
			case GLFW_MOUSE_BUTTON_LEFT:	canRotate = true; rotation = {}; break;
			}
		}
		else if (keyEvent.State == GLFW_RELEASE)
		{
			switch (key) {
			case GLFW_KEY_W:	direction.y -= 1.0f; break;
			case GLFW_KEY_S:	direction.y += 1.0f; break;
			case GLFW_KEY_A:	direction.x += 1.0f; break;
			case GLFW_KEY_D:	direction.x -= 1.0f; break;
			case GLFW_MOUSE_BUTTON_LEFT:	canRotate = false; break;
			}
		}

		m_InputHistory.PreviousKeyPressed = keyEvent;
	}

	// mouse position processing
	if (m_CameraMovementInfo.CanRotate)
	{
		const auto& mousePosVec = inputController.getLastNMouseEvents(2);

		if (mousePosVec.size() != 2)
			return;

		const auto& lastEvent = mousePosVec[0];
		if (lastEvent.Position == m_InputHistory.PreviousMousePosition)
			return;

		const auto& secondLastEvent = mousePosVec[1];

		glm::vec2 prevToNew = lastEvent.Position - secondLastEvent.Position;

		auto& rotation = m_CameraMovementInfo.Rotation;

		rotation = glm::vec3(prevToNew.x, prevToNew.y, 0.0f);
		m_InputHistory.PreviousMousePosition = lastEvent.Position;
	}

	// printf("Direction: %f %f %f\n", m_Direction.x, m_Direction.y, m_Direction.z);
}
