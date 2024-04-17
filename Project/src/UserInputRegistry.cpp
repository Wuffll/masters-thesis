#include "UserInputRegistry.h"

#include "Debug.h"
#include "FPSManager.h"

GLFWwindow* UserInputRegistry::__appWindow = nullptr;
CommandHistory UserInputRegistry::__commandHistory;

glm::vec3 UserInputRegistry::__movementDirection = {0.0f, 0.0f, 0.0f};
bool UserInputRegistry::__movementEnabled = false;

bool UserInputRegistry::__rotationEnabled = false;
MousePosition UserInputRegistry::__mousePos;

Controller* UserInputRegistry::__user = nullptr;

void UserInputRegistry::initUserControls(GLFWwindow* window, Controller* user)
{
	__appWindow = window;
	__user = user;

	glfwSetKeyCallback(window, keyboardInput);
	glfwSetCursorPosCallback(window, mousePosInput);
	glfwSetMouseButtonCallback(window, mouseButtonInput);
}

void UserInputRegistry::tick(const float& deltaTime)
{
	if (__user == nullptr)
		Debug::throwException(UserInputRegistry(),
							  "UserControls not initialized! (use function initUserControls())");

	const auto& kbCommand = __commandHistory.getNextKeyboardCommand();
	const auto& mouseCommand = __commandHistory.getNextMouseCommand();

	processKeyboardCommand(kbCommand, deltaTime);
	processMouseCommand(mouseCommand, deltaTime);
}

void UserInputRegistry::keyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Debug::printMessage(UserInputRegistry(), "Key pressed: " + STRING(key) + "; Action = " + STRING(action), DebugSeverityLevel::OK);
	Debug::printMessage(UserInputRegistry(), "GLFW_PRESS = " + STRING(GLFW_PRESS), DebugSeverityLevel::OK);

	if(action != GLFW_REPEAT)
		__commandHistory.addNewKeyboardCommand(key, action);
}

void UserInputRegistry::mousePosInput(GLFWwindow* window, double xpos, double ypos)
{
	/*
	Debug::printMessage(
		UserInputRegistry(), 
		"Mouse pos: x = " + STRING(xpos) + "; y = " + STRING(ypos), 
		DebugSeverityLevel::OK);
	*/

	updateMousePosition(xpos, ypos);
}

void UserInputRegistry::mouseButtonInput(GLFWwindow* window, int button, int action, int mods)
{
	Debug::printMessage(UserInputRegistry(), "Mouse button: " + STRING(button), DebugSeverityLevel::OK);

	if(action != GLFW_REPEAT)
		__commandHistory.addNewMouseCommand(button, action);
}

void UserInputRegistry::determineMovementDirection(const KeyboardCommand& kbCommand)
{
	glm::vec3 forward = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

	float directionVecLength = glm::length(__movementDirection);

	if (kbCommand.action == GLFW_PRESS)
	{
		if (kbCommand.keyPressed == GLFW_KEY_W)
		{
			__movementDirection += forward;
		}
		else if (kbCommand.keyPressed == GLFW_KEY_S)
		{
			__movementDirection -= forward;
		}
		else if (kbCommand.keyPressed == GLFW_KEY_D)
		{
			__movementDirection += right;
		}
		else if (kbCommand.keyPressed == GLFW_KEY_A)
		{
			__movementDirection -= right;
		}
	}
	else if (kbCommand.action == GLFW_RELEASE)
	{
		if (kbCommand.keyPressed == GLFW_KEY_W)
		{
			__movementDirection -= forward;
		}
		else if (kbCommand.keyPressed == GLFW_KEY_S)
		{
			__movementDirection += forward;
		}
		else if (kbCommand.keyPressed == GLFW_KEY_D)
		{
			__movementDirection -= right;
		}
		else if (kbCommand.keyPressed == GLFW_KEY_A)
		{
			__movementDirection += right;
		}
	}
}

void UserInputRegistry::updateMousePosition(const double& xpos, const double& ypos)
{
	__mousePos.previousPos = __mousePos.currentPos;
	__mousePos.currentPos.x = xpos;
	__mousePos.currentPos.y = ypos;
}

void UserInputRegistry::processKeyboardCommand(const KeyboardCommand& kbCommand, const float& deltaTime)
{
	shouldWindowClose(kbCommand);
	movementCalculation(kbCommand, deltaTime);
}

void UserInputRegistry::shouldWindowClose(const KeyboardCommand& kbCommand)
{
	if (kbCommand.keyPressed == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(__appWindow, true);
	}
}

void UserInputRegistry::processMouseCommand(const MouseCommand& mouseCommand, const float& deltaTime)
{
	rotationCalculation(mouseCommand, deltaTime);

	__mousePos.previousPos = __mousePos.currentPos;
}

void UserInputRegistry::movementCalculation(const KeyboardCommand& kbCommand, float deltaTime)
{
	determineMovementDirection(kbCommand);

	if (glm::length(__movementDirection) >= 0.95f)
	{
		__user->moveCamera(deltaTime * __movementDirection);
	}
}

void UserInputRegistry::rotationCalculation(const MouseCommand& mouseCommand, float deltaTime)
{
	determineRotationActivated(mouseCommand);

	if (__rotationEnabled && __mousePos.hasMoved())
	{
		glm::vec2 prevToNew = __mousePos.currentPos - __mousePos.previousPos;

		__user->rotateCamera(deltaTime * glm::vec3(prevToNew.y, prevToNew.x, 0.0f));
	}
}

void UserInputRegistry::determineRotationActivated(const MouseCommand& mouseCommand)
{
	if (mouseCommand.buttonPressed == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (mouseCommand.action == GLFW_PRESS)
		{
			__rotationEnabled = true;
		}
		else
		{
			__rotationEnabled = false;
		}
	}
}
