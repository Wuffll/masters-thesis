#include "IndexBufferGL.h"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include "Debug.h"

#define INITIAL_BUFFER_SIZE 1 * 1024 * 1024; // 1 MB in bytes

unsigned int IndexBufferGL::__boundIBO = 0;

IndexBufferGL::IndexBufferGL()
	:
	m_Usage(GL_STATIC_DRAW),
	m_Count(0)
{
	glGenBuffers(1, &m_RendererID);

	Debug::printMessage(*this, "IndexBufferGL created without any data! (mRendererID = " + STRING(m_RendererID) + ")", DebugSeverityLevel::MEDIUM);
}

IndexBufferGL::IndexBufferGL(const void* data, const unsigned int& count, const unsigned int& usage)
	:
	m_Usage(GL_STATIC_DRAW),
	m_Count(count)
{
	static_assert(sizeof(GLenum) == sizeof(unsigned int) && sizeof(GLuint) == sizeof(unsigned int));

	glGenBuffers(1, &m_RendererID);
	fillBuffer(data, count, usage);
}

IndexBufferGL::~IndexBufferGL()
{
	if (m_RendererID == 0)
		return;

	Debug::printMessage(*this, "IndexBufferGL " + STRING(m_RendererID) + " destroyed!", DebugSeverityLevel::OK);
	glDeleteBuffers(1, &m_RendererID);
}

IndexBufferGL::IndexBufferGL(IndexBufferGL&& other)
	:
	m_RendererID(std::move(other.m_RendererID)),
	m_Usage(std::move(other.m_Usage)),
	m_Count(std::move(other.m_Count)),
	m_BufferCapacity(std::move(other.m_BufferCapacity)),
	m_BufferSize(std::move(other.m_BufferSize))
{
	other.m_RendererID = 0;
}

IndexBufferGL& IndexBufferGL::operator=(IndexBufferGL&& other)
{
	m_RendererID = std::move(other.m_RendererID);
	m_Usage = std::move(other.m_Usage);
	m_Count = std::move(other.m_Count);
	m_BufferCapacity = std::move(other.m_BufferCapacity);
	m_BufferSize = std::move(other.m_BufferSize);

	other.m_RendererID = 0;

	return *this;
}

void IndexBufferGL::fillBuffer(const void* data, const unsigned int& count, const unsigned int& usage)
{
	adjustBufferSize(count * sizeof(unsigned int), usage);

	insertDataWithOffset(data, count, 0);

	m_BufferSize = count * sizeof(unsigned int);

	if (m_Count == 0)
	{
		this->m_Count = count;
	}
}

void IndexBufferGL::insertDataWithOffset(const void* data, const unsigned int& count, const unsigned int& offset)
{
	unsigned int size = count * sizeof(unsigned int);

	bind();
	adjustBufferSize(offset + size, m_Usage);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);

	m_BufferSize = (offset + size > m_BufferSize) ? offset + size : m_BufferSize;
	m_Count = ((offset / sizeof(unsigned int)) + count > m_Count) ? (offset / sizeof(unsigned int)) + count : m_Count;
}

unsigned int IndexBufferGL::appendData(const void* data, const unsigned int& count)
{
	auto offset = m_BufferSize;

	bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, count * sizeof(unsigned int), data);

	m_BufferSize += count * sizeof(unsigned int);

	return offset;
}

void IndexBufferGL::adjustBufferSize(const unsigned int& newSize, const unsigned int& usage)
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
			glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_BufferSize, data);
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_BufferCapacity, data, usage);

		free(data);
	}
}

void IndexBufferGL::bind() const
{
	if (m_Count == 0)
	{
		Debug::printMessage(*this, "IndexBufferGL " + STRING(m_RendererID) + " is not initialized! (count = 0)", DebugSeverityLevel::HIGH);
	}

	if (m_RendererID == __boundIBO)
		return;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	__boundIBO = m_RendererID;
}

void IndexBufferGL::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	__boundIBO = 0;
}

void IndexBufferGL::resetBuffer()
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_BufferSize, nullptr, m_Usage);

	m_Count = 0;
	m_BufferSize = 0;
	m_BufferCapacity = 0;
}

const unsigned int& IndexBufferGL::getIndicesCount() const
{
	return m_Count;
}

const unsigned int& IndexBufferGL::getBufferSize() const
{
	return m_BufferSize;
}

/// <summary>
/// 
/// </summary>
/// <returns>Returns offset (in bytes) at which the free memory starts</returns>
/// 
const unsigned int& IndexBufferGL::getOffset() const
{
	return m_BufferSize;
}