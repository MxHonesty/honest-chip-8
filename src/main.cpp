#include "tests/test_hardware_emulator.h"
#include "View.h"

int main(int argc, char *argv[]) {
    // Run tests.
    TestHardwareEmulator::run_all_tests();

    BYTE test_keys[16] = {0};

    Hardware hd;

    hd.screen_data.init();
    View test_view(hd, test_keys);
    test_view.init();
    test_view.draw_screen_data();

    SDL_Delay(2000);
    //test_view.close();
    return 0;
}
