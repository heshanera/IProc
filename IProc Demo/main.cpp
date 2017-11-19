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
    iproc.readImageFormatInfo("png");
    iproc.readImage("imgs/PNG/img1.png");
    
    // get the pixel in x,y position
    int x = 10, y = 20;
    RGBApixel pixel = iproc.getPixel(x,y);
    std::cout   <<"Img("<<x<<","<<y<<") = "
                <<"RGBA( "
                <<(int)pixel.r<<" "
                <<(int)pixel.g<<" "
                <<(int)pixel.b<<" "
                <<(int)pixel.a<<" "
                <<")\n";
    
    
    // replace the pixel in x,y position
    pixel.r = 1;
    pixel.g = 2;
    pixel.b = 3;
    pixel.a = 4;
    iproc.setPixel(x,y,pixel);
    
    iproc.writeImage("imgs/PNG/imgOut1.png");
    
    
    iproc.testMethod();
    
    return 0;
}

