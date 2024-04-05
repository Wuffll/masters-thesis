#include "UserControls.h"

#include "Debug.h"
#include "FPSManager.h"

CommandHistory UserControls::__commandHistory;
glm::vec3 UserControls::__movementDirection = {0.0f, 0.0f, 0.0f};
MousePosition UserControls::__mousePos;

Camera* UserControls::__userCamera = nullptr;

void UserControls::initUserControls(GLFWwindow* window, Camera* userCamera)
{
	__userCamera = userCamera;

	glfwSetKeyCallback(window, keyboardProcessing);
	glfwSetCursorPosCallback(window, mousePosProcessing);
	glfwSetMouseButtonCallback(window, mouseButtonProcessing);
}

void UserControls::tick(const float& deltaTime)
{
	if (__userCamera == nullptr)
		Debug::throwException(UserControls(),
							  "UserControls not initialized! (use function initUserControls())");

	movementCalculation(deltaTime);
	rotationCalculation(deltaTime);
}

void UserControls::keyboardProcessing(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Debug::printMessage(UserControls(), "Key pressed: " + STRING(key), DebugSeverityLevel::OK);

	__commandHistory.addNewKeyboardCommand(key, action);
}

void UserControls::mousePosProcessing(GLFWwindow* window, double xpos, double ypos)
{
	Debug::printMessage(UserControls(), 
		"Mouse pos: x = " + STRING(xpos) + "; y = " + STRING(ypos), DebugSeverityLevel::OK);

	updateMousePosition(xpos, ypos);
}

void UserControls::mouseButtonProcessing(GLFWwindow* window, int button, int action, int mods)
{
	Debug::printMessage(UserControls(), "Mouse button: " + STRING(button), DebugSeverityLevel::OK);

	__commandHistory.addNewMouseCommand(button, action);
}

void UserControls::determineMovementDirection()
{
	const auto& command = __commandHistory.getNextKeyboardCommand();

	glm::vec3 cameraForward = glm::vec3((*__userCamera).getForwardVector());
	glm::vec3 cameraRight = glm::vec3((*__userCamera).getRightVector());

	if (command.action == GLFW_PRESS)
	{
		if (command.keyPressed == GLFW_KEY_W)
		{
			__movementDirection -= cameraForward;
		}
		else if (command.keyPressed == GLFW_KEY_S)
		{
			__movementDirection += cameraForward;
		}
		else if (command.keyPressed == GLFW_KEY_D)
		{
			__movementDirection -= cameraRight;
		}
		else if (command.keyPressed == GLFW_KEY_A)
		{
			__movementDirection += cameraRight;
		}
	}
	else if (command.action == GLFW_RELEASE)
	{
		if (command.keyPressed == GLFW_KEY_W)
		{
			__movementDirection += cameraForward;
		}
		else if (command.keyPressed == GLFW_KEY_S)
		{
			__movementDirection -= cameraForward;
		}
		else if (command.keyPressed == GLFW_KEY_D)
		{
			__movementDirection += cameraRight;
		}
		else if (command.keyPressed == GLFW_KEY_A)
		{
			__movementDirection -= cameraRight;
		}
	}
}

void UserControls::updateMousePosition(const double& xpos, const double& ypos)
{
	__mousePos.previousPos = __mousePos.currentPos;
	__mousePos.currentPos.x = xpos;
	__mousePos.currentPos.y = ypos;
}

void UserControls::movementCalculation(float deltaTime)
{
	determineMovementDirection();

	const auto& cameraSpeed = __userCamera->getSpeed();
	__userCamera->move(deltaTime * cameraSpeed * __movementDirection);
}

void UserControls::rotationCalculation(float deltaTime)
{
}
