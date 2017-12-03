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
    
    int i;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        std::cout<<"error in the file '"<<filename<<"'";
        return 0;
    }    
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, file); // read the 54-byte header

    // extract image height and width from header
    setWidth(*(int*)&info[18]);
    setHeight(*(int*)&info[22]);

    imgDataStruct.imgPixArray = new RGBApixel[imgWidth*imgHeight];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
    
    int rowPadded = (imgWidth*3 + 3) & (~3);
    unsigned char* data = new unsigned char[rowPadded];
    unsigned char tmp;

    int row = -1;
    for(int i = 0; i < imgHeight; i++) {
        fread(data, sizeof(unsigned char), rowPadded, file); row++;
        fillRGBApixelArray(data,row);
    }
    
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
int BMPProcessor::fillRGBApixelArray(unsigned char* data, int row){

    int col = 0;
    int pixPos = row*imgWidth;
    for(int bytePos = 0; bytePos < imgWidth*3; bytePos += 3) {
        // pixel Order is Convert (B, G, R) in Bitmap
        imgDataStruct.imgPixArray[pixPos+col].r = (int)data[bytePos+2];
        imgDataStruct.imgPixArray[pixPos+col].g = (int)data[bytePos+1];
        imgDataStruct.imgPixArray[pixPos+col].b = (int)data[bytePos];
        imgDataStruct.imgPixArray[pixPos+col].a = 255;
        col++;
    }
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