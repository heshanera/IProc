/* 
 * File:   IProc.cpp
 * Author: heshan
 * 
 * Created on October 5, 2017, 1:32 PM
 */

#include <iostream>
#include <algorithm>
#include "IProc.h"

IProc::IProc() { }

IProc::IProc(const IProc& orig) { }

IProc::~IProc() { }

/**
 * 
 * @param path of the image ( source or the target)
 * @return an integer according to the image format
 * 1 : PNG
 * 2 : JPEG/JPG
 * 3 : TIFF/TIF
 * 4 : BMP
 */
int IProc::getImageFormat(std::string path){
    // getting the image type from path (file extension)
    std::string extension;
    extension = path.substr(path.find_last_of(".") + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    if (extension == "png") return 1;
    else if (extension == "jpeg") return 2;
    else if (extension == "jpg") return 2;
    else if (extension == "tiff") return 3;
    else if (extension == "tif") return 3;
    else if (extension == "bmp") return 4;
    else return 0;
    
}

/**
 * prints the version of the image library used [ libpng, libjpeg ]
 * @return 
 */
int IProc::readImageFormatInfo(std::string path){
    if ( path == "png" ){
        pngProc.readPNGVersionInfo();
    } else { 
        fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    return 0;
}

/**
 * 
 * @param imgPath path of the image source
 * @return 1
 */
int IProc::readImage(std::string imgPath){
    
    char *path = new char[imgPath.length() + 1];
    strcpy(path, imgPath.c_str());
    
    switch(getImageFormat(imgPath)){
        case 1:
            pngProc.readImage(path);
            imgDataStruct = pngProc.getImageDataStruct();
            pngProc.freeImageData();
            break;
        case 2:
            jpegProc.readImage(path);
            imgDataStruct = jpegProc.getImageDataStruct();
            jpegProc.freeImageData();
            break;
        case 3:
            tifProc.readImage(path);
            imgDataStruct = tifProc.getImageDataStruct();
            tifProc.freeImageData();
            break;    
        case 4:
            bmpProc.readImage(path);
            imgDataStruct = bmpProc.getImageDataStruct();
            bmpProc.freeImageData();
            break;    
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    delete [] path;
    return 1;
}

/**
 * 
 * @param imgPath path of the target image
 * @return 1 
 */
int IProc::writeImage(std::string imgPath){
    
    char *path = new char[imgPath.length() + 1];
    strcpy(path, imgPath.c_str());
    
    switch(getImageFormat(imgPath)){
        case 1:
            pngProc.writeImage(path,imgDataStruct);
            break;
        case 2:
            jpegProc.writeImage(path,imgDataStruct);
            break;    
        case 3:
            tifProc.writeImage(path,imgDataStruct);
            break;
        case 4:
            bmpProc.writeImage(path,imgDataStruct);
            break;    
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    return 0;

}

/**
 * 
 * @param x position of pixel
 * @param y position of pixel
 * @return RGBApixel data structure
 */
RGBApixel IProc::getPixel(int x,int y){
    
    RGBApixel pixel;
    pixel = imgDataStruct.imgPixArray[x+(y*imgDataStruct.imgWidth)];
    return pixel;
}

/**
 * 
 * @return ImageDataStruct
 */
ImageDataStruct IProc::getImageDataStruct(){
    
    return this->imgDataStruct;
}

/**
 * 
 * @param x position of pixel
 * @param y position of pixel
 * @param pixel new pixel to replace with the old pixel in that position
 * @return 1
 */
int IProc::setPixel(int x,int y,RGBApixel pixel){ 
    
    imgDataStruct.imgPixArray[x+(y*imgDataStruct.imgWidth)] = pixel;
    return 1;
}

/**
 * 
 * @param imgDataStruct image data structure
 * @return 1
 */
int IProc::setImageDataStruct(ImageDataStruct imgDataStruct){ 
    
    this->imgDataStruct = imgDataStruct;
    return 1;
}

/**
 * 
 * @param width new width of the image
 * @param height new height of the image
 * @return 1
 */
int IProc::resizeImage(int width, int height){
    
    
    return 1;
}

/**
 * 
 * @param row1
 * @param col1
 * @param row2
 * @param col2
 * @param originWidth
 * @param OriginalArray
 * @return 
 */
int IProc::crop(int row1, int col1, int row2, int col2){
    
    int newHeight = row2 - row1;
    int newWidth = col2 - col1;
    int newPixelSize = newWidth * newHeight;
    int row, pos;
    ImageDataStruct newImageDataStruct;
    newImageDataStruct.imgHeight = newHeight;
    newImageDataStruct.imgWidth = newWidth;
    newImageDataStruct.imgPixArray = new RGBApixel[newPixelSize];
    for ( int i = 0; i < newPixelSize; i++ ) {
        row = row1 + (int)(i/newWidth);
        pos = (imgDataStruct.imgWidth * row) + col1 + (i % newWidth);
        newImageDataStruct.imgPixArray[i] = imgDataStruct.imgPixArray[pos];
    }
    imgDataStruct = newImageDataStruct;
    return 1;
}

/**
 * Convert the RGB pixel values to grayscale 
 * @return 1 
 */
int IProc::grayscale(){
    
    int pixSize = imgDataStruct.imgWidth*imgDataStruct.imgHeight;
    RGBApixel pix;
    int grayPixVal;
    for(int i = 0; i < pixSize; i++){
        pix = imgDataStruct.imgPixArray[i];
//        grayPixVal = (pix.r>>2) + (pix.g>>1) + (pix.b>>2);
        grayPixVal = (int)((pix.r + pix.g + pix.b)/3);
        pix.r = grayPixVal;
        pix.g = grayPixVal;
        pix.b = grayPixVal;
        imgDataStruct.imgPixArray[i] = pix;
    }
    return 1;
}

/**
 * 
 * @param limit
 * @return 
 */
int IProc::binary(int limit){
    
    int pixSize = imgDataStruct.imgWidth * imgDataStruct.imgHeight;
    int grayVal,binVal;
    RGBApixel pix;
    for (int i = 0; i < pixSize; i++) {
        pix = imgDataStruct.imgPixArray[i];
        grayVal  = (int)((pix.r + pix.g + pix.b)/3);
        if (grayVal > limit) binVal = 255; 
        else binVal = 0;
        pix.r = binVal;
        pix.g = binVal;
        pix.b = binVal;
        imgDataStruct.imgPixArray[i] = pix;
    }
    return 1;
}