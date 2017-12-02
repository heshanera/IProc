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
int main(int argc, char** argv) {

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
    
    iproc.readImage("imgs/TIF/input/img4.TIF");
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
    iproc.writeImage("imgs/TIF/output/img4.TIF");
    
    
    iproc.testMethod();
    
    return 0;
}

