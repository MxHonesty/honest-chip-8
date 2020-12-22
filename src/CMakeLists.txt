cmake_minimum_required(VERSION 3.17)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp chip_types.h Emulator.cpp Emulator.h hardware_emulator.cpp hardware_emulator.h tests/test_hardware_emulator.cpp tests/test_hardware_emulator.h opcode_decoder.cpp opcode_decoder.h tests/test_opcode_decoder.cpp tests/test_opcode_decoder.h)