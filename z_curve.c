#include <math.h>
#include <stddef.h>
#include "header.h"
#include <immintrin.h>
#include <emmintrin.h>
#include <string.h>
//implementation simd version 1
/**
 * @brief 
 * 
 * @param degree 
 * @param x is list of x coordinates
 * @param y is list of y coordinates
 */
void z_curve(unsigned degree, coord_t* x, coord_t* y) {
    x[0] = 0;//coordinates for the first point of Z curve(n=0)
    y[0] = 0;
    if (degree==0) {//for degrree=0 return just one point
        return;
    }
    long j = 1;//pointer for next point which we need to initialize
    for (unsigned i = 1; i <= 1; i++) {//in every loop iteration we initialize coordinates for some degree i
        for (long i1 = 0; i1 <= j; i1++) {
            x[j+i1] = x[i1] + (int)pow(2, i-1);//initializing all x coordinates which are shifted right
            y[j+i1] = y[i1];//y coordinates are copied
        }
        j*=2;//now pointer looks to a adress of x and y coordinates of points which are in below part of Z curves
        //(x coordinates are the same then and y are shifted)
        for (long i1 = 0; i1 <= j; i1++) {
          x[j+i1] = x[i1];//coping x coordinates
          y[j+i1] = y[i1] + (int)pow(2, i-1);//shifting y coordinates
        }
        j*=2;//now pointer looks on the adress after last coordinate x nd y
    }
    if (degree < 2) {//for degree >= 2 in this implementation we are using simd
        return;
    }
    j = 4;//pointer at the first point which written in degree=2
    for (unsigned i = 2; i <= degree; i++) {//for every degree from 2 coordinates are calculated
        int p1 = 1 << (i - 1);//calculating shift(p1) for degree i, it is 2**(i-1)
        int p[] = {p1, p1, p1, p1};//making array of 4 numbers p1
        __m128i b = _mm_loadu_si128((__m128i*) p);//writing it in a form that is sued for simd operations
        for (long i1 = 0; i1 < j; i1+=4) {//writing coordinates x which are shifted right
            __m128i a = _mm_loadu_si128((__m128i*) &(x[i1]));
            a = _mm_add_epi32(b, a);//shifting x coordinates
            _mm_storeu_si128((__m128i*) &(x[j+i1]), a);
            a = _mm_loadu_si128((__m128i*) &(y[i1]));//coping y coordinates
            _mm_storeu_si128((__m128i*) &(y[j+i1]), a);
        }
        j*=2;
        for (long i1 = 0; i1 < j; i1+=4) {
            __m128i a = _mm_loadu_si128((__m128i*) &(x[i1]));
            _mm_storeu_si128((__m128i*) &(x[j+i1]), a);//coping all coordinates x which are below written coordinates(here x doesn't change)
            a = _mm_loadu_si128((__m128i*) &(y[i1]));
            a = _mm_add_epi32(a, b);//shifting y coordinates
            _mm_storeu_si128((__m128i*) &(y[j+i1]), a);
        }
        j*=2;
    }
}
