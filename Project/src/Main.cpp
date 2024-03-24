#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <string>
#include <filesystem>

#include "Shader.h"
#include "Debug.h"

void setWindowHints();
GLFWwindow* createWindow(const int& width, const int& height, const std::string& windowTitle);
GLFWwindow* initWindow(const int& width, const int& height, const std::string& windowTitle);

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void)
{
    std::string workingDirectory = std::filesystem::current_path().string();
    printf("Program starting...\n");
    printf("Working directory: %s\n", workingDirectory.c_str());

    GLFWwindow* window = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Application");

    Shader defaultShader(workingDirectory + "\\Resources\\shaders\\default.glsl");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void setWindowHints()
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
}

GLFWwindow* createWindow(const int& width, const int& height, const std::string& windowTitle)
{
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle.c_str(), NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        printf("ERROR: Unable to create window!\n");
        exit(-1);
    }

    return window;
}

GLFWwindow* initWindow(const int& width, const int& height, const std::string& windowTitle)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    /* Window creation hints */
    setWindowHints();

    /* Create a windowed mode window and its OpenGL context */
    window = createWindow(width, height, windowTitle);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

    // glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR: GLEW unable to be initialized!" << std::endl;
        exit(-1);
    }

    glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(MessageCallback, NULL);

    // glfwSetKeyCallback(window, key_callback);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.025f, 0.0f, 0.125f, 1.0f);

    return window;
}