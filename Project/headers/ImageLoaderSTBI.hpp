#pragma once

#include "ImageLoader.hpp"

class ImageLoaderSTBI : public ImageLoader
{
public:

	ImageLoaderSTBI() = default;

	virtual ImageInfo loadFromFile(const std::string& filePath);
	virtual ImageInfo load() const;

	virtual void setFilePath(const std::string& filePath);
	virtual const std::string& getFilePath() const;

private:

	std::string m_FilePath;

};
