#include "VertexBufferGL.h"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include "Debug.h"

#define INITIAL_BUFFER_SIZE 4 * 1024 * 1024 // 4 MB in bytes

unsigned int VertexBufferGL::__boundVBO = 0;

VertexBufferGL::VertexBufferGL()
	:
	m_Usage(GL_STATIC_DRAW)
{
	glGenBuffers(1, &m_RendererID);

	Debug::printMessage(*this, "VertexBufferGL created without any data! (mRendererID = " + STRING(m_RendererID) + ")", DebugSeverityLevel::MEDIUM);
}

VertexBufferGL::VertexBufferGL(const void* data, const unsigned int& size, unsigned int usage)
	:
	m_Initialized(true),
	m_Usage(usage)
{
	static_assert(sizeof(GLenum) == sizeof(unsigned int));

	glGenBuffers(1, &m_RendererID);
	fillBuffer(data, size, usage);
}

VertexBufferGL::~VertexBufferGL()
{
	Debug::printMessage(*this, "VertexBufferGL " + STRING(m_RendererID) + " destroyed!", DebugSeverityLevel::OK);
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBufferGL::fillBuffer(const void* data, const unsigned int& size, unsigned int usage)
{
	if (usage != m_Usage)
		Debug::printMessage(*this, "Inserted usage type is different from the member usage type! (mRendererID = " + STRING(m_RendererID) + ")", DebugSeverityLevel::HIGH);

	adjustBufferSize(size, usage);

	insertDataWithOffset(data, size, 0);

	m_Initialized = true;
}

void VertexBufferGL::insertDataWithOffset(const void* data, const unsigned int& size, const unsigned int& offset)
{
	bind();
	adjustBufferSize(offset + size, m_Usage);

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

	m_BufferSize = (offset + size > m_BufferSize) ? offset + size : m_BufferSize;
}

unsigned int VertexBufferGL::appendData(const void* data, const unsigned int& size)
{
	auto offset = m_BufferSize;

	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

	m_BufferSize += size;

	return offset;
}

const bool& VertexBufferGL::isInitialized() const
{
	return m_Initialized;
}

const unsigned int& VertexBufferGL::getRendererID() const
{
	return m_RendererID;
}

const unsigned int& VertexBufferGL::getBufferCapacity() const
{
	return m_BufferCapacity;
}

const unsigned int& VertexBufferGL::getBufferSize() const
{
	return m_BufferSize;
}

const unsigned int& VertexBufferGL::getOffset() const
{
	return m_BufferSize;
}

void VertexBufferGL::bind() const
{
	if (!m_Initialized)
	{
		Debug::printMessage(*this, "VertexBufferGL " + STRING(m_RendererID) + " is uninitialized! (mInitialized = false)", DebugSeverityLevel::HIGH);
	}

	if (__boundVBO == m_RendererID)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	__boundVBO = m_RendererID;
}

void VertexBufferGL::bind(const unsigned int& bindingIndex, const VertexBufferLayout& layout) const
{
	glBindVertexBuffer(bindingIndex, m_RendererID, 0, layout.getStride());
}

void VertexBufferGL::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	__boundVBO = 0;
}

void VertexBufferGL::adjustBufferSize(const unsigned int& newSize, const unsigned int& usage)
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

		free(data);
	}
}