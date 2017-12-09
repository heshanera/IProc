/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on October 5, 2017, 1:48 PM
 */

#include <cstdlib>
#include <libiproc.h>
#include <iostream>

using namespace std;

/*
 * 
 */
int main() {

    IProc iproc;
    
    /***** PNG images *****/
    
    iproc.readImageFormatInfo("png");
    iproc.readImage("imgs/PNG/input/img6.png");
    
    // get the pixel in x,y position
    int x = 20, y = 10;
    RGBApixel pixel = iproc.getPixel(x,y);
    std::cout   <<"Img("<<x<<","<<y<<") = "
                <<"RGBA( "
                <<(int)pixel.r<<" "
                <<(int)pixel.g<<" "
                <<(int)pixel.b<<" "
                <<(int)pixel.a<<" "
                <<")\n";
    
    // replace the pixel in i,j position
    for(int i = 5; i < 10; i++){
        for(int j = 10; j < 25; j++){
            RGBApixel pixel1 = iproc.getPixel(i,j);
            pixel1.r = 100;
            pixel1.g = 200;
            pixel1.b = 100;
            pixel1.a = 255;
            iproc.setPixel(i,j,pixel1);
        }
    }
    // write the image with changed pixels
    iproc.writeImage("imgs/PNG/output/img6.png");
    
    /***** JPEG images *****/
    
    iproc.readImage("imgs/JPEG/input/img6.jpg");
    // get the pixel in x,y position
    x = 40, y = 100;
    pixel = iproc.getPixel(x,y);
    std::cout   <<"Img("<<x<<","<<y<<") = "
                <<"RGBA( "
                <<(int)pixel.r<<" "
                <<(int)pixel.g<<" "
                <<(int)pixel.b<<" "
                <<(int)pixel.a<<" "
                <<")\n";
    
    // replace the pixel in i,j position
    for(int i = 30; i < 100; i++){
        for(int j = 85; j < 100; j++){
            RGBApixel pixel1 = iproc.getPixel(i,j);
            pixel1.r = 200;
            pixel1.g = 100;
            pixel1.b = 80;
            pixel1.a = 255;
            iproc.setPixel(i,j,pixel1);
        }
    }
    // write the image with changed pixels
    iproc.writeImage("imgs/JPEG/output/img6.jpg");
    
    /***** TIFF images *****/
    
    iproc.readImage("imgs/TIF/input/img1.TIF");
    // get the pixel in x,y position
    x = 40, y = 100;
    pixel = iproc.getPixel(x,y);
    std::cout   <<"Img("<<x<<","<<y<<") = "
                <<"RGBA( "
                <<(int)pixel.r<<" "
                <<(int)pixel.g<<" "
                <<(int)pixel.b<<" "
                <<(int)pixel.a<<" "
                <<")\n";
    
    // replace the pixel in i,j position
    for(int i = 30; i < 100; i++){
        for(int j = 85; j < 100; j++){
            RGBApixel pixel1 = iproc.getPixel(i,j);
            pixel1.r = 200;
            pixel1.g = 100;
            pixel1.b = 80;
            pixel1.a = 255;       
            iproc.setPixel(i,j,pixel1);
        }
    }
    // write the image with changed pixels
    iproc.binary(150);
    iproc.writeImage("imgs/TIF/output/img4.tif");
    
    
    /***** BMP images *****/
    
    iproc.readImage("imgs/BMP/input/img1.BMP");
    // write the image with changed pixels
    for(int i = 36; i < 80; i++){
        for(int j = 45; j < 120; j++){
            RGBApixel pixel1 = iproc.getPixel(i,j);
            pixel1.r = 200;
            pixel1.g = 100;
            pixel1.b = 80;
            pixel1.a = 255;       
            iproc.setPixel(i,j,pixel1);
        }
    }
    iproc.grayscale();
    iproc.crop(10,10,125,80);
    iproc.writeImage("imgs/BMP/output/img1.BMP");
    
    
    /*****************************************************/
    /*****************************************************/
    /*****************************************************/
    /*****************************************************/
    
//    IProc ip;
//    ip.readImage("");
//    
//    RGBApixel pix = ip.getPixel(10,10);
//    ip.setPixel(10,15,pix);
//    
//    ImageDataStruct img = ip.getImageDataStruct();
//    std::cout<<"image height: "<<img.imgHeight;
//    std::cout<<"image width: "<<img.imgWidth;
//    
//    ip.resizeImage(100,20);
//    ip.grayscale();
//    
//    ip.writeImage("");
    
    
    
    return 0;
}

