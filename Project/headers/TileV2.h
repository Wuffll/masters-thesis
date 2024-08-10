#pragma once

#include <vector>

#include <FastNoiseLite/FastNoiseLite.h>

#include "VertexFormatLayout.h"
#include "VertexBufferGL.h"
#include "IndexBufferGL.h"
#include "VertexArray.h"

using VERTEX_FORMAT = VertexFormat::PositionColorTexCoord;

// number of squares in the Tile
struct TileInfo
{
	glm::vec3 StartPosition;
	int Columns;
	int Rows;
};

/**
* TileV2 is a field of [Width * Height] squares that make up the whole tile
*/
class TileV2
{
public:

	TileV2();
	TileV2(TileInfo tileInfo);

	TileV2(TileV2& other);
	TileV2& operator=(const TileV2& other);

	TileV2(TileV2&& other);
	TileV2& operator=(TileV2&& other);

	static void setNoiseType(FastNoiseLite::NoiseType type);

	const TileInfo& getTileInfo() const;

	void changeStartOffset(glm::vec3 offset);

	void setVisibility(bool isVisible);
	bool getVisibility() const;

	void draw();

private:

	static FastNoiseLite noiseInstance;

	void init();

	void generateVertices();
	void generateIndices();
	void fillBuffers();

	TileInfo m_TileInfo;

	bool m_IsVisible;

	std::vector<VERTEX_FORMAT> m_Vertices;
	std::vector<unsigned int> m_Indices;

	VertexBufferGL m_VertexBuffer;
	IndexBufferGL m_IndexBuffer;
	VertexArray m_VertexArray;

};