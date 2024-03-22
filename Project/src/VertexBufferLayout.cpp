#include "VertexBufferLayout.h"

#include "Debug.hpp"

const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const
{
    return m_Elements;
}

const unsigned int& VertexBufferLayout::getStride() const
{
    if (!isInitialized())
        Debug::throwException(*this, "VertexBufferLayout not initialized!");

    return m_Stride;
}

const bool VertexBufferLayout::isInitialized() const
{
    return m_Elements.size() != 0;
}