#pragma once

#include <string>

#include "Image.h"

class ImageLoader
{
public:

	virtual ImageInfo loadFromFile(const std::string& filePath) = 0;

};