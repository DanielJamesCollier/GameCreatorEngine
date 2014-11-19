#include "ImageLoader.h"
#include "stb_image.h"
#include "Logger.h"
#include "PicoPNG.h"
#include "IOManager.h"
#include "cout.h"

ImageLoader::ImageLoader()
{

}

ImageLoader::~ImageLoader()
{

}

GLTexture* ImageLoader::loadTexture(std::string file_path, unsigned int texture_type, bool &found)
{
	GLTexture* texture = new GLTexture();

	int width, height, numComponents;
	unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &numComponents, 4);

	// check if the data has been found
	if (data == NULL)
	{
		Logger::errorBlock("Texture not Found", "File Path: " + file_path, true);
		found = false;
	}
	else
	{
		Logger::infoBlock("Texure loaded with sbi_image", "File path: " + file_path + "\nwidth: " + std::to_string(width) + "\nheight: " + std::to_string(height), true);
		found = true;
	}

	glGenTextures(1, &texture->texture_id);
	glBindTexture(texture_type, texture->texture_id);

	// sent the image to the gpu
	glTexImage2D(texture_type, 0, GL_RGBA, width, height, 0.1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// if the mesh is bigger than the texture the texture will wrap
	glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	// unbind the texture and free data
	glBindTexture(texture_type, 0);
	stbi_image_free(data);

	//apply the loaded settins to the GLtexture
	texture->width = width;
	texture->height = height;
	texture->texture_type = texture_type;

	

	return texture;
}

GLTexture* ImageLoader::loadPNGTexture(std::string file_path, bool &found)
{

	GLTexture* texture = new GLTexture();

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long width, height;

	if (IOManager::readFileToBuffer(file_path, in) == false)
	{
		Logger::errorBlock("Texture not Found", "File Path: " + file_path, true);
	}

	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

	if (errorCode != 0)
	{
		Logger::errorBlock("PNG Decode Failed", "picoPng error code: " + std::to_string(errorCode), true);
		found = false;
	}
	else
	{
		Logger::infoBlock("Texure loaded with picoPNG", "File path: " + file_path + "\nwidth: " + std::to_string(width) + "\nheight: " + std::to_string(height), true);
		found = true;
	}

	glGenTextures(1, &texture->texture_id);
	glBindTexture(GL_TEXTURE_2D, texture->texture_id);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	// if the mesh is bigger than the texture the texture will wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	texture->texture_type = GL_TEXTURE_2D;
	texture->width = width;
	texture->height = height;

	return texture;
}