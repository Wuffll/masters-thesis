#include "Tile.h"

Tile::Tile()
	:
	m_Position({0, 0}),
	m_pNeighbors({}),
	m_NeightborExists({false, false, false, false}),
	m_pBufferIndices(nullptr)
{
}

Tile::Tile(const unsigned int& x, const unsigned int& y)
	:
	m_Position({ x, y }),
	m_pNeighbors({}),
	m_NeightborExists({ false, false, false, false }),
	m_pBufferIndices(nullptr)
{
}

Tile::Tile(const glm::uvec2& position)
	:
	m_Position(position),
	m_pNeighbors({}),
	m_NeightborExists({ false, false, false, false }),
	m_pBufferIndices(nullptr)
{
}

void Tile::assignNeighbors(Tile* top, Tile* right, Tile* bottom, Tile* left)
{
	m_pNeighbors[Neighbor::TOP] = top;
	m_pNeighbors[Neighbor::RIGHT] = right;
	m_pNeighbors[Neighbor::BOTTOM] = bottom;
	m_pNeighbors[Neighbor::LEFT] = left;

	for (auto& n : m_NeightborExists)
	{
		n = true;
	}
}

void Tile::setIndicesPointer(unsigned int* pIndices)
{
	m_pBufferIndices = pIndices;
}

const unsigned int* Tile::getIndicesPointer() const
{
	return m_pBufferIndices;
}

const glm::vec3& Tile::getColor() const
{
	return m_Color;
}

const Tile* Tile::getTopNeighbor() const
{
	return m_pNeighbors[Neighbor::TOP];
}

const Tile* Tile::getRightNeighbor() const
{
	return m_pNeighbors[Neighbor::RIGHT];
}

const Tile* Tile::getBottomNeighbor() const
{
	return m_pNeighbors[Neighbor::BOTTOM];
}

const Tile* Tile::getLeftNeighbor() const
{
	return m_pNeighbors[Neighbor::LEFT];
}

void Tile::setColor(const glm::vec3& color)
{
	m_Color = color;
}

void Tile::setTopNeighbor(Tile* top)
{
	m_pNeighbors[Neighbor::TOP] = top;

	m_NeightborExists[Neighbor::TOP] = true;
}

void Tile::setRightNeighbor(Tile* right)
{
	m_pNeighbors[Neighbor::RIGHT] = right;

	m_NeightborExists[Neighbor::RIGHT] = true;
}

void Tile::setBottomNeighbor(Tile* bottom)
{
	m_pNeighbors[Neighbor::BOTTOM] = bottom;

	m_NeightborExists[Neighbor::BOTTOM] = true;
}

void Tile::setLeftNeighbor(Tile* left)
{
	m_pNeighbors[Neighbor::LEFT] = left;

	m_NeightborExists[Neighbor::LEFT] = true;
}
