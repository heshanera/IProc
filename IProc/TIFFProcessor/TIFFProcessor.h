/* 
 * File:   TIFFProcessor.h
 * Author: heshan
 *
 * Created on December 2, 2017, 9:28 AM
 */

#ifndef TIFFPROCESSOR_H
#define TIFFPROCESSOR_H

#include <stdio.h>
#include <iostream>
#include "tiffio.h"
#include "../PixelProcessor/pixel.h"

class TIFFProcessor {
public:
    TIFFProcessor();
    TIFFProcessor(const TIFFProcessor& orig);
    virtual ~TIFFProcessor();
    
    int readImage(char* path);
    int writeImage(char* path,ImageDataStruct);
    
    int getWidth();
    int getHeight();
    int setWidth(int width);
    int setHeight(int height);
    
    int fillRGBApixelArray(uint32* raster,int npixels);
    ImageDataStruct getImageDataStruct();
    
private:
    int imgHeight,imgWidth;
    ImageDataStruct imgDataStruct;

};

#endif /* TIFFPROCESSOR_H */

