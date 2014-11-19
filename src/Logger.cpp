#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Logger.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

std::string Logger::_log = "";
std::string Logger::_error_log = "";

Logger::Logger()
{
	
}

Logger::~Logger()
{
	
}

void Logger::infoBlock(std::string block_header, std::string block_info,bool print_to_console)
{
	std::string _block = "";

	_block = "\n\n\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
		+ block_header + " *\n"
		+ "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n"
		+ block_info
		+ "\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

	Logger::_log += _block;

	if (print_to_console) std::cout << _block;
}

void Logger::infoBlock(std::string block_header, std::vector<char> block_info, bool print_to_console)
{
	std::string _block = "";

	_block = "\n\n\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n* "
		+ block_header + " *\n"
		+ "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";

	for (unsigned int i = 0; i < block_info.size(); i++)
	{
		_block += block_info[i];
	}
	
	_block += "\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

	Logger::_log += _block;

	if (print_to_console) std::cout << _block;
}

void Logger::infoBlock(std::string block_header, std::string block_info_s, std::vector<char> block_info, bool print_to_console)
{
	std::string _block = "";

	_block = "\n\n\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n* "
		+ block_header + " *\n"
		+ "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";

	_block += block_info_s + "\n";

	for (unsigned int i = 0; i < block_info.size(); i++)
	{
		_block += block_info[i];
	}

	_block += "\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

	Logger::_log += _block;

	if (print_to_console) std::cout << _block;
}

void Logger::errorBlock(std::string block_header, std::string block_error, bool print_to_console)
{
	std::string _block = "";

	_block = "\n\n\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n* "
		+ block_header + " *\n"
		+ "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n"
		+ block_error
		+ "\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

	Logger::_error_log += _block;

	if (print_to_console) std::cout << _block;
}

void Logger::errorBlock(std::string block_header, std::vector<char> block_error, bool print_to_console)
{
	std::string _block = "";

	_block = "\n\n\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n* "
		+ block_header + " *\n"
		+ "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";

	for (unsigned int i = 0; i < block_error.size(); i++)
	{
		_block += block_error[i];
	}

	_block += "\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

	Logger::_error_log += _block;

	if (print_to_console) std::cout << _block;
}

void Logger::errorBlock(std::string block_header, std::string block_error_s, std::vector<char> block_error, bool print_to_console)
{
	std::string _block = "";

	_block = "\n\n\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n* "
		+ block_header + " *\n"
		+ "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";

	_block += block_error_s + "\n";

	for (unsigned int i = 0; i < block_error.size(); i++)
	{
		_block += block_error[i];
	}

	_block += "\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";

	Logger::_error_log += _block;

	if (print_to_console) std::cout << _block;
}

 const std::string Logger::currentDateTime()
{
	 time_t rawtime;
	 struct tm * timeinfo;
	 char buffer[80];

	 time(&rawtime);
	 timeinfo = localtime(&rawtime);

	 strftime(buffer, 80, "date - [%d-%m-%Y] time - [%I-%M-%S]", timeinfo);
	 std::string str(buffer);

	return buffer;
}

void Logger::dumpLogsToFile()
{
	dumpLogToFile();
	dumpErrorLogToFile();
}

void Logger::dumpLogToFile()
{
	std::ofstream output_file;

	std::string file_name = "[LOG] " + currentDateTime() + ".txt";

	output_file.open("Logs/" + file_name);

	if (output_file.fail()) Logger::errorBlock("File failed to open", file_name, true);

	output_file << _log;
	output_file.close();
}

void Logger::dumpErrorLogToFile()
{
	std::ofstream output_file;

	std::string file_name = "[ERROR_LOG] " + currentDateTime() + ".txt";

	output_file.open("Logs/" + file_name);

	if (output_file.fail()) Logger::errorBlock("File failed to open", file_name, true);

	output_file << _error_log;
	output_file.close();
}