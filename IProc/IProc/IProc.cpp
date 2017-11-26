/* 
 * File:   IProc.cpp
 * Author: heshan
 * 
 * Created on October 5, 2017, 1:32 PM
 */

#include <iostream>
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
//    switch ("test") {
//        case "png":
//            return 1;
//        case "jpeg":
//            return 2;
//        case "jpg":
//            return 2;
//        default:
//            break;
//    }
    return 1;
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
            break;
        case 2:
            jpegProc.readImage(path);
            imgDataStruct = jpegProc.getImageDataStruct();
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
    
    std::cout<<"start testing...\n\n";
    
//    pixProc.resize(pngProc.getWidth(), pngProc.getHeight(), 10, 10, pngProc.getPixelArray());
    
//    RGBApixel pix = pixProc.getPixel(5,10,pngProc.getImageDataStruct());
//    std::cout<<(int)pix.r;
    
    std::cout<<"end testing...\n\n";
    
//    PNGProcessor pngProc;
//    pngProc.readPNGVersionInfo();
    
//    readImageFormatInfo("png");
//    
//    char path[] = "dsdsd";
//    readImage(path);
//    
//    std::cout<<"\n\nstart testing...";
    
    return 0;
}