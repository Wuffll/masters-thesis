#include "Transform.h"

Transform::Transform()
{
}

Transform::Transform(const glm::mat4& matrix)
	:
	m_Matrix(matrix)
{
}

Transform::~Transform()
{
}

const glm::mat4& Transform::getMatrix()
{
	if (m_HasTransformed)
		updateMatrix();

	return m_Matrix;
}

const glm::vec3& Transform::getPosition() const
{
	return m_Position;
}

const glm::vec3& Transform::getOrientation() const
{
	return m_Orientation;
}

const glm::vec3& Transform::getScale() const
{
	return m_Scale;
}

void Transform::setPosition(const glm::vec3& pos)
{
	m_HasTransformed = true;

	glm::vec3 direction = (pos - m_Position);
	m_Translation = glm::translate(m_Translation, direction);
	m_Position = pos;
}

void Transform::setOrientation(const glm::vec3& orientation)
{
	m_HasTransformed = true;

	glm::vec3 endOrientation = orientation - m_Orientation;

	glm::vec3 axis = { 1.0f, 0.0f, 0.0f };
	m_Rotation = glm::rotate(m_Rotation, glm::radians(endOrientation.x), axis);

	axis.x = 0.0f;
	axis.y = 1.0f;
	m_Rotation = glm::rotate(m_Rotation, glm::radians(endOrientation.y), axis);

	axis.y = 0.0f;
	axis.z = 1.0f;
	m_Rotation = glm::rotate(m_Rotation, glm::radians(endOrientation.z), axis);

	m_Orientation = endOrientation;
}

void Transform::setOrientation(const glm::vec3& axis, const float& angle)
{
	if (angle == 0.0f)
		return;

	m_HasTransformed = true;

	m_Rotation = glm::mat4(1.0f);

	m_Rotation = glm::rotate(m_Rotation, angle, axis);

	m_Orientation = calculateRotationMatrixAngles(m_Rotation);
}

void Transform::setOrientation(const glm::mat4& rotationMatrix)
{
	m_HasTransformed = true;

	m_Rotation = rotationMatrix;

	m_Orientation = calculateRotationMatrixAngles(rotationMatrix);
}

void Transform::setScale(const glm::vec3& scale)
{
	if (scale == m_Scale)
		return;

	m_HasTransformed = true;

	m_Scale = scale;
	m_Scaling = glm::scale(glm::mat4(1.0f), scale);
}

void Transform::setScaleUniformly(const float& scale)
{
	m_HasTransformed = true;

	glm::vec3 scaleVector{ scale, scale, scale };

	m_Scale = scaleVector;
	m_Scaling = glm::scale(glm::mat4(1.0f), scaleVector);
}

void Transform::resetScale()
{
	m_HasTransformed = true;

	m_Scale = { 1.0f, 1.0f, 1.0f };
	m_Scaling = { glm::mat4{1.0f} };
}

void Transform::translation(const glm::vec3& translation)
{
	if (translation.length() == 0.0f)
		return;

	m_HasTransformed = true;

	m_Translation = glm::translate(m_Translation, translation);
	m_Position += translation;
}

void Transform::rotate(const glm::vec3& rotation)
{
	if (rotation.length() == 0.0f)
		return;

	m_HasTransformed = true;

	glm::vec3 axis{ 1.0f, 0.0f, 0.0f };
	m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.x), axis);

	axis = { 0.0f, 1.0f, 0.0f };
	m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.y), axis);

	axis = { 0.0f, 0.0f, 1.0f };
	m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.z), axis);

	m_Orientation += rotation;
}

void Transform::scale(const glm::vec3& scale)
{
	m_HasTransformed = true;

	m_Scaling = glm::scale(m_Scaling, scale);
	m_Scale *= scale;
}

glm::vec3 Transform::calculateRotationMatrixAngles(const glm::mat4 rotationMatrix)
{
	glm::vec3 output;
	output.x = atan2(m_Rotation[2][3], m_Rotation[3][3]);
	output.y = atan2(-m_Rotation[1][3], sqrt(pow(m_Rotation[2][3], 2) + pow(m_Rotation[3][3], 2)));
	output.z = atan2(m_Rotation[1][2], m_Rotation[1][1]);

	return output;
}

void Transform::updateMatrix()
{
	m_Matrix = m_Translation * m_Rotation * m_Scaling;

	m_HasTransformed = false;
}
