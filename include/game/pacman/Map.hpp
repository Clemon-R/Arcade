//
// EPITECH PROJECT, 2018
// Map.hpp
// File description:
// Class Map Header
//

#ifndef MAP_HPP
# define MAP_HPP

#include <string>
#include <vector>
#include <map>

#include "Graphic.hpp"

#ifdef GETY
# undef GETY
#endif
#ifdef GETX
# undef GETX
#endif
#define GETY(y)	(_graphic.getCharSize(1) * (y))
#define GETX(x)	(_graphic.getCharSize(0) * (x))

class Map
{
public:
	Map(std::string const &fileName, Graphic &graphic);
	int			loadMap(std::string const &fileName) noexcept;
	std::size_t const	getScale() const noexcept;
	void			display();
	std::map<char, std::size_t>	getPlayerPos(void) const;
	std::vector<std::string>	*getMap(void);
	std::vector<std::map<char, std::size_t>>	getGhostPos(void) const;
	std::size_t const	countPacgums() const;
private:
	std::vector<std::string>	_map;
	Graphic				&_graphic;
	std::size_t			_width;
	std::size_t			_height;
	std::size_t			_scale;
};

#endif /* !MAP_HPP */
