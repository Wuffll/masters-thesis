#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "CommandHistory.h"
#include "Camera.h"


struct MousePosition
{
	glm::vec2 currentPos = { 0.0f, 0.0f };
	glm::vec2 previousPos = { 0.0f, 0.0f };
};

class UserControls
{
public:

	static void initUserControls(GLFWwindow* window, Camera* userCamera);

	static void tick(const float& deltaTime);

private:
	
	static void keyboardProcessing(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mousePosProcessing(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonProcessing(GLFWwindow* window, int button, int action, int mods);

	static void determineMovementDirection();

	static void updateMousePosition(const double& xpos, const double& ypos);

	static void movementCalculation(float deltaTime);
	static void rotationCalculation(float deltaTime);

	static CommandHistory __commandHistory;
	static glm::vec3 __movementDirection;
	static MousePosition __mousePos;

	static Camera* __userCamera;

};

