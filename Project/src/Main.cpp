#include <vector>
#include <string>
#include <filesystem>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Image.h"
#include "Debug.h"
#include "TileManager.h"
#include "Camera.h"
#include "FPSManager.h"
#include "UserControls.h"

#include "Window.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void)
{
    std::string workingDirectory = std::filesystem::current_path().string();
    printf("Program starting...\n");
    printf("Working directory: %s\n", workingDirectory.c_str());

    Window window;
    Camera userCamera;
    UserControls::initUserControls(window.getWindowPointer(), &userCamera);
 
    Shader defaultShader(workingDirectory + "\\Resources\\shaders\\default.glsl"); // if you run from RenderDoc, remember to update the shaders in the shader file in the build folder

    Image heightmap = Image(workingDirectory + "\\Resources\\heightmaps\\snowdon.png");
    heightmap.convertToGrayscale();

    // TileManager manager(heightmap, 350.0f);
    TileManager manager(32, 32, 200);
    manager.setUser(userCamera);

    userCamera.setPosition({ 0.0f, 20.0f, 0.0f });
    userCamera.setShader(&defaultShader);

    glm::mat4 projMat = glm::perspective(45.0f, 1.0f, 0.1f, 3000.0f);
    glm::mat4 modelMat(1.0f);

    defaultShader.bind();
    defaultShader.setUniformMatrix4f("uProjection", projMat);
    defaultShader.setUniformMatrix4f("uModel", modelMat);

    float targetFps = 200.0f;
    FPSManager fpsManager(targetFps);

    float frameTime = 0.0f, elapsedTime = 0.0f, interval = 5.0f;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.getWindowPointer()))
    {
        UserControls::tick(frameTime);
        manager.tick();

        Debug::printMessage(fpsManager, "FPS = " + STRING(fpsManager.getFps()), DebugSeverityLevel::OK);

        // Frame start
        fpsManager.startFrame();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        manager.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window.getWindowPointer());

        // Frame end
        fpsManager.endFrame();

        frameTime = fpsManager.getFrameTime();

        userCamera.updateTranform();

        /* Poll for and process events */
        glfwPollEvents();

        elapsedTime += frameTime;
        interval -= frameTime;
    }

    glfwTerminate();
    return 0;
}