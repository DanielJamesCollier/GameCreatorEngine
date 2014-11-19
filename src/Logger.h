#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <glew.h>

class Logger
{
public:
	Logger();
	~Logger();

	static void infoBlock(std::string block_header, std::string block_info,bool print_to_console);
	static void infoBlock(std::string block_header, std::vector<char> block_info, bool print_to_console);
	static void infoBlock(std::string block_header, std::string block_error_s, std::vector<char> block_info, bool print_to_console);

	static void errorBlock(std::string block_header, std::string block_error, bool print_to_console);
	static void errorBlock(std::string block_header, std::vector<char> block_error, bool print_to_console);
	static void errorBlock(std::string block_header, std::string block_error_s, std::vector<char> block_error, bool print_to_console);
	static void dumpLogsToFile();

private:
	static const std::string currentDateTime();
	static void dumpLogToFile();
	static void dumpErrorLogToFile();

	static std::string _log;
	static std::string _error_log;

};
#endif

