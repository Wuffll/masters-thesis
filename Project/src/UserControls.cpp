#include "UserControls.h"

#include "Debug.h"
#include "FPSManager.h"

GLFWwindow* UserControls::__appWindow = nullptr;
CommandHistory UserControls::__commandHistory;

glm::vec3 UserControls::__movementDirection = {0.0f, 0.0f, 0.0f};
bool UserControls::__movementEnabled = false;

bool UserControls::__rotationEnabled = false;
MousePosition UserControls::__mousePos;

Camera* UserControls::__userCamera = nullptr;

void UserControls::initUserControls(GLFWwindow* window, Camera* userCamera)
{
	__appWindow = window;
	__userCamera = userCamera;

	glfwSetKeyCallback(window, keyboardInput);
	glfwSetCursorPosCallback(window, mousePosInput);
	glfwSetMouseButtonCallback(window, mouseButtonInput);
}

void UserControls::tick(const float& deltaTime)
{
	if (__userCamera == nullptr)
		Debug::throwException(UserControls(),
							  "UserControls not initialized! (use function initUserControls())");

	const auto& kbCommand = __commandHistory.getNextKeyboardCommand();
	const auto& mouseCommand = __commandHistory.getNextMouseCommand();

	processKeyboardCommand(kbCommand, deltaTime);
	processMouseCommand(mouseCommand, deltaTime);
}

void UserControls::keyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Debug::printMessage(UserControls(), "Key pressed: " + STRING(key) + "; Action = " + STRING(action), DebugSeverityLevel::OK);
	Debug::printMessage(UserControls(), "GLFW_PRESS = " + STRING(GLFW_PRESS), DebugSeverityLevel::OK);

	if(action != GLFW_REPEAT)
		__commandHistory.addNewKeyboardCommand(key, action);
}

void UserControls::mousePosInput(GLFWwindow* window, double xpos, double ypos)
{
	/*
	Debug::printMessage(UserControls(), 
		"Mouse pos: x = " + STRING(xpos) + "; y = " + STRING(ypos), DebugSeverityLevel::OK);
	*/

	updateMousePosition(xpos, ypos);
}

void UserControls::mouseButtonInput(GLFWwindow* window, int button, int action, int mods)
{
	Debug::printMessage(UserControls(), "Mouse button: " + STRING(button), DebugSeverityLevel::OK);

	if(action != GLFW_REPEAT)
		__commandHistory.addNewMouseCommand(button, action);
}

void UserControls::determineMovementDirection(const KeyboardCommand& kbCommand)
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

void UserControls::updateMousePosition(const double& xpos, const double& ypos)
{
	__mousePos.previousPos = __mousePos.currentPos;
	__mousePos.currentPos.x = xpos;
	__mousePos.currentPos.y = ypos;
}

void UserControls::processKeyboardCommand(const KeyboardCommand& kbCommand, const float& deltaTime)
{
	shouldWindowClose(kbCommand);
	movementCalculation(kbCommand, deltaTime);
}

void UserControls::shouldWindowClose(const KeyboardCommand& kbCommand)
{
	if (kbCommand.keyPressed == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(__appWindow, true);
	}
}

void UserControls::processMouseCommand(const MouseCommand& mouseCommand, const float& deltaTime)
{
	rotationCalculation(mouseCommand, deltaTime);

	__mousePos.previousPos = __mousePos.currentPos;
}

void UserControls::movementCalculation(const KeyboardCommand& kbCommand, float deltaTime)
{
	determineMovementDirection(kbCommand);

	if (glm::length(__movementDirection) >= 0.95f)
	{
		__userCamera->move(deltaTime * __movementDirection);
	}
}

void UserControls::rotationCalculation(const MouseCommand& mouseCommand, float deltaTime)
{
	determineRotationActivated(mouseCommand);

	if (__rotationEnabled && __mousePos.hasMoved())
	{
		glm::vec2 prevToNew = __mousePos.currentPos - __mousePos.previousPos;

		__userCamera->rotate(deltaTime * glm::vec3(prevToNew.y, prevToNew.x, 0.0f));
	}
}

void UserControls::determineRotationActivated(const MouseCommand& mouseCommand)
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
