/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
	#define PACMAN_HPP_

#include <iostream>
#include <functional>
#include "Graphic.hpp"
#include "game/pacman/Map.hpp"
#include "game/pacman/Player.hpp"
#include "game/pacman/Ghost.hpp"
#include "game/pacman/Timer.hpp"

class Pacman {
public:
	Pacman(Graphic **graphic, const std::string &name);
	~Pacman();
	void			moveGhost();
	std::size_t		start();
	void			move(Timer &playerTimer, Timer &ghostTimer);
	void			displayInfo(Timer const &gameTimer);
	int			verifyWindowSize();
private:
	void			handlerEvent(int key);
	Graphic			**_graphic;
	const std::string   	_name;
	bool			_run;
	Map			*_map;
	Player			*_player;
	std::vector<Ghost *>	_ghost;
	int						_dir;
};

#endif /* !PACMAN_HPP_ */
