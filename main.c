#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
/**
 * @brief  Rahmenprogram
 * 
 * @param x list of x coordinates
 * @param y list of y coordinates
 * @param length length of list
 * @param degree degree of z curve
 * @param bflag flag for option B (testing).Also to represent number of repetitions
 * @param dflag flag for option d(To see if degree is given)
 * @param pflag flag for option p(z_curve_pos)
 * @param iflag flag for option i(z_curve_at)
 * @param xflag flag for xcoordinate for pos function.Also xcoordinate
 * @param yflag flag for ycoordinate for pos function.Also ycoordinate
 * @param implementation variable for storing implementation number (z_curve)
 * @param option variable for commandlline parsing
 * @param idx index for z_curve_at function
 *
 */

void coord_free(coord_t *x, coord_t *y)//to free malloc allocated memory
{
    free(x);
    free(y);
}
void printhelp(){

printf("Use ./main - and the following option\n\n");//printing help for option h and --help
            printf("-d<int>    : o give a degree >=1\n");
            printf("-V<int>    : select implemenation version\n\t0:Main Implementation(simd version 1)(z_curve)\n\t1:Simd (version 2) implementation(z_curve_V1)\n\t2:Bitmask implementation(z_curve_V2)\n");
            printf(" \t3:First and basic implementation(z_curve_V3)\n");
            printf("\tIf option not set main Implementation selected(For eg. ./main -d<int> calls main Implementation).\n");
            printf("\tz_curve_at has only two implementations and z_curve_pos has 3\n");
            printf("-B<int>    : number of repetitions for testing\n");
            printf("-h,--help  : help\n");
            printf("-i<int>    :To set index and call z_curve_at\n");
            printf("-p         : use this to call z_curve_pos\n");
            printf("<int> <int>: to give coordinates for z_curve_pos funciton\n");
}

int main(int argc, char **argv)
{  
     errno=0;
    char* endptr;
    long length;
    int option = 0;
    int bflag=0,pflag=0,iflag=0,dflag=0,xflag=-1,yflag=-1; //flags for commandline  options
    long implementation = 0;
    unsigned degree = 0;
    size_t idx=-1;
    for(int i=1;i<argc;i++){
        if(xflag>=0&&yflag>=0)
         break;
        
        long number=strtol(argv[i],&endptr,10);
        
        if(endptr==argv[i]||*endptr!='\0'||errno==ERANGE)
         continue;
        
        if(xflag==-1){
            xflag=(int)number;
        }
        else{
          yflag=(int)number;
        }

    }

    while ((option = getopt(argc, argv, "d:V:B:pi:hxy-::")) != -1)// command line options
    {
     switch (option)
     {
       
        //give degree
        case 'd':
        { //SIMD
             dflag=1;
             errno=0;
            long temp =strtol(optarg,&endptr,10);
            if(endptr==optarg||*endptr!='\0'||errno==ERANGE){
                fprintf(stderr,"Please give valid degree\n.");
                return -1;
            }
            
            if (temp >= 32)//because of segmentation fault.Memory shortage
            {
                printf("degree 32 and over is too big for malloc\n");
                return EXIT_FAILURE;
            }
            if (temp <0)//not possible to draw z_curve
            {
                fprintf(stderr, "Error:degree less than 0.Please try again with degree>=0\n");
                return EXIT_FAILURE;
            }
            degree=(unsigned)temp;
            break;
        }
       //selection of implementation.
        case 'V':
        { 
            errno=0;
            implementation =strtol(optarg,&endptr,10);
            if(endptr==optarg||*endptr!='\0'||errno==ERANGE){
                fprintf(stderr,"Please give valid version\n.");
                return -1;
            }
            if(implementation>=4){//only implementation till 3
                fprintf(stderr,"Please give a valid implementaion.Use ./main -h to see all the options\n");
                return EXIT_FAILURE;
            }
            break;
        }
        // to call z_curve_pos
        case 'p':
        {   pflag=1;
            break;
        }
            // BENCHMARKS
            //bflag used as number of repetitions
        case 'B':
        {   
             errno=0;
            long temp =strtol(optarg,&endptr,10);
            
            if(endptr==optarg||*endptr!='\0'||errno==ERANGE){
                fprintf(stderr,"Please give valid repitition\n.");
                return -1;
            }
            bflag=(int)temp;
            if (bflag <= 0)//not a valid repitition
            {
                fprintf(stderr, "Please give a valid repetition for testing and try again.Use ./main -h for help\n");
                return EXIT_FAILURE;
            }
            break;
        }
       
        //To call z_curve_at
        case 'i':{
            iflag=1;
             errno=0;
            long temp =strtol(optarg,&endptr,10);
            
            if(endptr==optarg||*endptr!='\0'||errno==ERANGE){
                fprintf(stderr,"Please give valid index\n.");
                return -1;
            }
            if(temp<=-1){
                fprintf(stderr,"Please use an index>=0 and try again.\n");
                return EXIT_FAILURE;
            }
            
            idx=(size_t)temp;
            break;
        }
        //help
        case 'h':
        {   printhelp();
            break;
        }
        //help
        case '-':
        {   
            if(!strcmp(optarg,"help"))
             printhelp();
            else
             fprintf(stderr,"Use ./main -h for help\n");
            break;
        }
        default:
        {
            fprintf(stderr,"Use ./main -h for help\n");
            return EXIT_FAILURE;
        }
     }
    }      
    //end of switch 
     
     
    if(dflag==0){//to check if degree is given or not
         fprintf(stderr,"Please give a degree.Use ./main -h for help\n");
         return EXIT_FAILURE;
    } 
          length = (long)(pow(2, 2 * ((double)degree)));
        coord_t *x, *y;
        x = (coord_t *)malloc(sizeof(coord_t) * length);
        y = (coord_t *)malloc(sizeof(coord_t) * length);
        if ((x == NULL) || (y == NULL)) {
            printf("Error at allocating memory\n");
            return -1;
        }


        //calling z_curve implementation according to option    only if pflag iflag and bflag not set
    if(!pflag&&!bflag&&!iflag){

            switch (implementation)
            {
                
                case 0:
                {
                    z_curve(degree, x, y);
                    printf("Main implementation (simd version 1) used\n");
                    break;
                }
                case 1:
                {
                    z_curve_V1(degree, x, y);
                    printf("z_curve_V1(simd version 2) used\n");
                    break;
                }
                case 2:
                {
                    z_curve_V2(degree, x, y);
                    printf("z_curve_V2(bitmasking) used\n");
                    break;
                }
                case 3:
                {
                    z_curve_V3(degree, x, y);
                    printf("z_curve_V3(first and base) used\n");
                    break;
                }
                default:{
                    fprintf(stderr, "Wrong implementation version given.Please try again with numbers in between 0-3.Use ./main -h to see the corresponding funcitons\n");
                    return EXIT_FAILURE;
                }
            }
        plot(length, degree, x, y); //to make svg file
        printf("\n");
    }        
    //calling z_curve_pos if pflag is set     
    if(pflag){
        //xflag x coordinate(int)
        //yflag y coordinate(int)
        size_t (*z)(unsigned, coord_t, coord_t); //to assign calling function
        if(xflag<0||yflag<0){
            fprintf(stderr,"Please give valid x and y coordinates for the Pos function.\nUse ./main -h for help\n");
            return -1;
        }
    
        switch (implementation)
        {
            case 0:
            {
                z = &z_curve_pos;
                printf("z_curve_pos(bitmask)\n");
                break;
            }
            case 1:
            {
                z = &z_curve_pos_V1;
                printf("z_curve_pos_V1(quadtree)\n");
                break;
            }
            case 2:
            {
                z = &z_curve_pos_V2;
                printf("z_curve_pos_V2(base )\n");
                break;
            }
            default:{
                fprintf(stderr, "Please give a valid implementation version.z_curve_pos only has 3 versions.0,1 and 2.\n.Use ./main -h help and try again\n");
                return EXIT_FAILURE;
                }
        }
        int tempindex =(int) (*z)(degree, (coord_t)xflag,(coord_t) yflag);
        if(tempindex==-1){
            printf("x or y coordinate doesn't exist in z_curve.Please try again with valid coordinates\nUse ./main -h for help");
            return -1;
        }
        printf("Index at (%d,%d) is: %d\n",xflag,yflag,tempindex);
        
    }
           
    //Testing if bflag is set with bflag as number of repitions 
    if(bflag){

        void (*z)(unsigned, coord_t *, coord_t *);//to assign the implementation
        //bflag=repetition
        
     switch (implementation)
        {
            case 0:
            {
                z = &z_curve;
                printf("Testing z_curve(simd version 1) Implementation with repetition %d\n", bflag);
                break;
            }
            case 1:
            {
                z = &z_curve_V1;
                printf("Testing z_curve(simd version 2) Implementation with repetition %d\n", bflag);
                break;
            }
            case 2:
            {
                z = &z_curve_V2;
                printf("Testing z_curve(bitmasking) Implementation with repetition %d\n", bflag);
                break;
            }
            case 3:
            {
                z = &z_curve_V3;
                printf("Testing z_curve(first and basic) Implementation with repetition %d\n", bflag);
                break;
            }
            default:{
                fprintf(stderr, "Implemenation version  wrong.Please use  ./main -h for help and try again\n");
                return EXIT_FAILURE;
                }
        }

        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < bflag; i++)
        {
            (*z)(degree, x, y);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time = end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
        printf("done with %f seconds\n", time); 
    }
    if(iflag){
        void (*z)(unsigned,size_t,coord_t*,coord_t*);
        coord_t x=0;
        coord_t y=0;
        
        if(idx>=(int)pow(2,2*degree)){
            fprintf(stderr,"Coordinates does not exist for the given Index in the z_curve.Please give a valid index and try again\n");
            return EXIT_FAILURE;
        }

        switch (implementation)
        {
            case 0:
            {
                z = &z_curve_at;
                printf(" z_curve_at(bitmasking) Implementation\n");
                break;
            }
            case 1:
            {
                z = &z_curve_at_V1;
                printf("z_curve_at_V1 (base) Implementation\n");
                break;
            }

            default:{
                fprintf(stderr, "Please give a valid implementation version.z_curve_at only has 2 versions.0 and 1.\nUse ./main -h for help ");
                return EXIT_FAILURE;}
        } 
        (*z)(degree,idx,&x,&y);
            printf("Coordinates at Index:%lu are x: %d y: %d\n",idx, x, y);
    }
    coord_free(x, y);
 
    
    printf("Done\n");

    return 0;
}
