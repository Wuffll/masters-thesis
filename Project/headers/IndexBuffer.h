#pragma once

class IndexBuffer
{
public:

	IndexBuffer();
	IndexBuffer(const void* data, const unsigned int& count, const unsigned int& usage);
	~IndexBuffer();

	void fillBuffer(const void* data, const unsigned int& count, const unsigned int& usage);
	void insertDataWithOffset(const void* data, const unsigned int& count, const unsigned int& offset);
	unsigned int appendData(const void* data, const unsigned int& count);

	void adjustBufferSize(const unsigned int& newSize, const unsigned int& usage);

	void bind() const;
	void unbind() const;

	const unsigned int& getIndicesCount() const;
	const unsigned int& getBufferSize() const;
	const unsigned int& getOffset() const;


private:

	static unsigned int __boundIBO;

	unsigned int m_RendererID = 0;
	unsigned int m_Usage;

	unsigned int m_Count = 0;
	unsigned int m_BufferCapacity = 0; // free space + used up space (= initial size); in bytes
	unsigned int m_BufferSize = 0; // used up space; in bytes
};