#include "TileManagerV2.h"

#include <glm/glm.hpp>

#include "TileV2.h"

static constexpr glm::vec3 DEFAULT_START_POS = { 0.0f, 0.0f, 0.0f };
static constexpr glm::ivec2 DEFAULT_TILE_SIZE = { 128, 128 };
static constexpr float CENTER_Y_OFFSET = 10.0f;

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
			auto tile = std::make_unique<TileV2>(TileInfo(
				glm::vec3(startPos.x + (tileSize.x + 1) * x, startPos.y, startPos.z + (tileSize.y + 1) * z),
				tileSize.x,
				tileSize.y));

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
			auto tile = std::make_unique<TileV2>(TileInfo(
				glm::vec3(startPos.x + (tileSize.x + 1) * x, startPos.y, startPos.z + (tileSize.y + 1) * z),
				tileSize.x,
				tileSize.y));

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
			auto tile = std::make_unique<TileV2>(TileInfo(
				glm::vec3(startPos.x + (tileSize.x + 1) * x, startPos.y, startPos.z + (tileSize.y + 1) * z),
				tileSize.x,
				tileSize.y));

			m_Tiles.push_back(std::move(tile));
		}
	}
}

void TileManagerV2::draw()
{
	for (auto& tile : m_Tiles)
	{
		tile->draw();
	}
}

glm::vec3 TileManagerV2::getCenter() const
{
	glm::vec3 output;

	auto tileSize = m_Tiles[0].get()->getTileInfo().Rows;

	output.x = m_startPosition.x + 5.0f * (tileSize / 2.0f);
	output.y = m_startPosition.y + CENTER_Y_OFFSET;
	output.z = m_startPosition.z + 5.0f * (tileSize / 2.0f);

	return output;
}

void TileManagerV2::cameraPositionUpdate(glm::vec3 newPos)
{
	printf("TileManagerV2 -> New Camera Pos: %f %f %f\n", newPos.x, newPos.y, newPos.z);
}
