#include "GLFWCallbacks.h"

#include "WindowController.h"
#include "UserInputController.h"

void keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	WindowController* pWindowController =
		reinterpret_cast<WindowController*>(glfwGetWindowUserPointer(window));

	if (!pWindowController)
	{
		throw std::exception("UserInputController not initialized at the start of program/main function!");
	}

	// printf("Pressing key: %d %d %d\n", key, action, mods);

	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else
	{
		UserInputController& controller = pWindowController->getMutableInputController();
		controller.updateKeyPressInput({ key, action, mods });
	}
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	WindowController* pWindowController =
		reinterpret_cast<WindowController*>(glfwGetWindowUserPointer(window));

	if (!pWindowController)
	{
		throw std::exception("UserInputController not initialized at the start of program/main function!");
	}

	// printf("Pressing button: %d %d\n", button, action);

	UserInputController& controller = pWindowController->getMutableInputController();
	controller.updateKeyPressInput({ button, action, mods });
}

void mousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	WindowController* pWindowController =
		reinterpret_cast<WindowController*>(glfwGetWindowUserPointer(window));

	if (!pWindowController)
	{
		throw std::exception("UserInputController not initialized at the start of program/main function!");
	}

	// printf("Mouse pos: %lf %lf\n", xpos, ypos);

	UserInputController& controller = pWindowController->getMutableInputController();
	controller.updateMousePos({ xpos, ypos });
}

void setupCallbackFunctions(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keyboardKeyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, mousePositionCallback);
}