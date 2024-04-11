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
#define DEFAULT_MAX_HEIGHT

struct TileMapStructure
{
	unsigned int columns = 0;
	unsigned int rows = 0;
};

struct UserPosition
{
	Camera* camera;
	unsigned int positionTileIndex;
};

class TileManager : public Drawable
{
public:

	TileManager();
	TileManager(const unsigned int& width, const unsigned int& height, const float& maxHeight);
	TileManager(const Image& heightmap, const float& maxHeight);

	void draw() const;

	void tick();

	void setTileScaling(const glm::vec3& scale);
	const glm::vec3& getTileScaling() const;

	const unsigned int& getWidth() const;
	const unsigned int& getHeight() const;

	const Tile& getTile(const unsigned int& x, const unsigned int& y) const;
	const std::vector<Tile>& getTiles() const;

	void setUser(Camera& camera);

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

	TileMapStructure m_TileMapInfo;

	unsigned int m_Width = 0; // num of horizontal VERTICES (NOT Tiles)
	unsigned int m_Depth = 0; // num of vertical VERTICES (NOT Tiles)
	float m_MaxHeight = 0;
	glm::mat4 m_ScalingMat;
	glm::vec3 m_ScalingVec;

	UserPosition m_User;

	std::vector<Tile> m_Tiles;
	Tile* m_ActiveTile = nullptr;

	std::vector<TILE_VERTEX_FORMAT> m_VertexData;
	std::vector<unsigned int> m_IndexData;

	VertexBuffer* m_pVBO;
	IndexBuffer* m_pIBO;
	VertexArray m_VAO;
};

