#include "ImageLoaderSTBI.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

ImageLoaderSTBI::ImageLoaderSTBI()
{
	stbi_set_flip_vertically_on_load(true);
}

ImageInfo ImageLoaderSTBI::loadFromFile(const std::string& filePath)
{
	ImageInfo output;

	Pixel* imageData = (Pixel*) stbi_load(filePath.c_str(), &output.width, &output.height, &output.numChannels, 0);;

	const unsigned int imagePixelNum = output.getPixelNum();

	output.image.assign(imageData, imageData + imagePixelNum);

	stbi_image_free(imageData);

	if (!output.image.data())
		printf("WARNING (ImageLoaderSTBI.hpp): Loading an image (%s) was unsuccessful!", filePath.c_str());

	return output;
}