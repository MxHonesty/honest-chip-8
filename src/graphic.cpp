//
// Created by Stelian Stoian on 29/12/2020.
//

#include <memory.h>
#include "graphic.h"

BYTE graphic::get_pixel(int pos_x, int pos_y) {
    return data[pos_x][pos_y];
}

void graphic::set_pixel(int pos_x, int pos_y, BYTE new_value) {
    data[pos_x][pos_y] = new_value;
}

void graphic::invert_pixel(int pos_x, int pos_y) {
    data[pos_x][pos_y] ^= 1;
}

void graphic::init() {
    memset(data, 0, sizeof(data));  // set registers to 0.
}
