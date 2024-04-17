#include "FPSManager.h"

#include <GLFW/glfw3.h>
#include <thread>

#include "Debug.h"

double FPSManager::__applicationFPS = 0.0;

FPSManager::FPSManager(float targetFps)
    :
    m_TargetFps(targetFps)
{
}

void FPSManager::startFrame()
{
    m_Timer.start();
}

void FPSManager::endFrame()
{
    float frameTime = m_Timer.stop();

    float delta = (1.0f / m_TargetFps) - frameTime;
    
    if (delta >= 0.0001f)
    {
        unsigned int microseconds = delta * 1000000;
        std::this_thread::sleep_for(std::chrono::microseconds(microseconds));

        frameTime += delta;
    }

    __applicationFPS = calculateFps(frameTime);
}

const double& FPSManager::getFps()
{
    return __applicationFPS;
}

const float& FPSManager::getFrameTime() const
{
    return 1.0 / __applicationFPS;
}

void FPSManager::setTargetFps(float targetFps)
{
    m_TargetFps = targetFps;
}

double FPSManager::calculateFps(const double& timeElapsed)
{
    return 1.0 / timeElapsed;
}
