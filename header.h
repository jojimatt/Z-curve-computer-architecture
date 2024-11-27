#include <stddef.h>
#include <stdio.h>

typedef int coord_t;
void plot(long length,unsigned degree,coord_t* x,coord_t* y);
void z_curve(unsigned length, coord_t* x, coord_t* y);
void z_curve_V1(unsigned length, coord_t* x, coord_t* y);
void z_curve_V2(unsigned length, coord_t* x, coord_t* y);
void z_curve_V3(unsigned length, coord_t* x, coord_t* y);
size_t z_curve_pos(unsigned degree, coord_t x, coord_t y);
size_t z_curve_pos_V1(unsigned degree, coord_t x, coord_t y);
size_t z_curve_pos_V2(unsigned degree, coord_t x, coord_t y);
void z_curve_at(unsigned degree, size_t idx, coord_t* x, coord_t* y);
void z_curve_at_V1(unsigned degree, size_t idx, coord_t* x, coord_t* y);