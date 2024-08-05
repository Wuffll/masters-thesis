#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Debug.h"

Camera::Camera()
    :
    m_RightVec(glm::cross(m_ForwardVec, m_UpVec)),
    m_pShader(nullptr)
{
    m_ViewMatrix = glm::lookAt(m_Pos, m_Pos + m_ForwardVec, m_UpVec);
}

Camera::Camera(const glm::vec3& pos)
    :
    m_Pos(pos),
    m_RightVec(glm::cross(m_ForwardVec, m_UpVec)),
    m_pShader(nullptr)
{
    m_ViewMatrix = glm::lookAt(m_Pos, m_Pos + m_ForwardVec, m_UpVec);
}

Camera::Camera(const glm::vec3& pos, const glm::vec3& direction, Shader* pShader)
    :
    m_Pos(pos),
    m_ForwardVec(direction),
    m_RightVec(glm::cross(m_ForwardVec, m_UpVec)),
    m_pShader(pShader)
{
    m_ViewMatrix = glm::lookAt(m_Pos, m_Pos + glm::vec3(m_ForwardVec), glm::vec3(m_UpVec));

    updateShaderViewMatrix();
    updateShaderPerspectiveMatrix();
}

const glm::vec3& Camera::getPosition() const
{
    return m_Pos;
}

const glm::vec3& Camera::getForwardVector() const
{
    return m_ForwardVec;
}

const glm::vec3& Camera::getRightVector() const
{
    return m_RightVec;
}

const bool& Camera::hasChanged() const
{
    return m_HasChanged;
}

void Camera::setPosition(const glm::vec3& pos)
{
    m_Pos = pos;

    m_HasChanged = true;
}

void Camera::setShader(Shader* pShader)
{
    if (!pShader || pShader == m_pShader)
        return;

    m_pShader = pShader;

    updateShaderViewMatrix();
    updateShaderPerspectiveMatrix();
}

void Camera::updateTranform()
{
    if(m_HasChanged)
        updateShaderViewMatrix();

    m_HasChanged = false;
}

void Camera::move(const glm::vec3& delta)
{
    m_Pos += delta;

    // Debug::printMessage(*this, "Position = " + GLM_TOSTRING(m_Pos), DebugSeverityLevel::OK);

    m_HasChanged = true;
}

void Camera::rotate(const glm::vec3& delta)
{
    float rotX = delta.x;
    float rotY = delta.y;

    glm::vec3 newForwardVec = glm::rotate(m_ForwardVec, glm::radians(-rotY), m_RightVec);

    // forward vector calculation
    // clamp from -85deg to 85deg
    if (abs(glm::angle(newForwardVec, m_UpVec) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        m_ForwardVec = newForwardVec;
    }
    else
    {
        m_ForwardVec = m_ForwardVec;
    }
    m_ForwardVec = glm::rotate(m_ForwardVec, glm::radians(-rotX), m_UpVec);

    m_RightVec = glm::cross(m_ForwardVec, m_UpVec);

    m_HasChanged = true;
}

void Camera::updateShaderViewMatrix()
{
    if (!m_pShader)
        Debug::throwException(*this, "Member pointer to shader not set!");

    m_ViewMatrix = glm::lookAt(m_Pos, m_Pos + m_ForwardVec, m_UpVec);

    m_pShader->bind();
    m_pShader->setUniformMatrix4f(VIEW_MATRIX_UNIFORM_NAME, m_ViewMatrix);
}

void Camera::updateShaderPerspectiveMatrix()
{
    if (!m_pShader)
        Debug::throwException(*this, "Member pointer to shader not set!");

    glm::mat4 perspective = glm::perspective(45.0f, 1.0f, 0.1f, 2000.0f);;

    m_pShader->bind();
    m_pShader->setUniformMatrix4f(PROJ_MATRIX_UNIFORM_NAME, perspective);
}