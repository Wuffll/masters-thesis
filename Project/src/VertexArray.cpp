#include "VertexArray.h"

#include "Debug.hpp"

VertexArray::VertexArray()
	:
	m_Usage(GL_STATIC_DRAW),
	m_DrawingMode(GL_TRIANGLES)
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

const VertexBufferLayout& VertexArray::getLayout() const
{
	return m_Layout;
}

const unsigned int& VertexArray::getUsage() const
{
	return m_Usage;
}

const unsigned int& VertexArray::getDrawingMode() const
{
	return m_DrawingMode;
}

void VertexArray::setLayout(const VertexBufferLayout& layout, const bool& buffersSeperated)
{
	m_Layout = layout;
	m_LayoutBuffersSeperated = buffersSeperated;
}

void VertexArray::setUsage(const unsigned int& usageType)
{
	m_Usage = usageType;
}

void VertexArray::setDrawingMode(const unsigned int& drawingMode)
{
	m_DrawingMode = drawingMode;
}

void VertexArray::addBuffer(const VertexBuffer& vb, const IndexBuffer& ib)
{
	if (!m_Layout.isInitialized())
	{
		Debug::throwException(*this, "Layout is not set for Vertex Array! (mRendererID = " + STRING(m_RendererID) + ")");
	}

	bind();

	assignVertexAttributes();

	vb.bind(0, m_Layout);
	ib.bind();
}

void VertexArray::bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::assignVertexAttributes()
{
	unsigned int offset = 0;
	const auto& elements = m_Layout.getElements();

	unsigned int bindingIndex = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& e = elements[i];

		glEnableVertexAttribArray(i);
		// glVertexAttribPointer(i, e.count, e.type, e.normalized, mLayout.GetStride(), (void*)(offset));
		glVertexAttribFormat(i, e.count, e.type, e.normalized, offset);
		glVertexAttribBinding(i, bindingIndex);

		if (m_LayoutBuffersSeperated)
			bindingIndex++;

		offset += e.count * VertexBufferElement::sizeOfDataType(e.type);
	}
}