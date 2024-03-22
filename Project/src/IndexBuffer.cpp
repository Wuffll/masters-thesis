#include "IndexBuffer.h"
#include <GL/glew.h>

#include "Debug.hpp"

#define INITIAL_BUFFER_SIZE 1 * 1024 * 1024; // 1 MB in bytes

unsigned int IndexBuffer::__boundIBO = 0;

IndexBuffer::IndexBuffer()
	:
	m_Usage(GL_STATIC_DRAW),
	m_Count(0)
{
	glGenBuffers(1, &m_RendererID);

	Debug::printMessage(*this, "IndexBuffer created without any data! (mRendererID = " + STRING(m_RendererID) + ")", DebugSeverityLevel::MEDIUM);
}

IndexBuffer::IndexBuffer(const void* data, const unsigned int& count, const unsigned int& usage)
	:
	m_Usage(GL_STATIC_DRAW),
	m_Count(count)
{
	static_assert(sizeof(GLenum) == sizeof(unsigned int) && sizeof(GLuint) == sizeof(unsigned int));

	glGenBuffers(1, &m_RendererID);
	fillBuffer(data, count, usage);
}

IndexBuffer::~IndexBuffer()
{
	Debug::printMessage(*this, "Index buffer " + STRING(m_RendererID) + " destroyed!", DebugSeverityLevel::OK);
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::fillBuffer(const void* data, const unsigned int& count, const unsigned int& usage)
{
	adjustBufferSize(count * sizeof(unsigned int), usage);

	insertDataWithOffset(data, count, 0);

	m_BufferSize = count * sizeof(unsigned int);

	if (m_Count == 0)
	{
		this->m_Count = count;
	}
}

void IndexBuffer::insertDataWithOffset(const void* data, const unsigned int& count, const unsigned int& offset)
{
	size_t size = count * sizeof(unsigned int);

	bind();
	adjustBufferSize(offset + size, m_Usage);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);

	m_BufferSize = (offset + size > m_BufferSize) ? offset + size : m_BufferSize;
	m_Count = ((offset / sizeof(unsigned int)) + count > m_Count) ? (offset / sizeof(unsigned int)) + count : m_Count;
}

unsigned int IndexBuffer::appendData(const void* data, const unsigned int& count)
{
	auto offset = m_BufferSize;

	bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, count * sizeof(unsigned int), data);

	m_BufferSize += count * sizeof(unsigned int);

	return offset;
}

void IndexBuffer::adjustBufferSize(const unsigned int& newSize, const unsigned int& usage)
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

		delete data;
	}
}

void IndexBuffer::bind() const
{
	if (m_Count == 0)
	{
		Debug::printMessage(*this, "Index buffer " + STRING(m_RendererID) + " is not initialized! (count = 0)", DebugSeverityLevel::HIGH);
	}

	/*
	if (mRendererID == boundIBO)
		return;
	*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	__boundIBO = m_RendererID;
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const unsigned int& IndexBuffer::getIndicesCount() const
{
	return m_Count;
}

const unsigned int& IndexBuffer::getBufferSize() const
{
	return m_BufferSize;
}

/// <summary>
/// 
/// </summary>
/// <returns>Returns offset (in bytes) at which the free memory starts</returns>
/// 
const unsigned int& IndexBuffer::getOffset() const
{
	return m_BufferSize;
}