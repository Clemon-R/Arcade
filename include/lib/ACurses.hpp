/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** ACurses
*/

#ifndef ACURSES_HPP_
	#define ACURSES_HPP_

	#define GETX(x) (x * _offsetX)
	#define GETY(y) (y * _offsetY)

	#include <ncurses.h>
	#include <iostream>
	#include <list>
	#include <tuple>
	#include "Graphic.hpp"

class ACurses : public Graphic {
public:
	ACurses();
	~ACurses();
	bool	openWindow() override final;
	void	closeWindow() override final;
    void    drawLine(const Vector2i, const Vector2i, const Color) override final;
    void    drawBox(const Vector2i, const Vector2i, const Color) override final;
    void    refresh() override final;
	bool	isOpen() override final;
	void    setEventHandler(std::function<void (int)>) override final;
    void    setValue(int value) override final;
    void    drawSquare(const Vector2i, const Vector2i, const Color) override final;
	int		getCharSize(char) override final;
    void    print(const Vector2i, const std::string &text, bool, const Color) override final;
	int		getWidth() override final;
	int		getHeight() override final;
	void	clear() override final;
	void	setMinSize(int, int) override final;
private:
	int		getColor(Color);
	void	handleEvent(int key);

	enum	WindowOpened
	{
		LAUNCHER,
		GAME,
		EMPTY,
		NONE
	};
	WindowOpened	_state;
	WINDOW			*_window;
	std::function<void (int)>	_handler;
	char	_value;
	int		_min[2];
};

#endif /* !ACURSES_HPP_ */
