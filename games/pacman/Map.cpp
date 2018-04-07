//
// EPITECH PROJECT, 2018
// Map.cpp
// File description:
// Class Map
//

#include <fstream>
#include <iostream>

#include "game/pacman/Map.hpp"

Map::Map(std::string const &fileName, Graphic &graphic) :
	_graphic(graphic)
{
	this->loadMap(fileName);
}

int	Map::loadMap(std::string const &fileName) noexcept
{
	std::fstream	fs(fileName, std::fstream::in);
	std::string	tmp;

	if (!fs.is_open()) {
		std::cout << "Can't open file : " << fileName << std::endl;
		return (1);
	}
	std::cout << "Loading map" << std::endl;
	while (!fs.eof()) {
		std::getline(fs, tmp);
		if (tmp.size() > 0)
			_map.push_back(tmp);
	}
	_width = _map[0].size();
	_height = _map.size();
	_scale = _graphic.getWidth() / GETY(_width);
	if (_graphic.getHeight() / GETY(_height) < _scale)
		_scale = _graphic.getHeight() / GETY(_height);
	return (0);
}

std::map<char, std::size_t>	Map::getPlayerPos(void) const
{
	std::map<char, std::size_t>	pos;

	pos['y'] = 0;
	pos['x'] = 0;
	for (size_t i = 0; i < _map.size(); i++) {
		for (size_t j = 0; j < _map[i].size(); ++j) {
			if (_map[i][j] == 'p') {
				pos['x'] = j;
				pos['y'] = i;
			}
		}
	}
	return (pos);
}

std::vector<std::map<char, std::size_t>>	Map::getGhostPos(void) const
{
	std::vector<std::map<char, std::size_t>>	pos;
	std::map<char, std::size_t>			tmp;

	for (size_t i = 0; i < _map.size(); ++i) {
		for (size_t j = 0; j < _map[i].size(); ++j) {
			if (_map[i][j] == 'g') {
				tmp['x'] = j;
				tmp['y'] = i;
				pos.push_back(tmp);
			}
		}
	}
	return (pos);
}

std::vector<std::string>	*Map::getMap()
{
	return (&_map);
}

std::size_t const	Map::getScale() const noexcept
{
	return (_scale);
}

void	Map::display(void)
{
	std::size_t	mid = (_graphic.getWidth() - GETY(_map[0].size()) * _scale) / 2;
	std::size_t	offset = (GETY(1) - GETX(1)) / 2;

	for (size_t i = 0; i < _map.size(); i++) {
		for (size_t j = 0; j < _map[i].size(); ++j) {
			switch (_map[i][j]) {
			case '#':
				_graphic.drawSquare(std::make_pair(mid + GETY(j) * _scale, GETY(i) * _scale), std::make_pair(GETY(_scale), GETY(_scale)), Graphic::Color::BLUE);
				break;
			case 'p':
				_graphic.drawSquare(std::make_pair(mid + GETY(j) * _scale, GETY(i) * _scale), std::make_pair(GETY(_scale), GETY(_scale)), Graphic::Color::YELLOW);
				break;
			case 'g':
				_graphic.drawSquare(std::make_pair(mid + GETY(j) * _scale, GETY(i) * _scale), std::make_pair(GETY(_scale), GETY(_scale)), Graphic::Color::GREEN);
				break;
			case '.':
				_graphic.drawSquare(std::make_pair(mid + (offset + GETY(j)) * _scale, (offset + GETY(i)) * _scale), std::make_pair(GETX(_scale), GETX(_scale)), Graphic::Color::RED);
				break;
			case 'O':
				_graphic.drawSquare(std::make_pair(mid + GETY(j) * _scale, GETY(i) * _scale), std::make_pair(GETY(_scale), GETY(_scale)), Graphic::Color::WHITE);
				break;
			}
		}
	}
}
