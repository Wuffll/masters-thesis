#pragma once

#include "IndexBuffer.h"

class IndexBufferGL : public IndexBuffer
{
public:

	IndexBufferGL();
	IndexBufferGL(const void* data, const unsigned int& count, const unsigned int& usage);
	~IndexBufferGL();

	IndexBufferGL(IndexBuffer&) = delete;
	IndexBufferGL& operator=(IndexBuffer&) = delete;

	IndexBufferGL(IndexBufferGL&& other);
	IndexBufferGL& operator=(IndexBufferGL&& other);

	void fillBuffer(const void* data, const unsigned int& count, const unsigned int& usage);
	void insertDataWithOffset(const void* data, const unsigned int& count, const unsigned int& offset);
	unsigned int appendData(const void* data, const unsigned int& count);

	void bind() const;
	void unbind() const;

	void resetBuffer();

	const unsigned int& getIndicesCount() const;
	const unsigned int& getBufferSize() const;
	const unsigned int& getOffset() const;


private:

	void adjustBufferSize(const unsigned int& newSize, const unsigned int& usage);

	static unsigned int __boundIBO;

	unsigned int m_RendererID = 0;
	unsigned int m_Usage;

	unsigned int m_Count = 0;
	unsigned int m_BufferCapacity = 0; // free space + used up space (= initial size); in bytes
	unsigned int m_BufferSize = 0; // used up space; in bytes
};