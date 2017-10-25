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
    
}

u_int* PixelProcessor::grayScale(int originWidth, int originHeight, u_int* OriginalArray){
    
    u_int *pntrBWImage=(u_int*) //..data pointer..;  //assumes 4*width*height bytes with 32 bits i.e. 4 bytes per pixel
    u_int fourBytes;
    u_char r,g,b;
    int arraySize = originWidth * originHeight;
    for (int i = 0; i < arraySize; i++)
    {
        fourBytes=pntrBWImage[i];//caches 4 bytes at a time
        r=(fourBytes>>16);
        g=(fourBytes>>8);
        b=fourBytes;
    
        I_Out[i] = (r >>2)+ (g>>1) + (b>>2); //This runs in 0.00065s on my pc and produces slightly darker results
        //I_Out[index]=((unsigned int)(r+g+b))/3;     //This runs in 0.0011s on my pc and produces a pure average
    }
    /*
    
        for (int i = 0; i < NumRow; i++) 
       { 
          for (int j = 0; j < numCol; j++) 
          { 
             Color c = bmp.GetPixel(j, i);// Extract the color of a pixel 
             int rd = c.R; int gr = c.G; int bl = c.B;// extract the red,green, blue components from the color.
             double d1 = 0.2989 * (double)rd + 0.5870 * (double)gr + 0.1140 * (double)bl; 
             int c1 = (int)Math.Round(d1); 
             Color c2 = Color.FromArgb(c1, c1, c1);
             GRAY.SetPixel(j, i, c2);
          }
       }
       
    */
    
}

u_int* PixelProcessor::rotate(){
    
}