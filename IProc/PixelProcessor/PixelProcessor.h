/* 
 * File:   PixelProcessor.h
 * Author: heshan
 *
 * Created on September 24, 2017, 1:02 PM
 */

#ifndef PIXELPROCESSOR_H
#define PIXELPROCESSOR_H

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include "pixel.h"

class PixelProcessor {
public:
    PixelProcessor();
    PixelProcessor(const PixelProcessor& orig);
    virtual ~PixelProcessor();
    
    RGBApixel getPixel(int x, int y, unsigned char**);
    
    u_int* resize(int, int, int, int, u_int*);
    unsigned char ** resize(int, int, int, int, unsigned char**);
    u_int* crop(int, int, int, int, int, u_int*);
    u_int* shear();
    u_int* grayScale(int, int, u_int*);
    u_int* rotate();
    u_int* binary(int, int, int, u_int*);
    
    
    
private:
    int* pixelArray;
    RGBApixel * rgbaPixArray;

};

#endif /* PIXELPROCESSOR_H */