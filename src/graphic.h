//
// Created by Stelian Stoian on 29/12/2020.
//

#ifndef SRC_GRAPHIC_H
#define SRC_GRAPHIC_H
#include "chip_types.h"
/*
 * Class responsible for managing the visual data.
 */
class graphic {
    BYTE data[64][32];  // 64x32 resolution.
public:
    BYTE get_pixel(int pos_x, int pos_y);  // Get the pixel value.
    void set_pixel(int pos_x, int pos_y, BYTE new_value);  // Set the given pixel to new_value.
    void invert_pixel(int pos_x, int pos_y);  // Invert the pixel.
    void init();  // Initializes visual data matrix as 0.
    graphic();
};


#endif //SRC_GRAPHIC_H
