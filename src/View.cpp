//
// Created by Stelian Stoian on 24/12/2020.
//

#include "View.h"
#include "SDL.h"
#include <iostream>

View::View(graphic *gfx_interface, BYTE *keys) {
    keys_data = keys;
    gfx = gfx_interface;
    quit = false;
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
            if(gfx->get_pixel(i, j) ==  1)
                SDL_FillRect(ScreenSurface, &rect, SDL_MapRGB(ScreenSurface->format, 255, 255, 255));
            else if(gfx->get_pixel(i, j) ==  0)
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

void View::handle_events() {
    while(SDL_PollEvent(&e) != 0){
        switch(e.type){
            case SDL_QUIT: quit = true; break;
            case SDL_KEYDOWN:  // Key pressed.
                switch(e.key.keysym.sym){
                    case SDLK_1:
                        keys_data[KEY_1] = 1;
                        break;
                    case SDLK_2:
                        keys_data[KEY_2] = 1;
                        break;
                    case SDLK_3:
                        keys_data[KEY_3] = 1;
                        break;
                    case SDLK_4:
                        keys_data[KEY_C] = 1;
                        break;
                    case SDLK_q:
                        keys_data[KEY_4] = 1;
                        break;
                    case SDLK_w:
                        keys_data[KEY_5] = 1;
                        break;
                    case SDLK_e:
                        keys_data[KEY_6] = 1;
                        break;
                    case SDLK_r:
                        keys_data[KEY_D] = 1;
                        break;
                    case SDLK_a:
                        keys_data[KEY_7] = 1;
                        break;
                    case SDLK_s:
                        keys_data[KEY_8] = 1;
                        break;
                    case SDLK_d:
                        keys_data[KEY_9] = 1;
                        break;
                    case SDLK_f:
                        keys_data[KEY_E] = 1;
                        break;
                    case SDLK_z:
                        keys_data[KEY_A] = 1;
                        break;
                    case SDLK_x:
                        keys_data[KEY_0] = 1;
                        break;
                    case SDLK_c:
                        keys_data[KEY_B] = 1;
                        break;
                    case SDLK_v:
                        keys_data[KEY_F] = 1;
                        break;
                }
                break;
            case SDL_KEYUP:  // Key unpressed.
                switch(e.key.keysym.sym){
                    case SDLK_1:
                        keys_data[KEY_1] = 0;
                        break;
                    case SDLK_2:
                        keys_data[KEY_2] = 0;
                        break;
                    case SDLK_3:
                        keys_data[KEY_3] = 0;
                        break;
                    case SDLK_4:
                        keys_data[KEY_C] = 0;
                        break;
                    case SDLK_q:
                        keys_data[KEY_4] = 0;
                        break;
                    case SDLK_w:
                        keys_data[KEY_5] = 0;
                        break;
                    case SDLK_e:
                        keys_data[KEY_6] = 0;
                        break;
                    case SDLK_r:
                        keys_data[KEY_D] = 0;
                        break;
                    case SDLK_a:
                        keys_data[KEY_7] = 0;
                        break;
                    case SDLK_s:
                        keys_data[KEY_8] = 0;
                        break;
                    case SDLK_d:
                        keys_data[KEY_9] = 0;
                        break;
                    case SDLK_f:
                        keys_data[KEY_E] = 0;
                        break;
                    case SDLK_z:
                        keys_data[KEY_A] = 0;
                        break;
                    case SDLK_x:
                        keys_data[KEY_0] = 0;
                        break;
                    case SDLK_c:
                        keys_data[KEY_B] = 0;
                        break;
                    case SDLK_v:
                        keys_data[KEY_F] = 0;
                        break;
                }
                break;

        }
    }
}
