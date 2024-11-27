#include <math.h>
#include <stddef.h>
#include "header.h"
//bitmask implementation
/**
 * @brief 
 * 
 * @param degree degree of curve
 * @param x x coordinate
 * @param y y coordinate
 * @return size_t index of searched point
 */
size_t z_curve_pos(unsigned degree, coord_t x, coord_t y) {
    int indx = 0;
    int length = 1 << (degree);
    if ((x >= length) || (y >= length)) {//if coordinates out of array
        return -1;
    }
    for (unsigned i = 0; i < degree; i++) {
        int bit = x % 2;//last bit of x
        bit = bit << (2*i);//shifting to 2i position
        indx += bit;//writing bit to 2i postion in indx
        x = x >> 1;//shift to the right
        bit = y % 2;//last bit of y
        bit = bit << (2*i + 1);//shifitng to 2i+1 position
        indx += bit;//writing bit to the position
        y = y >> 1;//shifiting y to the left
    }
    return indx;
}