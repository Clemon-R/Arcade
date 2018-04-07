/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** ASfml
*/

#include "lib/ASfml.hpp"

ASfml::ASfml() : _window(nullptr)
{
	_min[0] = -1;
	_min[1] = -1;
}

ASfml::~ASfml()
{
    closeWindow();
}

void    ASfml::closeWindow()
{
    if (_window){
        _window->close();
        _window = nullptr;
    }
}

int ASfml::getCharSize(char axe)
{
    return (axe == 0 ? 8 : 18);
}

void    ASfml::setMinSize(int width, int height)
{
	_min[0] = width;
	_min[1] = height;
}

sf::Color     ASfml::getColor(Color color)
{
    sf::Color   result = sf::Color::White;

    switch (color){
        case Color::BLACK:
        result = sf::Color::Black;
        break;
        case Color::RED:
        result = sf::Color::Red;
        break;
        case Color::GREEN:
        result = sf::Color::Green;
        break;
        case Color::BLUE:
        result = sf::Color::Blue;
        break;
        case Color::YELLOW:
        result = sf::Color::Yellow;
        break;
    }
    return (result);
}

void    ASfml::print(const Vector2i pos, const std::string &text, bool selected, const Color color)
{
    sf::Font    font;
    sf::Text    txt;
    sf::Color   txtColor = getColor(color);

    if (!_window || !font.loadFromFile("./fonts/coolvetica rg.ttf"))
        return;
    txt.setString(text);
    txt.setFont(font);
    txt.setCharacterSize(14);
    txt.setPosition(sf::Vector2f(pos.first, pos.second));
    if (selected){
        drawSquare(std::make_pair(pos.first, pos.second + 1)
            , std::make_pair(txt.getLocalBounds().width + 2, txt.getLocalBounds().height + 8), Color::WHITE);
        txtColor = sf::Color::Black;
    }
    txt.setColor(txtColor);
    _window->draw(txt);
}

void    ASfml::setValue(int value)
{
}

void    ASfml::drawSquare(const Vector2i pos, const Vector2i size, const Color color)
{
    sf::RectangleShape  rectangle(sf::Vector2f(size.first, size.second));

    rectangle.setFillColor(getColor(color));
    rectangle.setPosition(sf::Vector2f(pos.first, pos.second));
    if (_window)
        _window->draw(rectangle);
}

bool    ASfml::openWindow()
{
    _window = new sf::RenderWindow(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Window");
    if (!_window)
        return (false);
    _window->clear(sf::Color::Black);
    return (true);
}

void    ASfml::drawLine(const Vector2i pos1, const Vector2i pos2, const Color color)
{
    sf::Vertex  point[2];
    sf::Color   current = getColor(color);

    if (!_window)
        return;
    point[0].color = current;
    point[1].color = current;
    point[0].position = sf::Vector2f(pos1.first, pos1.second);
    point[1].position = sf::Vector2f(pos2.first, pos2.second);
    _window->draw(point, 2, sf::Lines);
}

int ASfml::getWidth()
{
    return (_window->getSize().x);
}

int ASfml::getHeight()
{
    return (_window->getSize().y);
}

void    ASfml::drawBox(const Vector2i pos, const Vector2i size, const Color color)
{
    if (!_window)
        return;
    drawLine(std::make_pair(pos.first, pos.second)
            , std::make_pair(pos.first + size.first, pos.second), color);
    drawLine(std::make_pair(pos.first, pos.second)
            , std::make_pair(pos.first, pos.second + size.second), color);
    drawLine(std::make_pair(pos.first + size.first, pos.second)
            , std::make_pair(pos.first + size.first
                            , pos.second + size.second), color);
    drawLine(std::make_pair(pos.first, pos.second + size.second)
            , std::make_pair(pos.first + size.first
                            , pos.second + size.second), color);
}

void    ASfml::clear()
{
    _window->clear(sf::Color::Black);
}

void    ASfml::handleEvent(sf::Event &event)
{
    int key;

	if (event.type == sf::Event::Resized)
		_window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
    else if (event.type == sf::Event::Closed)
        _window->close();
    else if (event.type == sf::Event::KeyPressed){
        key = event.key.code >= 0 && event.key.code <= 25 
            ? event.key.code + 97 
            : getSpecialKey(event.key.code);
        if (_handler != nullptr && key != -1)
            _handler(key);
        if (event.key.code == sf::Keyboard::Escape)
            closeWindow();
    }
}

int     ASfml::getSpecialKey(int key)
{
    int result = -1;

    switch (key){
        case sf::Keyboard::Return:
        result = 10;
        break;
        case sf::Keyboard::BackSpace:
        result = 263;
        break;
        case sf::Keyboard::Space:
        result = ' ';
        break;
    }
    return (result);
}

void    ASfml::refresh()
{
    sf::Event   event;

    if (_window){
		if ((_min[0] != -1 && _min[0] > getWidth()) 
			|| (_min[1] != -1 && _min[1] > getHeight())){
				clear();
				print(std::make_pair(0, 0), "La fenetre est trop petite."
					, false, Color::WHITE);
			}
        _window->display();
        if (_window->pollEvent(event))
            handleEvent(event);
    }
}

bool    ASfml::isOpen()
{
    return (_window && _window->isOpen());
}

void    ASfml::setEventHandler(std::function<void (int)> func)
{
    _handler = func;
}

extern "C" Graphic  *createGraphic()
{
    return (new ASfml());
}
