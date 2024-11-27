#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "header.h"
//implementation basic 
//calls z_curve and then finds coordinates using list
void z_curve_at_V1(unsigned degree, size_t idx, coord_t* x, coord_t* y) {
    unsigned length =(unsigned) (pow(2,2*((double)degree)));
    if (idx >= length) {
        *x=-1;
        *y=-1;
        return;
    }
    coord_t* x_list = (coord_t*)malloc(sizeof(coord_t)*length);
    assert(x_list != NULL);

    coord_t* y_list = (coord_t*)malloc(sizeof(coord_t)*length);
    assert(y_list != NULL);

    z_curve(degree, x_list, y_list);

    *x = x_list[idx];
    *y = y_list[idx];

    free(x_list);
    free(y_list);
}