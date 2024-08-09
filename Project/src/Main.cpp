#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

#include "TileV2.h"
#include "TileManagerV2.h"

#include "WindowController.h"

#include "Window.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void)
{
    WindowController windowController(WINDOW_WIDTH, WINDOW_HEIGHT);
    auto& window = windowController.getMutableWindow();

    glfwSetWindowUserPointer(window.getWindowPointer(), reinterpret_cast<void*>(&windowController));

    std::string workingDirectory = std::filesystem::current_path().string();
    printf("Program starting...\n");
    printf("Working directory: %s\n", workingDirectory.c_str());
 
    Shader defaultShader(workingDirectory + "\\Resources\\shaders\\default.glsl"); // if you run from RenderDoc, remember to update the shaders in the shader file in the build folder

    auto& cameraController = windowController.getMutableCameraController();
    cameraController.setCameraMoveSpeed(128.0f);

    auto& camera = cameraController.getMutableCamera();
    camera.setShader(&defaultShader);
    camera.move({ 0.0f, 20.0f, 0.0f });
    camera.rotate({ 90.0f, 20.0f, 0.0f });

    // Image heightmap = Image(workingDirectory + "\\Resources\\heightmaps\\snowdon.png");
    // heightmap.convertToGrayscale();

    // TileManager manager(heightmap, 350.0f);
    // TileManager manager(1024, 1024, 200);

    glm::mat4 modelMat(1.0f);

    TileManagerV2 manager({0.0f, 0.0f, 0.0f}, {32, 32});

    /*
    TileV2* tiles[9];

    int index = 0;
    for (int z = 0; z < 3; z++)
    {
        for (int x = 0; x < 3; x++)
        {
            tiles[index] = new TileV2({{129.0f * x, 0.0f, 129.0f * z}, 128, 128});

            index++;
        }
    }
    */

    defaultShader.bind();
    defaultShader.setUniformMatrix4f("uModel", modelMat);

    float targetFps = 144.0f;

    // not working
    FPSManager fpsManager(targetFps);

    float frameTime = 0.0f, elapsedTime = 0.0f, interval = 5.0f;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.getWindowPointer()))
    {
        // Frame start
        fpsManager.startFrame();

        windowController.tick(frameTime);

        if (interval <= 0.0f)
        {
            Debug::printMessage(fpsManager, ">>>>>>>>>>> FPS = " + STRING(fpsManager.getFps()), DebugSeverityLevel::OK);
            interval = 5.0f;
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        manager.draw();

        for (int i = 0; i < 9; i++)
        {
            //tiles[i]->draw();
        }

        

        /* Swap front and back buffers */
        glfwSwapBuffers(window.getWindowPointer());

        /* Poll for and process events */
        glfwPollEvents();

        // Frame end
        fpsManager.endFrame();

        frameTime = fpsManager.getFrameTime();

        elapsedTime += frameTime;
        interval -= frameTime;
    }

    glfwTerminate();
    return 0;
}