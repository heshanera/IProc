/* 
 * File:   PixelProcessor.cpp
 * Author: heshan
 * 
 * Created on September 24, 2017, 1:02 PM
 */

#include "PixelProcessor.h"

PixelProcessor::PixelProcessor() { }

PixelProcessor::PixelProcessor(const PixelProcessor& orig) { }

PixelProcessor::~PixelProcessor() { }

RGBApixel PixelProcessor::getPixel(int x, int y, ImageDataStruct imgDataStruct){
    return imgDataStruct.imgPixArray[x+(y*imgDataStruct.imgWidth)];
}

/**
 * |-------------------------|
 * |-------------------------|          |------|
 * |-------------------------|  ==>     |------|
 * |-------------------------|          |------|
 * |-------------------------|
 * 
 * @param originWidth Original image width
 * @param originHeight Original image height
 * @param newWidth new image width
 * @param newHeight new image height
 * @param OriginalArray Original pixel Array
 * @return resized pixel array
 */
u_int* PixelProcessor::resize(int originWidth, int originHeight, int newWidth, int newHeight, u_int *OriginalArray){
  
    int i;
    int j;
    int l;
    int c;
    float t;
    float u;
    float tmp;
    float d1, d2, d3, d4;
    u_int p1, p2, p3, p4; /* nearby pixels */
    u_char red, green, blue;
    
    u_int *newPixelArray;
    int newPixelSize = newWidth * newHeight;
    newPixelArray = new u_int[newPixelSize];
    
    for (i = 0; i < newHeight; i++) {
        for (j = 0; j < newWidth; j++) {
    
            tmp = (float) (i) / (float) (newHeight - 1) * (originHeight - 1);
            l = (int) floor(tmp);
            if (l < 0) {
                l = 0;
            } else {
                if (l >= originHeight - 1) {
                    l = originHeight - 2;
                }
            }
    
            u = tmp - l;
            tmp = (float) (j) / (float) (newWidth - 1) * (originWidth - 1);
            c = (int) floor(tmp);
            if (c < 0) {
                c = 0;
            } else {
                if (c >= originWidth - 1) {
                    c = originWidth - 2;
                }
            }
            t = tmp - c;
    
            /* coefficients */
            d1 = (1 - t) * (1 - u);
            d2 = t * (1 - u);
            d3 = t * u;
            d4 = (1 - t) * u;
    
            /* nearby pixels: a[i][j] */
            p1 = *((u_int*)OriginalArray + (l * originWidth) + c);
            p2 = *((u_int*)OriginalArray + (l * originWidth) + c + 1);
            p3 = *((u_int*)OriginalArray + ((l + 1)* originWidth) + c + 1);
            p4 = *((u_int*)OriginalArray + ((l + 1)* originWidth) + c);
    
            /* color components */
            blue = (u_char)p1 * d1 + (u_char)p2 * d2 + (u_char)p3 * d3 + (u_char)p4 * d4;
            green = (u_char)(p1 >> 8) * d1 + (u_char)(p2 >> 8) * d2 + (u_char)(p3 >> 8) * d3 + (u_char)(p4 >> 8) * d4;
            red = (u_char)(p1 >> 16) * d1 + (u_char)(p2 >> 16) * d2 + (u_char)(p3 >> 16) * d3 + (u_char)(p4 >> 16) * d4;
    
            /* new pixel R G B  */
            *((u_int*)newPixelArray + (i * newWidth) + j) = (red << 16) | (green << 8) | (blue);       
        }
    }
    return newPixelArray;
}

/**
 * |-------------------------|
 * |-------------------------|          |------|
 * |-------------------------|  ==>     |------|
 * |-------------------------|          |------|
 * |-------------------------|
 * 
 * @param originWidth Original image width
 * @param originHeight Original image height
 * @param newWidth new image width
 * @param newHeight new image height
 * @param OriginalArray Original pixel Array
 * @return resized pixel array
 */
unsigned char ** PixelProcessor::resize(int originWidth, int originHeight, int newWidth, int newHeight, unsigned char **OriginalArray){
    
    int i;
    int j;
    int l;
    int c;
    float t;
    float u;
    float tmp;
    float d1, d2, d3, d4;
    u_int p1, p2, p3, p4; /* nearby pixels */
    u_char red, green, blue;
    
    unsigned char **newPixelArray;
    int newPixelSize = newWidth * newHeight;
    newPixelArray = new unsigned char *[newPixelSize];
    
//    for(int y = 0; y < newHeight; y++) {
//        unsigned char * row = OriginalArray[y];
//        for(int x = 0; x < newHeight; x++) {
//            unsigned char * px = &(row[x * 4]);
//            // Do something awesome for each pixel here...
//            //std::cout<<x<<" "<<y<<" = RGBA ("<<px[0]<<" "<<px[1]<<" "<<px[2]<<" "<<px[3]<<")\n";    
//            printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
//            //printf("%4d, %4d\n", x, y);
//            //std::cout<<x<<" "<<y<<"\n";
//        }
//    }
    
    for (i = 0; i < newHeight; i++) {
        for (j = 0; j < newWidth; j++) {
    
            tmp = (float) (i) / (float) (newHeight - 1) * (originHeight - 1);
            l = (int) floor(tmp);
            if (l < 0) {
                l = 0;
            } else {
                if (l >= originHeight - 1) {
                    l = originHeight - 2;
                }
            }
    
            u = tmp - l;
            tmp = (float) (j) / (float) (newWidth - 1) * (originWidth - 1);
            c = (int) floor(tmp);
            if (c < 0) {
                c = 0;
            } else {
                if (c >= originWidth - 1) {
                    c = originWidth - 2;
                }
            }
            t = tmp - c;
    
            /* coefficients */
            d1 = (1 - t) * (1 - u);
            d2 = t * (1 - u);
            d3 = t * u;
            d4 = (1 - t) * u;   
    
            /* nearby pixels: a[i][j] */
            p1 = *((u_char*)OriginalArray + (l * originWidth) + c);
            p2 = *((u_char*)OriginalArray + (l * originWidth) + c + 1);
            p3 = *((u_char*)OriginalArray + ((l + 1)* originWidth) + c + 1);
            p4 = *((u_char*)OriginalArray + ((l + 1)* originWidth) + c);
            
            printf("%3d %3d %3d %3d\n",d1,d2,d3,d4);
            
            /* color components */
            blue = (u_char)p1 * d1 + (u_char)p2 * d2 + (u_char)p3 * d3 + (u_char)p4 * d4;
            green = (u_char)(p1 >> 8) * d1 + (u_char)(p2 >> 8) * d2 + (u_char)(p3 >> 8) * d3 + (u_char)(p4 >> 8) * d4;
            red = (u_char)(p1 >> 16) * d1 + (u_char)(p2 >> 16) * d2 + (u_char)(p3 >> 16) * d3 + (u_char)(p4 >> 16) * d4;
    
            /* new pixel R G B  */
            *((u_char*)newPixelArray + (i * newWidth) + j) = (red << 16) | (green << 8) | (blue);
//            printf("%d, %d := ( %3d %3d %3d )\n",i,j,*((u_char*)newPixelArray + (i * newWidth) + j)>>16,*((u_char*)newPixelArray + (i * newWidth) + j)>>8,*((u_char*)newPixelArray + (i * newWidth) + j));
//            printf("%3d\n",green);
        
        }
    }
    
//    for(int y = 0; y < newHeight; y++) {
//        unsigned char * row = newPixelArray[y];
//        for(int x = 0; x < newHeight; x++) {
//            unsigned char * px = &(row[x * 4]);
//            std::cout<<x<<" "<<y<<" = RGBA ("<<px[0]<<" "<<px[1]<<" "<<px[2]<<" "<<px[3]<<")\n";    
//            printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
//            printf("%4d, %4d\n", x, y);
//            std::cout<<x<<" "<<y<<"\n";
//            printf("%4d, %4d := ( %3d %3d %3d )\n",x,y,*((u_char*)newPixelArray + (x * newWidth) + y)>>16,*((u_char*)newPixelArray + (x * newWidth) + y)>>8,*((u_char*)newPixelArray + (x * newWidth) + y));
//    
//        }
//    }
    
    return newPixelArray;
}

/**
 *              col1           col2
 *      |----------------------------------|
 * row1 |----------------------------------|
 *      |----------------------------------|
 *      |----------------------------------|
 * row2 |----------------------------------|
 *      |----------------------------------|
 * 
 * @param row1 cropped image top row coordinate
 * @param col1 cropped image left coordinate         
 * @param row2 cropped image bottom coordinate
 * @param col2 cropped image right coordinate 
 * @param originWidth Original image width
 * @param originHeight Original image height
 * @param OriginalArray Original pixel array
 * @return cropped image pixel array
 */
u_int* PixelProcessor::crop(int row1, int col1, int row2, int col2, int originWidth, u_int *OriginalArray){
    
    int newHeight = row2 - row1;
    int newWidth = col2 - col1;
    u_int *newPixelArray;
    int newPixelSize = newWidth * newHeight;
    int row, pos;
    newPixelArray = new u_int[newPixelSize];
    for ( int i = 0; i < newPixelSize; i++ ) {
        row = row1 + (int)(i/newWidth);
        pos = (originWidth * row) + col1 + (i % newWidth);
        newPixelArray[i] = OriginalArray[pos];
    }
    return newPixelArray;
}

u_int* PixelProcessor::shear(){
    u_int *newPixelArray;
    return newPixelArray;
}

/**
 * @param originWidth Original image width
 * @param originHeight Original image height
 * @param OriginalArray Original pixel array
 * @return gray pixel array
 */
u_int* PixelProcessor::grayScale(int originWidth, int originHeight, u_int* OriginalArray){
    
    //u_int *pntrBWImage=(u_int*); //..data pointer..;  //assumes 4*width*height bytes with 32 bits i.e. 4 bytes per pixel
    u_int fourBytes;
    u_char r,g,b;
    int arraySize = originWidth * originHeight;
    
    u_int *newPixelArray;
    newPixelArray = new u_int[arraySize];
    
    for (int i = 0; i < arraySize; i++)
    {
        fourBytes = OriginalArray[i];//caches 4 bytes at a time
        r = (fourBytes>>16);
        g = (fourBytes>>8);
        b = fourBytes;
    
        newPixelArray[i] = (r >>2)+ (g>>1) + (b>>2); //This runs in 0.00065s on my pc and produces slightly darker results
        //newPixelArray[i]=((u_int)(r+g+b))/3;     //This runs in 0.0011s on my pc and produces a pure average
    }
    return newPixelArray;
}

u_int* PixelProcessor::rotate(){
    u_int *newPixelArray;
    return newPixelArray;
}

/**
 * 
 * @param originWidth Original image width
 * @param originHeight Original image height
 * @param limit pixel divider boundary
 * @param OriginalArray Original pixel array
 * @return binary pixel array
 */
u_int* PixelProcessor::binary(int originWidth, int originHeight, int limit, u_int* OriginalArray){
    
    int arraySize = originWidth * originHeight;
    u_int *newPixelArray;
    newPixelArray = new u_int[arraySize];
    
    for (int i = 0; i < arraySize; i++)
    {
        if (OriginalArray[i] > limit)
            newPixelArray[i] = 255;
        else newPixelArray[i] = 0;
    }
    return newPixelArray;
}