#include "ImageLoaderSTBI.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

ImageInfo ImageLoaderSTBI::loadFromFile(const std::string& filePath)
{
	ImageInfo output;

	int comp;
	output.m_Data = stbi_load(filePath.c_str(), &output.m_Width, &output.m_Height, &comp, 1);

	if (!output.m_Data)
		printf("WARNING (ImageLoaderSTBI.hpp): Loading an image (%s) was unsuccessful!", filePath.c_str());

	return output;
}