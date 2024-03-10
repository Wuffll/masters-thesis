#pragma once

#include <string>

#include "Image.hpp"

class ImageLoader
{
public:

	virtual ImageInfo loadFromFile(const std::string& filePath) = 0;
	virtual ImageInfo load() const = 0; // for when the file path is set

	virtual void setFilePath(const std::string& filePath) = 0;
	virtual const std::string& getFilePath() const = 0;

};