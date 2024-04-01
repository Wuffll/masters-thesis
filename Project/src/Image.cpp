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

		m_ImageLoaded = (!m_ImageInfo.data.data()) ? false : true;
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

const std::vector<Pixel>& Image::getImageData() const
{
	return m_ImageInfo.data;
}

void Image::convertToGrayscale()
{
	unsigned char calculatedColor = 0;
	for (int i = 0; i < m_ImageInfo.getPixelNum(); i++)
	{
		calculatedColor = (m_ImageInfo.data[i].R + m_ImageInfo.data[i].G + m_ImageInfo.data[i].B) / 3;
		m_ImageInfo.data[i].R = calculatedColor;
		m_ImageInfo.data[i].G = calculatedColor;
		m_ImageInfo.data[i].B = calculatedColor;
	}
}

std::vector<PixelFloat> Image::createNormalized01() const
{
	std::vector<PixelFloat> outputVector{};
	outputVector.reserve(m_ImageInfo.getDataSize());

	for (int i = 0; i < m_ImageInfo.getPixelNum(); i++)
	{
		PixelFloat pixel;
		pixel.R = (float)m_ImageInfo.data[i].R / 255.0f;
		pixel.G = (float)m_ImageInfo.data[i].G / 255.0f;
		pixel.B = (float)m_ImageInfo.data[i].B / 255.0f;

		outputVector.push_back(pixel);
	}

	return outputVector;
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
