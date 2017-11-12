/* 
 * File:   PNGPixelProcessor.cpp
 * Author: heshan
 * 
 * Created on October 30, 2017, 11:27 PM
 */

#include "PNGPixelProcessor.h"

PNGPixelProcessor::PNGPixelProcessor() { }

PNGPixelProcessor::PNGPixelProcessor(const PNGPixelProcessor& orig) { }

PNGPixelProcessor::~PNGPixelProcessor() { }

u_int* PNGPixelProcessor::resize(int originWidth, int originHeight, int newWidth, int newHeight, png_bytep *OriginalArray){

    // converting the pixel array
    
    
    // calling the PixelProcessor method
    PixelProcessor::resize(originWidth, originHeight, newWidth, newHeight, OriginalArray);
    
}
