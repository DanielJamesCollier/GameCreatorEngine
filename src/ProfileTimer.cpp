#include "ProfileTimer.h"
#include <iostream>
#include <chrono>

ProfileTimer::ProfileTimer()
{
	
}


ProfileTimer::~ProfileTimer()
{
}

void ProfileTimer::begin()
{
	_start = _clock.now();
}

void ProfileTimer::end()
{
	_end = _clock.now();
	_time_span = std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start);
}

void ProfileTimer::displayResult()
{
	std::cout << "Time Taken: " << _time_span.count() << std::endl;
}

int ProfileTimer::getResult()
{
	return 0;
}
