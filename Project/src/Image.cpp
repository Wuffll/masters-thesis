#include "Image.hpp"

#include <cassert>

#include "ImageLoaderSTBI.hpp"

Image::Image()
{
	m_pImageLoader = new ImageLoaderSTBI();
}

Image::Image(const std::string& filePath)
{
	m_pImageLoader = new ImageLoaderSTBI();
	
	m_pImageLoader->setFilePath(filePath.c_str());
}

Image::Image(const std::string& filePath, ImageLoader* imageLoader)
	:
	m_pImageLoader(imageLoader)
{
	m_pImageLoader->setFilePath(filePath.c_str());
}

Image::~Image()
{
	if (m_ImageLoaded)
		m_ImageInfo.free();

	if (m_pImageLoader)
		delete m_pImageLoader;
}

ImageInfo Image::GetImage()
{
	if (!m_ImageLoaded)
	{
		m_ImageInfo.free();
		m_ImageInfo = m_pImageLoader->load();

		m_ImageLoaded = (!m_ImageInfo.m_Data) ? false : true;
	}

	assert(m_ImageLoaded && "Image not loaded!");

	return m_ImageInfo;
}

void Image::setFilePath(const std::string& filePath)
{
	m_ImageLoaded = false;
	m_pImageLoader->setFilePath(filePath.c_str());
}

const std::string& Image::getFilePath() const
{
	return m_pImageLoader->getFilePath();
}
