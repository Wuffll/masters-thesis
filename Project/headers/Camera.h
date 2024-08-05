#pragma once

#include <glm/glm.hpp>

#include "Transform.h"
#include "Shader.h"

#define VIEW_MATRIX_UNIFORM_NAME "uView"
#define PROJ_MATRIX_UNIFORM_NAME "uProjection"

class Camera
{
public:

	Camera();
	Camera(const glm::vec3& pos);
	Camera(const glm::vec3& pos, const glm::vec3& direction, Shader* pShader);

	const glm::vec3& getPosition() const;
	const glm::vec3& getForwardVector() const;
	const glm::vec3& getRightVector() const;

	const bool& hasChanged() const;

	void setPosition(const glm::vec3& pos);
	void setShader(Shader* pShader);

	void updateTranform();

	void move(const glm::vec3& delta);
	void rotate(const glm::vec3& delta);

private:

	void updateShaderViewMatrix();
	void updateShaderPerspectiveMatrix();

	glm::mat4 m_ViewMatrix = { 1.0f };

	glm::vec3 m_Pos = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_ForwardVec = { 0.0f, 0.0f, -1.0f };
	glm::vec3 m_UpVec = { 0.0f, 1.0f, 0.0f };
	glm::vec3 m_RightVec = { 1.0f, 0.0f, 0.0f };

	Shader* m_pShader;
	bool m_HasChanged = false;
};

