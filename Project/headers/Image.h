#pragma once

#include <string>
#include <vector>
#include <cstdlib>

class ImageLoader;

struct Pixel
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

struct PixelFloat
{
	float R;
	float G;
	float B;
};

struct ImageInfo
{
	std::vector<Pixel> data;
	// unsigned char* m_Data = nullptr;
	int width = -1;
	int height = -1;
	int numChannels = -1;

	int getDataSize() const 
	{
		return width * height * numChannels;
	}

	int getPixelNum() const
	{
		return width * height;
	}

	void free()
	{
	}
};

class Image
{
public:

	Image();
	Image(const std::string& filePath);
	Image(const std::string& filePath, ImageLoader* imageLoader);

	~Image();

	void loadImage();

	const ImageInfo& getImageInfo() const;
	const std::vector<Pixel>& getImageData() const;

	void convertToGrayscale();
	std::vector<PixelFloat> createNormalized01() const; // normalizes image data from 0-255 to 0.0-1.0

	void setFilePath(const std::string& filePath);
	const std::string& getFilePath() const;

private:

	/*
	* 
	* Image is in stored in the following format:
	* 				
	* 			Width of the image
	___________________________________________

	R G B R G B R G B ... ... ... ... ... R G B		|
	R G B R G B R G B ... ... ... ... ... R G B		| 
	R G B R G B R G B ... ... ... ... ... R G B		|	Height of the
	R G B R G B R G B ... ... ... ... ... R G B		|		image
	R G B R G B R G B ... ... ... ... ... R G B		|
	R G B R G B R G B ... ... ... ... ... R G B		|

	-------------------------------------------
	* 
	* Each letter is an unsigned char value defining a value for one channel of the pixel it belongs to
	* (I will probably create a Array2D to store this in a more understandable way)
	*
	*/

	std::string m_filePath;

	ImageLoader* m_pImageLoader = nullptr;
	ImageInfo m_ImageInfo;
	bool m_ImageLoaded = false;

};