//
// EPITECH PROJECT, 2018
// Ghost.cpp
// File description:
// Ghost Class functions
//

#include "game/pacman/Ghost.hpp"
#include "game/pacman/Map.hpp"

Ghost::Ghost(std::size_t x, std::size_t y, std::vector<std::string> *map,
Player *player) :
	_x(x),
	_y(y),
	_map(map),
	_player(player),
	_lastCase(' ')
{
}

int	Ghost::checkValidMove(int const x, int const y)
{
	if (x < _map[0][0].size() && y < _map->size() && _map[0][y][x] != '#'
	&& _map[0][y][x] != 'g')
		return (0);
	return (1);
}

void	Ghost::move(int const x, int const y)
{
	char	tmp;

	if (_map[0][y][x] == 'p')
		_player->setDead(true);
	_map[0][_y][_x] = _lastCase;
	_lastCase = _map[0][y][x];
	_map[0][y][x] = 'g';
	_y = y;
	_x = x;
}

void	Ghost::moveOnTarget(int const diff_x, int const diff_y)
{
	int	x = _x + DIRECTION(diff_x);
	int	y = _y + DIRECTION(diff_y);

	if (std::abs(diff_x) > std::abs(diff_y) && !checkValidMove(x, _y))
		move(x, _y);
	else if (!checkValidMove(_x, y))
		move(_x, y);
	else {
		x = _x + DIRECTION(-diff_x);
		y = _y + DIRECTION(-diff_y);
		if (!checkValidMove(x, _y))
			move(x, _y);
		else if (!checkValidMove(_x, y))
			move(_x, y);
	}
}

void	Ghost::move()
{
	for (size_t i = 0; i < _map[0].size(); i++) {
		for (size_t j = 0; j < _map[0][0].size(); ++j) {
			if (_map[0][i][j] == 'p') {
				moveOnTarget(j - _x, i - _y);
				break;
			}
		}
	}
}
