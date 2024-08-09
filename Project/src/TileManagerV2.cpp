#include "TileManagerV2.h"

#include <glm/glm.hpp>

#include "TileV2.h"

static constexpr glm::vec3 DEFAULT_START_POS = { 0.0f, 0.0f, 0.0f };
static constexpr glm::ivec2 DEFAULT_TILE_SIZE = { 128, 128 };

TileManagerV2::TileManagerV2()
	:
	m_startPosition(DEFAULT_START_POS)
{
	m_Tiles.reserve(25);

	auto tileSize = DEFAULT_TILE_SIZE;
	auto startPos = m_startPosition;

	for (int z = 0; z < 5; z++)
	{
		for (int x = 0; x < 5; x++)
		{
			TileV2 tile = TileV2({ 
				{startPos.x + (tileSize.x + 1) * x, startPos.y, startPos.z + (tileSize.y + 1) * z}, 
				tileSize.x,
				tileSize.y });

			m_Tiles.push_back(std::move(tile));
		}
	}
}

TileManagerV2::TileManagerV2(glm::vec3 startPos)
	:
	m_startPosition(startPos)
{
	m_Tiles.reserve(25);

	auto tileSize = DEFAULT_TILE_SIZE;

	for (int z = 0; z < 5; z++)
	{
		for (int x = 0; x < 5; x++)
		{
			TileV2 tile = TileV2({
				{startPos.x + (tileSize.x + 1) * x, startPos.y, startPos.z + (tileSize.y + 1) * z},
				tileSize.x,
				tileSize.y });

			m_Tiles.push_back(std::move(tile));
		}
	}
}

TileManagerV2::TileManagerV2(glm::vec3 startPos, glm::ivec2 tileSize)
	:
	m_startPosition(startPos)
{
	m_Tiles.reserve(25);

	for (int z = 0; z < 5; z++)
	{
		for (int x = 0; x < 5; x++)
		{
			TileV2 tile = TileV2({
				{startPos.x + (tileSize.x + 1) * x, startPos.y, startPos.z + (tileSize.y + 1) * z},
				tileSize.x,
				tileSize.y });

			m_Tiles.push_back(std::move(tile));
		}
	}
}

void TileManagerV2::draw()
{
	for (auto& tile : m_Tiles)
	{
		tile.draw();
	}
}
