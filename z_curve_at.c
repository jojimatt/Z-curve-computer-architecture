#include <stddef.h>
#include "header.h"
//implementation with bitmask 
/**
 * @brief 
 * 
 * @param degree degree of curve
 * @param idx index for searched coordinates
 * @param x address to write x
 * @param y address to write y
 */
void z_curve_at(unsigned degree, size_t idx, coord_t* x, coord_t* y) {
    size_t length = 1 << (degree * 2);
    if (length <= idx) {//if idx out of array return -1
        *x=-1;
        *y=-1;
        return;
    }
    for (unsigned i = 0; i < 2 * degree; i++) {
        int bit = idx % 2;//last bit of idx
        bit = bit << (int) (i/2);//shifitng it to the right position
        if (i % 2) {//if even position in idx, then write to y else to x
            *y = *y + bit;
        } else {
            *x = *x + bit;
        }
        idx = idx >> 1;//shift idx
    }
}