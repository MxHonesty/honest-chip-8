//
// Created by Stelian Stoian on 22/12/2020.
//

#include <cassert>
#include "../hardware_emulator.h"
#include "test_hardware_emulator.h"

 void TestHardwareEmulator::test_load_game_into_memory(){
    auto *he = new Hardware;
    he->load_game_into_memory(R"(D:\Projects\C++\honest-chip-8\roms\test.txt)");
    assert(he->get_game_memory()[0x200] == 49);  // 49 Ascii = 1 character
    assert(he->get_game_memory()[0x201] == 49);
    delete he;
}

void TestHardwareEmulator::run_all_tests() {
    test_load_game_into_memory();
}
