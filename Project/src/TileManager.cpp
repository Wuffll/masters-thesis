#include "TileManager.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Debug.h"

TileManager::TileManager()
	:
	m_Width(DEFAULT_TILE_GRID_SIZE + 1),
	m_Depth(DEFAULT_TILE_GRID_SIZE + 1),
	m_TileMapInfo({ DEFAULT_TILE_GRID_SIZE, DEFAULT_TILE_GRID_SIZE }),
	m_MaxHeight(DEFAULT_MAX_HEIGHT),
	m_pVBO(new VertexBufferGL()),
	m_pIBO(new IndexBufferGL()),
	m_VAO(VertexArray())
{
	generateTiles();
}

TileManager::TileManager(const unsigned int& width, const unsigned int& height, const float& maxHeight)
	:
	m_Width(width + 1),
	m_Depth(height + 1),
	m_TileMapInfo({ width, height }),
	m_MaxHeight(maxHeight),
	m_pVBO(new VertexBufferGL()),
	m_pIBO(new IndexBufferGL()),
	m_VAO(VertexArray())
{
	if (width == 0 || height == 0)
		Debug::throwException(*this, "Width and height both must be greater than 0!");

	generateTiles();
}

TileManager::TileManager(const Image& heightmap, const float& maxHeight)
	:
	m_Width(heightmap.getImageInfo().width),
	m_Depth(heightmap.getImageInfo().height),
	m_TileMapInfo({(unsigned int) heightmap.getImageInfo().width - 1, (unsigned int) heightmap.getImageInfo().height - 1}),
	m_MaxHeight(maxHeight),
	m_pVBO(new VertexBufferGL()),
	m_pIBO(new IndexBufferGL()),
	m_VAO(VertexArray())
{
	generateTiles(&heightmap);
}

void TileManager::draw() const
{
	m_VAO.bind();
	m_pVBO->bind();
	glDrawElements(m_VAO.getDrawingMode(), m_pIBO->getIndicesCount(), GL_UNSIGNED_INT, 0);
}

void TileManager::userPositionUpdate(const glm::vec3& position)
{
	double xPos = floor(position.x) - m_TileMapInfo.columns / 2.0f; // Tiles are 1x1 so no need for mutliplication
	double yPos = floor(position.z) - m_TileMapInfo.rows / 2.0f;

	Debug::printMessage(*this, "Player position -> (" + STRING(xPos) + ", " + STRING(yPos) + ")", DebugSeverityLevel::OK);
}

void TileManager::setTileScaling(const glm::vec3& scale)
{
	m_ScalingVec = scale;
	m_ScalingMat = glm::scale(glm::mat4(1.0f), scale);
}

const glm::vec3& TileManager::getTileScaling() const
{
	return m_ScalingVec;
}

const unsigned int& TileManager::getWidth() const
{
	return m_Width;
}

const unsigned int& TileManager::getHeight() const
{
	return m_Depth;
}

const Tile& TileManager::getTile(const unsigned int& x, const unsigned int& y) const
{
	return m_Tiles[x * m_Width + y];
}

const std::vector<Tile>& TileManager::getTiles() const
{
	return m_Tiles;
}

void TileManager::generateTiles(const Image* heightmap)
{
	initVertices(heightmap);
	initIndices();
	initTiles();

	loadVertexBuffers();

	initActiveTile();
}

void TileManager::initVertices(const Image* heightmap)
{
	const unsigned int totalNumVertices = m_Width * m_Depth;
	m_VertexData.resize(totalNumVertices);

	initVertexPositions(heightmap);
	initVertexNormals();
	initVertexTexCoords();
}

void TileManager::initVertexPositions(const Image* heightmap)
{
	glm::vec3 position;

	unsigned int index = 0;
	for (unsigned int z = 0; z < m_Depth; z++)
	{
		for (unsigned int x = 0; x < m_Width; x++)
		{
			index = z * m_Width + x;

			position.x = ((float)x - m_Width / 2.0f);
			position.z = ((float)z - m_Depth / 2.0f);

			if (heightmap)
			{
				position.y = m_MaxHeight * (heightmap->getImageData()[index].R / 255.0f);
			}
			else
			{
				position.y = 0.0f;
			}

			m_VertexData[index].first = position;
		}
	}
}

void TileManager::initVertexNormals()
{
	unsigned int u, ur, r, b, bl, l; // adjecent vertices: up, upper right, right, ...
	const glm::vec3* pUPos = 0, * pURPos = 0, * pRPos = 0, * pBPos = 0, * pBLPos = 0, * pLPos = 0;

	glm::vec3 normal;
	unsigned int index = 0;
	for (unsigned int z = 0; z < m_Depth; z++)
	{
		for (unsigned int x = 0; x < m_Width; x++)
		{
			index = z * m_Width + x;

			if (z < m_Depth - 1)
			{
				u = (z + 1) * m_Width + x;
				pUPos = &m_VertexData[u].first;

				if (x < m_Width - 1)
				{
					ur = (z + 1) * m_Width + (x + 1);
					pURPos = &m_VertexData[ur].first;
				}
			}

			if (z > 0)
			{
				b = (z - 1) * m_Width + x;
				pBPos = &m_VertexData[b].first;

				if (x > 0)
				{
					bl = (z - 1) * m_Width + (x - 1);
					pBLPos = &m_VertexData[bl].first;
				}
			}

			if (x > 0)
			{
				l = z * m_Width + (x - 1);
				pLPos = &m_VertexData[l].first;
			}

			if (x < m_Width - 1)
			{
				r = z * m_Width + (x + 1);
				pRPos = &m_VertexData[r].first;
			}

			normal = calculateNormal(pUPos, pURPos, pRPos, pBPos, pBLPos, pLPos);
			
			m_VertexData[index].second = normal;
		}
	}
}

glm::vec3 TileManager::calculateNormal(const glm::vec3* pUPos, const glm::vec3* pURPos, 
									   const glm::vec3* pRPos, const glm::vec3* pBPos, 
									   const glm::vec3* pBLPos, const glm::vec3* pLPos)
{
	glm::vec3 output;

	if (true) // TODO: add appropriate boolean expression
		output = calculateNormalComplex(pUPos, pURPos, pRPos, pBPos, pBLPos, pLPos);
	else
		output = calculateNormalSimple(pUPos, pRPos, pBPos, pLPos);

	return output;
}

glm::vec3 TileManager::calculateNormalComplex(const glm::vec3* pUPos, const glm::vec3* pURPos, 
											  const glm::vec3* pRPos, const glm::vec3* pBPos, 
											  const glm::vec3* pBLPos, const glm::vec3* pLPos)
{
	glm::vec3 output;

	// Formula when all the normals from adjacent triangles (to the current vertex) are added: 
	// N = N1 + N2 + N3 + N4 + N5 + N6
	// less taxing than calculating all the cross products

	if (!pUPos || !pURPos || !pRPos || !pLPos || !pBLPos || !pLPos)
		return { 0.0f, 1.0f, 0.0f };

	output.x = (2.0f * (pLPos->y - pRPos->y) - pURPos->y + pBLPos->y + pUPos->y - pBPos->y);
	output.y = 6.0f;
	output.z = (2.0f * (pBPos->y - pUPos->y) + pURPos->y + pBLPos->y - pUPos->y - pLPos->y);

	output = glm::normalize(output);
	return output;
}

glm::vec3 TileManager::calculateNormalSimple(const glm::vec3* pUPos, const glm::vec3* pRPos, 
											 const glm::vec3* pBPos, const glm::vec3* pLPos)
{
	glm::vec3 output;

	// Formula when taking into account only the top, right, bottom and left adjacent vertices (triangles):
	// N = N1 + N2 + N3 + N4
	// less taxing than calculating all the cross products

	if (!pUPos || !pRPos || !pLPos || !pBPos)
		return { 0.0f, 1.0f, 0.0f };

	output.x = (pLPos->y - pRPos->y);
	output.y = 2.0f;
	output.z = (pBPos->y - pUPos->y);

	output = glm::normalize(output);
	return output;
}

void TileManager::initVertexTexCoords()
{
	// TODO : Currently using it for color

	unsigned int index = 0;
	for (unsigned int z = 0; z < m_Depth; z++)
	{
		for (unsigned int x = 0; x < m_Width; x++)
		{
			index = z * m_Width + x;

			m_VertexData[index].third = DEFAULT_TILE_COLOR;
		}
	}
}

void TileManager::initIndices()
{
	const unsigned int totalNumIndices = (m_Width - 1) * (m_Depth - 1) * NUM_OF_INDICES_PER_TILE;
	m_IndexData.reserve(totalNumIndices);

	const auto& tileColumns = m_TileMapInfo.columns;
	const auto& tileRows = m_TileMapInfo.rows;

	for (unsigned int z = 0; z < tileRows; z++)
	{
		unsigned int bottomLeft, topLeft, topRight, bottomRight;
		for (unsigned int x = 0; x < tileColumns; x++)
		{
			bottomLeft = z * m_Width + x;
			topLeft = (z + 1) * m_Width + x;
			topRight = (z + 1) * m_Width + (x + 1);
			bottomRight = z * m_Width + (x + 1);

			// top triangle
			m_IndexData.push_back(bottomLeft);
			m_IndexData.push_back(topLeft);
			m_IndexData.push_back(topRight);

			// bottom triangle
			m_IndexData.push_back(bottomLeft);
			m_IndexData.push_back(topRight);
			m_IndexData.push_back(bottomRight);
		}
	}
}

void TileManager::initTiles()
{
	unsigned int* pTileIndices = m_IndexData.data();

	const auto& tileColumns = m_TileMapInfo.columns;
	const auto& tileRows = m_TileMapInfo.rows;
	unsigned int numOfTiles = tileColumns * tileRows;

	m_Tiles.reserve(numOfTiles);

	for (unsigned int z = 0; z < tileRows; z++)
	{
		for (unsigned int x = 0; x < tileColumns; x++)
		{
			Tile newTile(x, z);
			newTile.setIndicesPointer(pTileIndices);

			m_Tiles.push_back(newTile);

			pTileIndices += NUM_OF_INDICES_PER_TILE;
		}
	}

	initTileNeighbors();
}

void TileManager::initTileNeighbors()
{
	Tile *top, *right, *left, *bottom;

	const auto& tileColumns = m_TileMapInfo.columns;
	const auto& tileRows = m_TileMapInfo.rows;

	for (unsigned int z = 0; z < tileRows; z++)
	{
		for (unsigned int x = 0; x < tileColumns; x++)
		{
			auto& currentTile = m_Tiles[z * tileColumns + x];

			if (z != tileRows - 1)
			{
				top = &m_Tiles[(z + 1) * tileColumns + x];
				currentTile.setTopNeighbor(top);
			}

			if (z != 0)
			{
				bottom = &m_Tiles[(z - 1) * tileColumns + x];
				currentTile.setBottomNeighbor(bottom);
			}

			if (x != 0)
			{
				left = &m_Tiles[z * tileRows + x - 1];
				currentTile.setLeftNeighbor(left);
			}

			if (x != tileColumns - 1)
			{
				right = &m_Tiles[z * tileRows + x + 1];
				currentTile.setRightNeighbor(right);
			}
		}
	}
}

void TileManager::loadVertexBuffers()
{
	VertexBufferLayout vaoLayout;

	// Adjust for vertex format (TILE_VERTEX_FORMAT)
	vaoLayout.push<float>(3);
	vaoLayout.push<float>(3);
	vaoLayout.push<float>(3);

	m_VAO.bind();
	m_VAO.setLayout(vaoLayout, false);
	m_VAO.setDrawingMode(GL_TRIANGLES);
	m_VAO.setUsage(GL_STATIC_DRAW);

	m_pVBO->bind();

	m_pVBO->fillBuffer(m_VertexData.data(), (unsigned int)m_VertexData.size() * sizeof(TILE_VERTEX_FORMAT), GL_STATIC_DRAW);
	m_pIBO->fillBuffer(m_IndexData.data(), (unsigned int)m_IndexData.size(), GL_STATIC_DRAW);

	m_VAO.addBuffer(*m_pVBO, *m_pIBO);
}

void TileManager::initActiveTile()
{
	const auto& rows = m_TileMapInfo.rows;
	const auto& columns = m_TileMapInfo.columns;

	unsigned int middleTileIndex = (rows / 2)* columns + (columns / 2);

	setTileActive(&m_Tiles[middleTileIndex]);
}

void TileManager::setTileActive(Tile* active)
{
	if (m_ActiveTile)
		changeTileColor(m_ActiveTile, DEFAULT_TILE_COLOR);

	m_ActiveTile = active;

	changeTileColor(active, ACTIVE_TILE_COLOR);
}

void TileManager::setTileActive(const unsigned int& index)
{
	if (m_ActiveTile)
		changeTileColor(m_ActiveTile, DEFAULT_TILE_COLOR);

	m_ActiveTile = &m_Tiles[index];

	changeTileColor(m_ActiveTile, ACTIVE_TILE_COLOR);
}

void TileManager::changeTileColor(Tile* active, const glm::vec3& color)
{
	active->setColor(color);

	const auto& indices = active->getIndicesPointer();

	for (int i = 0; i < NUM_OF_INDICES_PER_TILE; i++)
	{
		auto& vertexIndex = *(indices + i);
		auto& currentVertex = m_VertexData[vertexIndex];

		currentVertex.third = color;
	}
}
