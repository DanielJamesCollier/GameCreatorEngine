#include <fstream>

#include "IOManager.h"
#include "Logger.h"
#include "Shader.h"


IOManager::IOManager()
{
}


IOManager::~IOManager()
{
}

std::string IOManager::loadTextFile(const std::string& path)
{
	std::string file_text;
	std::ifstream input_file;

	input_file.open(path);

	if (input_file.is_open())
	{
		std::string line = "";
		while (getline(input_file, line))
		{
			file_text += line + "\n";			
		}
	}
	else
	{
		Logger::errorBlock("The File Could Not Be Open", "File name: " + path,true);
	}

	input_file.close();

	return file_text;
}

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	//seek to the end
	file.seekg(0, std::ios::end);

	//Get the file size
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	//Reduce the file size by any header bytes that might be present
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	return true;
}
