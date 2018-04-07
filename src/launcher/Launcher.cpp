/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** Launcher
*/

#include "Launcher.hpp"
#include "Exception.hpp"
#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <algorithm>

Launcher::Launcher(std::string &lib) : _graphic(nullptr), _dll(nullptr)
                                    , _change(false), _currentGraph(-1)
                                    , _name("inconnue")
{
    std::get<0>(_pos) = 0;
    std::get<1>(_pos) = 1;
    std::cout << "Launcher: init of the launcher...\n";
	if (lib.size() == 0)
		return;
	loadGraphicLib(lib);
    if (!_graphic)
        return;
}

void	Launcher::start()
{
    loadLibsGraphic();
    loadLibsGames();
	loadScores();
    run();
}

void    Launcher::run()
{
    std::function<void (int)>   handler = std::bind(&Launcher::handlerEvent
                                                , this
                                                , std::placeholders::_1);

    _graphic->openWindow();
    _graphic->setEventHandler(handler);
    while (_graphic != nullptr && _graphic->isOpen()){
        _graphic->clear();
		_panel.clear();
        printMenuGraphic();
        printMenuGames();
        printUsage();
        printScore();
        printInputName();
        _graphic->refresh();
        if (_change && std::get<0>(_pos) >= 0)
            eventSelect();
    }
}

void    Launcher::eventSelect()
{
    std::function<void (int)>   handler = std::bind(&Launcher::handlerEvent
                                                , this, std::placeholders::_1);
    std::list<std::string>::iterator    graph = _libs.begin();
    std::list<std::string>::iterator    games = _games.begin();

    if (std::get<0>(_pos) == 1){
        std::advance(games, std::get<1>(_pos) - 1);
        loadGameLib(std::string("./games/").append(*games));
    }
    else if (_change && std::get<0>(_pos) == 0 
            && _currentGraph != std::get<1>(_pos)){
        std::advance(graph, std::get<1>(_pos) - 1);
        _currentGraph = std::get<1>(_pos);
        loadGraphicLib(std::string("./lib/").append(*graph));
        _graphic->openWindow();
    }
    _graphic->setEventHandler(handler);
    _change = false;
}

Launcher::~Launcher()
{
	std::vector<std::pair<std::string, std::size_t>>::iterator	it = _scores.begin();
	std::ofstream	file("scores", std::ios::out | std::ios::trunc);

    if (_graphic)
        delete _graphic;
    if (_dll)
        dlclose(_dll);
	if (file.is_open()){
		for (int i = 0;i < 10 && it != _scores.end();it++,i++){
			file << it->first.append(":")
							.append(std::to_string(it->second))
							.append("\n");
		}
		file.close();
	}
}

static bool	comparePair(const std::pair<std::string, std::size_t> &v1, const std::pair<std::string, std::size_t> &v2)
{
	return (std::get<1>(v1) > std::get<1>(v2));
}

void    Launcher::loadGameLib(std::string &lib)
{
    void    *dll;
    createGame  func;

    if (lib.at(0) != '.' && lib.at(0) != '/')
        lib = "./" + lib;
    dll = dlopen(lib.c_str(), RTLD_LAZY);
    if (!dll)
        throw Exception("Impossible to load the game library");
    func = (createGame)dlsym(dll, "start");
    if (!func)
        throw Exception("Impossible to find the \"start\" function");
    _scores.push_back(std::make_pair(_name, func(&_graphic, _name)));
	std::sort(_scores.begin(), _scores.end(), comparePair);
    dlclose(dll);
}

void    Launcher::loadGraphicLib(std::string &lib)
{
    createFunction func = nullptr;
    void    *dll = nullptr;
    
    if (_graphic)
        delete _graphic;
    if (_dll)
        dlclose(_dll);
    if (lib.at(0) != '.' && lib.at(0) != '/')
        lib = "./" + lib;
    dll = dlopen(lib.c_str(), RTLD_LAZY);
    if (!dll)
        throw Exception("Lib graphic not found");
    func = (createFunction)dlsym(dll, "createGraphic");
    if (!func)
        throw Exception("Fonction \"createGraphic\" not found");
    _dll = dll;
    _graphic = func();
}

void	Launcher::loadScores()
{
	std::ifstream	file("./scores");
	std::string		line;
	int				pos;

	if (!file.is_open())
		return;
	while (getline(file, line)){
		if ((pos = line.find(':')) == std::string::npos)
			continue;
		_scores.push_back(std::make_pair(line.substr(0, pos)
						, std::stoi(line.substr(pos + 1))));
	}
	std::sort(_scores.begin(), _scores.end(), comparePair);
	file.close();
}

void    Launcher::handlerEvent(int key)
{
    _graphic->print(std::make_pair(0, 0), std::to_string(key));
    if (std::get<0>(_pos) == -1 && _change){
        if (key == Control::BACKSPACE)
            _name = _name.substr(0, _name.size() - 1);
        else if (key != Control::ENTER)
            _name = _name + static_cast<char>(key);
        _change = key != Control::ENTER;
        return;
    }
    switch (key){
        case Control::UP:
            if (std::get<1>(_pos) > 1)
                std::get<1>(_pos) -= 1;
            break;
        case Control::DOWN:
            if (std::get<0>(_pos) == 0 && std::get<1>(_pos) < _libs.size())
                std::get<1>(_pos) += 1;
            else if (std::get<0>(_pos) == 1 && std::get<1>(_pos) < _games.size())
                std::get<1>(_pos) += 1;
            break;
        case Control::RIGHT:
        case Control::LEFT:
            if (key == Control::LEFT && std::get<0>(_pos) > -1)
                std::get<0>(_pos) -= 1;
            else if (key == Control::RIGHT && std::get<0>(_pos) < 1)
                std::get<0>(_pos) += 1;
            std::get<1>(_pos) = 1;
        break;
        case Control::ENTER:
            _change = true;
        break;
    }
}

void    Launcher::printMenuGraphic()
{
    int i = 1;
    std::size_t size = GETX(33);
    std::size_t start = _graphic->getWidth() / 2 - size + 1;
    std::list<std::string>::iterator    it;
	Vector2i	pos = std::make_pair(start - 1, 0);
	Vector2i	sizem = std::make_pair(size, GETY(1 + _libs.size()) + 2);

	adjustPosMenu(pos, sizem);
    _graphic->drawBox(pos, sizem);
	_panel.push_back(std::make_tuple(pos.first, pos.second, sizem.first, sizem.second));
	pos.first += 1;
	pos.second += 1;
    _graphic->print(pos, "Listes des moteurs graphiques :");
    for (it = _libs.begin();it != _libs.end();it++){
		pos.second += GETY(1);
        _graphic->print(pos, *it, std::get<0>(_pos) == 0
                                && std::get<1>(_pos) == i);
        i++;
    }
}

void    Launcher::printMenuGames()
{
    int i = 1;
    std::size_t size = GETX(33);
    std::size_t mid = _graphic->getWidth() / 2;
	Vector2i	pos = std::make_pair(mid, 0);
	Vector2i	sizem = std::make_pair(size, GETY(1 + _games.size()) + 2);

	adjustPosMenu(pos, sizem);
    _graphic->drawBox(pos, sizem);
	_panel.push_back(std::make_tuple(pos.first, pos.second, sizem.first, sizem.second));
	pos.first += 1;
	pos.second += 1;
    _graphic->print(pos, "Listes des jeux :");
    for (std::list<std::string>::iterator it = _games.begin();
        it != _games.end();it++){
		pos.second += GETY(1);
        _graphic->print(pos, *it, std::get<0>(_pos) == 1 
                                    && std::get<1>(_pos) == i);
        i++;
    }
}

void    Launcher::printUsage()
{
    std::size_t start = _graphic->getWidth() / 2 
                        + GETX(33) + 1;
	Vector2i	pos = std::make_pair(start - 1, 0);
	Vector2i	size = std::make_pair(GETX(31), GETY(6) + 2);

	adjustPosMenu(pos, size);
    _graphic->drawBox(pos, size);
	_panel.push_back(std::make_tuple(pos.first, pos.second, size.first, size.second));
	pos.first += 1;
	pos.second += 1;
    _graphic->print(pos, "Listes des commandes :");
	pos.second += GETY(1);
    _graphic->print(pos, std::string("Haut : ") + static_cast<char>(Control::UP));
	pos.second += GETY(1);
    _graphic->print(pos, std::string("Bas : ") + static_cast<char>(Control::DOWN));
	pos.second += GETY(1);
    _graphic->print(pos, std::string("Gauche : ") + static_cast<char>(Control::LEFT));
	pos.second += GETY(1);
    _graphic->print(pos, std::string("Droite : ") + static_cast<char>(Control::RIGHT));
	pos.second += GETY(1);
    _graphic->print(pos, "Valider/Selectionner : Entree");
}

void    Launcher::printScore()
{
    std::size_t start = _graphic->getWidth() / 2 + GETX(33);
	Vector2i	pos = std::make_pair(start, GETY(6) + 2);
	Vector2i	size = std::make_pair(GETX(33), GETY(1 + _scores.size()) + 2);
	std::vector<std::pair<std::string, std::size_t>>::iterator	it;

    if (_scores.size() == 0)
        return;
	adjustPosMenu(pos, size);
    _graphic->drawBox(pos, size);
	_panel.push_back(std::make_tuple(pos.first, pos.second, size.first, size.second));
	pos.first += 1;
	pos.second += 1;
    _graphic->print(pos, std::string("Top 10 : "));
	for (it = _scores.begin();it != _scores.end();it++){
		pos.second += GETY(1);
		_graphic->print(pos, std::string(it->first).append(" - ").append(std::to_string(it->second)));
	}
}

void    Launcher::printInputName()
{
    std::size_t start = _graphic->getWidth() / 2 - GETX(66);
	Vector2i	pos = std::make_pair(start, 0);
	Vector2i	size = std::make_pair(GETX(33), GETY(1) + 2);

	adjustPosMenu(pos, size);
    _graphic->drawBox(pos, size);
	_panel.push_back(std::make_tuple(pos.first, pos.second, size.first, size.second));
	pos.first += 1;
	pos.second += 1;
    _graphic->print(pos, "Pseudo :", std::get<0>(_pos) == -1);
	pos.first += GETX(9);
    _graphic->print(pos, _name.substr(_name.size() > 22 ? _name.size() - 22 : 0)
                , std::get<0>(_pos) == -1 && _change);
}

void    Launcher::loadLibsGraphic()
{
    DIR *rep = opendir("./lib/");
    struct dirent   *file;
    std::string     current;
    
    if (!rep)
        return;
    while ((file = readdir(rep))){
        current = std::string(file->d_name);
        if (current.size() < 10 || current.substr(0,10) != "lib_arcade")
            continue;
        _libs.push_back(current);
    } 
	closedir(rep);
}

void	Launcher::loadLibsGames()
{
	DIR *rep = opendir("./games/");
	struct dirent	*file;
	std::string		current;

	if (!rep)
		return;
	while ((file = readdir(rep))){
		current = std::string(file->d_name);
		if (current.substr(0,10) != "lib_arcade")
			continue;
		_games.push_back(current);
	}
	closedir(rep);
}

void	Launcher::adjustPosMenu(Vector2i &pos, const Vector2i &size)
{
	pos.first = getX(pos, size);
	pos.second = getY(pos, size);
}


std::size_t	Launcher::getX(const Vector2i &pos, const Vector2i &size)
{
	std::list<std::tuple<int, int, int, int>>::iterator it;
	std::size_t											result = 0;
	bool												first = true;
	std::size_t											space = pos.first;

	if (pos.first >= 0 && pos.first + size.first < _graphic->getWidth())
		return (pos.first);
	for (it = _panel.begin();it != _panel.end();it++){
		if (std::get<0>(*it) + size.first < _graphic->getWidth() && (abs(std::get<0>(*it) - pos.first) < space || first)){
			space = abs(std::get<0>(*it) - pos.first);
			result = std::get<0>(*it);
			first = false;
		}
	}
	return (result);
}

std::size_t	Launcher::getY(const Vector2i &pos, const Vector2i &size)
{
	std::list<std::tuple<int, int, int, int>>::iterator it;
	std::size_t											result = 0;
	bool												first = true;
	std::size_t											space = pos.second;

	for (it = _panel.begin();it != _panel.end();it++){
		if (std::get<0>(*it) == pos.first && (result == std::get<1>(*it))){
			result = std::get<1>(*it) + std::get<3>(*it);
			first = false;
		}
	}
	return (result);
}