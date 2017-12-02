/* 
 * File:   TIFFProcessor.cpp
 * Author: heshan
 * 
 * Created on December 2, 2017, 9:28 AM
 */

#include "TIFFProcessor.h"

TIFFProcessor::TIFFProcessor() { }

TIFFProcessor::TIFFProcessor(const TIFFProcessor& orig) { }

TIFFProcessor::~TIFFProcessor() { }

/**
 * @param height of the image
 * @return 1 
 */
int TIFFProcessor::setHeight(int height) {
    this->imgHeight = height;
    return 1;
}

/**
 * @param width of the image
 * @return 1
 */
int TIFFProcessor::setWidth(int width) {
    this->imgWidth = width;
    return 1;
}

/**
 * @return height of the image 
 */
int TIFFProcessor::getHeight() {
    return this->imgHeight;
}

/**
 * @return width of the image 
 */
int TIFFProcessor::getWidth() {
    return this->imgWidth;
}

/**
 * @param filename the path to the image
 * @return 1 if read the image without any errors
 */
int TIFFProcessor::readImage(char * filename) {
  
    

    return 1;
}

/**
 * @param filename target fie path
 * @param imageDataStruct pixel array of the image to be written
 * @return 1 if write the image without any errors
 */
int TIFFProcessor::writeImage (char * filename, ImageDataStruct imageDataStruct) {
  
    
    return 1;
}

/**
 * @return ImageDataStruct that contains pixel array and image meta data 
 */
ImageDataStruct TIFFProcessor::getImageDataStruct(){
    return this->imgDataStruct;
}

/**
 * @param buffer that contains decompressed image pixels 
 * @param pixPos pixel position
 * @param row_stride physical row width in image buffer 
 * @return 1 
 */
int TIFFProcessor::fillRGBApixelArray(){
    
//    for(int i = 0; i < row_stride; i+=3){
//        imgDataStruct.imgPixArray[pixPos].r = (int)buffer[0][i];
//        imgDataStruct.imgPixArray[pixPos].g = (int)buffer[0][i+1];
//        imgDataStruct.imgPixArray[pixPos].b = (int)buffer[0][i+2];
//        imgDataStruct.imgPixArray[pixPos].a = 255;
//        pixPos++;
//    }
    return 1;
}

