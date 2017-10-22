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

int PixelProcessor::resize(int width, int height){
    
    /*
    a - a primary array (which we need to stretch/compress) pointer.
    oldw - primary width
    oldh - primary height
    b - a secondary array (which we get after compressing/stretching) pointer
    neww - secondary width
    newh - seconday height
    */
//    
//    void *a, void *b, int oldw, int oldh, int neww,  int newh
//    
//    int i;
//    int j;
//    int l;
//    int c;
//    float t;
//    float u;
//    float tmp;
//    float d1, d2, d3, d4;
//    u_int p1, p2, p3, p4; /* nearby pixels */
//    u_char red, green, blue;
//    
//    for (i = 0; i < newh; i++) {
//        for (j = 0; j < neww; j++) {
//    
//            tmp = (float) (i) / (float) (newh - 1) * (oldh - 1);
//            l = (int) floor(tmp);
//            if (l < 0) {
//                l = 0;
//            } else {
//                if (l >= oldh - 1) {
//                    l = oldh - 2;
//                }
//            }
//    
//            u = tmp - l;
//            tmp = (float) (j) / (float) (neww - 1) * (oldw - 1);
//            c = (int) floor(tmp);
//            if (c < 0) {
//                c = 0;
//            } else {
//                if (c >= oldw - 1) {
//                    c = oldw - 2;
//                }
//            }
//            t = tmp - c;
//    
//            /* coefficients */
//            d1 = (1 - t) * (1 - u);
//            d2 = t * (1 - u);
//            d3 = t * u;
//            d4 = (1 - t) * u;
//    
//            /* nearby pixels: a[i][j] */
//            p1 = *((u_int*)a + (l * oldw) + c);
//            p2 = *((u_int*)a + (l * oldw) + c + 1);
//            p3 = *((u_int*)a + ((l + 1)* oldw) + c + 1);
//            p4 = *((u_int*)a + ((l + 1)* oldw) + c);
//    
//            /* color components */
//            blue = (u_char)p1 * d1 + (u_char)p2 * d2 + (u_char)p3 * d3 + (u_char)p4 * d4;
//            green = (u_char)(p1 >> 8) * d1 + (u_char)(p2 >> 8) * d2 + (u_char)(p3 >> 8) * d3 + (u_char)(p4 >> 8) * d4;
//            red = (u_char)(p1 >> 16) * d1 + (u_char)(p2 >> 16) * d2 + (u_char)(p3 >> 16) * d3 + (u_char)(p4 >> 16) * d4;
//    
//            /* new pixel R G B  */
//            *((u_int*)b + (i * neww) + j) = (red << 16) | (green << 8) | (blue);       
//        }
//    }
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
 * @param OriginalArray original pixel array
 * @return cropped image pixel array
 */
int PixelProcessor::crop(int row1, int col1, int row2, int col2, int originWidth, int originHeight, int *OriginalArray){
    
    int newHeight = row2 - row1;
    int newWidth = col2 - col1;
    int originalArraySize = originWidth * originHeight;
    
    int *newPixelArray;
    int newPixelSize = newWidth * newHeight;
    newPixelArray = new int[newPixelSize];
    for ( int i = 0; i < newPixelSize; i++ ) {
        //newPixelArray[i] = 
    }
    
//    0  1  2  3   4  5
//    6  7  8  9  10 11
//    12 13 14 15 16 17
//    18 19 20 21 22 23
//    24 25 26 27 28 29
//
//
//  (originWidth * row1) + col1 + (i % newWidth)
//    
    
}

int PixelProcessor::shear(){
    
}

int PixelProcessor::grayScale(){
    
//    unsigned int *pntrBWImage=(unsigned int*)..data pointer..;  //assumes 4*width*height bytes with 32 bits i.e. 4 bytes per pixel
//    unsigned int fourBytes;
//    unsigned char r,g,b;
//    for (int index=0;index<width*height;index++)
//    {
//        fourBytes=pntrBWImage[index];//caches 4 bytes at a time
//        r=(fourBytes>>16);
//        g=(fourBytes>>8);
//        b=fourBytes;
//    
//        I_Out[index] = (r >>2)+ (g>>1) + (b>>2); //This runs in 0.00065s on my pc and produces slightly darker results
//        //I_Out[index]=((unsigned int)(r+g+b))/3;     //This runs in 0.0011s on my pc and produces a pure average
//    }
//    /*
//    
//        for (int i = 0; i < NumRow; i++) 
//       { 
//          for (int j = 0; j < numCol; j++) 
//          { 
//             Color c = bmp.GetPixel(j, i);// Extract the color of a pixel 
//             int rd = c.R; int gr = c.G; int bl = c.B;// extract the red,green, blue components from the color.
//             double d1 = 0.2989 * (double)rd + 0.5870 * (double)gr + 0.1140 * (double)bl; 
//             int c1 = (int)Math.Round(d1); 
//             Color c2 = Color.FromArgb(c1, c1, c1);
//             GRAY.SetPixel(j, i, c2);
//          }
//       }
//       
//    */
    
}

int PixelProcessor::rotate(){
    
}