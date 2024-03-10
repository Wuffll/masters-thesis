#include "ImageLoaderSTBI.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

ImageInfo ImageLoaderSTBI::loadFromFile(const std::string& filePath)
{
	ImageInfo output;

	setFilePath(filePath);

	output = std::move(load());

	return output;
}

ImageInfo ImageLoaderSTBI::load() const
{
	ImageInfo output;

	if (m_FilePath.empty())
	{
		printf("WARNING (ImageLoaderSTBI.hpp): m_FilePath not set when trying to load image via the loadFromImage(const char*) function!\n");
		return output;
	}

	int comp;
	output.m_Data = stbi_load(m_FilePath.c_str(), &output.m_Width, &output.m_Height, &comp, 1);

	if (!output.m_Data)
		printf("WARNING (ImageLoaderSTBI.hpp): Loading an image (%s) was unsuccessful!", m_FilePath.c_str());

	return output;
}

void ImageLoaderSTBI::setFilePath(const std::string& filePath)
{
	if (filePath.empty())
		return;

    m_FilePath = filePath;
}

const std::string& ImageLoaderSTBI::getFilePath() const
{
    return m_FilePath;
}
