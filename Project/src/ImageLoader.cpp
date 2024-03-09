#include "ImageLoader.hpp"

#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

ImageLoader::ImageLoader()
{
}

ImageLoader::ImageLoader(const std::string& filePath)
	:
	m_FilePath(filePath)
{
}

void ImageLoader::LoadImage()
{
	if (m_FilePath.empty())
	{
		printf("WARNING (ImageLoader.hpp): m_FilePath not set when trying to load image via the LoadImage() function!\n");
		return;
	}

	int comp;
	m_pImage = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &comp, 1);

	if(m_pImage)
		m_ImageLoaded = true;
}

const unsigned char& const ImageLoader::GetImage()
{
	if (!m_ImageLoaded && !m_FilePath.empty())
		LoadImage();

	assert(m_ImageLoaded && "Image not loaded!");

	return *m_pImage;
}

void ImageLoader::setFilePath(const std::string& filePath)
{
	if (m_FilePath == filePath)
		return;

	m_ImageLoaded = false;
	m_FilePath = filePath;
}

const std::string& ImageLoader::getFilePath() const
{
	return m_FilePath;
}
