//
// Created by Stelian Stoian on 22/12/2020.
//

#include <cstdlib>  // Used rand() method.
#include "opcode_decoder.h"


void opcode_decoder::decode_opcode(WORD opcode) {
    //printf("%x ", opcode);  // DEBUG PRINT OPCODE
    switch(opcode & 0xF000){
        case 0xF000: {
            switch(opcode & 0x00FF){
                case 0x0065: OpcodeFX65(opcode); break;
                case 0x0055: OpcodeFX55(opcode); break;
                case 0x0033: OpcodeFX33(opcode); break;
                case 0x0029: OpcodeFX29(opcode); break;
                case 0x001E: OpcodeFX1E(opcode); break;
                case 0x0018: OpcodeFX18(opcode); break;
                case 0x0015: OpcodeFX15(opcode); break;
                case 0x000A: OpcodeFX0A(opcode); break;
                case 0x0007: OpcodeFX07(opcode); break;
            }
        } break;
        case 0xE000: {
            switch(opcode & 0x000F){
                case 0x000E: OpcodeEX9E(opcode); break;
                case 0x0001: OpcodeEXA1(opcode); break;
            }
        } break;
        case 0xD000: OpcodeDXYN(opcode); break;
        case 0xC000: OpcodeCXNN(opcode); break;
        case 0xB000: OpcodeBNNN(opcode); break;
        case 0xA000: OpcodeANNN(opcode); break;
        case 0x9000: Opcode9XY0(opcode); break;
        case 0x8000: {
            switch(opcode & 0x000F){
                case 0x000E: Opcode8XYE(opcode); break;
                case 0x0007: Opcode8XY7(opcode); break;
                case 0x0006: Opcode8XY6(opcode); break;
                case 0x0005: Opcode8XY5(opcode); break;
                case 0x0004: Opcode8XY4(opcode); break;
                case 0x0003: Opcode8XY3(opcode); break;
                case 0x0002: Opcode8XY2(opcode); break;
                case 0x0001: Opcode8XY1(opcode); break;
                case 0x0000: Opcode8XY0(opcode); break;
            }
        } break;
        case 0x7000: Opcode7XNN(opcode); break;
        case 0x6000: Opcode6XNN(opcode); break;
        case 0x5000: Opcode5XY0(opcode); break;
        case 0x4000: Opcode4XNN(opcode); break;
        case 0x3000: Opcode3XNN(opcode); break;
        case 0x2000: Opcode2NNN(opcode); break;
        case 0x1000: Opcode1NNN(opcode); break;  // jump opcode.
        case 0x0000: {
            switch(opcode & 0x000F){
                case 0x000E: Opcode00EE(opcode); break;  // return subroutine.
                case 0x0000: Opcode00E0(opcode); break;  // clear screen.
            }
        } break;
        default: std::cout<<"UNSUPPORTED OPCODE"; break;
    }
}

int opcode_decoder::get_x(WORD opcode) {
    int reg_x = opcode & 0x0F00;
    reg_x >>= 8;
    return reg_x;
}

int opcode_decoder::get_y(WORD opcode) {
    int reg_y = opcode & 0x00F0;
    reg_y >>= 4;
    return reg_y;
}

void opcode_decoder::Opcode1NNN(WORD opcode) {
    hardware->set_program_counter(opcode & 0x0FFF);
}

void opcode_decoder::Opcode00E0(WORD opcode) {
    hardware->screen_data->init();
}

void opcode_decoder::Opcode00EE(WORD opcode) {
    WORD jump_address = hardware->stack.back();
    hardware->set_program_counter(jump_address);
    hardware->stack.pop_back();
}

opcode_decoder::opcode_decoder(Hardware *he) {
    hardware = he;
}

void opcode_decoder::Opcode2NNN(WORD opcode) {
    hardware->stack.push_back(hardware->get_program_counter());  // Push counter to stack.
    hardware->set_program_counter(opcode & 0x0FFF);  // Jump to NNN.
}

void opcode_decoder::Opcode5XY0(WORD opcode) {
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);

    if(hardware->get_register(reg_x) == hardware->get_register(reg_y))
        hardware->set_program_counter(hardware->get_program_counter() + 2);
}

void opcode_decoder::Opcode8XY5(WORD opcode) {
    hardware->set_register(0xF, 1);
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);

    BYTE x_value = hardware->get_register(reg_x);
    BYTE y_value = hardware->get_register(reg_y);
    if(y_value > x_value)
        hardware->set_register(0xF, 0);  // Update carry-flag.
    hardware->set_register(reg_x, x_value - y_value);
}

void opcode_decoder::OpcodeDXYN(WORD opcode) {
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);

    int height = opcode & 0x000F;
    int x_position = hardware->get_register(reg_x);
    int y_position = hardware->get_register(reg_y);

    hardware->set_register(0xF, 0);  // Reset carry-flag.

    for(int yline = 0; yline < height; yline++){
        BYTE data = hardware->get_memory(hardware->get_address_i() + yline);
        int xpixelinv = 7;
        int xpixel = 0;
        for(xpixel = 0; xpixel < 8; xpixel++, xpixelinv--){
            int mask = 1 << xpixelinv;
            if(data & mask){
                int x = x_position + xpixel;
                int y = y_position + yline;
                if(hardware->screen_data->get_pixel(x, y) == 1)
                    hardware->set_register(0xF, 1);  // Collision.
                hardware->screen_data->invert_pixel(x, y);
            }
        }
    }
}

void opcode_decoder::OpcodeFX33(WORD opcode) {
    int reg_x = get_x(opcode);
    BYTE value = hardware->get_register(reg_x);

    BYTE hundreds = value / 100;
    BYTE tens = (value / 10) % 10;
    BYTE units = value % 10;

    WORD i_address = hardware->get_address_i();
    hardware->set_memory(i_address, hundreds);
    hardware->set_memory(i_address+1, tens);
    hardware->set_memory(i_address+2, units);
}

void opcode_decoder::OpcodeANNN(WORD opcode) {
    WORD new_address = opcode & 0x0FFF;
    hardware->set_address_i(new_address);
}

void opcode_decoder::OpcodeBNNN(WORD opcode) {
    WORD jump_address = opcode & 0x0FFF;
    hardware->set_program_counter(jump_address + hardware->get_register(0));
}

void opcode_decoder::Opcode3XNN(WORD opcode) {
    BYTE value = opcode & 0x00FF;
    int reg_x = get_x(opcode);
    WORD current_position = hardware->get_program_counter();
    if(value == hardware->get_register(reg_x))
        hardware->set_program_counter(current_position + 2);
}

void opcode_decoder::Opcode4XNN(WORD opcode) {
    BYTE value = opcode & 0x00FF;
    int reg_x = get_x(opcode);
    WORD current_position = hardware->get_program_counter();
    if(value != hardware->get_register(reg_x))
        hardware->set_program_counter(current_position + 2);
}

void opcode_decoder::Opcode6XNN(WORD opcode) {
    BYTE value = opcode & 0x00FF;
    int reg_x = get_x(opcode);
    hardware->set_register(reg_x, value);
}

void opcode_decoder::Opcode7XNN(WORD opcode) {
    BYTE value = opcode & 0x00FF;
    int reg_x = get_x(opcode);
    BYTE value_from_reg = hardware->get_register(reg_x);
    BYTE new_value = value_from_reg + value;
    hardware->set_register(reg_x, new_value);
}

void opcode_decoder::Opcode8XY0(WORD opcode) {
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);
    hardware->set_register(reg_x, hardware->get_register(reg_y));
}

void opcode_decoder::Opcode8XY1(WORD opcode) {
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    BYTE y_value = hardware->get_register(reg_y);
    hardware->set_register(reg_x, x_value | y_value);
}

void opcode_decoder::Opcode8XY2(WORD opcode) {
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    BYTE y_value = hardware->get_register(reg_y);
    hardware->set_register(reg_x, x_value & y_value);

}

void opcode_decoder::Opcode8XY3(WORD opcode) {
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    BYTE y_value = hardware->get_register(reg_y);
    hardware->set_register(reg_x, x_value ^ y_value);

}

void opcode_decoder::Opcode8XY4(WORD opcode) {
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    BYTE y_value = hardware->get_register(reg_y);

    hardware->set_register(0xF, 0);
    if((int)x_value + (int)y_value > 255)  // If they add up higher than 8-bit int limit.
        hardware->set_register(0xF, 1);
    BYTE new_value = x_value + y_value;
    hardware->set_register(reg_x, new_value);
}

void opcode_decoder::Opcode8XY6(WORD opcode) {
    int reg_x = get_x(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    hardware->set_register(0xF, x_value & 1);
    x_value >>= 1;
    hardware->set_register(reg_x, x_value);
}

void opcode_decoder::Opcode8XY7(WORD opcode) {
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    BYTE y_value = hardware->get_register(reg_y);

    hardware->set_register(0xF, 1);
    if(x_value > y_value)
        hardware->set_register(0xF, 0);

    BYTE new_value = y_value - x_value;
    hardware->set_register(reg_x, new_value);
}

void opcode_decoder::Opcode8XYE(WORD opcode) {
    int reg_x = get_x(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    hardware->set_register(0xF, x_value & 0x80);
    x_value <<= 1;
    hardware->set_register(reg_x, x_value);
}

void opcode_decoder::Opcode9XY0(WORD opcode) {
    int reg_x = get_x(opcode);
    int reg_y = get_y(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    BYTE y_value = hardware->get_register(reg_y);

    WORD current_position = hardware->get_program_counter();
    if(x_value != y_value)
        hardware->set_program_counter(current_position + 2);
}

void opcode_decoder::OpcodeCXNN(WORD opcode) {
    std::cout<<"APELAT ";
    int reg_x = get_x(opcode);
    BYTE value = opcode & 0x00FF;
    BYTE random_value = rand()%256;
    hardware->set_register(reg_x, random_value & value);
}

void opcode_decoder::OpcodeFX1E(WORD opcode) {
    int reg_x = get_x(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    WORD i_value = hardware->get_address_i();
    hardware->set_address_i(i_value + x_value);
}

void opcode_decoder::OpcodeFX29(WORD opcode) {
    int reg_x = get_x(opcode); // Font values start at 0. Each character is 5 bytes long.
    WORD position = hardware->get_register(reg_x);
    hardware->set_address_i(position * 5);
}

void opcode_decoder::OpcodeFX55(WORD opcode) {
    int reg_x = get_x(opcode);
    WORD i_address = hardware->get_address_i();
    for(int i = 0; i <= reg_x; i++)
        hardware->set_memory(i_address + i, hardware->get_register(i));
    hardware->set_address_i(i_address + reg_x + 1);
}

void opcode_decoder::OpcodeFX65(WORD opcode) {
    int reg_x = get_x(opcode);
    WORD i_address = hardware->get_address_i();
    for(int i = 0; i <= reg_x; i++)
        hardware->set_register(i, hardware->get_memory(i_address + i));
    hardware->set_address_i(i_address + reg_x + 1);
}

void opcode_decoder::OpcodeEX9E(WORD opcode) {
    int reg_x = get_x(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    WORD current_position = hardware->get_program_counter();
    if(hardware->is_key_pressed(x_value))
        hardware->set_program_counter(current_position + 2);
}

void opcode_decoder::OpcodeEXA1(WORD opcode) {
    int reg_x = get_x(opcode);
    BYTE x_value = hardware->get_register(reg_x);
    WORD current_position = hardware->get_program_counter();
    if(not hardware->is_key_pressed(x_value))
        hardware->set_program_counter(current_position + 2);
}

void opcode_decoder::OpcodeFX0A(WORD opcode) {
    int reg_x = get_x(opcode);
    bool key_pressed = false;
    for(int i = 0; i < 16; i++)  // Loop through all the keys and check if pressed.
        if(hardware->is_key_pressed(i)) {
            hardware->set_register(reg_x, i);
            key_pressed = true;
    }
    if(not key_pressed)
        hardware->set_program_counter(hardware->get_program_counter() - 2);  // Execute this opcode again.
}

void opcode_decoder::OpcodeFX07(WORD opcode) {
    int reg_x = get_x(opcode);
    hardware->set_register(reg_x, hardware->get_delay_timer());
}

void opcode_decoder::OpcodeFX15(WORD opcode) {
    int reg_x = get_x(opcode);
    hardware->set_delay_timer(hardware->get_register(reg_x));
}

void opcode_decoder::OpcodeFX18(WORD opcode) {
    /*
     * Audio support will be implemented in the future!
     */
}

opcode_decoder::opcode_decoder() {
    hardware = nullptr;
}

