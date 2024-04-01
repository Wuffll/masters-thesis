#pragma once

#include "VertexBuffer.h"

class VertexBufferGL : public VertexBuffer
{
public:

	VertexBufferGL();
	VertexBufferGL(const void* data, const unsigned int& size, unsigned int usage);
	~VertexBufferGL();

	void fillBuffer(const void* data, const unsigned int& size, unsigned int usage);
	void insertDataWithOffset(const void* data, const unsigned int& size, const unsigned int& offset);
	unsigned int appendData(const void* data, const unsigned int& size);

	const bool& isInitialized() const;

	const unsigned int& getRendererID() const;
	const unsigned int& getBufferCapacity() const;
	const unsigned int& getBufferSize() const;
	const unsigned int& getOffset() const;

	void bind() const;
	void bind(const unsigned int& bindingIndex, const VertexBufferLayout& layout) const;
	void unbind() const;

private:

	void adjustBufferSize(const unsigned int& newSize, const unsigned int& usage);

	

	// Member variables

	static unsigned int __boundVBO;

	bool m_Initialized = false;
	unsigned int m_RendererID = 0;
	unsigned int m_Usage;

	unsigned int m_BufferCapacity = 0; // (filled memory + reserved memory); in bytes
	unsigned int m_BufferSize = 0; // (filled memory); in bytes
};