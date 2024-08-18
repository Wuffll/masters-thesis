#include "TileV2.h"

constexpr glm::vec3 DEFAULT_TILE_POS = { 0.0f, 0.0f, 0.0f };
constexpr int DEFAULT_TILE_WIDTH = 32;
constexpr int DEFAULT_TILE_DEPTH = 32;

constexpr glm::vec3 DEFAULT_COLOR = {0.0f, 1.0f, 0.0f};

constexpr int NUM_OF_INDICES_PER_SQUARE = 6;

FastNoiseLite TileV2::noiseInstance = FastNoiseLite();

TileV2::TileV2()
	:
	m_TileInfo({ DEFAULT_TILE_POS, DEFAULT_TILE_WIDTH, DEFAULT_TILE_DEPTH }),
	m_IsVisible(true),
	m_Vertices({}),
	m_Indices({})
{
	init();
}

TileV2::TileV2(TileInfo tileInfo)
	:
	m_TileInfo(tileInfo),
	m_IsVisible(true),
	m_Vertices({}),
	m_Indices({})
{
	init();
}

TileV2::TileV2(TileV2& other)
	:
	m_TileInfo(m_TileInfo),
	m_IsVisible(other.m_IsVisible),
	m_Vertices(m_Vertices),
	m_Indices(m_Indices)
{
	init();
}

TileV2& TileV2::operator=(const TileV2& other)
{
	m_TileInfo = other.m_TileInfo;
	m_IsVisible = other.m_IsVisible;
	m_Vertices = other.m_Vertices;
	m_Indices = other.m_Indices;

	m_VertexBuffer.resetBuffer();
	m_IndexBuffer.resetBuffer();
	init();

	return *this;
}

TileV2::TileV2(TileV2&& other)
	:
	m_TileInfo(std::move(other.m_TileInfo)),
	m_IsVisible(std::move(other.m_IsVisible)),
	m_Vertices(std::move(other.m_Vertices)),
	m_Indices(std::move(other.m_Indices)),
	m_VertexArray(std::move(other.m_VertexArray)),
	m_VertexBuffer(std::move(other.m_VertexBuffer)),
	m_IndexBuffer(std::move(other.m_IndexBuffer))
{
}

TileV2& TileV2::operator=(TileV2&& other)
{
	m_TileInfo = std::move(other.m_TileInfo);
	m_IsVisible = std::move(other.m_IsVisible);
	m_Vertices = std::move(other.m_Vertices);
	m_Indices = std::move(other.m_Indices);
	m_VertexArray = std::move(other.m_VertexArray);
	m_VertexBuffer = std::move(other.m_VertexBuffer);
	m_IndexBuffer = std::move(other.m_IndexBuffer);

	return *this;
}

void TileV2::setNoiseType(FastNoiseLite::NoiseType type)
{
	noiseInstance.SetNoiseType(type);
}

const TileInfo& TileV2::getTileInfo() const
{
	return m_TileInfo;
}

void TileV2::changeStartOffset(glm::vec3 offset)
{
	m_TileInfo.StartPosition = std::move(offset);

	generateVertices();
	fillBuffers();
}

void TileV2::setVisibility(bool isVisible)
{
	m_IsVisible = isVisible;
}

bool TileV2::getVisibility() const
{
	return m_IsVisible;
}

void TileV2::draw()
{
	if (!m_IsVisible)
		return;

	m_VertexArray.bind();
	m_VertexBuffer.bind();
	m_IndexBuffer.bind();
	glDrawElements(m_VertexArray.getDrawingMode(), m_IndexBuffer.getIndicesCount(), GL_UNSIGNED_INT, 0);
}

void TileV2::init()
{
	if(m_Vertices.size() == 0)
		generateVertices();

	if(m_Indices.size() == 0)
		generateIndices();
	
	fillBuffers();

	return;
}

void TileV2::generateVertices()
{
	const auto& cols = m_TileInfo.Columns;
	const auto& rows = m_TileInfo.Rows;

	const auto& startOffset = m_TileInfo.StartPosition;

	const unsigned int totalNumVerts = (rows + 1) * (cols + 1);
	m_Vertices.resize(totalNumVerts);

	long index = 0;
	for (int z = 0; z < rows + 1; z++)
	{
		for (int x = 0; x < cols + 1; x++)
		{
			VERTEX_FORMAT vertex;

			float y = 0.0f;

			y = noiseInstance.GetNoise(x + startOffset.x, z + startOffset.z) * 50.0f;

			vertex.first = startOffset + glm::vec3( x, y, z );
			vertex.second = {1.0f, y / 50.f, y / 50.f};

			m_Vertices[index] = std::move(vertex);

			index++;
		}
	}
}

void TileV2::generateIndices()
{
	const auto& cols = m_TileInfo.Columns;
	const auto& rows = m_TileInfo.Rows;

	const unsigned int totalNumIndices = cols * rows * NUM_OF_INDICES_PER_SQUARE;
	m_Indices.reserve(totalNumIndices);

	for (unsigned int z = 0; z < rows; z++)
	{
		unsigned int bottomLeft, topLeft, topRight, bottomRight;
		for (unsigned int x = 0; x < cols; x++)
		{
			bottomLeft = z * (cols + 1) + x;
			topLeft = (z + 1) * (cols + 1) + x;
			bottomRight = z * (cols + 1) + (x + 1);
			topRight = (z + 1) * (cols + 1) + (x + 1);

			// top triangle
			m_Indices.push_back(bottomLeft);
			m_Indices.push_back(topLeft);
			m_Indices.push_back(topRight);

			// bottom triangle
			m_Indices.push_back(bottomRight);
			m_Indices.push_back(bottomLeft);
			m_Indices.push_back(topRight);
		}
	}
}

void TileV2::fillBuffers()
{
	VertexBufferLayout vaoLayout;

	// Adjust for vertex format (TILE_VERTEX_FORMAT)
	vaoLayout.push<float>(3);
	vaoLayout.push<float>(3);
	vaoLayout.push<float>(2);

	m_VertexArray.bind();
	m_VertexArray.setLayout(vaoLayout, false);
	m_VertexArray.setDrawingMode(GL_TRIANGLES);
	m_VertexArray.setUsage(GL_STATIC_DRAW);

	m_VertexBuffer.fillBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(VERTEX_FORMAT), GL_STATIC_DRAW);
	m_IndexBuffer.fillBuffer(m_Indices.data(), m_Indices.size(), GL_STATIC_DRAW);

	m_VertexArray.addBuffer(m_VertexBuffer, m_IndexBuffer);
}
