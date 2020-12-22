//
// Created by Stelian Stoian on 22/12/2020.
//

#ifndef SRC_OPCODE_DECODER_H
#define SRC_OPCODE_DECODER_H
#include "hardware_emulator.h"

class opcode_decoder {
    Hardware *hardware;

    static void Opcode1NNN(WORD opcode);  // Jump opcode.
    static void Opcode00E0(WORD opcode);  // Clear screen opcode.
    static void Opcode00EE(WORD opcode);  // Return subroutine.
public:
    explicit opcode_decoder(Hardware he);  // Constructor.
    static void decode_opcode(WORD opcode);  // Translates the opcode into a hardware function.
};


#endif //SRC_OPCODE_DECODER_H
