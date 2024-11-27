#include <math.h>
#include <stddef.h>
#include "header.h"
#include <string.h>
//implementation  bitmask.
#include <math.h>

/**
 * @brief for each index the coordinates are calculated with bitmasking and stored at multiple locations where the values get repeated
 * 
 * @param index temporary index for using the algorithm 
 * @param ix temporary x coordinate 
 * @param iy temporary coordinate
 * @param
 */
void z_curve_V2(unsigned degree, coord_t* x, coord_t* y) {
 
   long length=(long)pow(2, 2*degree);
    for (long i = 0; i < length; i++) {
      if(length==1){
        x[i]=0;
        break;
      }
      
      if(i!=0){
        if(i%8==0){
          i=i+8;
        }
        if(i%32==0){
          i=i+32;
        }
      }
      
      if(i>=length){
        break;
      }
      
      long index=i;
      int ix=0;
      int bitsToShift=0;
      
      while(index!=0){        //calculating x coordinate values for each index
          ix=((index&1)<<bitsToShift)+(ix); //shifting last bit of index left required number of bits,add x to it and store it in x
          index=index>>2; //shift index two bits right to get the next  bit for x
          bitsToShift++;
      }
      
      x[i]=ix;  //storing it at the current position and also where the values are repeated.
      x[i+2]=ix;
      
      if(degree>=2){
        x[i+8]=ix;
        x[i+10]=ix;
          if(degree>=3){
            x[i+32]=ix;
            x[i+34]=ix;
            x[i+40]=ix;
            x[i+42]=ix;
          }
      }
      
      if(i%2!=0)
      i=i+2;
     

    }
    for (long i = 0; i < length; i=i+2) {
      if(length==1){
        y[i]=0;
        return;
      }
      
      if(i!=0){
        if(i%4==0){
          i=i+4;
        }
        if(i%16==0){
          i=i+16;
        }
        if(i%64==0&&i<length){
          memcpy(y+i,y+i-64,64*4);
          i=i+64;
        }
      }
      
      if(i>=length){
        return;
      }
      
      long index=i;
      int iy=0;
      int bitsToShift=0;
      index= index>>1; //to get the first y coordinate
      
      while(index!=0){     //calculating y coordinate values for each index
            iy=((index&1)<<bitsToShift)+(iy);///shifting last bit of index left the required number of bits,add y to it and store it in y
          index=index>>2; ////shift index two bits right to get the next  bit for y
          bitsToShift++;
      }
      y[i]=iy;//storing it at the current position and also where the values are repeated.
      y[i+1]=iy;
      
      if(degree>=2){
        y[i+4]=iy;
        y[i+5]=iy;
          if(degree>=3){
            y[i+16]=iy;
            y[i+17]=iy;
            y[i+20]=iy;
            y[i+21]=iy;
          }
      }
    }

}
