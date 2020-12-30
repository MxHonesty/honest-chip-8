//
// Created by Stelian Stoian on 24/12/2020.
//

#ifndef SRC_VIEW_H
#define SRC_VIEW_H
#include "SDL.h"
#include "hardware_emulator.h"

class View {
    BYTE *keys_data;
    Hardware *hardware;

    static const int WIDTH = 64;
    static const int HEIGHT = 32;
    const int multiplier = 10;  // in_game_pixel = multiplier * actual_pixel

    //The window we'll be rendering to
    SDL_Window* Window = nullptr;

    //The surface contained by the window
    SDL_Surface* ScreenSurface = nullptr;

public:
    View(Hardware hardware, BYTE *keys);  // Constructor.
    bool init();  // Starts up SDL and creates a window. Returns true if window created.
    bool draw_screen_data();  // Loads image to window.
    void close();  // SDL CLOSE.
};


#endif //SRC_VIEW_H
