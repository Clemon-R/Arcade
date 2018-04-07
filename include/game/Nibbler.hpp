/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
	#define NIBBLER_HPP_

    #include "Graphic.hpp"
    #ifdef GETY
        #undef  GETY
    #endif
    #ifdef GETX
        #undef  GETX
    #endif
    #define GETY(y) ((*_graphic)->getCharSize(1) * (y))
    #define GETX(y) ((*_graphic)->getCharSize(0) * (y))
    #include <iostream>
    #include <functional>
    #include <list>
    #include <memory>
    #include <tuple>
    #include "Control.hpp"

typedef struct	snake_s
{
	std::size_t	posX;
	std::size_t	posY;
    Graphic::Color  color;
    char        shape;
}				snake_t;
class Nibbler {
public:
    Nibbler(Graphic **graphic, const std::string &name);
    ~Nibbler();
    std::size_t    start();
private:
    enum    TypePart
    {
        HEAD,
        COMMON,
        QUEUE
    };
    void    printSnake();
    void    printArea();
    void    printFood();
    void    printScore();

    void    moveSnake();
    bool    eatOrWall(std::list<std::unique_ptr<snake_t>>::iterator);

    void    spawnFood();
    bool    eatFoodIfAvailable(std::list<std::unique_ptr<snake_t>>::iterator);

    std::unique_ptr<snake_t>    createSnakePart(std::size_t x, std::size_t y);
    void    setWitchPart(std::unique_ptr<snake_t> &, TypePart);

    void    handlerEvent(int key);

    Graphic **_graphic;
    const std::string   _name;
    std::size_t _score;
    bool    _run;
    std::size_t _size;
    std::size_t _mapSize;
    char    _dir[2];
	std::list<std::unique_ptr<snake_t>>	_snake;
    std::tuple<bool, std::size_t, std::size_t, std::size_t>  _food;
    bool    _keyEntered;
    std::size_t _boost;
};

#endif /* !NIBBLER_HPP_ */
