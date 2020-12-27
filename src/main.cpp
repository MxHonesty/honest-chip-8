#include "tests/test_hardware_emulator.h"
#include "SDL.h"
#include <iostream>

int main(int argc, char *argv[]) {
    // Run tests.
    TestHardwareEmulator::run_all_tests();

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Window *window = nullptr;
    SDL_Surface *screenSurface = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout<<"SDL coult not initialize!";
    else{  // SDL init
        window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == nullptr)
            std::cout<<"Window could not be created";
        else{  // Window created.
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
