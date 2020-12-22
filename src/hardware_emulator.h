//
// Created by Stelian Stoian on 22/12/2020.
//

#ifndef SRC_HARDWARE_EMULATOR_H
#define SRC_HARDWARE_EMULATOR_H

#include <vector>
#include "chip_types.h"

class Hardware {
public:
    // TODO: membrii privati cu getteri. game_memory este folosit in test_hardware_emulator.cpp
    BYTE game_memory[0xFFF];  // 0xFFF bytes of memory.
    BYTE registers[16];  // 16 registers, 1 byte each.
    WORD address_i;  // the 16-bit address register I.
    WORD program_counter;  // 16-bit program counter.
    BYTE screen_data[64][32];  // 64x32 resolution.
    std::vector<WORD> stack;  // 16-bit stack.

    void cpu_reset();  // Reset the cpu.
    void load_game_into_memory(const char *filename);  // Load game file into memory.




};


#endif //SRC_HARDWARE_EMULATOR_H
