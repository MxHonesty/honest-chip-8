//
// Created by Stelian Stoian on 22/12/2020.
//

#include <cstring>
#include <cstdio>
#include "hardware_emulator.h"

void Hardware::cpu_reset() {
    address_i = 0;
    program_counter = 0x200;
    memset(registers, 0, sizeof(registers));  // set registers to 0.

    load_game_into_memory(R"(D:\Projects\C++\honest-chip-8\roms)");
}

void Hardware::load_game_into_memory(const char* filename) {
    FILE *in;
    in = fopen(filename, "rb");
    fread(&game_memory[0x200], 0xfff, 1, in);
    fclose(in);
}

BYTE *Hardware::get_game_memory() {
    return this->game_memory;
}

BYTE *Hardware::get_registers() {
    return this->registers;
}

WORD Hardware::get_address_i() const {
    return this->address_i;
}

WORD Hardware::get_program_counter() const {
    return this->program_counter;
}

void Hardware::set_address_i(WORD new_value) {
    this->address_i = new_value;
}

void Hardware::set_program_counter(WORD new_value) {
    this->program_counter = new_value;
}

WORD Hardware::get_next_opcode() {
    WORD res = game_memory[program_counter];
    res <<= 8;  // We shift the high part of the word to the left.
    res |= game_memory[program_counter + 1];  // Append the low part of the word.
    program_counter += 2;
    return res;
}
