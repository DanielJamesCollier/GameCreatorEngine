#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

static std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

static bool doesFileExist(const std::string& file_name)
{
	std::ifstream f(file_name.c_str());
	if (f.good()) {
		f.close();
		return true;
	}
	else {
		f.close();
		return false;
	}
}

static std::string loadFileText(const std::string& file_path)
{
	std::string source;

	std::ifstream file(file_path);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			source += line + "\n";
		}
		file.close();
	}
	return source;
}

#endif