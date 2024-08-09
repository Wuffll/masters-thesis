#include "WindowController.h"

#include "UserInputController.h"
#include "GLFWCallbacks.h"

WindowController::WindowController()
{
	init();
}

WindowController::WindowController(short windowWidth, short windowHeight)
	:
	m_Window(Window(windowWidth, windowHeight, "Application"))
{
	init();
}

void WindowController::tick(float deltaTime)
{
	m_UserCameraController.tick(deltaTime);
}

const Window& WindowController::getWindow() const
{
	return m_Window;
}

Window& WindowController::getMutableWindow()
{
	return m_Window;
}

const UserInputController& WindowController::getInputController() const
{
	return m_UserInputController;
}

UserInputController& WindowController::getMutableInputController()
{
	return m_UserInputController;
}

const CameraController& WindowController::getCameraController() const
{
	return m_UserCameraController;
}

CameraController& WindowController::getMutableCameraController()
{
	return m_UserCameraController;
}

void WindowController::init()
{
	m_UserInputController.addSubscriber(&m_UserCameraController);
	setupCallbackFunctions(m_Window.getWindowPointer());
}

