#pragma once

#include <vector>

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

	void changeStartOffset(glm::vec3 offset);

	void draw();

private:

	void init();

	void generateVertices();
	void generateIndices();
	void fillBuffers();

	TileInfo m_TileInfo;

	std::vector<VERTEX_FORMAT> m_Vertices;
	std::vector<unsigned int> m_Indices;

	VertexBufferGL m_VertexBuffer;
	IndexBufferGL m_IndexBuffer;
	VertexArray m_VertexArray;

};