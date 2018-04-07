//
// EPITECH PROJECT, 2018
// Timer.cpp
// File description:
// Timer Class Functions
//

#include "game/pacman/Timer.hpp"

Timer::Timer() :
	_start(std::chrono::system_clock::now())
{
}

void	Timer::restart()
{
	_start = std::chrono::system_clock::now();
}

int	Timer::getTimeMS() const
{
	std::chrono::time_point<std::chrono::system_clock>	current;

	current = std::chrono::system_clock::now();
	return (std::chrono::duration_cast<std::chrono::milliseconds>
	(current - _start).count());
}

int	Timer::getTimeS() const
{
	std::chrono::time_point<std::chrono::system_clock>	current;

	current = std::chrono::system_clock::now();
	return (std::chrono::duration_cast<std::chrono::seconds>
	(current - _start).count());
}
