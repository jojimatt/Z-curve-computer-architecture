#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include "header.h"
//quadtree
/**
 * @brief 
 * This algorithm is named "quad search" with an idea derived from quadtree. 
 * It decomposes an array in to 4 parts recursively, and narrows down the scope and find an index of given x and y coordinates. 
 * @param degree 
 * @param offset being added or subtracted from a or b, changing quadrant's standard
 * @param x given x coordinate
 * @param y given y coordinate
 * @param a criteria for dividing quadrants (x achse)
 * @param b criteria for dividing quadrants (y achse)
 * @param start start index of an array 
 * @param end end index of an array
 * @return size_t found index
 */
size_t quadrant(unsigned degree, unsigned offset, coord_t x, coord_t y, coord_t a, coord_t b, size_t start, size_t end);

size_t z_curve_pos_V1(unsigned degree, coord_t x, coord_t y) {

    // list intialized 

    size_t offset = (coord_t)(pow(2, (double)degree));
    size_t arr_length = (coord_t)(pow(2, 2*(double)degree));
    coord_t a = (coord_t)(pow(2, (double)degree))/2;
    coord_t b = (coord_t)(pow(2, (double)degree))/2;

    if(x >= (coord_t)offset || y >= (coord_t)offset)
    {
        
        return -1;
    }

    size_t index = quadrant(degree, offset/4, x, y, a, b, 0, arr_length-1);

    return index;
    
}

size_t quadrant(unsigned degree, unsigned offset, coord_t x, coord_t y, coord_t a, coord_t b, size_t start, size_t end) {

    if(start == end) {
        return start;
    }

    size_t idx_1 = (size_t) (pow(2,2*((double)degree)-2) );
    size_t idx_2 = (size_t) (pow(2,2*((double)degree)-1) );
    size_t idx_3 = (size_t) (3*pow(2,2*((double)degree)-2) );

    if(x < a && y < b){
        // first quadrant
        a = a - offset;
        b = b - offset;
        end -= idx_3;

    } else if(x >= a && y < b){
        // second quadrant
        a = a + offset;
        b = b - offset;
        start += idx_1;
        end -= idx_2;

    } else if( x < a && y >= b){
        // third quadrant
        a = a - offset;
        b = b + offset;
        start += idx_2;
        end -= idx_1;

    } else if( x >= a && y >= b){
        // fourth quadrant
        a = a + offset;
        b = b + offset;
        start += idx_3;
    }

    degree = degree - 1; 
    offset = offset/2;

    size_t index = quadrant(degree, offset, x, y, a, b, start, end);

    return index;
}