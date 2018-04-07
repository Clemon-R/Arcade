/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** ACurses
*/

#include "lib/ACurses.hpp"
#include <unistd.h>
#include <dirent.h>

ACurses::ACurses() : _state(WindowOpened::NONE), _window(nullptr)
					, _value('*')
{
	_min[0] = -1;
	_min[1] = -1;
}

ACurses::~ACurses()
{
	closeWindow();
}

void    ACurses::closeWindow()
{
	if (_window){
		delwin(_window);
		endwin();
		_window = nullptr;
		_state = WindowOpened::NONE;
	}
}

void    ACurses::setMinSize(int width, int height)
{
	_min[0] = width;
	_min[1] = height;
}

void    ACurses::setValue(int value)
{
	_value = value;
}

void    ACurses::drawSquare(const Vector2i pos, const Vector2i size, const Color color)
{
	int current = getColor(color);

	wattron(_window, COLOR_PAIR(current));
	for (int i = 0;i < size.second;i += 1){
		wmove(_window, pos.second + i, pos.first);
		whline(_window, _value, size.first);
	}
	wattroff(_window, COLOR_PAIR(current));
}

bool    ACurses::openWindow()
{
	if (_state != WindowOpened::NONE)
		return (false);
	_window = initscr();
	if (!_window)
		return (false);
	curs_set(0);
	wtimeout(_window, 100);
	keypad(_window, true);
	noecho();
	cbreak();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_RED);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_YELLOW, COLOR_YELLOW);
	_state = WindowOpened::EMPTY;
	return (true);
}

int ACurses::getCharSize(char)
{
	return (1);
}

int     ACurses::getColor(Color color)
{
	int result = 5;

    switch (color){
        case Color::BLACK:
        result = 6;
        break;
        case Color::RED:
        result = 2;
        break;
        case Color::GREEN:
        result = 3;
        break;
        case Color::BLUE:
        result = 4;
        break;
        case Color::YELLOW:
        result = 5;
        break;
    }
    return (result);
}

void    ACurses::print(const Vector2i pos, const std::string &text, bool selected, const Color color)
{
	int current = selected ? 1 : 7;

	if (!_window)
		return;
	wattron(_window, COLOR_PAIR(current));
	mvwprintw(_window, pos.second, pos.first, text.c_str());
	wattroff(_window, COLOR_PAIR(current));
}

void    ACurses::drawLine(const Vector2i pos1, const Vector2i pos2, const Color color)
{
	wattron(_window, COLOR_PAIR(getColor(color)));
	if (pos1.first == pos2.first){
		wmove(_window, pos1.second, pos1.first);
		wvline(_window, _value, pos2.second - pos1.second);
	}
	else if (pos1.second == pos2.second){
		wmove(_window, pos1.second, pos1.first);
		whline(_window, _value, pos2.first - pos1.first);
	}
	wattroff(_window, COLOR_PAIR(getColor(color)));
}

int ACurses::getWidth()
{
	return (COLS);
}

int ACurses::getHeight()
{
	return (LINES);
}

void    ACurses::drawBox(const Vector2i pos, const Vector2i size, const Color color)
{
	char    old = _value;
	
	_value = ' ';
	drawLine(std::make_pair(pos.first, pos.second)
			, std::make_pair(pos.first + size.first, pos.second), color);
	drawLine(std::make_pair(pos.first, pos.second + size.second - 1)
			, std::make_pair(pos.first + size.first
							, pos.second + size.second - 1), color);
	_value = ' ';
	drawLine(std::make_pair(pos.first, pos.second)
			, std::make_pair(pos.first, pos.second + size.second), color);
	drawLine(std::make_pair(pos.first + size.first - 1, pos.second)
			, std::make_pair(pos.first + size.first - 1
							, pos.second + size.second), color);
	_value = old;
}

void    ACurses::clear()
{
	if (_window)
		wclear(_window);
}

void    ACurses::setEventHandler(std::function<void (int)> func)
{
	_handler = func;
}

void    ACurses::handleEvent(int key)
{
	if (key == -1)
		return;
	if (_handler != nullptr)
		_handler(key);
	switch (key){
		case 27:
			closeWindow();
		break;
	}
}

void    ACurses::refresh()
{
	if (_state == WindowOpened::NONE)
		return;
	if (COLS < _min[0] || LINES < _min[1]){
		clear();
		print(std::make_pair(0, 0), "La fenêtre est trop petite.", false, Color::WHITE);
	}
	wrefresh(_window);
	handleEvent(getch());
}

bool    ACurses::isOpen()
{
	return (_state != WindowOpened::NONE);
}

extern "C" Graphic  *createGraphic()
{
	return (new ACurses());
}
