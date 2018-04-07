/*
 ** EPITECH PROJECT, 2018
 ** arcade
 ** File description:
 ** Pacman
 */

#include "game/pacman/Pacman.hpp"
#include "Control.hpp"
#include <memory>
#include <unistd.h>
#include <ctime>
#include <sys/timeb.h>

static int  getMilliseconds()
{
    timeb   tb;

    ftime(&tb);
    return (tb.millitm + (tb.time & 0xfffff) * 1000);
}

Pacman::Pacman(Graphic **graphic, const std::string &name) :
	_graphic(graphic),	
	_name(name),
	_run(true),
	_dir(-1)
{
	std::map<char, std::size_t>			playerPos;
	std::vector<std::map<char, std::size_t>>	ghostPos;
	
	_map = new Map("./games/pacman/map/original.map", **_graphic);
	playerPos = _map->getPlayerPos();
	_player = new Player(playerPos['x'], playerPos['y'], _map->getMap());
	ghostPos = _map->getGhostPos();
	for (std::size_t i = 0; i < ghostPos.size(); ++i) {
		_ghost.push_back(new Ghost(ghostPos[i]['x'],
		ghostPos[i]['y'], _map->getMap(), _player));
	}
}

Pacman::~Pacman()
{
	delete _map;
	for (auto it : _ghost)
		delete it;
	delete _player;
}

void	Pacman::moveGhost()
{
	for (auto it : _ghost)
		it->move();
}

std::size_t	Pacman::start()
{
	std::function<void (int)>   handler =
	std::bind(&Pacman::handlerEvent, this, std::placeholders::_1);
	std::size_t	next = getMilliseconds() + 500;
	bool	move = true;

	(*_graphic)->setEventHandler(handler);
	while (*_graphic && (*_graphic)->isOpen() && _run &&
	!_player->getDead()) {
		if (next > getMilliseconds())
			continue;
		else if (_map->getScale() <= 0){
			(*_graphic)->clear();
			(*_graphic)->print(std::make_pair(0, 0), "Fenetre trop petite pour afficher le jeu");
			(*_graphic)->refresh();
			continue;
		}
		if (move)
			this->moveGhost();
		move = !move;
		_player->move(_dir);
		(*_graphic)->clear();
		_map->display();
		(*_graphic)->print(std::make_pair(0, 0)
                    , "Score : " + std::to_string(_player->getScore()));
		(*_graphic)->refresh();
		next = getMilliseconds() + 100;
	}
	(*_graphic)->setEventHandler(nullptr);
	return (_player->getScore());
}

void    Pacman::handlerEvent(int key)
{
	switch (key) {
		case Control::BACKSPACE:
			_run = false;
			break;
		case Control::UP:
		case Control::DOWN:
		case Control::LEFT:
		case Control::RIGHT:
			_dir = key;
			break;
	}
}

extern "C" std::size_t start(Graphic **graphic, const std::string &name)
{
	std::unique_ptr<Pacman>  own = std::make_unique<Pacman>(graphic, name);

	return (own->start());
}
