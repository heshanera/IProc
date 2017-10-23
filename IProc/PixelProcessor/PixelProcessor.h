/* 
 * File:   PixelProcessor.h
 * Author: heshan
 *
 * Created on September 24, 2017, 1:02 PM
 */

#ifndef PIXELPROCESSOR_H
#define PIXELPROCESSOR_H

#include <stdio.h>
#include <math.h>
#include <sys/types.h>

class PixelProcessor {
public:
    PixelProcessor();
    PixelProcessor(const PixelProcessor& orig);
    virtual ~PixelProcessor();
    
    int resize(int, int);
    int crop(int, int, int, int, int, int*);
    int shear();
    int grayScale();
    int rotate();
    
private:
    int* pixelArray;

};

#endif /* PIXELPROCESSOR_H */