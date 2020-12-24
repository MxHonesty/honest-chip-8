//
// Created by Stelian Stoian on 24/12/2020.
//

#ifndef SRC_VIEW_H
#define SRC_VIEW_H
#include "SDL.h"

class View {
    // https://github.com/stevensona/chip8/blob/master/display.h
    Hardware *hardware;

    SDL_Rect screen_rect = NULL;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    static const uint8_t SCREEN_WIDTH = 64;
    static const uint8_t SCREEN_HEIGHT = 32;
    static const uint8_t PIXEL_SIZE = 12;  // 1 CHIP8 pixel -> 12 pixels.

public:
    explicit  View(Hardware he);  // Constructor.
    ~View();
    void update();
    void update(const SDL_Rect &rect);

};


#endif //SRC_VIEW_H
