/*
 ** EPITECH PROJECT, 2018
 ** arcade
 ** File description:
 ** Pacman
 */

#include <memory>
#include <unistd.h>
#include "game/pacman/Pacman.hpp"
#include "Control.hpp"

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

void	Pacman::move(Timer &playerTimer, Timer &ghostTimer)
{
	if (playerTimer.getTimeMS() >= 300) {
		_player->move(_dir);
		playerTimer.restart();
	}
	if ((_player->getKiller() && ghostTimer.getTimeMS() >= 700) ||
	ghostTimer.getTimeMS() >= 500) {
		this->moveGhost();
		ghostTimer.restart();
	}
}

void	Pacman::displayInfo(Timer const &gameTimer)
{
	(*_graphic)->print(std::make_pair(0, 0)
	    , "Score : " + std::to_string(_player->getScore()));
	(*_graphic)->print(std::make_pair(0, 15),
	"Time : " + std::to_string(
	(gameTimer.getTimeMS() + 500.0) / 1000.0));
}

int	Pacman::verifyWindowSize()
{
	if (_map->getScale() <= 0){
		(*_graphic)->clear();
		(*_graphic)->print(std::make_pair(0, 0),
		"Fenetre trop petite pour afficher le jeu");
		(*_graphic)->refresh();
		return (1);
	}
	return (0);
}

std::size_t	Pacman::start()
{
	std::function<void (int)>   handler =
	std::bind(&Pacman::handlerEvent, this, std::placeholders::_1);
	Timer	playerTimer;
	Timer	ghostTimer;
	Timer	gameTimer;

	(*_graphic)->setEventHandler(handler);
	while (*_graphic && (*_graphic)->isOpen() && _run &&
	!_player->getDead() && _map->countPacgums() > 0) {
		if (this->verifyWindowSize())
			continue;
		(*_graphic)->clear();
		_map->display();
		this->move(playerTimer, ghostTimer);
		this->displayInfo(gameTimer);
		(*_graphic)->refresh();
		usleep(100);
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
		if (!_player->tryMove(key))
			_dir = key;
		break;
	}
}

extern "C" std::size_t start(Graphic **graphic, const std::string &name)
{
	std::unique_ptr<Pacman>  own = std::make_unique<Pacman>(graphic, name);

	return (own->start());
}
