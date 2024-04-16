#pragma once

#include <string>

#include "ImageInfo.h"

class ImageLoader
{
public:

	virtual ImageInfo loadFromFile(const std::string& filePath) = 0;

};