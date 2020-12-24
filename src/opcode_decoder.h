//
// Created by Stelian Stoian on 22/12/2020.
//

#ifndef SRC_OPCODE_DECODER_H
#define SRC_OPCODE_DECODER_H
#include "hardware_emulator.h"

/*
 * Interfaces with hardware class through:
 * get_register, set_register, get_program_counter, set_program_counter, get_memory, set_memory.
 */
class opcode_decoder {
    Hardware *hardware;

    // Utils.

    static int get_x(WORD opcode);  // Get the X value in 0x0X00;
    static int get_y(WORD opcode);  // Get the Y value in 0x00Y0;

    // Opcode handling.

    void Opcode00E0(WORD opcode);  // Clear screen opcode.
    void Opcode00EE(WORD opcode);  // Return subroutine.
    void Opcode1NNN(WORD opcode);  // Jump opcode.
    void Opcode2NNN(WORD opcode);  // Calls subroutine at NNN.
    void Opcode3XNN(WORD opcode);  // Skip next instr if NN == VX.
    void Opcode4XNN(WORD opcode);  // Skip next instr if NN != VX.
    void Opcode5XY0(WORD opcode);  // Skip next instruction if VX == VY.
    void Opcode6XNN(WORD opcode);  // Set VX to NN.
    void Opcode7XNN(WORD opcode);  // Add NN to VX (Doesn't affect carry).
    void Opcode8XY0(WORD opcode);  // Sets the value of VX to VY.
    void Opcode8XY1(WORD opcode);  // Sets VX to VX BITWISE_OR VY.
    void Opcode8XY2(WORD opcode);  // Sets VX to VX BITWISE_AND VY.
    void Opcode8XY3(WORD opcode);  // Sets VX to VX BITWISE_XOR VY.
    void Opcode8XY4(WORD opcode);  // Adds VY to VX. Changes Carry.
    void Opcode8XY5(WORD opcode);  // reg_y is subtracted from reg_x.
    void Opcode8XY6(WORD opcode);  // Stores least significant bit of VX to VF and shifts VX right.
    void Opcode8XY7(WORD opcode);  // Sets VX to VY - VX. VF set to 0 when borrow.
    void Opcode8XYE(WORD opcode);  // Move most significant bit of VX to VF. Shift VX left.
    void Opcode9XY0(WORD opcode);  // Skip the next instruction if VX doenst equal VY.
    void OpcodeANNN(WORD opcode);  // Sets I to address NNN.
    void OpcodeBNNN(WORD opcode);  // Jump to address NNN + V0.
    void OpcodeCXNN(WORD opcode);  // Sets VX to random number BITWISE_AND NN.
    void OpcodeDXYN(WORD opcode);  // Draws a sprite as X,Y Coords. 8px wide and N px tall.
    void OpcodeEX9E(WORD opcode);  // Skips the next instruction if the key in VX is pressed.
    void OpcodeEXA1(WORD opcode);  // Skips the next instruction if the key in VX in NOT pressed.
    void OpcodeFX07(WORD opcode);  // Sets VX to the value of the delay timer.
    void OpcodeFX0A(WORD opcode);  // Awaits a key press and stores it in VX. Blocking operation.
    void OpcodeFX15(WORD opcode);  // Sets delay timer to VX.
    void OpcodeFX18(WORD opcode);  // Sets sound timer to VX.
    void OpcodeFX1E(WORD opcode);  // Adds VX to I. Does not affect carry.
    void OpcodeFX29(WORD opcode);  // Sets I to the location of the sprite for the character in VX.
    void OpcodeFX33(WORD opcode);  // Stores each digit of the value in reg_x.
    void OpcodeFX55(WORD opcode);  // Stores registers in memory at address I.
    // Fills V0 to VX with values from memory at addres I. I is increased by 1 for each val.
    void OpcodeFX65(WORD opcode);

public:
    explicit opcode_decoder(Hardware he);  // Constructor.
    void decode_opcode(WORD opcode);  // Translates the opcode into a hardware function.
};


#endif //SRC_OPCODE_DECODER_H
