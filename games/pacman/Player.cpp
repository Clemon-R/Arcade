//
// EPITECH PROJECT, 2018
// Player.cpp
// File description:
// Payer Class functions
//

#include "game/pacman/Player.hpp"
#include "Control.hpp"

Player::Player(std::size_t x, std::size_t y, std::vector<std::string> *map) :
	_x(x),
	_y(y),
	_map(map),
	_dead(false),
	_score(0)
{
}

int	Player::checkValidMove(int const x, int const y)
{
	if (x < _map[0][0].size() && y < _map->size() && _map[0][y][x] != '#')
		return (0);
	return (1);
}

void	Player::move(int const x, int const y)
{
	if (_map[0][y][x] == 'g')
		_dead = true;
	if (_map[0][y][x] == '.')
		_score += 20;
	_map[0][_y][_x] = ' ';
	_map[0][y][x] = 'p';
	_y = y;
	_x = x;
}

void	Player::move(int key)
{
	switch (key) {
	case Control::UP:
		if (!checkValidMove(_x, _y - 1))
			move(_x, _y - 1);
		break;
	case Control::DOWN:
		if (!checkValidMove(_x, _y + 1))
			move(_x, _y + 1);
		break;
	case Control::LEFT:
		if (!checkValidMove(_x - 1, _y))
			move(_x - 1, _y);
		break;
	case Control::RIGHT:
		if (!checkValidMove(_x + 1, _y))
			move(_x + 1, _y);
		break;
	}
}

bool const	Player::getDead() const
{
	return (_dead);
}

void	Player::setDead(bool dead)
{
	_dead = dead;
}

std::size_t const	Player::getScore() const
{
	return (_score);
}
