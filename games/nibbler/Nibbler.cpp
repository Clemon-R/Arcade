/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** Nibbler
*/

#include "game/Nibbler.hpp"
#include <memory>
#include <cstdlib>
#include <ctime>
#include <sys/timeb.h>

static int  getMilliseconds()
{
    timeb   tb;

    ftime(&tb);
    return (tb.millitm + (tb.time & 0xfffff) * 1000);
}

Nibbler::Nibbler(Graphic **graphic, const std::string &name) : 
                    _graphic(graphic), _name(name), _run(true)
                    , _score(1), _keyEntered(false), _boost(0)
{
    std::size_t v = (*_graphic)->getHeight() / (*_graphic)->getCharSize(1);
    std::size_t h = (*_graphic)->getWidth() / (*_graphic)->getCharSize(1);
    std::size_t mid = 0;

    _size = GETY(h < v ? h : v);
    std::get<0>(_food) = false;
    std::get<3>(_food) = 0;
    _mapSize = (h < v ? h : v) - 2;
    mid = _mapSize / 2;
    _dir[0] = 0;
    _dir[1] = 1;
    _snake.push_back(createSnakePart(mid, mid + 3));
    setWitchPart(_snake.front(), TypePart::HEAD);
    _snake.push_back(createSnakePart(mid, mid + 2));
    _snake.push_back(createSnakePart(mid, mid + 1));
    _snake.push_back(createSnakePart(mid, mid + 0));
    setWitchPart(_snake.back(), TypePart::QUEUE);
}

Nibbler::~Nibbler()
{

}

std::unique_ptr<snake_t>    Nibbler::createSnakePart(std::size_t x, std::size_t y)
{
    std::unique_ptr<snake_t>    current;

    current.reset(new snake_t);
    current->posX = x;
    current->posY = y;
    setWitchPart(current, TypePart::COMMON);
    return (current);
}

void    Nibbler::setWitchPart(std::unique_ptr<snake_t> &part, TypePart type)
{
    switch (type){
        case TypePart::HEAD:
            part->color = Graphic::Color::RED;
            part->shape = '0';
            break;
        case TypePart::COMMON:
            part->color = Graphic::Color::GREEN;
            part->shape = 'o';
            break;
        case TypePart::QUEUE:
            part->color = Graphic::Color::BLUE;
            part->shape = 'Q';
            break;
    }
}

void    Nibbler::printSnake()
{
    std::size_t start = ((*_graphic)->getWidth()  - _size) / 2;
    std::list<std::unique_ptr<snake_t>>::iterator   it;
    int i = 0;

    for (it = _snake.begin();it != _snake.end();it++){
        (*_graphic)->setValue((*it)->shape);
        (*_graphic)->drawSquare(std::make_pair(start + GETY((*it)->posX + 1)
                        , GETY((*it)->posY + 1))
                        , std::make_pair(GETY(1), GETY(1)), (*it)->color);
        i += 1;
    }
}

void    Nibbler::spawnFood()
{
    std::size_t posX;
    std::size_t posY;

    if (std::get<0>(_food))
        return;
    std::get<1>(_food) = std::rand() % (_mapSize - 1);
    std::get<2>(_food) = std::rand() % (_mapSize - 1);
    std::get<0>(_food) = true;
}

void    Nibbler::moveSnake()
{
    std::list<std::unique_ptr<snake_t>>::iterator   it;
    std::size_t old[2];
    std::size_t tmp[2];
    int i = 0;

    for (it = _snake.begin();it != _snake.end();it++, i++){
        tmp[0] = old[0];
        tmp[1] = old[1];
        old[0] = (*it)->posX;
        old[1] = (*it)->posY;
        if (i != 0){
            (*it)->posX = tmp[0];
            (*it)->posY = tmp[1];
        }
        if (i == 0){
            (*it)->posX += _dir[0];
            (*it)->posY += _dir[1];
        }
    }
    _keyEntered = false;
    eatFoodIfAvailable(_snake.begin());
    if (std::get<3>(_food) > 0){
        setWitchPart(_snake.back(), TypePart::COMMON);
        _snake.push_back(createSnakePart(old[0], old[1]));
        setWitchPart(_snake.back(), TypePart::QUEUE);
        std::get<3>(_food) -= 1;
    }
}

bool    Nibbler::eatFoodIfAvailable(std::list<std::unique_ptr<snake_t>>::iterator first)
{
    if (!std::get<0>(_food))
        return (false);
    else if (std::get<1>(_food) == (*first)->posX && std::get<2>(_food) == (*first)->posY){
        std::get<0>(_food) = false;
        _score += 10 * _snake.size();
        std::get<3>(_food) += std::rand() % 4 + 1;
        return (true);
    }
    return (false);
}

bool    Nibbler::eatOrWall(std::list<std::unique_ptr<snake_t>>::iterator first)
{
    std::list<std::unique_ptr<snake_t>>::iterator   it;
    int i = 0;

    if ((*first)->posX < 0 || (*first)->posX >= _mapSize)
        return (true);
    else if ((*first)->posY < 0 || (*first)->posY >= _mapSize)
        return (true);
    for (it = _snake.begin();it != _snake.end();it++, i++){
        if (i == 0)
            continue;
        else if ((*it)->posX == (*first)->posX && (*it)->posY == (*first)->posY)
            return (true);
    }
    return (false);
}

void    Nibbler::printArea()
{
    std::size_t mid = ((*_graphic)->getWidth()  - _size) / 2;

    (*_graphic)->setValue('*');
    (*_graphic)->drawSquare(std::make_pair(mid, 0)
                        , std::make_pair(_size, _size));
    (*_graphic)->setValue(' ');
    (*_graphic)->drawSquare(
                std::make_pair(mid + GETY(1), GETY(1))
                , std::make_pair(_size - GETY(2), _size - GETY(2)),
                            Graphic::Color::BLACK);
}

void    Nibbler::printFood()
{
    if (std::get<0>(_food)){
        (*_graphic)->drawSquare(
                    std::make_pair(((*_graphic)->getWidth()  - _size) 
                                    / 2 + GETY(std::get<1>(_food) + 1)
                                , GETY(std::get<2>(_food) + 1))
                    , std::make_pair(GETY(1), GETY(1)));
    }
}

void    Nibbler::printScore()
{      
    (*_graphic)->print(std::make_pair(0, 0)
                    , "Score : " + std::to_string(_score));
}

std::size_t    Nibbler::start()
{
    std::function<void (int)>   handler = std::bind(&Nibbler::handlerEvent, this, std::placeholders::_1);
    std::size_t old = 0;
    std::size_t current;

    (*_graphic)->setEventHandler(handler);
    (*_graphic)->setMinSize(_size, _size);
    std::srand(std::time(nullptr));
    while (*_graphic && (*_graphic)->isOpen() && _run){
        (*_graphic)->clear();
        printArea();
        if ((current = getMilliseconds()) > old){
            _score += _snake.size();
            moveSnake();
            if (eatOrWall(_snake.begin()))
                break;
            old = current + 250 - (_snake.size() * 2) - _boost;
            _boost = 0;
            spawnFood();
        }
        printSnake();
        printFood();
        printScore();
        (*_graphic)->refresh();
    }
    (*_graphic)->setEventHandler(nullptr);
    (*_graphic)->setMinSize();
    return (_score);
}

void    Nibbler::handlerEvent(int key)
{
    switch (key){
        case Control::BACKSPACE:
            _run = false;
        break;
        case Control::LEFT:
        case Control::RIGHT:
            if (_keyEntered)
                break;
            if (_dir[0] != 0){
                _dir[1] = (key == 'q' ? -1 : 1) * _dir[0];
                _dir[0] = 0;
            }else if (_dir[1] != 0){
                _dir[0] = (key == 'q' ? 1 : -1) * _dir[1];
                _dir[1] = 0;
            }
            break;
        case Control::SPACE:
            _boost = 100;
            break;
    }
    _keyEntered = true;
}

extern "C" std::size_t start(Graphic **graphic, const std::string &name)
{
    std::unique_ptr<Nibbler>  own = std::make_unique<Nibbler>(graphic, name);
    
    return (own->start());
}