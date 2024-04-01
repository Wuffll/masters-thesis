#include "Camera.h"

#include "Debug.h"

Camera::Camera()
    :
    m_Position({0.0f, 0.0f, 0.0f}),
    m_Orientation({0.0f, 0.0f, 0.0f}),
    m_Direction({0.0f, 0.0f, -1.0f}),
    m_UpVec({0.0f, 1.0f, 0.0f}),
    m_RightVec({1.0f, 0.0f, 0.0f}),
    m_pShader(nullptr)
{
    m_Transform = glm::lookAt(m_Position, m_Position + m_Direction, m_UpVec);
}

Camera::Camera(const glm::vec3& pos, const glm::vec3& direction, Shader* pShader)
    :
    m_Position(pos),
    m_Orientation({ 0.0f, 0.0f, 0.0f }),
    m_Direction(direction),
    m_UpVec({ 0.0f, 1.0f, 0.0f }),
    m_RightVec({ 1.0f, 0.0f, 0.0f }),
    m_pShader(pShader)
{
    m_Transform = glm::lookAt(m_Position, m_Position + m_Direction, m_UpVec);
}

const glm::vec3& Camera::getPosition() const
{
    return m_Position;
}

const glm::vec3& Camera::getDirection() const
{
    return m_Direction;
}

void Camera::setPosition(const glm::vec3& pos)
{

    m_Transform.setPosition(-pos);
    m_Position = pos;

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
    m_Position += delta;

    m_HasChanged = true;
}

void Camera::rotate(const glm::vec3& delta)
{
    m_Transform.rotate(delta);
    m_Orientation += delta;

    m_HasChanged = true;
}

void Camera::updateShaderData()
{
    if (!m_pShader)
        Debug::throwException(*this, "Memeber pointer to shader not set!");

    m_pShader->bind();
    m_pShader->setUniformMatrix4f(VIEW_MATRIX_UNIFORM_NAME, m_Transform.getMatrix());
}
