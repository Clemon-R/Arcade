/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** ASdl
*/

#ifndef ASDL_HPP_
        #define ASDL_HPP_

        #include <SDL2/SDL.h>
        #include "Graphic.hpp"
        #include "Config.hpp"

class ASdl : public Graphic {
public:
    ASdl();
    ~ASdl();
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
    int     *getColor(int);
    int     getSpecialKey(int);
    void    handlerEvent(SDL_Event &event);

    SDL_Window  *_window;
    SDL_Renderer    *_render;
    std::function<void (int)>   _handler;
};

#endif /* !ASDL_HPP_ */
