#pragma once

#include <GLFW/glfw3.h>
#include "Camera.h"

// Temporary; will be used to setup control scheme ()
// void setKeyboard();
// void setMouse();

// void setController();

static Camera* m_pMainCamera = nullptr;

void keyCallbackFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_W)
        {
            m_pMainCamera->move(glm::vec3(0.0f, 0.0f, 5.0f));
        }
        else if (key == GLFW_KEY_S)
        {
            m_pMainCamera->move(glm::vec3(0.0f, 0.0f, -5.0f));
        }
        else if (key == GLFW_KEY_A)
        {
            m_pMainCamera->move(glm::vec3(5.0f, 0.0f, 0.0f));
        }
        else if (key == GLFW_KEY_D)
        {
            m_pMainCamera->move(glm::vec3(-5.0f, 0.0f, 0.0f));
        }
        else if (key == GLFW_KEY_Q)
        {
            m_pMainCamera->rotate(glm::vec3(10.0f, 00.0f, 0.0f));
        }
        else if (key == GLFW_KEY_E)
        {
            m_pMainCamera->rotate(glm::vec3(0.0f, 00.0f, 0.0f));
        }
    }
}