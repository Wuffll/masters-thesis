#pragma once

#include "ImageLoader.h"

class ImageLoaderSTBI : public ImageLoader
{
public:

	ImageLoaderSTBI();

	virtual ImageInfo loadFromFile(const std::string& filePath);

};
