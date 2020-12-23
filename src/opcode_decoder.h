//
// Created by Stelian Stoian on 22/12/2020.
//

#ifndef SRC_OPCODE_DECODER_H
#define SRC_OPCODE_DECODER_H
#include "hardware_emulator.h"

class opcode_decoder {
    Hardware *hardware;

    void Opcode1NNN(WORD opcode);  // Jump opcode.
    void Opcode2NNN(WORD opcode);  // Calls subroutine at NNN.
    void Opcode00E0(WORD opcode);  // Clear screen opcode.
    void Opcode00EE(WORD opcode);  // Return subroutine.
    void Opcode5XY0(WORD opcode);  // Skip next instruction if VX == VY.
    void Opcode8XY5(WORD opcode);  // reg_y is subtracted from reg_x.
    void OpcodeDXYN(WORD opcode);  // Draws a sprite as X,Y Coords. 8px wide and N px tall.
    void OpcodeFX33(WORD opcode);  // Stores each digit of the value in reg_x.
    void OpcodeFX55(WORD opcode);  // Stores registers in memory at address I.
public:
    explicit opcode_decoder(Hardware he);  // Constructor.
    void decode_opcode(WORD opcode);  // Translates the opcode into a hardware function.
};


#endif //SRC_OPCODE_DECODER_H
