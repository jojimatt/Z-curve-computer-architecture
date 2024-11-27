#include <math.h>
#include <stddef.h>
#include "header.h"
//implementation first and basic
/**
 * @brief 
 * 
 * @param degree 
 * @param x is list of x coordinates
 * @param y is list of y coordinates
 */

void z_curve_V3(unsigned degree, coord_t* x, coord_t* y) {
    x[0] = 0;//coordinates for the first point of Z curve(n=0)
    y[0] = 0;
    if (degree == 0) {//for degrree=0 return just one point
        return;
    }
    unsigned j = 1;//pointer for next point which we need to initialize
    for (unsigned i = 1; i <= degree; i++) {//in every loop iteration we initialize coordinates for some degree i
        for (unsigned i1 = 0; i1 < j; i1++) {//initializing all x coordinates which are shifted right
            x[j+i1] = x[i1] + (int)pow(2, i-1);
        }
        j*=2;//now pointer looks to a adress of x coordinates of points which are in below part of Z curves
        //(x coordinates are the same then)
        for (unsigned i1 = 0; i1 < j; i1++) {
          x[j+i1] = x[i1];//coping coordinates
        }
        j*=2;//now pointer looks on the adress after last coordinate x
    }
    
    j = 1;//below is the same algorithm as for x, but shifting is after coping(right part has the same y coordinates, below is shifted)
    for (unsigned i = 1; i <= degree; i++) {
        for (unsigned i1 = 0; i1 < j; i1++) {
            y[j+i1] = y[i1];
        }
        j*=2;
        for (unsigned i1 = 0; i1 < j; i1++) {
            y[j+i1] = y[i1] + (int)pow(2, i-1);
        }
        j*=2;
    }
}
