/* 
 * File:   IProc.h
 * Author: heshan
 *
 * Created on October 5, 2017, 1:32 PM
 */

#ifndef IPROC_H
#define IPROC_H

#include <cstring>

#include "../PNGProcessor/PNGProcessor.h"
#include "../JPEGProcessor/JPEGProcessor.h"
#include "../TIFFProcessor/TIFFProcessor.h"
#include "../BMPProcessor/BMPProcessor.h"
#include "../PixelProcessor/PixelProcessor.h"
#include "../PixelProcessor/pixel.h"

class IProc {
public:
    IProc();
    IProc(const IProc& orig);
    virtual ~IProc();
    
    int readImageFormatInfo(std::string);
    
    int getImageFormat(std::string);
    
    int readImage(std::string);
    int writeImage(std::string);
    int writeImage(std::string, std::string);
    
    RGBApixel getPixel(int,int);
    int setPixel(int,int,RGBApixel);
    
    int resizeImage(int, int);
    int grayscale();
    
    int testMethod();
    
private:
    
    PNGProcessor pngProc;
    JPEGProcessor jpegProc;
    TIFFProcessor tifProc;
    BMPProcessor bmpProc;
    PixelProcessor pixProc;
    ImageDataStruct imgDataStruct;
    
};

#endif /* IPROC_H */

