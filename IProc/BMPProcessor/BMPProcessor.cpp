/* 
 * File:   BMPProcessor.cpp
 * Author: heshan
 * 
 * Created on December 3, 2017, 12:29 AM
 */

#include "BMPProcessor.h"

BMPProcessor::BMPProcessor() { }

BMPProcessor::BMPProcessor(const BMPProcessor& orig) { }

BMPProcessor::~BMPProcessor() { }

/**
 * @param height of the image
 * @return 1 
 */
int BMPProcessor::setHeight(int height) {
    this->imgHeight = height;
    return 1;
}

/**
 * @param width of the image
 * @return 1
 */
int BMPProcessor::setWidth(int width) {
    this->imgWidth = width;
    return 1;
}

/**
 * @return height of the image 
 */
int BMPProcessor::getHeight() {
    return this->imgHeight;
}

/**
 * @return width of the image 
 */
int BMPProcessor::getWidth() {
    return this->imgWidth;
}

/**
 * @param filename the path to the image
 * @return 1 if read the image without any errors
 */
int BMPProcessor::readImage(char * filename) {
    
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        std::cout<<"error in the file '"<<filename<<"'";
        return 0;
    }    
    unsigned char * info = new unsigned char[54];
    fread(info, sizeof(unsigned char), 54, file); // read the 54-byte header

    // extract image height and width from header
    setWidth(*(int*)&info[18]);
    setHeight(*(int*)&info[22]);
    
    int bBit = *(int*)&info[28];
    int byteSize;
    if (bBit == 24) byteSize = 3;
    else if (bBit == 32) byteSize = 4;

    imgDataStruct.imgPixArray = new RGBApixel[imgWidth*imgHeight];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
    
    int rowPadded = (imgWidth*byteSize + byteSize) & (~byteSize);
    unsigned char* data = new unsigned char[rowPadded];

    int row = imgHeight;
    for(int i = 0; i < imgHeight; i++) {
        fread(data, sizeof(unsigned char), rowPadded, file); row--;
        fillRGBApixelArray(data,row,byteSize);
    }
    
    delete info,data;
    fclose(file);
    return 1;
}

/**
 * @param filename target fie path
 * @param imageDataStruct pixel array of the image to be written
 * @return 1 if write the image without any errors
 */
int BMPProcessor::writeImage (char * filename, ImageDataStruct imageDataStruct, int bBit = 32) {
    
    imgHeight = imageDataStruct.imgHeight;
    imgWidth = imageDataStruct.imgWidth;
    
    int byteSize;
    if (bBit == 24) byteSize = 3;
    else if (bBit == 32) byteSize = 4;
    
    FILE *file;
    unsigned char *img = NULL;
    int pixSize = byteSize*imgWidth*imgHeight;
    int filesize = 54 + pixSize;  
    img = (unsigned char *)malloc(byteSize*imgWidth*imgHeight);
    
    memset(img,0,pixSize);
    int x,y,r,g,b,a;
  
    if (bBit == 24) {
        for(int i=0; i<imgWidth; i++) {
            for(int j=0; j<imgHeight; j++) {
                x=i; y=(imgHeight-1)-j;
                r = imageDataStruct.imgPixArray[x + y*imgWidth].r;
                g = imageDataStruct.imgPixArray[x + y*imgWidth].g;
                b = imageDataStruct.imgPixArray[x + y*imgWidth].b;
                img[(x+y*imgWidth)*3+2] = (unsigned char)(r);
                img[(x+y*imgWidth)*3+1] = (unsigned char)(g);
                img[(x+y*imgWidth)*3+0] = (unsigned char)(b);
            }
        }
    } else if (bBit == 32) {
        for(int i=0; i<imgWidth; i++) {
            for(int j=0; j<imgHeight; j++) {
                x=i; y=(imgHeight-1)-j;
                r = imageDataStruct.imgPixArray[x + y*imgWidth].r;
                g = imageDataStruct.imgPixArray[x + y*imgWidth].g;
                b = imageDataStruct.imgPixArray[x + y*imgWidth].b;
                a = imageDataStruct.imgPixArray[x + y*imgWidth].a;
                img[(x+y*imgWidth)*4+3] = (unsigned char)(a);
                img[(x+y*imgWidth)*4+2] = (unsigned char)(r);
                img[(x+y*imgWidth)*4+1] = (unsigned char)(g);
                img[(x+y*imgWidth)*4+0] = (unsigned char)(b);
            }
        }
    }
    
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[4] = {0,0,0,0};

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize>> 8);
    bmpfileheader[4] = (unsigned char)(filesize>>16);
    bmpfileheader[5] = (unsigned char)(filesize>>24);

    bmpinfoheader[4] = (unsigned char)(imgWidth);
    bmpinfoheader[5] = (unsigned char)(imgWidth>> 8);
    bmpinfoheader[6] = (unsigned char)(imgWidth>>16);
    bmpinfoheader[7] = (unsigned char)(imgWidth>>24);
    bmpinfoheader[8] = (unsigned char)(imgHeight);
    bmpinfoheader[9] = (unsigned char)(imgHeight>> 8);
    bmpinfoheader[10] = (unsigned char)(imgHeight>>16);
    bmpinfoheader[11] = (unsigned char)(imgHeight>>24);
    
    bmpinfoheader[14] = bBit;

    file = fopen(filename,"wb");
    fwrite(bmpfileheader,1,14,file);
    fwrite(bmpinfoheader,1,40,file);
    for(int i=0; i<imgHeight; i++)
    {
        fwrite(img+(imgWidth*(imgHeight-i-1)*byteSize),byteSize,imgWidth,file);
        fwrite(bmppad,1,(4-(imgWidth*byteSize)%4)%4,file);
    }

    delete imageDataStruct.imgPixArray;
    free(img);
    fclose(file);
    
    return 1;
}

/**
 * @return ImageDataStruct that contains pixel array and image meta data 
 */
ImageDataStruct BMPProcessor::getImageDataStruct(){
    return this->imgDataStruct;
}

/**
 * @param buffer that contains decompressed image pixels 
 * @param pixPos pixel position
 * @param row_stride physical row width in image buffer 
 * @return 1 
 */
int BMPProcessor::fillRGBApixelArray(unsigned char* data, int row, int byteSize){

    int col = 0;
    int pixPos = row*imgWidth;
    if ( byteSize == 3) {
        for(int bytePos = 0; bytePos < imgWidth*3; bytePos += 3) {
            // pixel Order is Convert (B, G, R) in Bitmap
            imgDataStruct.imgPixArray[pixPos+col].r = (int)data[bytePos+2];
            imgDataStruct.imgPixArray[pixPos+col].g = (int)data[bytePos+1];
            imgDataStruct.imgPixArray[pixPos+col].b = (int)data[bytePos];
            imgDataStruct.imgPixArray[pixPos+col].a = 255;
            col++;
        }
    } else if ( byteSize == 4) {
        for(int bytePos = 0; bytePos < imgWidth*4; bytePos += 4) {
            imgDataStruct.imgPixArray[pixPos+col].a = (int)data[bytePos+3];
            imgDataStruct.imgPixArray[pixPos+col].r = (int)data[bytePos+2];
            imgDataStruct.imgPixArray[pixPos+col].g = (int)data[bytePos+1];
            imgDataStruct.imgPixArray[pixPos+col].b = (int)data[bytePos];
            col++;
        }
    }   
    return 1;
}

/**
 * free the pixel array in imageDataStruct
 * @return 1 
 */
int BMPProcessor::freeImageData(){
    imgDataStruct.imgPixArray = NULL;
    return 1;
}