#include "TileManagerV2.h"

#include <glm/glm.hpp>

#include "TileV2.h"

static constexpr glm::vec3 DEFAULT_START_POS = { 0.0f, 0.0f, 0.0f };
static constexpr glm::ivec2 DEFAULT_TILE_SIZE = { 128, 128 };
static constexpr float CENTER_Y_OFFSET = 10.0f;

static constexpr float OFFSET_BETWEEN_TILES = 1.0f;

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
				glm::vec3(startPos.x + (tileSize.x) * x, startPos.y, startPos.z + (tileSize.y) * z),
				tileSize.x,
				tileSize.y));
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
				glm::vec3(startPos.x + (tileSize.x) * x, startPos.y, startPos.z + (tileSize.y) * z),
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
				glm::vec3(startPos.x + (tileSize.x) * x, startPos.y, startPos.z + (tileSize.y) * z),
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
		if (tile)
		{
			if (!(tile->getVisibility()))
				throw new std::exception("Tile not visible!");

			tile->draw();
		}
		else
		{
			throw new std::exception("Invalid Tile Object!");
		}
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
	auto startUserInfo = m_UserInfo;

	auto currPos = m_UserInfo.TilePos.value_or<glm::ivec2>({0, 0});
	auto tileSize = m_Tiles[0].get()->getTileInfo().Rows;

	if (newPos.x >= (currPos.x) * tileSize && newPos.x <= (currPos.x + 1) * tileSize &&
		newPos.z >= (currPos.y) * tileSize && newPos.z <= (currPos.y + 1) * tileSize)
	{
		return;
	}

	m_UserInfo.TilePos = { floor(newPos.x / tileSize), floor(newPos.z / tileSize) };

	if(startUserInfo.TilePos.has_value())
		playerOnNewTile(startUserInfo, m_UserInfo);

	printf("User position: %d %d\n", m_UserInfo.TilePos.value().x
								   , m_UserInfo.TilePos.value().y);
}

void TileManagerV2::playerOnNewTile(UserInfo before, UserInfo after)
{
	auto difference = after.TilePos.value() - before.TilePos.value();
	printf("Delta (X, Y) = (%d, %d)\n", difference.x, difference.y);

	generateTiles(difference);
}

void TileManagerV2::generateTiles(glm::ivec2 difference)
{
	printf("Starting algorithm for allocating new tiles and moving current ones\n");

	if (difference.y != 0)
	{
		// OpenGL camera looks towards Z-, so going forward is actually going towards z- (or y- in this case)
		// X axis should be normal though (x+ on the right, x- on the left)

		if (difference.y < 0) // Forward movement
		{
			for (int z = 3; z >= 0; z--)
			{
				for (int x = 0; x < 5; x++)
				{
					m_Tiles[(z + 1) * 5 + x] = std::move(m_Tiles[z * 5 + x]);
				}

				if (z == 0)
				{
					auto tileSize = m_Tiles[(z + 1) * 5].get()->getTileInfo().Rows;

					for (int x = 0; x < 5; x++)
					{
						auto previousRowOffset = m_Tiles[(z + 1) * 5 + x].get()->getTileInfo().StartPosition;
						m_Tiles[z * 5 + x] = std::make_unique<TileV2>(TileInfo(previousRowOffset + glm::vec3(0.0f, 0.0f, -tileSize), tileSize, tileSize));
					}
				}
			}
		}
		else // Backward movement
		{
			for (int z = 1; z < 5; z++)
			{
				for (int x = 0; x < 5; x++)
				{
					m_Tiles[(z - 1) * 5 + x] = std::move(m_Tiles[z * 5 + x]);
				}

				if (z == 4)
				{
					auto tileSize = m_Tiles[0].get()->getTileInfo().Rows;

					for (int x = 0; x < 5; x++)
					{
						auto previousRowOffset = m_Tiles[(z - 1) * 5 + x].get()->getTileInfo().StartPosition;
						m_Tiles[z * 5 + x] = std::make_unique<TileV2>(TileInfo(previousRowOffset + glm::vec3(0.0f, 0.0f, tileSize), tileSize, tileSize));
					}
				}
			}
		}
	}

	if (difference.x != 0)
	{
		if (difference.x < 0) // Left movement
		{
			for (int x = 3; x >= 0; x--)
			{
				for (int z = 0; z < 5; z++)
				{
					m_Tiles[z * 5 + (x + 1)] = std::move(m_Tiles[z * 5 + x]);
				}

				if (x == 0)
				{
					auto tileSize = m_Tiles[1].get()->getTileInfo().Rows;

					for (int z = 0; z < 5; z++)
					{
						auto previousRowOffset = m_Tiles[z * 5 + (x + 1)].get()->getTileInfo().StartPosition;
						m_Tiles[z * 5 + x] = std::make_unique<TileV2>(TileInfo(previousRowOffset + glm::vec3(-tileSize, 0.0f, 0.0f), tileSize, tileSize));
					}
				}
			}
		}
		else // Right movement
		{
			for (int x = 1; x < 5; x++)
			{
				for (int z = 0; z < 5; z++)
				{
					m_Tiles[z * 5 + (x - 1)] = std::move(m_Tiles[z * 5 + x]);
				}

				if (x == 4)
				{
					auto tileSize = m_Tiles[0].get()->getTileInfo().Rows;

					for (int z = 0; z < 5; z++)
					{
						auto previousRowOffset = m_Tiles[z * 5 + (x - 1)].get()->getTileInfo().StartPosition;
						m_Tiles[z * 5 + x] = std::make_unique<TileV2>(TileInfo(previousRowOffset + glm::vec3(tileSize, 0.0f, 0.0f), tileSize, tileSize));
					}
				}
			}
		}
	}
}