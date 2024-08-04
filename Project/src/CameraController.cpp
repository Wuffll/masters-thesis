#include "CameraController.h"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

static constexpr float DEFAULT_MOVE_SPEED = 100.0f;

CameraController::CameraController()
	:
	m_RotationActivated(false),
	m_Direction({}),
	m_Rotation({}),
	m_MoveSpeed(DEFAULT_MOVE_SPEED)
{
}

void CameraController::tick(float deltaTime)
{
	if (glm::length(m_Direction) > 0.0f)
	{
		if (m_Direction.x != 0.0f)
		{
			const auto& right = m_Camera.getRightVector();

			m_Camera.move(m_Direction.x * right * deltaTime);
		}

		if (m_Direction.y != 0.0f)
		{
			const auto& forward = m_Camera.getForwardVector();

			m_Camera.move(m_Direction.y * forward * deltaTime);
		}
	}

	if (m_RotationActivated)
	{
		m_Camera.rotate(m_Rotation * deltaTime);

		// printf("Rotation for: %f %f %f\n", m_Rotation.x, m_Rotation.y, m_Rotation.z);

		m_Rotation = {};
	}

	glm::vec3 position = m_Camera.getPosition();


	// printf("Camera position: %f %f %f\n", position.x, position.y, position.z);

	m_Camera.updateTranform();
}

void CameraController::setCamera(Camera camera)
{
	m_Camera = std::move(camera);
}

const Camera& CameraController::getCamera() const
{
	return m_Camera;
}

Camera& CameraController::getMutableCamera()
{
	return m_Camera;
}

void CameraController::userInputUpdate(const UserInputController& inputController)
{
	printf("Processing user input in CameraController\n");

	// key/button press processing
	const auto& keyEvent = inputController.getLatestKeyEvent();

	if (keyEvent != m_InputHistory.PreviousKeyPressed)
	{
		const auto& key = keyEvent.Key;

		if (keyEvent.State == GLFW_PRESS)
		{
			switch (key) {
			case GLFW_KEY_W:	m_Direction.y += 1.0f; break;
			case GLFW_KEY_S:	m_Direction.y -= 1.0f; break;
			case GLFW_KEY_A:	m_Direction.x -= 1.0f; break;
			case GLFW_KEY_D:	m_Direction.x += 1.0f; break;
			case GLFW_MOUSE_BUTTON_LEFT:	m_RotationActivated = true; m_Rotation = {}; break;
			}
		}
		else if (keyEvent.State == GLFW_RELEASE)
		{
			switch (key) {
			case GLFW_KEY_W:	m_Direction.y -= 1.0f; break;
			case GLFW_KEY_S:	m_Direction.y += 1.0f; break;
			case GLFW_KEY_A:	m_Direction.x += 1.0f; break;
			case GLFW_KEY_D:	m_Direction.x -= 1.0f; break;
			case GLFW_MOUSE_BUTTON_LEFT:	m_RotationActivated = false; break;
			}
		}

		m_InputHistory.PreviousKeyPressed = keyEvent;
	}

	// mouse position processing
	if (m_RotationActivated)
	{
		const auto& mousePosVec = inputController.getLastNMouseEvents(2);

		if (mousePosVec.size() != 2)
			return;

		const auto& lastEvent = mousePosVec[0];
		if (lastEvent.Position == m_InputHistory.PreviousMousePosition)
			return;

		const auto& secondLastEvent = mousePosVec[1];

		glm::vec2 prevToNew = lastEvent.Position - secondLastEvent.Position;

		m_Rotation = glm::vec3(prevToNew.x, prevToNew.y, 0.0f);
		m_InputHistory.PreviousMousePosition = lastEvent.Position;
	}

	// printf("Direction: %f %f %f\n", m_Direction.x, m_Direction.y, m_Direction.z);
}
