#include <iostream>
#include "tests/test_hardware_emulator.h"
#include "View.h"
#include "Emulator.h"

int main(int argc, char *argv[]) {
    // Run tests.
    TestHardwareEmulator::run_all_tests();

    Emulator emulator;
    View view = View(emulator.hardware.screen_data, emulator.hardware.keys);
    emulator.view = &view;
    emulator.view->init();

    // TODO INPUT HANDLING.
    emulator.init();

    SDL_Delay(500);
    emulator.view->close();
    return 0;
}
