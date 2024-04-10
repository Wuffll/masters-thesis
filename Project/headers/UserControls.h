#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "CommandHistory.h"
#include "Camera.h"


struct MousePosition
{
	glm::vec2 currentPos = { 0.0f, 0.0f };
	glm::vec2 previousPos = { 0.0f, 0.0f };

	bool hasMoved() const
	{
		return !((abs(currentPos.x - previousPos.x) <= 0.00001f) && (abs(currentPos.y - previousPos.y) <= 0.00001f));
	}
};

class UserControls
{
public:

	static void initUserControls(GLFWwindow* window, Camera* userCamera);

	static void tick(const float& deltaTime);

private:
	
	static void keyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mousePosInput(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonInput(GLFWwindow* window, int button, int action, int mods);

	static void updateMousePosition(const double& xpos, const double& ypos);

	static void processKeyboardCommand(const KeyboardCommand& kbCommand, const float& deltaTime);
	static void shouldWindowClose(const KeyboardCommand& kbCommand);
	static void movementCalculation(const KeyboardCommand& kbCommand, float deltaTime);
	static void determineMovementDirection(const KeyboardCommand& kbCommand);

	static void processMouseCommand(const MouseCommand& mouseCommand, const float& deltaTime);
	static void rotationCalculation(const MouseCommand& mouseCommand, float deltaTime);
	static void determineRotationActivated(const MouseCommand& mouseCommand);

	static GLFWwindow* __appWindow;
	static CommandHistory __commandHistory;

	static glm::vec3 __movementDirection;
	static bool __movementEnabled;

	static bool __rotationEnabled;
	static MousePosition __mousePos;

	static Camera* __userCamera;

};

