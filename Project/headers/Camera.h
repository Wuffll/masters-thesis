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
	const glm::vec3& getDirection() const;

	void setPosition(const glm::vec3& pos);
	void setShader(Shader* pShader);

	void updateTranform();

	void move(const glm::vec3& delta);
	void rotate(const glm::vec3& delta);

private:

	void updateShaderData();

	Transform m_Transform;
	Shader* m_pShader;

	glm::vec3 m_Position;
	glm::vec3 m_Orientation;
	bool m_HasChanged = false;

	glm::vec3 m_Direction;
	glm::vec3 m_RightVec;
	glm::vec3 m_UpVec;

};

