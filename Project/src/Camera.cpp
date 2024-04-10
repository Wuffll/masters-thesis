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

Camera::Camera(const glm::vec3& pos, const glm::vec3& direction, Shader* pShader)
    :
    m_RightVec(glm::cross(m_ForwardVec, m_UpVec)),
    m_pShader(pShader)
{
    m_ViewMatrix = glm::lookAt(m_Pos, m_Pos + glm::vec3(m_ForwardVec), glm::vec3(m_UpVec));
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

const float& Camera::getSpeed() const
{
    return m_Speed;
}

const float& Camera::getSensitivity() const
{
    return m_Sensitivity;
}

void Camera::setPosition(const glm::vec3& pos)
{
    m_Pos = pos;

    m_HasChanged = true;
}

void Camera::setShader(Shader* shader)
{
    m_pShader = shader;
}

void Camera::updateTranform()
{
    if(m_HasChanged)
        updateShaderData();

    m_HasChanged = false;
}

void Camera::move(const glm::vec3& delta)
{
    m_Pos += m_Speed * delta.x * glm::cross(m_ForwardVec, m_UpVec); // m_RightVector; THIS IS CAUSING JITTER
    m_Pos += m_Speed * delta.y * m_ForwardVec;

    m_HasChanged = true;
}

void Camera::rotate(const glm::vec3& delta)
{
    float rotX = m_Sensitivity * delta.x;
    float rotY = m_Sensitivity * delta.y;

    glm::vec3 newForwardVec = glm::rotate(m_ForwardVec, glm::radians(-rotX), glm::normalize(glm::cross(m_ForwardVec, m_UpVec)));

    if (abs(glm::angle(newForwardVec, m_UpVec) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        m_ForwardVec = newForwardVec;
    }
    else
    {
        m_ForwardVec = m_ForwardVec;
    }

    m_ForwardVec = glm::rotate(m_ForwardVec, glm::radians(-rotY), m_UpVec);

    m_HasChanged = true;
}

void Camera::updateShaderData()
{
    if (!m_pShader)
        Debug::throwException(*this, "Member pointer to shader not set!");
    
    glm::mat4 mat = glm::lookAt(m_Pos, m_Pos + m_ForwardVec, m_UpVec);

    m_pShader->bind();
    m_pShader->setUniformMatrix4f(VIEW_MATRIX_UNIFORM_NAME, mat);
}
