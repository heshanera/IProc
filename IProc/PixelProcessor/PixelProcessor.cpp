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

int PixelProcessor::crop(int x1, int y1, int x2, int y2){
    
    int newWidth = x2 - x1;
    int newHeight = y2 - y1;
//    int originalArraySize = imgWidth * imgHeight;
//    
//    int *newPixelArray;
//    newPixelArray = new int[newWidth * newHeigth];
//    for ( int i = 0; i < originalArraySize; i++ ) {
//        row = i % imgWidth;
//        col = i % imgHeigth;
//    }
    
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