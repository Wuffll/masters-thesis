#pragma once

#include <glm/gtc/matrix_transform.hpp>

// To be implemented
enum RotationOrder
{
	XYZ,
	XZY,
	YXZ,
	YZX,
	ZXY,
	ZYX
};

class Transform
{
public:

	Transform();
	Transform(const glm::mat4& matrix);

	~Transform();

	const glm::vec3& getPosition() const;
	const glm::vec3& getOrientation() const;
	const glm::vec3& getScale() const;

	const glm::mat4& getMatrix();
	const glm::mat4& getTranslationMat() const;
	const glm::mat4& getRotationMat() const;
	const glm::mat4& GetScalingMat() const;


	void setPosition(const glm::vec3& pos);
	void setOrientation(const glm::vec3& orientation);
	void setOrientation(const glm::vec3& axis, const float& angle);
	void setOrientation(const glm::mat4& rotationMatrix);
	void setScale(const glm::vec3& scale);
	void setScaleUniformly(const float& scale);

	void resetScale();

	void translation(const glm::vec3& translation);
	void translation(const glm::vec4& translation);

	void rotate(const glm::vec3& rotation);
	void rotate(const glm::vec3& axis, const float& angle);

	void scale(const glm::vec3& scale);

private:

	glm::vec3 calculateRotationMatrixAngles(const glm::mat4 rotationMatrix);
	void updateMatrix();



	// Member variables

	glm::mat4 m_Matrix{ 1.0f };
	bool m_HasTransformed = false;

	glm::vec3 m_Position{ 0.0f };
	glm::mat4 m_Translation{ 1.0f };

	RotationOrder m_RotationOrder = RotationOrder::XYZ;
	glm::vec3 m_Orientation{ 0.0f };
	glm::mat4 m_Rotation{ 1.0f };

	glm::vec3 m_Scale{ 1.0f };
	glm::mat4 m_Scaling{ 1.0f };

};