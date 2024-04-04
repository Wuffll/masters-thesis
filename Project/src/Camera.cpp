#include "Camera.h"

#include "Debug.h"

Camera::Camera()
    :
    m_ForwardVec({0.0f, 0.0f, -1.0f, 1.0f}),
    m_UpVec({0.0f, 1.0f, 0.0f, 1.0f}),
    m_RightVec({1.0f, 0.0f, 0.0f, 1.0f}),
    m_pShader(nullptr)
{
    const auto& position = m_Transform.getPosition();
    m_Transform = glm::lookAt(position, position + glm::vec3(m_ForwardVec), glm::vec3(m_UpVec));
}

Camera::Camera(const glm::vec3& pos, const glm::vec3& direction, Shader* pShader)
    :
    m_ForwardVec(direction, 1.0f),
    m_UpVec({ 0.0f, 1.0f, 0.0f, 1.0f }),
    m_RightVec({ 1.0f, 0.0f, 0.0f, 1.0f }),
    m_pShader(pShader)
{
    const auto& position = m_Transform.getPosition();
    m_Transform = glm::lookAt(position, position + glm::vec3(m_ForwardVec), glm::vec3(m_UpVec));
}

const glm::vec3& Camera::getPosition() const
{
    return m_Transform.getPosition();
}

const glm::vec3& Camera::getOrientation() const
{
    return m_Transform.getOrientation();
}

const float& Camera::getSpeed() const
{
    return m_Speed;
}

const glm::vec4& Camera::getForwardVector() const
{
    return m_ForwardVec;
}

const glm::vec4& Camera::getRightVector() const
{
    return m_RightVec;
}

void Camera::setPosition(const glm::vec3& pos)
{
    m_Transform.setPosition(pos);

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
    m_Transform.translation(delta);

    m_HasChanged = true;
}

void Camera::rotate(const glm::vec3& delta)
{
    m_Transform.rotate(delta);

    m_RightVec = m_RightVec;
    m_ForwardVec = m_ForwardVec;
    m_UpVec = m_UpVec;

    m_HasChanged = true;
}

void Camera::updateShaderData()
{
    if (!m_pShader)
        Debug::throwException(*this, "Memeber pointer to shader not set!");

    m_pShader->bind();
    m_pShader->setUniformMatrix4f(VIEW_MATRIX_UNIFORM_NAME, m_Transform.getMatrix());
}
