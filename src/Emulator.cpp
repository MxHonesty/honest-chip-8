//
// Created by Stelian Stoian on 22/12/2020.
//

#include "Emulator.h"

Emulator::Emulator() {
    gfx.init();
    hardware.screen_data = &gfx;
}
