#pragma once

#include <glm/glm.hpp>

namespace VertexFormat
{
	struct OneVec3
	{
		glm::vec3 first = { 0.0f, 0.0f, 0.0f };
	};

	struct TwoVec3
	{
		glm::vec3 first = { 0.0f, 0.0f, 0.0f };
		glm::vec3 second = { 0.0f, 0.0f, 0.0f };
	};
	using PositionColor = TwoVec3;
	using PositionNormal = TwoVec3;

	struct ThreeVec3
	{
		glm::vec3 first = {0.0f, 0.0f, 0.0f};
		glm::vec3 second = { 0.0f, 0.0f, 0.0f };
		glm::vec3 third = { 0.0f, 0.0f, 0.0f };
	};

	struct TwoVec3OneVec2
	{
		glm::vec3 first = { 0.0f, 0.0f, 0.0f };
		glm::vec3 second = { 0.0f, 0.0f, 0.0f };
		glm::vec2 third = { 0.0f, 0.0f };
	};
	using PositionColorTexCoord = TwoVec3OneVec2;
}