#include "tests/test_hardware_emulator.h"
#include "SDL.h"

int main(int argc, char *argv[]) {
    TestHardwareEmulator::run_all_tests();

    return 0;
}
