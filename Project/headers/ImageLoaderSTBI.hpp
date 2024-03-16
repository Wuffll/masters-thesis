#pragma once

#include "ImageLoader.hpp"

class ImageLoaderSTBI : public ImageLoader
{
public:

	ImageLoaderSTBI() = default;

	virtual ImageInfo loadFromFile(const std::string& filePath);

};
