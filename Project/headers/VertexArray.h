#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:

	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray&) = delete;

	VertexArray(VertexArray&&);
	VertexArray& operator=(VertexArray&&);

	const VertexBufferLayout& getLayout() const;
	const unsigned int& getUsage() const;
	const unsigned int& getDrawingMode() const;

	void setLayout(const VertexBufferLayout& layout, const bool& buffersSeperated);
	void setUsage(const unsigned int& usageType);
	void setDrawingMode(const unsigned int& drawingMode);

	void addBuffer(const VertexBuffer& vb, const IndexBuffer& ib);

	void bind() const;
	void unbind() const;

private:

	void assignVertexAttributes();

	static unsigned int __boundVAO;

	unsigned int m_RendererID;

	VertexBufferLayout m_Layout;
	bool m_LayoutBuffersSeperated = false;

	unsigned int m_Usage;
	unsigned int m_DrawingMode;

};