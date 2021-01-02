//
// Created by Stelian Stoian on 22/12/2020.
//

#ifndef SRC_EMULATOR_H
#define SRC_EMULATOR_H
#include "hardware_emulator.h"
#include "View.h"

class Emulator{
    graphic gfx;  // Instantiate graphics class.
public:
    Hardware hardware;
    View *view;
    Emulator();  // Constructor

};


#endif //SRC_EMULATOR_H
