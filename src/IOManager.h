#pragma once
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>

class IOManager
{
public:
	IOManager();
	~IOManager();

	static std::string loadTextFile(const std::string& path);
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

private:

};
#endif

