#pragma once

#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

class Window
{
public:

	Window();
	Window(unsigned short width, unsigned short height, const std::string& name);

	GLFWwindow* getWindowPointer() const;

	const unsigned short& getWidth() const;
	const unsigned short& getHeight() const;

private:

	GLFWwindow* createWindow(const unsigned short& width, const unsigned short& height, const std::string& name);

	void setWindowHints();
	void setClearColor(float r, float g, float b);
	void enableFeatures(const GLFWwindow* window);

	GLFWwindow* m_Window = nullptr;
	std::string m_Name = "";

	unsigned short m_Width = DEFAULT_WIDTH;
	unsigned short m_Height = DEFAULT_HEIGHT;

};

