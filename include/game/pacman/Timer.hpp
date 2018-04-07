//
// EPITECH PROJECT, 2018
// Timer.hpp
// File description:
// Timer Class Header
//

#ifndef TIMER_HPP
# define TIMER_HPP

#include <chrono>

class Timer
{
public:
	Timer();
	void	restart();
	int	getTimeMS() const;
	int	getTimeS() const;
private:
	std::chrono::time_point<std::chrono::system_clock>	_start;
};

#endif /* !TIMER_HPP */
