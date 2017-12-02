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
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    delete [] path;
    return 0;
}

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
 * @param x position of pixel
 * @param y position of pixel
 * @param pixel new pixel to replace with the old pixel in that position
 * @return 1
 */
int IProc::setPixel(int x,int y,RGBApixel pixel){ 
    
    imgDataStruct.imgPixArray[x+(y*imgDataStruct.imgWidth)] = pixel;
    return 1;
}

int IProc::resizeImage(int width, int height){
    
    switch(getImageFormat("empty")){
        case 1:
            break;
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    return 0;
}

int IProc::testMethod(){
    std::cout<<"\n\ntest method...\n\n";    
    return 0;
}