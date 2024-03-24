#pragma once

#include "VertexBufferLayout.h"

class VertexBuffer
{
public:

	virtual void fillBuffer(const void* data, const unsigned int& size, unsigned int usage) = 0;
	virtual void insertDataWithOffset(const void* data, const unsigned int& size, const unsigned int& offset) = 0;
	virtual unsigned int appendData(const void* data, const unsigned int& size) = 0;

	virtual const bool& isInitialized() const = 0;

	virtual const unsigned int& getRendererID() const = 0;
	virtual const unsigned int& getBufferCapacity() const = 0;
	virtual const unsigned int& getBufferSize() const = 0;
	virtual const unsigned int& getOffset() const = 0;

	virtual void bind() const = 0;
	virtual void bind(const unsigned int& bindingIndex, const VertexBufferLayout& layout) const = 0;
	virtual void unbind() const = 0;

private:

	virtual void adjustBufferSize(const unsigned int& newSize, const unsigned int& usage) = 0;

};