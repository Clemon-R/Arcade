/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** ASdl
*/

#include "lib/ASdl.hpp"
#include <iostream>
#include <SDL2/SDL_ttf.h>

ASdl::ASdl() : _window(nullptr)
{

}

ASdl::~ASdl()
{
    closeWindow();
}

int ASdl::getCharSize(char axe)
{
    return (axe == 0 ? 8 : 18);
}

void    ASdl::setMinSize(int, int)
{
}

void    ASdl::print(const Vector2i pos, const std::string &text, bool selected, const Color color)
{
    TTF_Font    *font = nullptr;
    SDL_Surface *surface = nullptr;
    SDL_Rect    rect;
    int         *tmp = getColor(color);
    SDL_Color   current = {(Uint8)tmp[0], (Uint8)tmp[1], (Uint8)tmp[2]};

    font = TTF_OpenFont("./fonts/coolvetica rg.ttf", 14);
    if (!font)
        return;
    if (selected)
        current = {0, 0, 0};
    surface = TTF_RenderText_Blended(font, text.c_str(), current);
    if (selected)
        drawSquare(std::make_pair(pos.first, pos.second + 1)
            , std::make_pair(surface->w, surface->h), Color::WHITE);
    rect = {pos.first, pos.second, surface->w, surface->h};
    SDL_RenderCopy(_render, SDL_CreateTextureFromSurface(_render, surface)
                    , nullptr, &rect);
    TTF_CloseFont(font);
}

void    ASdl::setValue(int value)
{
}

int     *ASdl::getColor(int key)
{
    int *result = new int[3];

    result[0] = result[1] = result[2] = 255;
    switch (key){
        case Color::BLACK:
        result[0] = result[1] = result[2] = 0;
        break;
        case Color::RED:
        result[1] = result[2] = 0;
        break;
        case Color::GREEN:
        result[0] = result[2] = 0;
        break;
        case Color::BLUE:
        result[0] = result[1] = 0;
        break;
        case Color::YELLOW:
        result[2] = 0;
        break;
    }
    return (result);
}

void    ASdl::drawSquare(const Vector2i pos, const Vector2i size, const Color color)
{
    SDL_Rect    rect;
    int *tmp = getColor(color);

    SDL_SetRenderDrawColor(_render, tmp[0], tmp[1], tmp[2], SDL_ALPHA_OPAQUE);
    rect.h = size.second;
    rect.w = size.first;
    rect.x = pos.first;
    rect.y = pos.second;
    SDL_RenderDrawRect(_render, &rect);
    SDL_RenderFillRect(_render, &rect);
}

void    ASdl::closeWindow()
{
    if (_render){
        SDL_DestroyRenderer(_render);
        _render = nullptr;
    }
    if (!_window)
        return;
    SDL_DestroyWindow(_window);
    _window = nullptr;
    TTF_Quit();
    SDL_Quit();
}

bool    ASdl::openWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return (false);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &_window, &_render);
    if (!_window || !_render)
        return (false);
    TTF_Init();
    return (true);
}

void    ASdl::drawLine(const Vector2i pos1, const Vector2i pos2, const Color color)
{
    int *tmp = getColor(color);

    SDL_SetRenderDrawColor(_render, tmp[0], tmp[1], tmp[2], SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(_render, pos1.first, pos1.second, pos2.first, pos2.second);
}

int ASdl::getWidth()
{
    return (WINDOW_WIDTH);
}

int ASdl::getHeight()
{
    return (WINDOW_HEIGHT);
}

void    ASdl::drawBox(const Vector2i pos, const Vector2i size, const Color color)
{
    SDL_Rect    rect;
    int *tmp = getColor(color);

    if (!_window)
            return;
    SDL_SetRenderDrawColor(_render, tmp[0], tmp[1], tmp[2], SDL_ALPHA_OPAQUE);
    rect.h = size.second;
    rect.w = size.first;
    rect.x = pos.first;
    rect.y = pos.second;
    SDL_RenderDrawRect(_render, &rect);
}

void    ASdl::clear()
{
    SDL_SetRenderDrawColor(_render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_render);
}

void    ASdl::refresh()
{
    SDL_Event   event;

    SDL_RenderPresent(_render);
    if (SDL_PollEvent(&event))
        handlerEvent(event);
}

void    ASdl::handlerEvent(SDL_Event &event)
{
    int key = -1;

    if (event.type == SDL_QUIT)
        closeWindow();
    else if (event.type == 768){
        key = event.key.keysym.sym >= 97 && event.key.keysym.sym <= 122 
            ? event.key.keysym.sym : getSpecialKey(event.key.keysym.sym);
        if (_handler != nullptr && key != -1)
            _handler(key);
        if (event.key.keysym.sym == SDLK_ESCAPE)
            closeWindow();
    }
}

int     ASdl::getSpecialKey(int key)
{
    int result = -1;
    switch (key){
        case SDLK_RETURN:
        result = 10;
        break;
        case SDLK_BACKSPACE:
        result = 263;
        break;
        case SDLK_SPACE:
        result = ' ';
        break;
    }
    return (result);
}

bool    ASdl::isOpen()
{
    return (_window && _render);
}

void    ASdl::setEventHandler(std::function<void (int)> func)
{
    _handler = func;
}

extern "C" Graphic  *createGraphic()
{
    return (new ASdl());
}
