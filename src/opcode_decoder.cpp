//
// Created by Stelian Stoian on 22/12/2020.
//

#include "opcode_decoder.h"

#include <utility>

void opcode_decoder::decode_opcode(WORD opcode) {
    switch(opcode & 0x000F){
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

}

void opcode_decoder::Opcode00E0(WORD opcode) {

}

void opcode_decoder::Opcode00EE(WORD opcode) {

}

opcode_decoder::opcode_decoder(Hardware he) {
    hardware = &he;
}
