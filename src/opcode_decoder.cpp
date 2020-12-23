//
// Created by Stelian Stoian on 22/12/2020.
//

#include "opcode_decoder.h"


void opcode_decoder::decode_opcode(WORD opcode) {
    switch(opcode & 0xF000){
        case 0x1000: Opcode1NNN(opcode); break;  // jump opcode.
        case 0x0000: {
            switch(opcode & 0x000F){
                case 0x0000: Opcode00E0(opcode); break;  // clear screen.
                case 0x000E: Opcode00EE(opcode); break;  // return subroutine.
            }
        }
        break;
        default: break;  // yet to be handled.
    }
}

void opcode_decoder::Opcode1NNN(WORD opcode) {
    hardware->set_program_counter(opcode & 0x0FFF);
}

void opcode_decoder::Opcode00E0(WORD opcode) {

}

void opcode_decoder::Opcode00EE(WORD opcode) {

}

opcode_decoder::opcode_decoder(Hardware he) {
    hardware = &he;
}

void opcode_decoder::Opcode2NNN(WORD opcode) {
    hardware->stack.push_back(hardware->get_program_counter());  // Push counter to stack.
    hardware->set_program_counter(opcode & 0x0FFF);  // Jump to NNN.
}

void opcode_decoder::Opcode5XY0(WORD opcode) {
    int reg_x = opcode & 0x0F00;
    reg_x = reg_x >> 8;
    int reg_y = opcode & 0x00F0;
    reg_y = reg_y >> 4;  // Overlapping reg_x and reg_y.

    if(hardware->get_registers()[reg_x] == hardware->get_registers()[reg_y])
        hardware->set_program_counter(hardware->get_program_counter() + 2);
}

void opcode_decoder::Opcode8XY5(WORD opcode) {
    hardware->get_registers()[0xF] = 1;
    int reg_x = opcode & 0x0F00;
    reg_x = reg_x >> 8;
    int reg_y = opcode & 0x00F0;
    reg_y = reg_y >> 4;

    int x_value = hardware->get_registers()[reg_x];
    int y_value = hardware->get_registers()[reg_y];
    if(y_value > x_value)
        hardware->get_registers()[0xF] = 0;  // Update carry-flag.
    hardware->get_registers()[reg_x] = x_value - y_value;
}

void opcode_decoder::OpcodeDXYN(WORD opcode) {
    int reg_x = opcode & 0x0F00;
    reg_x = reg_x >> 8;
    int reg_y = opcode & 0x00F0;
    reg_y = reg_y >> 4;

    int height = opcode & 0x000F;
    int x_position = hardware->get_registers()[reg_x];
    int y_position = hardware->get_registers()[reg_y];

    hardware->get_registers()[0xF] = 0;  // Reset carry-flag.

    for(int yline = 0; yline < height; yline++){
        BYTE data = hardware->get_game_memory()[hardware->get_address_i() + yline];
        int xpixelinv = 7;
        int xpixel = 0;
        for(xpixel = 0; xpixel < 8; xpixel++, xpixelinv--){
            int mask = 1 << xpixelinv;
            if(data & mask){
                int x = x_position + xpixel;
                int y = y_position + yline;
                if(hardware->screen_data[x][y] == 1)
                    hardware->get_registers()[0xF] = 1;  // Collision.
                hardware->screen_data[x][y] ^= 1;
            }
        }
    }
}

void opcode_decoder::OpcodeFX33(WORD opcode) {
    int reg_x = opcode & 0x0F00;
    reg_x >>= 8;
    int value = hardware->get_registers()[reg_x];

    int hundreds = value / 100;
    int tens = (value / 10) % 10;
    int units = value % 10;

    WORD i_address = hardware->get_address_i();
    hardware->get_game_memory()[i_address] = hundreds;
    hardware->get_game_memory()[i_address+1] = tens;
    hardware->get_game_memory()[i_address+2] = units;
}

void opcode_decoder::OpcodeFX55(WORD opcode) {
    int reg_x = opcode & 0x0F00;
    reg_x >>= 8;
    WORD i_address = hardware->get_address_i();
    for(int i = 0; i <= reg_x; i++)
        hardware->get_game_memory()[i_address + i] =
                hardware->get_registers()[i];
    hardware->set_address_i(i_address + reg_x + 1);

}
