//
// EPITECH PROJECT, 2018
// Ghost.hpp
// File description:
// Ghost Class Header
//

#ifndef GHOST_HPP
# define GHOST_HPP

#include <string>
#include <vector>

#include "game/pacman/Player.hpp"

#define DIRECTION(val)	(val < 0 ? -1 : 1)

class Ghost
{
public:
	Ghost(std::size_t x, std::size_t y, std::vector<std::string> *map,
	Player *player);
	void	move();
	void	move(int const x, int const y);
	void	moveOnTarget(int const diff_x, int const diff_y);
	int	checkValidMove(int const x, int const y);
private:
	std::size_t			_x;
	std::size_t			_y;
	std::vector<std::string>	*_map;
	Player				*_player;
	char				_lastCase;
	bool				_dead;
};

#endif /* !GHOST_HPP */
