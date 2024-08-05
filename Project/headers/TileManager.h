#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Drawable.h"

#include "Camera.h"
#include "Image.h"
#include "Tile.h"
#include "VertexFormatLayout.h"
#include "VertexBufferGL.h"
#include "IndexBufferGL.h"
#include "VertexArray.h"

#define DEFAULT_TILE_GRID_SIZE 128
#define DEFAULT_MAX_HEIGHT 255

// TileGridInfo detailed explanation
/* 
*1st     2nd	 3rd	 4th vertex column
*|		 |		 |		 |
*v		 v		 v		 v
* _______ _______ _______	<- 2nd vertex row
*|      /|      /|      /|
*|     / |     / |     / |
*|    /  |    /  |    /  |
*|   /   |   /   |   /   |
*|  /    |  /    |  /    |
*| /     | /     | /     |
* ------- ------- -------	<- 1st
*
* Above is a 3x1 set of tiles which consists of 4 vertex columns. Each tile consists of 2 vertex columns.
* Neighboring tiles share the vertex column between them.
* Therefore, for AxB grid there are (A + 1) vertex columns and (B + 1) vertex rows (smallest grid is 1x1).
* 
* So, if you are wondering why there is a (tileColumns + 1) in the initIndices function, it is because
* of this fact: if the grid consists of 5 horizontal tiles (tileColumns = 5) then there is 5 + 1 (tileColumns + 1)
* vertex columns.
*/

struct TileGridInfo
{
	unsigned int columns = 0;
	unsigned int rows = 0;
};

class TileManager : public Drawable
{
public:

	TileManager();
	TileManager(const unsigned int& width, const unsigned int& height, const float& maxHeight);
	TileManager(const Image& heightmap, const float& maxHeight);

	void draw() const;

	void setTileScaling(const glm::vec3& scale);
	const glm::vec3& getTileScaling() const;

	const unsigned int& getWidth() const;
	const unsigned int& getHeight() const;

	const Tile& getTile(const unsigned int& x, const unsigned int& y) const;
	const std::vector<Tile>& getTiles() const;

	void setTileActive(Tile* active);
	void setTileActive(const unsigned int& index);

	const std::vector<TILE_VERTEX_FORMAT>& getVertexData() const { return m_VertexData; }
	const std::vector<unsigned int>& getIndexData() const { return m_IndexData; }

private:

	void generateTiles(const Image* heightmap = nullptr);

	void initVertices(const Image* heightmap = nullptr);

	void initVertexPositions(const Image* heightmap = nullptr);

	void initVertexNormals();
	glm::vec3 calculateNormal(const glm::vec3* pUPos, const glm::vec3* pURPos, const glm::vec3* pRPos,
							  const glm::vec3* pBPos, const glm::vec3* pBLPos, const glm::vec3* pLPos);
	glm::vec3 calculateNormalComplex(const glm::vec3* pUPos, const glm::vec3* pURPos, 
									 const glm::vec3* pRPos, const glm::vec3* pBPos, 
									 const glm::vec3* pBLPos, const glm::vec3* pLPos);
	glm::vec3 calculateNormalSimple(const glm::vec3* pUPos, const glm::vec3* pRPos, 
									const glm::vec3* pBPos, const glm::vec3* pLPos);

	void initVertexTexCoords();

	void initIndices();
	void initTiles();
	void initTileNeighbors();

	void loadVertexBuffers();

	void initActiveTile();

	// void setTileActive(Tile* active);
	void changeTileColor(Tile* active, const glm::vec3& color);

	TileGridInfo m_TileMapInfo;

	float m_MaxHeight;
	glm::mat4 m_ScalingMat;
	glm::vec3 m_ScalingVec;

	std::vector<Tile> m_Tiles;
	Tile* m_ActiveTile = nullptr;

	std::vector<TILE_VERTEX_FORMAT> m_VertexData;
	std::vector<unsigned int> m_IndexData;

	VertexBuffer* m_pVBO;
	IndexBuffer* m_pIBO;
	VertexArray m_VAO;
};

