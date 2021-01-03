//
// Created by Stelian Stoian on 22/12/2020.
//

#ifndef SRC_EMULATOR_H
#define SRC_EMULATOR_H
#include "hardware_emulator.h"
#include "View.h"
#include "opcode_decoder.h"

class Emulator{
    graphic gfx;  // Instantiate graphics class.
    int opcodes_per_second;  // opcodes to be executed each second.
    void execute_next_opcode();  // Executes the next opcode.
    bool running;
public:
    Hardware hardware;
    View *view;  // Pointer to initialized view.
    opcode_decoder decoder;
    Emulator();  // Constructor
    void load_game();  // Loads the game into memory.
    void main_loop();  // The main game loop.
    void init();  // Init the emulator.

};


#endif //SRC_EMULATOR_H
