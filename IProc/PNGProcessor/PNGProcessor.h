/* 
 * File:   PNGProcessor.h
 * Author: heshan
 *
 * Created on September 16, 2017, 10:37 PM
 */

#ifndef PNGPROCESSOR_H
#define PNGPROCESSOR_H

#include <iostream>
#include <stdio.h>
#include <png.h>
#include "zlib.h"
#include "writepng.h"
#include "../PixelProcessor/pixel.h"

class PNGProcessor {
public:
    PNGProcessor();
    PNGProcessor(const PNGProcessor& orig);
    virtual ~PNGProcessor();
    
    int readPNGVersionInfo();
    int readImage(char* path);
    int processImage();
    int writeImage(char* path,ImageDataStruct);
    
    int getWidth();
    int getHeight();
    int setWidth(int width);
    int setHeight(int height);
    
    png_bytep* getPixelArray();
    
    int fillRGBApixelArray();
    ImageDataStruct getImageDataStruct();
    
    
private:
    int colorType, bitDepth;
    png_uint_32 imgWidth, imgHeight;  //unsigned int
    png_color_16p pBackground;
    unsigned char *red, *green, *blue;
    double gamma, displayExponent;
    ImageDataStruct imgDataStruct;

};

#endif /* PNGPROCESSOR_H */