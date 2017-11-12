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

int IProc::setImageFormat(){
    this->imgType = 1;
    return 0;
}

int IProc::getImageFormat(){
    return this->imgType;
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
    
    setImageFormat();
    
    char *path = new char[imgPath.length() + 1];
    strcpy(path, imgPath.c_str());
    
    switch(getImageFormat()){
        case 1:
            pngProc.readImage(path);
            break;
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    delete [] path;
    return 0;
}

int IProc::resizeImage(int width, int height){
    
    switch(getImageFormat()){
        case 1:
            //pngProc.processImage();
            pixProc.resize(pngProc.getWidth(), pngProc.getHeight(), width, height, pngProc.getPixelArray());
            break;
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    return 0;
}

int IProc::writeImage(std::string imgPath){
    
    char *path = new char[imgPath.length() + 1];
    strcpy(path, imgPath.c_str());
    
    switch(getImageFormat()){
        case 1:
            pngProc.writeImage(path);
            break;
        default:
            fprintf(stderr, " Invalid Image Format or Image format is not supported by IProc\n");
    }
    return 0;

}



int IProc::testMethod(){
    
    std::cout<<"start testing...\n\n";
    
    pixProc.resize(pngProc.getWidth(), pngProc.getHeight(), 10, 10, pngProc.getPixelArray());
    
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