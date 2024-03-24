#pragma once

#include <string>
#include <unordered_map>

#include <glm/gtc/matrix_transform.hpp>

struct ShaderProgramSource
{
	std::string Vertex{};
	std::string Fragment{};
	std::string Geometry{};
};

enum ShaderType
{
	UNDEFINED = -1,
	VERT = 0,
	FRAG = 1,
	GEOM = 2
};

class Shader
{
public:

	Shader() = default;
	Shader(const std::string& filePath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setFilePath(const std::string& filePath);

	void setUniformMatrix4f(const std::string& name, const glm::mat4& matrix);
	void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void setUniform4fv(const std::string& name, const std::vector<float>& vec4f);

private:

	void init(const std::string& filePath);

	ShaderProgramSource readShaderFile(const std::string& filePath);
	unsigned int compileShader(unsigned int shaderType, const std::string& source);

	std::string getShaderTypeName(const unsigned int& type) const;

	int getUniformLocation(const std::string& name);

	static int __activeShaderID;

	unsigned int m_RendererID = 0;
	std::unordered_map<std::string, int> m_UniformLocationCache{};
	std::string m_FilePath{};

};