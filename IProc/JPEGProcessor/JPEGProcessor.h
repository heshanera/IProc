/* 
 * File:   JPEGProcessor.h
 * Author: heshan
 *
 * Created on October 5, 2017, 4:02 PM
 */

#ifndef JPEGPROCESSOR_H
#define JPEGPROCESSOR_H

#include <stdio.h>
#include <iostream>
#include <setjmp.h>
#include "jpeglib.h"
#include "../PixelProcessor/pixel.h"

class JPEGProcessor {
public:
    JPEGProcessor();
    JPEGProcessor(const JPEGProcessor& orig);
    virtual ~JPEGProcessor();
    
    int readImage(char* path);
    int writeImage(char* path,ImageDataStruct);
    
    int getWidth();
    int getHeight();
    int setWidth(int width);
    int setHeight(int height);
    
    int fillRGBApixelArray(JSAMPARRAY buffer, int pixPos, int row_stride);
    ImageDataStruct getImageDataStruct();
    
    void error_exit(j_common_ptr);
    
    struct error_mgr {
        struct jpeg_error_mgr pub;
        jmp_buf setjmp_buffer;
    };
    
private:
    int imgHeight,imgWidth;
    ImageDataStruct imgDataStruct;
    error_mgr * error_ptr;


};

#endif /* JPEGPROCESSOR_H */

