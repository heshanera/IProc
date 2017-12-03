/* 
 * File:   BMPProcessor.cpp
 * Author: heshan
 * 
 * Created on December 3, 2017, 12:29 AM
 */

#include "BMPProcessor.h"

BMPProcessor::BMPProcessor() { }

BMPProcessor::BMPProcessor(const BMPProcessor& orig) { }

BMPProcessor::~BMPProcessor() { }

/**
 * @param height of the image
 * @return 1 
 */
int BMPProcessor::setHeight(int height) {
    this->imgHeight = height;
    return 1;
}

/**
 * @param width of the image
 * @return 1
 */
int BMPProcessor::setWidth(int width) {
    this->imgWidth = width;
    return 1;
}

/**
 * @return height of the image 
 */
int BMPProcessor::getHeight() {
    return this->imgHeight;
}

/**
 * @return width of the image 
 */
int BMPProcessor::getWidth() {
    return this->imgWidth;
}

/**
 * @param filename the path to the image
 * @return 1 if read the image without any errors
 */
int BMPProcessor::readImage(char * filename) {
    
    return 1;
}

/**
 * @param filename target fie path
 * @param imageDataStruct pixel array of the image to be written
 * @return 1 if write the image without any errors
 */
int BMPProcessor::writeImage (char * filename, ImageDataStruct imageDataStruct) {
    
    return 1;
}

/**
 * @return ImageDataStruct that contains pixel array and image meta data 
 */
ImageDataStruct BMPProcessor::getImageDataStruct(){
    return this->imgDataStruct;
}

/**
 * @param buffer that contains decompressed image pixels 
 * @param pixPos pixel position
 * @param row_stride physical row width in image buffer 
 * @return 1 
 */
int BMPProcessor::fillRGBApixelArray(){
    
    return 1;
}

/**
 * free the pixel array in imageDataStruct
 * @return 1 
 */
int BMPProcessor::freeImageData(){
    imgDataStruct.imgPixArray = NULL;
    return 1;
}