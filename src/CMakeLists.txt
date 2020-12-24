cmake_minimum_required(VERSION 3.17)
project(src)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include/SDL2) # SDL Headers
link_directories(${PROJECT_SOURCE_DIR}/lib/SDL2)  # SDL .a files

add_executable(src main.cpp chip_types.h Emulator.cpp Emulator.h hardware_emulator.cpp hardware_emulator.h tests/test_hardware_emulator.cpp tests/test_hardware_emulator.h opcode_decoder.cpp opcode_decoder.h tests/test_opcode_decoder.cpp tests/test_opcode_decoder.h)

target_link_libraries(src SDL2main SDL2)