#pragma once

#include "ImageLoader.h"

class ImageLoaderSTBI : public ImageLoader
{
public:

	ImageLoaderSTBI() = default;

	virtual ImageInfo loadFromFile(const std::string& filePath);

};
