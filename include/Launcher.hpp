/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** Launcher
*/

#ifndef LAUNCHER_HPP_
	#define LAUNCHER_HPP_

    #include <list>
	#include <vector>
    #include <memory>
    #include "Graphic.hpp"
    #include "Control.hpp"

class Launcher {
public:
    Launcher(std::string &lib);
    ~Launcher();

	void	start();
private:
    void    printMenuGraphic();
    void    printMenuGames();
    void    printUsage();
    void    printScore();
    void    printInputName();

    void    adjustPosMenu(Vector2i &pos, const Vector2i &size);
	std::size_t	getX(const Vector2i &pos, const Vector2i &size);
	std::size_t	getY(const Vector2i &pos, const Vector2i &size);
    
    void    loadLibsGraphic();
    void    loadLibsGames();
	void	loadScores();

    void    handlerEvent(int key);

    void    loadGraphicLib(std::string &lib);
    void    loadGameLib(std::string &lib);
    void    eventSelect();
    void    run();

	std::vector<std::pair<std::string, std::size_t>>	_scores;

    Graphic *_graphic;
    void    *_dll;

    std::string _name;

    std::list<std::string>  _libs;
    std::list<std::string>  _games;

    int _currentGraph;
    bool    _change;
    std::tuple<int, int>                                    _pos;
    std::list<std::tuple<int, int, int, int>>               _panel;
};

using   createGame = std::size_t (*)(Graphic **, const std::string &);

#endif /* !LAUNCHER_HPP_ */
