#include "Image.h"

#include <cassert>

#include "Debug.h"
#include "ImageLoaderSTBI.h"

Image::Image()
{
	m_pImageLoader = new ImageLoaderSTBI();
}

Image::Image(const std::string& filePath)
	:
	m_filePath(filePath),
	m_pImageLoader(new ImageLoaderSTBI())
{
	loadImage();
}

Image::Image(const std::string& filePath, ImageLoader* imageLoader)
	:
	m_filePath(filePath),
	m_pImageLoader(imageLoader)
{
	loadImage();
}

Image::~Image()
{
	if (m_ImageLoaded)
		m_ImageInfo.free();

	if (m_pImageLoader)
		delete m_pImageLoader;
}

void Image::loadImage()
{
	if (!m_ImageLoaded)
	{
		m_ImageInfo.free();
		m_ImageInfo = m_pImageLoader->loadFromFile(m_filePath);

		m_ImageLoaded = (!m_ImageInfo.m_Data) ? false : true;
	}

	if (m_ImageLoaded)
		Debug::printMessage(*this, "Image load success (" + m_filePath + ")!", DebugSeverityLevel::OK);
	else
		Debug::throwException(*this, "Unable to load image (" + m_filePath + ")!");
}

const ImageInfo& Image::getImageInfo() const
{
	return m_ImageInfo;
}

const unsigned char* Image::getImageData() const
{
	return m_ImageInfo.m_Data;
}

void Image::setFilePath(const std::string& filePath)
{
	m_ImageLoaded = false;

	m_filePath.clear();
	m_filePath.append(filePath);
}

const std::string& Image::getFilePath() const
{
	return m_filePath;
}
