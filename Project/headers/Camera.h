#pragma once

#include <glm/glm.hpp>

#include "Transform.h"
#include "Shader.h"

#define VIEW_MATRIX_UNIFORM_NAME "uView"

class Camera
{
public:

	Camera();
	Camera(const glm::vec3& pos, const glm::vec3& direction, Shader* shader);

	const glm::vec3& getPosition() const;
	const glm::vec3& getOrientation() const;
	const float& getSpeed() const;
	const float& getSensitivity() const;

	const glm::vec4& getForwardVector() const;
	const glm::vec4& getRightVector() const;

	void setPosition(const glm::vec3& pos);
	void setShader(Shader* pShader);

	void updateTranform();

	void move(const glm::vec3& delta);
	void rotate(const glm::vec3& delta);

private:

	void updateShaderData();

	Transform m_Transform;
	float m_Speed = 500.0f;
	float m_Sensitivity = 30.0f;

	Shader* m_pShader;

	bool m_HasChanged = false;

	glm::vec4 m_ForwardVec;
	glm::vec4 m_RightVec;
	glm::vec4 m_UpVec;
};

