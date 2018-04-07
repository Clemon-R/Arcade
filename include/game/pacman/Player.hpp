//
// EPITECH PROJECT, 2018
// Player.hpp
// File description:
// Player Class Header
//

#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <string>
#include <vector>
#include "game/pacman/Map.hpp"
#include "game/pacman/Timer.hpp"

class Player
{
public:
	Player(std::size_t x, std::size_t y, std::vector<std::string> *map);
	void			move(int key);
	int			tryMove(int key);
	void			move(int const x, int const y);
	int			checkValidMove(int const x, int const y);
	bool const		getDead() const;
	void			setDead(bool dead);
	bool const		getKiller() const;
	void			setKiller(bool killer);
	std::size_t const	getScore() const;
	void			setScore(std::size_t score);
private:
	std::size_t			_x;
	std::size_t			_y;
	std::vector<std::string>	*_map;
	bool				_dead;
	std::size_t			_score;
	bool				_killer;
	Timer				_pacgumTimer;
};

#endif /* !PLAYER_HPP */
