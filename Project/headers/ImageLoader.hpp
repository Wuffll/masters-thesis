#include <string>
#include <vector>

class ImageLoader
{
public:

	ImageLoader();
	ImageLoader(const std::string& filePath);

	void LoadImage();

	const unsigned char& const GetImage();

	void setFilePath(const std::string& filePath);
	const std::string& getFilePath() const;

private:

	/*
	* 
	* Image is in stored in the following format:
	* 				
	* 			Width of the image
	___________________________________________

	R G B R G B R G B ... ... ... ... ... R G B		|
	R G B R G B R G B ... ... ... ... ... R G B		| 
	R G B R G B R G B ... ... ... ... ... R G B		|	Height of the
	R G B R G B R G B ... ... ... ... ... R G B		|		image
	R G B R G B R G B ... ... ... ... ... R G B		|
	R G B R G B R G B ... ... ... ... ... R G B		|

	-------------------------------------------
	* 
	* Each letter is an unsigned char value defining a value for one channel of the pixel it belongs to
	* (I will probably create a Array2D to store this in a more understandable way)
	*
	*/


	std::string m_FilePath;
	unsigned char* m_pImage = nullptr;
	bool m_ImageLoaded = false;

	int m_Width = 0;
	int m_Height = 0;

};