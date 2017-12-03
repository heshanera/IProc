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
    
    int i;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        std::cout<<"error in the file '"<<filename<<"'";
        return 0;
    }    
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, file); // read the 54-byte header

    // extract image height and width from header
    setWidth(*(int*)&info[18]);
    setHeight(*(int*)&info[22]);

    imgDataStruct.imgPixArray = new RGBApixel[imgWidth*imgHeight];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
    
    int rowPadded = (imgWidth*3 + 3) & (~3);
    unsigned char* data = new unsigned char[rowPadded];

    int row = imgHeight;
    for(int i = 0; i < imgHeight; i++) {
        fread(data, sizeof(unsigned char), rowPadded, file); row--;
        fillRGBApixelArray(data,row);
    }
    
    return 1;
}

/**
 * @param filename target fie path
 * @param imageDataStruct pixel array of the image to be written
 * @return 1 if write the image without any errors
 */
int BMPProcessor::writeImage (char * filename, ImageDataStruct imageDataStruct) {
    
    unsigned char file[14] = {
        'B','M', // magic
        0,0,0,0, // size in bytes
        0,0, // app data
        0,0, // app data
        40+14,0,0,0 // start of data offset
    };
    unsigned char info[40] = {
        40,0,0,0, // info hd size
        0,0,0,0, // width
        0,0,0,0, // heigth
        1,0, // number color planes
        24,0, // bits per pixel
        0,0,0,0, // compression is none
        0,0,0,0, // image bits size
        0x13,0x0B,0,0, // horz resoluition in pixel / m
        0x13,0x0B,0,0, // vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
        0,0,0,0, // #colors in pallete
        0,0,0,0, // #important colors
        };

    int w=imageDataStruct.imgWidth;
    int h=imageDataStruct.imgHeight;

    int padSize  = (4-(w*3)%4)%4;
    int sizeData = w*h*3 + h*padSize;
    int sizeAll  = sizeData + sizeof(file) + sizeof(info);

    file[ 2] = (unsigned char)( sizeAll    );
    file[ 3] = (unsigned char)( sizeAll>> 8);
    file[ 4] = (unsigned char)( sizeAll>>16);
    file[ 5] = (unsigned char)( sizeAll>>24);

    info[ 4] = (unsigned char)( w   );
    info[ 5] = (unsigned char)( w>> 8);
    info[ 6] = (unsigned char)( w>>16);
    info[ 7] = (unsigned char)( w>>24);

    info[ 8] = (unsigned char)( h    );
    info[ 9] = (unsigned char)( h>> 8);
    info[10] = (unsigned char)( h>>16);
    info[11] = (unsigned char)( h>>24);

    info[20] = (unsigned char)( sizeData    );
    info[21] = (unsigned char)( sizeData>> 8);
    info[22] = (unsigned char)( sizeData>>16);
    info[23] = (unsigned char)( sizeData>>24);

//    stream.write( (char*)file, sizeof(file) );
//    stream.write( (char*)info, sizeof(info) );
//
//    unsigned char pad[3] = {0,0,0};
//
//    for ( int y=0; y<h; y++ )
//    {
//        for ( int x=0; x<w; x++ )
//        {
//            long red = lround( 255.0 * waterfall[x][y] );
//            if ( red < 0 ) red=0;
//            if ( red > 255 ) red=255;
//            long green = red;
//            long blue = red;
//
//            unsigned char pixel[3];
//            pixel[0] = blue;
//            pixel[1] = green;
//            pixel[2] = red;
//
//            stream.write( (char*)pixel, 3 );
//        }
//        stream.write( (char*)pad, padSize );
//    }
    
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
int BMPProcessor::fillRGBApixelArray(unsigned char* data, int row){

    int col = 0;
    int pixPos = row*imgWidth;
    for(int bytePos = 0; bytePos < imgWidth*3; bytePos += 3) {
        // pixel Order is Convert (B, G, R) in Bitmap
        imgDataStruct.imgPixArray[pixPos+col].r = (int)data[bytePos+2];
        imgDataStruct.imgPixArray[pixPos+col].g = (int)data[bytePos+1];
        imgDataStruct.imgPixArray[pixPos+col].b = (int)data[bytePos];
        imgDataStruct.imgPixArray[pixPos+col].a = 255;
        col++;
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