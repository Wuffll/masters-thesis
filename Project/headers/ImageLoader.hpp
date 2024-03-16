#pragma once

#include <string>

#include "Image.hpp"

class ImageLoader
{
public:

	virtual ImageInfo loadFromFile(const std::string& filePath) = 0;

};