#pragma once
#ifndef PROFILETIMER_H
#define PROFILETIMER_H

#include <time.h>
#include <chrono>

class ProfileTimer
{
public:
	ProfileTimer();
	~ProfileTimer();

	void begin();
	void end();

	void displayResult();
	int  getResult();

private:
	std::chrono::high_resolution_clock    _clock;
	std::chrono::system_clock::time_point _start;
	std::chrono::system_clock::time_point _end;
	std::chrono::duration<double>         _time_span;
};
#endif

