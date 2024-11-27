#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include "header.h"
//basic implementation 
//calls z_curve and then finds position using the list
size_t z_curve_pos_V2(unsigned degree, coord_t x, coord_t y) {
    unsigned length =(unsigned) (pow(2,2*((double)degree)));
    coord_t* x_list = malloc(sizeof(coord_t) * length);
    coord_t* y_list = malloc(sizeof(coord_t) * length);
    if (x_list == 0 || y_list == 0) {
        fprintf(stderr, "Memmory not allocated in z_curve_pos_V2.c");
        return -1;
    }
    z_curve(degree, x_list, y_list);
    for (unsigned i = 0; i < length; i++) {
        if ((x_list[i] == x) && (y_list[i] == y)) {
            free(x_list);
            free(y_list);
            return i;
        }
    }
    free(x_list);
    free(y_list);
    return -1;
}

