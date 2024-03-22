#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <vector>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int sizeOfDataType(GLenum type)
	{
		switch (type)
		{
		case GL_DOUBLE:				return sizeof(double);
		case GL_INT:				return sizeof(int);
		case GL_FLOAT:				return sizeof(float);
		case GL_UNSIGNED_INT:		return sizeof(unsigned int);
		case GL_UNSIGNED_BYTE:		return sizeof(unsigned char);
		}

		return 0;
	}

	bool operator==(const VertexBufferElement& rhs)
	{
		return type == rhs.type && count == rhs.count && normalized == rhs.normalized;
	}
};

class VertexBufferLayout
{
public:

	VertexBufferLayout() = default;

	const std::vector<VertexBufferElement>& getElements() const;
	const unsigned int& getStride() const;

	const bool isInitialized() const;

	bool operator==(const VertexBufferLayout& rhs)
	{
		size_t size = m_Elements.size();
		if (size != rhs.m_Elements.size())
			return false;

		for (size_t i = 0; i < size; i++)
		{
			if (m_Elements[i] != rhs.m_Elements[i])
				return false;
		}

		return true;
	}

	template<typename T>
	void push(const unsigned int& count)
	{
		printf("Tried using unsupported data type!(%s)\n", typeid(T).name());
		exit(-1);
	}

	template<>
	void push<float>(const unsigned int& count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::sizeOfDataType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(const unsigned int& count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::sizeOfDataType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(const unsigned int& count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::sizeOfDataType(GL_UNSIGNED_BYTE);
	}

private:

	std::vector<VertexBufferElement> m_Elements{};
	unsigned int m_Stride = 0;

};