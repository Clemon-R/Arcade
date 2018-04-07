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

class Player
{
public:
	Player(std::size_t x, std::size_t y, std::vector<std::string> *map);
	void			move(int key);
	void			move(int const x, int const y);
	int			checkValidMove(int const x, int const y);
	bool const		getDead() const;
	void			setDead(bool dead);
	std::size_t const	getScore() const;
private:
	std::size_t			_x;
	std::size_t			_y;
	std::vector<std::string>	*_map;
	bool				_dead;
	std::size_t			_score;
};

#endif /* !PLAYER_HPP */
