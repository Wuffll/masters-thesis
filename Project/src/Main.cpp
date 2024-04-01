#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <filesystem>
#include <Windows.h>

#include "Array2D.h"
#include "Shader.h"
#include "Image.h"
#include "Debug.h"
#include "TileManager.h"
#include "Stopwatch.h"
#include "Camera.h"
#include "KeyPressCallbacks.h"

#include "VertexFormatLayout.h"

#include "VertexArray.h"
#include "VertexBufferGL.h"
#include "IndexBufferGL.h"

void setWindowHints();
GLFWwindow* createWindow(const int& width, const int& height, const std::string& windowTitle);
GLFWwindow* initWindow(const int& width, const int& height, const std::string& windowTitle);

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define MAX(x,y) ((x)>(y) ? (x) : (y))

int main(void)
{
    std::string workingDirectory = std::filesystem::current_path().string();
    printf("Program starting...\n");
    printf("Working directory: %s\n", workingDirectory.c_str());

    GLFWwindow* window = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Application");

    Shader defaultShader(workingDirectory + "\\Resources\\shaders\\default.glsl"); // if you run from RenderDoc, remember to update the shaders in the shader file in the build folder

    Image heightmap = Image(workingDirectory + "\\Resources\\heightmaps\\snowdon.png");
    heightmap.convertToGrayscale();

    TileManager manager(heightmap, 500.0f);

    Camera userCamera;
    m_pMainCamera = &userCamera;

    userCamera.setShader(&defaultShader);
    userCamera.move({ 0.0f, 0.0f, -1500.0f });
    userCamera.rotate({ 52.0f, 0.0f, 0.0f });

    glm::mat4 projMat = glm::perspective(45.0f, 1.0f, 0.1f, 3000.0f);
    glm::mat4 modelMat(1.0f);

    defaultShader.bind();
    defaultShader.setUniformMatrix4f("uProjection", projMat);
    defaultShader.setUniformMatrix4f("uModel", modelMat);

    Stopwatch timer;

    timer.start();
    float frameTime = 0.0f, elapsedTime = 0.0f, interval = 5.0f;
    glm::vec3 angle(0.0f, 45.0f, 0.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (interval <= 0.0f)
        {
            printf("%lf passed; %lf FPS\n", timer.getTimeElapsed(), 1.0 / timer.getTimeElapsed());

            interval = 5.0f;
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        manager.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        // userCamera.rotate(frameTime * angle);
        userCamera.updateTranform();
        /* Poll for and process events */
        glfwPollEvents();

        frameTime = (float)timer.lap();
        elapsedTime += frameTime;
        interval -= frameTime;
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

    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl << std::endl;

    // glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR: GLEW unable to be initialized!" << std::endl;
        exit(-1);
    }

    glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(MessageCallback, NULL);

    glfwSetKeyCallback(window, keyCallbackFunction);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.025f, 0.0f, 0.125f, 1.0f);

    return window;
}