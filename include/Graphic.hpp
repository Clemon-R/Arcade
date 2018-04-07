/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** Graphic
*/

#ifndef GRAPHIC_HPP_
    #define GRAPHIC_HPP_

    #include <functional>

    #ifdef GETY
        #undef  GETY
    #endif
    #ifdef GETX
        #undef  GETX
    #endif
    #define GETY(y) (_graphic->getCharSize(1) * (y))
    #define GETX(y) (_graphic->getCharSize(0) * (y))

    using Vector2i = std::pair<int, int>;

class Graphic {
public:
    enum    Color
    {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE,
	YELLOW
    };
	virtual ~Graphic() = default;

    virtual bool    openWindow() = 0;
    virtual void    closeWindow() = 0;
    virtual bool    isOpen() = 0;

    virtual void    refresh() = 0;
    virtual void    clear() = 0;

    virtual void    drawLine(const Vector2i pos1, const Vector2i pos2, const Color = Color::WHITE) = 0;
    virtual void    drawBox(const Vector2i pos, const Vector2i size, const Color = Color::WHITE) = 0;
    virtual void    drawSquare(const Vector2i pos, const Vector2i size, const Color = Color::WHITE) = 0;
    virtual void    print(const Vector2i pos, const std::string &text, bool selected = false, const Color = Color::WHITE) = 0;

    virtual void    setValue(int value) = 0;
    virtual void    setMinSize(int width = -1, int height = -1) = 0;
    virtual void    setEventHandler(std::function<void (int)>) = 0;

    virtual int     getCharSize(char axe) = 0;
    virtual int     getWidth() = 0;
    virtual int     getHeight() = 0;
};

using createFunction = Graphic *(*)();

#endif /* !GRAPHIC_HPP_ */
