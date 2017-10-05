/* 
 * File:   PNGProcessor.h
 * Author: heshan
 *
 * Created on September 16, 2017, 10:37 PM
 */

#ifndef PNGPROCESSOR_H
#define PNGPROCESSOR_H

#include <iostream>
#include <png.h>

class PNGProcessor {
public:
    PNGProcessor();
    PNGProcessor(const PNGProcessor& orig);
    virtual ~PNGProcessor();
    
    int readPNGVersionInfo();
    int readImage(char* path);
    int writeImage(char* path);
    
    
private:
    png_structp pngPointer;
    png_infop infoPointer;
    int colorType, bitDepth;
    png_uint_32 imgWidth, imgHeight;  //unsigned int
    png_color_16p pBackground;
    unsigned char *red, *green, *blue;
    double gamma, displayExponent;
    unsigned long *pRowbytes;
    int *pChannels;
    unsigned char *imageData;
    

};

#endif /* PNGPROCESSOR_H */