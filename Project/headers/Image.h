#pragma once

#include <string>
#include <vector>

class ImageLoader;

struct ImageInfo
{
	unsigned char* m_Data = nullptr;
	int m_Width = -1;
	int m_Height = -1;

	void free() 
	{ 
		if (m_Data)
		{
			delete m_Data;
		}
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
	const unsigned char* getImageData() const;

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