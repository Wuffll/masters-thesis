#pragma once

class IndexBuffer
{
public:

	virtual void fillBuffer(const void* data, const unsigned int& count, const unsigned int& usage) = 0;
	virtual void insertDataWithOffset(const void* data, const unsigned int& count, const unsigned int& offset) = 0;
	virtual unsigned int appendData(const void* data, const unsigned int& count) = 0;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual unsigned int getIndicesCount() const = 0;
	virtual unsigned int getBufferSize() const = 0;
	virtual unsigned int getOffset() const = 0;


private:

	virtual void adjustBufferSize(const unsigned int& newSize, const unsigned int& usage) = 0;

};