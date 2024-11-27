#include <stdio.h>
#include <stddef.h>
#include <immintrin.h>
#include <emmintrin.h>
#include <math.h>
#include "header.h"
#include <stdint.h>
#include <stdalign.h>
#include <string.h>
/**
 * @brief uses simd to calculate 4 coordinates at same time and memcpy to copy repeating values
 * 
 * @param srcstart start index of the source 
 * @param deststart start index of destination
 * @param destination memory address to copy 
 * @param a first four x coordinates
 * @param b for addition to get the next four coordinates
 * @param c first 4 y coordinates
 * @return int 
 */
//main implementation.Simd version 2
//function copies values using memcpy and returns the next index
int copy(int srcstart,int deststart,coord_t* destination){
  long difference = deststart - srcstart;
  long temp = deststart + difference;
  memcpy((destination + deststart),(destination + srcstart), (difference*4));
  return temp;
}

void z_curve_V1(unsigned degree, coord_t* x, coord_t* y){
  if(degree == 0){ 
  //for degree 1 special case
    x[0]=0;
    y[0]=0;
    return;
   }
   long fullsize=(long)pow(2.0,(2*degree));
   alignas(16) int value[4]={0,1,0,1};//first 4 value for x coordinate
   alignas(16) int value2[4]={2,2,2,2};//constant to be added for both x and y to get next 4 values
   alignas(16) int value3[4]={0,0,1,1};//first 4 values for y coordinates
   __m128i a=_mm_load_si128((__m128i*)value);
   __m128i b=_mm_load_si128((__m128i*)value2);
   __m128i c=_mm_load_si128((__m128i*)value3);
   
  if(degree==1){ //for degree 1 storing first 4 values for both x and y
    _mm_store_si128((__m128i*)x,a);
    _mm_store_si128((__m128i*)y,c);
    return;
  }
   long i;
   long checkx=32; //value for checking after every 8Z in the curve to copy for x.8*4=32
   long factor=4; //to increase the number of z to copy after each iteration
   for( i=0;i<fullsize;i=i+16){
      if(i!=0&&i%checkx==0){  //checkiif the number of z is a multiple of 8
        for( long k=checkx;i%k==0;k=k*factor){//copying old repeating values for x
              i=copy(i-k,i,x);
              if(i==fullsize)
              break;
        }
      }
      if(i==fullsize)
        break;
    
    _mm_store_si128((__m128i*)(x+i),a);//calculating and storing 16 coordinates each time in X
     _mm_store_si128((__m128i*)(x+i+8),a);
     a=_mm_add_epi32(a,b);
       _mm_store_si128((__m128i*)(x+i+4),a);
     _mm_store_si128((__m128i*)(x+i+12),a);
     a=_mm_add_epi32(a,b);
    
    }
  
   long checknum=16;//value for checking after every 4Z to copy y coordinates
   for(i=0;i<fullsize;i=i+16){
      if(i!=0 && (i%checknum)==0){//checking if the number is a multiple of 4 
           for( long k=checknum;i%k==0;k=k*factor){//copying the old repeating values
              i=copy(i-k,i,y);
              if(i==fullsize)
              return;
            }
      }
     
     _mm_store_si128((__m128i*)(y+i),c);//storing and calculating 16 coordinates in y
     _mm_store_si128((__m128i*)(y+i+4),c);
     c=_mm_add_epi32(c,b);
     _mm_store_si128((__m128i*)(y+i+8),c);
     _mm_store_si128((__m128i*)(y+i+12),c);
     c=_mm_add_epi32(c,b);
   }
   
}