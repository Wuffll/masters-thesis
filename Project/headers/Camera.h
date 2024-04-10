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
	const glm::vec3& getForwardVector() const;
	const glm::vec3& getRightVector() const;

	const float& getSpeed() const;
	const float& getSensitivity() const;

	void setPosition(const glm::vec3& pos);
	void setShader(Shader* pShader);

	void updateTranform();

	void move(const glm::vec3& delta);
	void rotate(const glm::vec3& delta);

private:

	void updateShaderData();

	glm::mat4 m_ViewMatrix = { 1.0f };

	glm::vec3 m_Pos = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_ForwardVec = { 0.0f, 0.0f, -1.0f };
	glm::vec3 m_UpVec = { 0.0f, 1.0f, 0.0f };
	glm::vec3 m_RightVec = { 1.0f, 0.0f, 0.0f };

	float m_Speed = 500.0f;
	float m_Sensitivity = 300.0f;

	Shader* m_pShader;
	bool m_HasChanged = false;
};

