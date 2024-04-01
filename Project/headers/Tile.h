#pragma once

#include <array>
#include <vector>

#include "glm/glm.hpp"

#include "VertexFormatLayout.h"

#define NUM_OF_INDICES_PER_TILE 6 // each tile (rectangle) is made of two triangles (2 * 3)

#define DEFAULT_TILE_COLOR glm::vec3(0.75f, 0.0f, 0.1f)
#define ACTIVE_TILE_COLOR glm::vec3(0.0f, 1.0f, 0.25f)
#define TILE_VERTEX_FORMAT VertexFormat::ThreeVec3

enum Neighbor
{
	TOP = 0,
	RIGHT = 1,
	BOTTOM = 2,
	LEFT = 3
};

class Tile
{
public:

	Tile();
	Tile(const unsigned int& x, const unsigned int& y);
	Tile(const glm::uvec2& position);

	void assignNeighbors(Tile* top, Tile* right, Tile* bottom, Tile* left);
	void setIndicesPointer(unsigned int* pIndices);

	const unsigned int* getIndicesPointer() const;

	const glm::vec3& getColor() const;

	const Tile* getTopNeighbor() const;
	const Tile* getRightNeighbor() const;
	const Tile* getBottomNeighbor() const;
	const Tile* getLeftNeighbor() const;

	void setColor(const glm::vec3& color);

	void setTopNeighbor(Tile* top);
	void setRightNeighbor(Tile* right);
	void setBottomNeighbor(Tile* bottom);
	void setLeftNeighbor(Tile* left);

private:

	glm::uvec2 m_Position;

	glm::vec3 m_Color = DEFAULT_TILE_COLOR;
	std::array<bool, 4> m_NeightborExists;
	std::array<Tile*, 4> m_pNeighbors; // top, right, down, left
	unsigned int* m_pBufferIndices;

};

