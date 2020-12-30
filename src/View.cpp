//
// Created by Stelian Stoian on 24/12/2020.
//

#include "View.h"
#include "SDL.h"
#include <iostream>

View::View(Hardware hardware_drawn, BYTE *keys) {
    hardware = &hardware_drawn;
    keys_data = keys;
}

bool View::init() {
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout<<"SDL could not init! SDL_Error: "<<SDL_GetError() <<std::endl;
        success = false;
    }
    else{  // SDL init.
        Window = SDL_CreateWindow("View window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  WIDTH * multiplier, HEIGHT * multiplier, SDL_WINDOW_SHOWN);
        if(Window == nullptr){
            std::cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<std::endl;
        }  // Window Created.
        else{
            ScreenSurface = SDL_GetWindowSurface(Window);
            SDL_FillRect(ScreenSurface, nullptr, SDL_MapRGB(ScreenSurface->format, 0x90, 0x90, 0x90));
            SDL_UpdateWindowSurface(Window);
        }
    }
    return success;
}

bool View::draw_screen_data() {
    bool success = true;
    SDL_Rect rect;
    for(int i = 0; i < WIDTH; i++)
        for(int j = 0; j < HEIGHT; j++){
            rect.x = i * multiplier;
            rect.y = j * multiplier;
            rect.w = multiplier;
            rect.h = multiplier;
            //std::cout<<hardware->screen_data.get_pixel(i, j)<<" ";  // DEBUG
            if(hardware->screen_data.get_pixel(i, j) ==  1)
                SDL_FillRect(ScreenSurface, &rect, SDL_MapRGB(ScreenSurface->format, 255, 255, 255));
            else if(hardware->screen_data.get_pixel(i, j) ==  0)
                SDL_FillRect(ScreenSurface, &rect, SDL_MapRGB(ScreenSurface->format, 0, 0, 0));
        }
    SDL_UpdateWindowSurface(Window);
    return success;
}

void View::close() {
    SDL_FreeSurface(ScreenSurface);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
