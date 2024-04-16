#pragma once

#include <vector>

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
	std::vector<Pixel> image;
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