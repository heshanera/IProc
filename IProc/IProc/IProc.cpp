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
 * @param targetWidth new width of the image
 * @param targetHeight new height of the image
 * @return 1
 */
int IProc::resize(int targetWidth, int targetHeight)  {    
    
    if (targetWidth == -1 && targetHeight == -1) {
        return 0;
    } else if (targetWidth == -1) {
        targetWidth = (int)(imgDataStruct.imgWidth)*targetHeight/imgDataStruct.imgHeight;
    } else if (targetHeight == -1) {
        targetHeight = (int)(imgDataStruct.imgHeight*targetWidth)/imgDataStruct.imgWidth;
    }
    
    ImageDataStruct newImgDataStruct;
    newImgDataStruct.imgWidth = targetWidth;
    newImgDataStruct.imgHeight = targetHeight;
    newImgDataStruct.imgPixArray = new RGBApixel[targetWidth*targetHeight];

    int sourceWidth = imgDataStruct.imgWidth; 
    int sourceHeight = imgDataStruct.imgHeight; 
    
    RGBApixel a, b, c, d; 
    int x, y, index;
    int x_ratio = ((int)(sourceWidth - 1)) / targetWidth;
    int y_ratio = ((int)(sourceHeight - 1)) / targetHeight;
    int x_diff, y_diff, blue, red, green ;
    int offset = 0 ;

    for (int i = 0; i < targetHeight; i++) {
        for (int j = 0; j < targetWidth; j++) {
            x = (int)(x_ratio * j) ;
            y = (int)(y_ratio * i) ;
            x_diff = (x_ratio * j) - x ;
            y_diff = (y_ratio * i) - y ;
            index = (y * sourceWidth + x) ;                
            a = imgDataStruct.imgPixArray[index] ;
            b = imgDataStruct.imgPixArray[index + 1] ;
            c = imgDataStruct.imgPixArray[index + sourceWidth] ;
            d = imgDataStruct.imgPixArray[index + sourceWidth + 1] ;

            // blue element
            blue = (a.b)*(1-x_diff)*(1-y_diff) + (b.b)*(x_diff)*(1-y_diff) +
                   (c.b)*(y_diff)*(1-x_diff)   + (d.b)*(x_diff*y_diff);

            // green element
            green = (a.g)*(1-x_diff)*(1-y_diff) + (b.g)*(x_diff)*(1-y_diff) +
                    (c.g)*(y_diff)*(1-x_diff)   + (d.g)*(x_diff*y_diff);

            // red element
            red = (a.r)*(1-x_diff)*(1-y_diff) + (b.r)*(x_diff)*(1-y_diff) +
                  (c.r)*(y_diff)*(1-x_diff)   + (d.r)*(x_diff*y_diff);

            newImgDataStruct.imgPixArray[offset].r = (int)red;
            newImgDataStruct.imgPixArray[offset].g = (int)green;
            newImgDataStruct.imgPixArray[offset].b = (int)blue;
            newImgDataStruct.imgPixArray[offset].a = (int)255;  
            offset++;
        }
    }
    this->imgDataStruct = newImgDataStruct;
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