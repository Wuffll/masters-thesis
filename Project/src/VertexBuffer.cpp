#include "VertexBuffer.h"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include "Debug.h"

#define INITIAL_BUFFER_SIZE 4 * 1024 * 1024 // 4 MB in bytes

unsigned int VertexBuffer::__boundVBO = 0;

VertexBuffer::VertexBuffer()
	:
	m_Usage(GL_STATIC_DRAW)
{
	glGenBuffers(1, &m_RendererID);

	Debug::printMessage(*this, "VertexBuffer created without any data! (mRendererID = " + STRING(m_RendererID) + ")", DebugSeverityLevel::MEDIUM);
}

VertexBuffer::VertexBuffer(const void* data, const unsigned int& size, unsigned int usage)
	:
	m_Initialized(true),
	m_Usage(usage)
{
	static_assert(sizeof(GLenum) == sizeof(unsigned int));

	glGenBuffers(1, &m_RendererID);
	fillBuffer(data, size, usage);
}

VertexBuffer::~VertexBuffer()
{
	Debug::printMessage(*this, "Vertex buffer " + STRING(m_RendererID) + " destroyed!", DebugSeverityLevel::OK);
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::fillBuffer(const void* data, const unsigned int& size, unsigned int usage)
{
	if (usage != m_Usage)
		Debug::printMessage(*this, "Inserted usage type is different from the member usage type! (mRendererID = " + STRING(m_RendererID) + ")", DebugSeverityLevel::HIGH);

	adjustBufferSize(size, usage);

	insertDataWithOffset(data, size, 0);

	m_Initialized = true;
}

void VertexBuffer::insertDataWithOffset(const void* data, const unsigned int& size, const unsigned int& offset)
{
	bind();
	adjustBufferSize(offset + size, m_Usage);

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

	m_BufferSize = (offset + size > m_BufferSize) ? offset + size : m_BufferSize;
}

unsigned int VertexBuffer::appendData(const void* data, const unsigned int& size)
{
	auto offset = m_BufferSize;

	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

	m_BufferSize += size;

	return offset;
}

void VertexBuffer::adjustBufferSize(const unsigned int& newSize, const unsigned int& usage)
{
	bool sizeChanged = false;

	if (m_BufferCapacity == 0)
	{
		m_BufferCapacity = INITIAL_BUFFER_SIZE;
		sizeChanged = true;
	}

	while (m_BufferCapacity < newSize)
	{
		m_BufferCapacity += m_BufferCapacity;
		sizeChanged = true;
	}

	if (sizeChanged)
	{
		bind();

		void* data = nullptr;

		if (m_BufferSize != 0)
		{
			data = malloc(m_BufferSize);
			glGetBufferSubData(GL_ARRAY_BUFFER, 0, m_BufferSize, data);
		}

		glBufferData(GL_ARRAY_BUFFER, m_BufferCapacity, data, usage);

		delete data;
	}
}

const bool& VertexBuffer::isInitialized() const
{
	return m_Initialized;
}

const unsigned int& VertexBuffer::getRendererID() const
{
	return m_RendererID;
}

const unsigned int& VertexBuffer::getBufferCapacity() const
{
	return m_BufferCapacity;
}

const unsigned int& VertexBuffer::getBufferSize() const
{
	return m_BufferSize;
}

const unsigned int& VertexBuffer::getOffset() const
{
	return m_BufferSize;
}

void VertexBuffer::bind() const
{
	if (!m_Initialized)
	{
		Debug::printMessage(*this, "Vertex buffer " + STRING(m_RendererID) + " is uninitialized! (mInitialized = false)", DebugSeverityLevel::HIGH);
	}

	/*
	if (boundVBO == mRendererID)
		return;
	*/

	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	__boundVBO = m_RendererID;
}

void VertexBuffer::bind(const unsigned int& bindingIndex, const VertexBufferLayout& layout) const
{
	glBindVertexBuffer(bindingIndex, m_RendererID, 0, layout.getStride());
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	__boundVBO = 0;
}