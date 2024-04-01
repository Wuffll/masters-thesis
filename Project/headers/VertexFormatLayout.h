#pragma once

#include <glm/glm.hpp>

namespace VertexFormat
{
	struct OneVec3
	{
		glm::vec3 first;
	};

	struct TwoVec3
	{
		glm::vec3 first;
		glm::vec3 second;
	};
	using PositionColor = TwoVec3;
	using PositionNormal = TwoVec3;

	struct ThreeVec3
	{
		glm::vec3 first;
		glm::vec3 second;
		glm::vec3 third;
	};
	using PositionNormalTexture = ThreeVec3;
}