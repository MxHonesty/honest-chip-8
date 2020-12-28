#include "tests/test_hardware_emulator.h"
#include "View.h"

int main(int argc, char *argv[]) {
    // Run tests.
    TestHardwareEmulator::run_all_tests();

    BYTE test_keys[16] = {0};

    BYTE test_screen_data[64][32] = {0};
    for(int i = 0; i < 64; i++)
        for(int j = 0; j < 32; j++)
            test_screen_data[i][j] = 1;

    test_screen_data[10][10] = 1;
    View test_view(test_screen_data, test_keys);
    test_view.init();
    test_view.draw_screen_data();

    SDL_Delay(2000);
    test_view.close();
    return 0;
}
