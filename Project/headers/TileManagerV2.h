#pragma once

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class TileV2;

class TileManagerV2
{
public:

	TileManagerV2();
	TileManagerV2(glm::vec3 startPos);
	TileManagerV2(glm::vec3 startPos, glm::ivec2 tileSize);

	void draw();

private:

	glm::vec3 m_startPosition; // bottom left of whole tile set

	std::vector<TileV2> m_Tiles;

};