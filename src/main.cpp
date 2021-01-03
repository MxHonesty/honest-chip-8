#include <iostream>
#include "tests/test_hardware_emulator.h"
#include "View.h"
#include "Emulator.h"

int main(int argc, char *argv[]) {
    // Run tests.
    TestHardwareEmulator::run_all_tests();

    Emulator emulator;
    View view = View(emulator.hardware.screen_data);
    emulator.view = &view;
    emulator.view->init();


    emulator.view->draw_screen_data();
    SDL_Delay(2000);

    emulator.hardware.screen_data->set_pixel(10, 10, 1);
    emulator.view->draw_screen_data();

    SDL_Delay(2000);
    emulator.view->close();
    return 0;
}
