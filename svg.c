
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"
/**
 * @brief makes zcurve.svg for visualizing Z-Curve
 * @param length number of coordinates
 * @param factor for changing coordinates,line stroke dynamically
 * @param w width of image area
 * @param h height of image area
 */
void plot(long length, unsigned degree, coord_t *x, coord_t *y)
{
int factor = 0;
  const char *filename = "zcurve.svg";
  FILE *f = fopen(filename, "w");
  int w = 4000, h = 3200;
  //decreasing distance between coordinates dynamically
  if (degree <= 3)
  {
    factor = 100;
  }
  else if (degree <= 4)
  {
    factor = 50;
  }
  else if (degree <= 5)
  {
    factor = 25;
  }
  else if (degree <= 6)
  {
    factor = 12;
  }
  else if (degree <= 7)
  {
    factor = 6;
  }
  else
  {
    factor = 3;
  }
  
  //increasing image area dynamically
  if(degree>=11){
   int power=4;
   power=(int)pow(4,degree-8);
   w=w*power;
   h=h*power;
  }
  
  fprintf(f, "<svg width=\"%dpx\" height=\"%dpx\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n", w, h);
  
  //for degree 0 only one point
  if(length == 1){
    fprintf(f, "<circle r=\"0.5\" cx=\"%d\" cy=\"%d\" style=\"fill:none;stroke:black;stroke-width:1;\" />\n",
            x[0]+5,y[0]+3);
  }
 
  //printing polyline points for degrees >=1
  else{
    
    fprintf(f,"<polyline  fill=\"none\" stroke=\"black\" stroke-width=\"%d/2\" points=\"",factor/2);
    long divider = (1 << 10) - 1;//(2 power 10) -1
    for (long i = 0; i < length ; i++) {
      
      if (((i!=0) && (i% divider == 0)) && ((length - 1) != i)) {
        fprintf(f,"%d,%d ",x[i]*factor,(y[i]*factor)+3);
        fprintf(f,"\"/>\n");
        fprintf(f,"<polyline  fill=\"none\" stroke=\"black\" stroke-width=\"%d/2\" points=\"%d,%d ",factor/2, x[i]*factor,(y[i]*factor)+3);
      }
      else {
        fprintf(f,"%d,%d ",x[i]*factor,(y[i]*factor)+3);
      }

    }
  }

  fprintf(f,"\"/>");
  fprintf(f, "\n\n</svg>\n");
  fclose(f);

}