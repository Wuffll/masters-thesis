#include "Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <fstream>

int Shader::__activeShaderID = -1;

Shader::Shader(const std::string& filePath)
	:
	m_FilePath(filePath)
{
	init(filePath);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}


void Shader::bind() const
{
	if (__activeShaderID != m_RendererID)
	{
		glUseProgram(m_RendererID);
		__activeShaderID = m_RendererID;
	}
}

void Shader::unbind() const
{
	glUseProgram(0);

	__activeShaderID = -1;
}

void Shader::setFilePath(const std::string& filePath)
{
	m_FilePath = filePath;
}

void Shader::setUniformMatrix4f(const std::string& name, const glm::mat4& matrix)
{
	int location = getUniformLocation(name);

	if (location == -1)
		return;

	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	int location = getUniformLocation(name);

	if (location == -1)
		return;

	glUniform4f(location, f0, f1, f2, f3);
}

void Shader::setUniform4fv(const std::string& name, const std::vector<float>& vec4f)
{
	int location = getUniformLocation(name);

	if (location == -1)
		return;

	glUniform4fv(location, 4, vec4f.data());
}

void Shader::init(const std::string& filePath)
{
	ShaderProgramSource source = readShaderFile(filePath);

	m_RendererID = glCreateProgram();
	unsigned int shader;
	std::vector<unsigned int> shaders{};

	if (source.Vertex.size() != 0)
	{
		shader = compileShader(GL_VERTEX_SHADER, source.Vertex);
		glAttachShader(m_RendererID, shader);
		shaders.push_back(shader);
	}

	if (source.Fragment.size() != 0)
	{
		shader = compileShader(GL_FRAGMENT_SHADER, source.Fragment);
		glAttachShader(m_RendererID, shader);
		shaders.push_back(shader);
	}

	if (source.Geometry.size() != 0)
	{
		shader = compileShader(GL_GEOMETRY_SHADER, source.Geometry);
		glAttachShader(m_RendererID, shader);
		shaders.push_back(shader);
	}

	glLinkProgram(m_RendererID);
	glValidateProgram(m_RendererID);

	for (auto& s : shaders)
	{
		glDeleteShader(s);
	}
}

ShaderProgramSource Shader::readShaderFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (!file.is_open())
		throw false && "File was not able to be opened!";


	ShaderType type = ShaderType::UNDEFINED;
	ShaderProgramSource source;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("VERT") != std::string::npos)
				type = ShaderType::VERT;
			else if (line.find("FRAG") != std::string::npos)
				type = ShaderType::FRAG;
			else if (line.find("GEOM") != std::string::npos)
				type = ShaderType::GEOM;
		}
		else
		{
			switch (type)
			{
			case VERT:
				source.Vertex.append(line + "\n");
				break;
			case FRAG:
				source.Fragment.append(line + "\n");
				break;
			case GEOM:
				source.Geometry.append(line + "\n");
				break;
			}
		}
	}

	return source;
}

unsigned int Shader::compileShader(unsigned int shaderType, const std::string& source)
{
	unsigned int id = glCreateShader(shaderType);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result, length;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, &msg[0]);

		std::cout << "Failed to compile shader! (shader = " << shaderType << ")" << std::endl;
		std::cout << msg << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

int Shader::getUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
	{
		std::cout << "There is no uniform with name \"" << name << "\"! (mRendererID = " << m_RendererID << "; check whether the uniform is used in GLSL shader)" << std::endl;
		return location;
	}

	m_UniformLocationCache[name] = location;
	return location;
}