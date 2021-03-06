/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on October 5, 2017, 1:48 PM
 */

#include <cstdlib>
#include <libiproc.h>
#include <iostream>

int main() {
    
    IProc ip;
    ip.readImage("imgs/JPEG/input/img5.jpg");
    
    int x = 10, y = 10;
    RGBApixel pixel = ip.getPixel(x, y);
    std::cout   <<"Image("<<x<<","<<y<<") = "
                <<"RGBA( "
                <<(int)pixel.r<<" "
                <<(int)pixel.g<<" "
                <<(int)pixel.b<<" "
                <<(int)pixel.a<<" "
                <<")\n";
    
    ip.setPixel(10,15,pixel);
    
    ImageDataStruct img = ip.getImageDataStruct();
    std::cout<<"image height: "<<img.imgHeight;
    std::cout<<"\n";
    std::cout<<"image width: "<<img.imgWidth;
    
    ip.writeImage("imgs/PNG/output/img1.png");
    
    ip.readImage("imgs/JPEG/input/img5.jpg");
    ip.grayscale();
    ip.writeImage("imgs/PNG/output/img2.png");
    
    ip.readImage("imgs/JPEG/input/img5.jpg");
    ip.binary(180);
    ip.writeImage("imgs/PNG/output/img3.png");
    
    ip.readImage("imgs/JPEG/input/img5.jpg");
    ip.resize(100,100);
    ip.writeImage("imgs/PNG/output/img4.png");
    
//    IProc iproc;
//    
//    /***** PNG images *****/
//    
//    iproc.readImageFormatInfo("png");
//    iproc.readImage("imgs/PNG/input/img6.png");
//    
//    // get the pixel in x,y position
//    int x = 20, y = 10;
//    RGBApixel pixel = iproc.getPixel(x,y);
//    std::cout   <<"Img("<<x<<","<<y<<") = "
//                <<"RGBA( "
//                <<(int)pixel.r<<" "
//                <<(int)pixel.g<<" "
//                <<(int)pixel.b<<" "
//                <<(int)pixel.a<<" "
//                <<")\n";
//    
//    // replace the pixel in i,j position
//    for(int i = 5; i < 10; i++){
//        for(int j = 10; j < 25; j++){
//            RGBApixel pixel1 = iproc.getPixel(i,j);
//            pixel1.r = 100;
//            pixel1.g = 200;
//            pixel1.b = 100;
//            pixel1.a = 255;
//            iproc.setPixel(i,j,pixel1);
//        }
//    }
//    // write the image with changed pixels
//    iproc.writeImage("imgs/PNG/output/img6.png");
//    
//    /***** JPEG images *****/
//    
//    iproc.readImage("imgs/JPEG/input/img6.jpg");
//    // get the pixel in x,y position
//    x = 40, y = 100;
//    pixel = iproc.getPixel(x,y);
//    std::cout   <<"Img("<<x<<","<<y<<") = "
//                <<"RGBA( "
//                <<(int)pixel.r<<" "
//                <<(int)pixel.g<<" "
//                <<(int)pixel.b<<" "
//                <<(int)pixel.a<<" "
//                <<")\n";
//    
//    // replace the pixel in i,j position
//    for(int i = 30; i < 100; i++){
//        for(int j = 85; j < 100; j++){
//            RGBApixel pixel1 = iproc.getPixel(i,j);
//            pixel1.r = 200;
//            pixel1.g = 100;
//            pixel1.b = 80;
//            pixel1.a = 255;
//            iproc.setPixel(i,j,pixel1);
//        }
//    }
//    // write the image with changed pixels
//    iproc.resize(-1,150);
//    iproc.writeImage("imgs/JPEG/output/img6.jpg");
//    
//    /***** TIFF images *****/
//    
//    iproc.readImage("imgs/TIF/input/img1.TIF");
//    // get the pixel in x,y position
//    x = 40, y = 100;
//    pixel = iproc.getPixel(x,y);
//    std::cout   <<"Img("<<x<<","<<y<<") = "
//                <<"RGBA( "
//                <<(int)pixel.r<<" "
//                <<(int)pixel.g<<" "
//                <<(int)pixel.b<<" "
//                <<(int)pixel.a<<" "
//                <<")\n";
//    
//    // replace the pixel in i,j position
//    for(int i = 30; i < 100; i++){
//        for(int j = 85; j < 100; j++){
//            RGBApixel pixel1 = iproc.getPixel(i,j);
//            pixel1.r = 200;
//            pixel1.g = 100;
//            pixel1.b = 80;
//            pixel1.a = 255;       
//            iproc.setPixel(i,j,pixel1);
//        }
//    }
//    // write the image with changed pixels
//    iproc.binary(150);
//    iproc.writeImage("imgs/TIF/output/img4.TIF");
//    
//    
//    /***** BMP images *****/
//    
//    iproc.readImage("imgs/BMP/input/img1.BMP");
//    // write the image with changed pixels
//    for(int i = 36; i < 80; i++){
//        for(int j = 45; j < 120; j++){
//            RGBApixel pixel1 = iproc.getPixel(i,j);
//            pixel1.r = 200;
//            pixel1.g = 100;
//            pixel1.b = 80;
//            pixel1.a = 255;       
//            iproc.setPixel(i,j,pixel1);
//        }
//    }
//    iproc.grayscale();
//    iproc.crop(10,10,125,80);
//    iproc.writeImage("imgs/BMP/output/img1.BMP",32);
    
    return 0;
}

