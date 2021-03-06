//
// Created by Stelian Stoian on 22/12/2020.
//

#ifndef SRC_HARDWARE_EMULATOR_H
#define SRC_HARDWARE_EMULATOR_H

#include "graphic.h"

class Hardware {
    BYTE game_memory[0xFFF];  // 0xFFF bytes of memory.
    BYTE registers[16];  // 16 registers, 1 byte each.
    WORD address_i;  // the 16-bit address register I.
    WORD program_counter;  // 16-bit program counter. Points to the current instruction.
    BYTE delay_timer;  // The delay timer. Ticks 60 times a second.

    void init_font_data();  // Initializes font data.
public:
    std::vector<WORD> stack;  // 16-bit stack.
    BYTE keys[17] = {0};  // 1 - pressed, 0 - not pressed. Positions 0-15 - Key mapping for Chip-8. 16 - Stop emulator.
    graphic *screen_data;

    void cpu_reset();  // Reset the cpu.
    void load_game_into_memory(const char *filename);  // Load game file into memory.
    void tick_timers();  // Decreases the timers by 1 if they are greater than 0.
    WORD get_next_opcode();  // Returns the next opcode value. Increments program_counter by 2.
    Hardware();  // Constructor.


    // Getters
    bool is_key_pressed(BYTE pos);  // Returns true if the key with pos position is pressed.
    BYTE* get_game_memory();  // Returns pointer to first element of game_memory.
    BYTE get_memory(int pos);  // Returns BYTE pos from memory.
    BYTE* get_registers(); // Returns pointer to first element of registers.
    BYTE get_register(int pos);  // Get the value of the pos register.
    WORD get_address_i() const;  // Returns the value of the address register.
    WORD get_program_counter() const;  // Returns the value of the program counter.
    BYTE get_delay_timer() const;  // Returns the value of the delay timer.

    // Setters
    void set_memory(int pos, BYTE value);  // Set the pos BYTE in memory to value.
    void set_register(int pos, BYTE value);  // Set the value of the pos register at value.
    void set_address_i(WORD new_value);  // Sets the value of the address register.
    void set_program_counter(WORD new_value);  // Sets the value of the program counter.
    void set_delay_timer(BYTE new_delay_value);  // Sets the value of the delay timer.
};


#endif //SRC_HARDWARE_EMULATOR_H
