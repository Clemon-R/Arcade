/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** ASfml
*/

#ifndef ASFML_HPP_
	#define ASFML_HPP_
    
    #include <iostream>
    #include "Graphic.hpp"
    #include <SFML/Graphics.hpp>
    #include "Config.hpp"

class ASfml : public Graphic {
public:
    ASfml();
    ~ASfml();
    bool    openWindow() override final;
    void    closeWindow() override final;
    void    drawLine(const Vector2i, const Vector2i, const Color) override final;
    void    drawBox(const Vector2i, const Vector2i, const Color) override final;
    void    refresh() override final;
    bool    isOpen() override final;
    void    setEventHandler(std::function<void (int)>) override final;
    void    setValue(int value) override final;
    void    drawSquare(const Vector2i, const Vector2i, const Color) override final;
	int		getCharSize(char) override final;
    void    print(const Vector2i, const std::string &text, bool, const Color) override final;
	int		getWidth() override final;
	int		getHeight() override final;
    void    clear() override final;
    void    setMinSize(int, int) override final;
private:
    sf::Color   getColor(Color);
    void    handleEvent(sf::Event &);
    int     getSpecialKey(int);

    sf::RenderWindow    *_window;
    std::function<void (int)>   _handler;
	int			_min[0];
};

#endif /* !ASFML_HPP_ */
