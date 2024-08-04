#include "FPSManager.h"

#include <GLFW/glfw3.h>
#include <thread>
#include <Windows.h>

#include "Debug.h"

double FPSManager::__applicationFPS = 0.0;

FPSManager::FPSManager()
    :
    m_TargetFps(60.0f)
{
}

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
    double frameTime = m_Timer.checkpoint();
    
    double delta = (1.0 / m_TargetFps) - frameTime;
    
    // DOESN'T WORK
    /*
    if (delta >= 0.001f)
    {
        const unsigned int deltaInNanoseconds = (delta * 1000000000.0);

        std::this_thread::sleep_for(std::chrono::nanoseconds(deltaInNanoseconds));
    }
    */

    frameTime = m_Timer.stop();

    // Debug::printMessage(*this, STRING(frameTime), DebugSeverityLevel::OK);

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
