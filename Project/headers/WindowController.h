#pragma once

#include "Window.h"
#include "UserInputController.h"
#include "CameraController.h"

class WindowController
{
public:

	WindowController();
	WindowController(short windowWidth, short windowHeight);

	void tick(float deltaTime);

	const Window& getWindow() const;
	Window& getMutableWindow();

	const UserInputController& getInputController() const;
	UserInputController& getMutableInputController();

	const CameraController& getCameraController() const;
	CameraController& getMutableCameraController();
	
private:

	void init();

	Window m_Window;

	UserInputController m_UserInputController;
	CameraController m_UserCameraController;

};