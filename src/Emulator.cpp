//
// Created by Stelian Stoian on 22/12/2020.
//

#include "Emulator.h"
#include <chrono>
#include <thread>

Emulator::Emulator() {
    opcodes_per_second = 600;
    gfx.init();
    hardware.screen_data = &gfx;
    decoder = opcode_decoder(&hardware);
    running = true;
}

void Emulator::execute_next_opcode() {
    WORD current_opcode = hardware.get_next_opcode();
    decoder.decode_opcode(current_opcode);
}

void Emulator::main_loop(){
    int opcodes_per_frame = opcodes_per_second / 60;
    while (not view->quit) {  // Each loop is executed once a frame.
        view->handle_events();
        for(int i = 0; i < opcodes_per_frame; i++){  // Execute opcodes_per_frame opcodes every frame.
            execute_next_opcode();
        }
        view->draw_screen_data();  // Draw the screen data every frame.
        hardware.tick_timers();   // Tick timers once every frame.
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void Emulator::load_game() {
    hardware.load_game_into_memory(R"(D:\Projects\C++\honest-chip-8\roms\Space Invaders [David Winter].ch8)");  // Add the filename HERE.
}

void Emulator::init() {
    load_game();
    main_loop();
}

