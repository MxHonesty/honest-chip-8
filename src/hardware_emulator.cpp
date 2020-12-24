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
    init_font_data();

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

BYTE Hardware::get_register(int pos) {
    return registers[pos];
}

void Hardware::set_register(int pos, BYTE value) {
    if(pos < 16 && pos >= 0)
        registers[pos] = value;
}

BYTE Hardware::get_memory(int pos) {
    return game_memory[pos];
}

void Hardware::set_memory(int pos, BYTE value) {
    game_memory[pos] = value;
}

void Hardware::init_font_data() {
    // 0
    game_memory[0] = 0xF0;
    game_memory[1] = 0x90;
    game_memory[2] = 0x90;
    game_memory[3] = 0x90;
    game_memory[4] = 0xF0;

    //1
    game_memory[5] = 0x20;
    game_memory[6] = 0x60;
    game_memory[7] = 0x20;
    game_memory[8] = 0x20;
    game_memory[9] = 0x70;

    //2
    game_memory[10] = 0xF0;
    game_memory[11] = 0x10;
    game_memory[12] = 0xF0;
    game_memory[13] = 0x80;
    game_memory[14] = 0xF0;

    //3
    game_memory[15] = 0xF0;
    game_memory[16] = 0x10;
    game_memory[17] = 0xF0;
    game_memory[18] = 0x10;
    game_memory[19] = 0xF0;

    //4
    game_memory[20] = 0x90;
    game_memory[21] = 0x90;
    game_memory[22] = 0xF0;
    game_memory[23] = 0x10;
    game_memory[24] = 0x10;

    //5
    game_memory[25] = 0xF0;
    game_memory[26] = 0x80;
    game_memory[27] = 0xF0;
    game_memory[28] = 0x10;
    game_memory[29] = 0xF0;

    //6
    game_memory[30] = 0xF0;
    game_memory[31] = 0x80;
    game_memory[32] = 0xF0;
    game_memory[33] = 0x90;
    game_memory[34] = 0xF0;

    //7
    game_memory[35] = 0xF0;
    game_memory[36] = 0x10;
    game_memory[37] = 0x20;
    game_memory[38] = 0x40;
    game_memory[39] = 0x40;

    //8
    game_memory[40] = 0xF0;
    game_memory[41] = 0x90;
    game_memory[42] = 0xF0;
    game_memory[43] = 0x90;
    game_memory[44] = 0xF0;

    //9
    game_memory[45] = 0xF0;
    game_memory[46] = 0x90;
    game_memory[47] = 0xF0;
    game_memory[48] = 0x10;
    game_memory[49] = 0xF0;

    //A
    game_memory[50] = 0xF0;
    game_memory[51] = 0x90;
    game_memory[52] = 0xF0;
    game_memory[53] = 0x90;
    game_memory[54] = 0x90;

    //B
    game_memory[55] = 0xE0;
    game_memory[56] = 0x90;
    game_memory[57] = 0xE0;
    game_memory[58] = 0x90;
    game_memory[59] = 0xE0;

    //C
    game_memory[60] = 0xF0;
    game_memory[61] = 0x80;
    game_memory[62] = 0x80;
    game_memory[63] = 0x80;
    game_memory[64] = 0xF0;

    //D
    game_memory[65] = 0xE0;
    game_memory[66] = 0x90;
    game_memory[67] = 0x90;
    game_memory[68] = 0x90;
    game_memory[69] = 0xE0;

    //E
    game_memory[70] = 0xF0;
    game_memory[71] = 0x80;
    game_memory[72] = 0xF0;
    game_memory[73] = 0x80;
    game_memory[74] = 0xF0;

    //F
    game_memory[75] = 0xF0;
    game_memory[76] = 0x80;
    game_memory[77] = 0xF0;
    game_memory[78] = 0x80;
    game_memory[79] = 0x80;
}
