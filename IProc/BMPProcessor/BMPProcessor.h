/* 
 * File:   BMPProcessor.h
 * Author: heshan
 *
 * Created on December 3, 2017, 12:29 AM
 */

#ifndef BMPPROCESSOR_H
#define BMPPROCESSOR_H

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "../PixelProcessor/pixel.h"

class BMPProcessor {
public:
    BMPProcessor();
    BMPProcessor(const BMPProcessor& orig);
    virtual ~BMPProcessor();
    
    int readImage(char* path);
    int writeImage(char* path,ImageDataStruct);
    
    int getWidth();
    int getHeight();
    int setWidth(int width);
    int setHeight(int height);
    
    int fillRGBApixelArray(unsigned char* data, int row);
    ImageDataStruct getImageDataStruct();
    
    int freeImageData();
    
private:
    int imgHeight,imgWidth;
    ImageDataStruct imgDataStruct;
    
};

#endif /* BMPPROCESSOR_H */

