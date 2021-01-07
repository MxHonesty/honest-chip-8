//
// Created by Stelian Stoian on 24/12/2020.
//

#ifndef SRC_VIEW_H
#define SRC_VIEW_H
#include "SDL.h"
#include "graphic.h"

class View {
    graphic *gfx;
    BYTE *keys_data;
    SDL_Event e;  // SDL event for handler.

    static const int WIDTH = 64;
    static const int HEIGHT = 32;
    const int multiplier = 10;  // in_game_pixel = multiplier * actual_pixel

    enum KeyPress{  // Position of each chip-8 key in keys_data.
        KEY_1, KEY_2, KEY_3, KEY_C,
        KEY_4, KEY_5, KEY_6, KEY_D,
        KEY_7, KEY_8, KEY_9, KEY_E,
        KEY_A, KEY_0, KEY_B, KEY_F,
        TOTAL_KEYS
    };

    //The window we'll be rendering to
    SDL_Window* Window = nullptr;

    //The surface contained by the window
    SDL_Surface* ScreenSurface = nullptr;

public:
    bool quit;  // Main execution loop flag.

    explicit View(graphic *gfx, BYTE *keys);  // Constructor.
    bool init();  // Starts up SDL and creates a window. Returns true if window created.
    bool draw_screen_data();  // Loads image to window.
    void handle_events();  // Handle events.
    void close();  // SDL CLOSE.
};


#endif //SRC_VIEW_H
