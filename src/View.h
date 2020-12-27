//
// Created by Stelian Stoian on 24/12/2020.
//

#ifndef SRC_VIEW_H
#define SRC_VIEW_H
#include "SDL.h"
#include "hardware_emulator.h"

class View {
    BYTE *keys_data;
    BYTE **screen_data;
    Hardware hardware;

public:
    explicit  View(BYTE *screen[], BYTE *keys);  // Constructor.
};


#endif //SRC_VIEW_H
