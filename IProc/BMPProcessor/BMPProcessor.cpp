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
    
    unsigned int headers[13];
    FILE * outfile;
    int extrabytes;
    int paddedsize;
    int x; int y; int n;
    int red, green, blue;
    
    imgWidth = imageDataStruct.imgWidth;
    imgHeight = imageDataStruct.imgHeight;
    
    extrabytes = 4 - ((imgWidth * 3) % 4);  // How many bytes of padding to add to each
                                            // horizontal line - the size of which must
                                            // be a multiple of 4 bytes.
    if (extrabytes == 4) extrabytes = 0;
    paddedsize = ((imgWidth * 3) + extrabytes) * imgHeight;

    headers[0]  = paddedsize + 54;  // bfSize (whole file size)
    headers[1]  = 0;                // bfReserved (both)
    headers[2]  = 54;               // bfOffbits
    headers[3]  = 40;               // biSize
    headers[4]  = imgWidth;         // biWidth
    headers[5]  = imgHeight;        // biHeight
    headers[7]  = 0;                // biCompression
    headers[8]  = paddedsize;       // biSizeImage
    headers[9]  = 0;                // biXPelsPerMeter
    headers[10] = 0;                // biYPelsPerMeter
    headers[11] = 0;                // biClrUsed
    headers[12] = 0;                // biClrImportant

    outfile = fopen(filename, "wb");

    for (n = 0; n <= 5; n++) {
       fprintf(outfile, "%c", headers[n] & 0x000000FF);
       fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
       fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
       fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
    }

    fprintf(outfile, "%c", 1);
    fprintf(outfile, "%c", 0);
    fprintf(outfile, "%c", 24);
    fprintf(outfile, "%c", 0);

    for (n = 7; n <= 12; n++) {
       fprintf(outfile, "%c", headers[n] & 0x000000FF);
       fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
       fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
       fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
    }

    int pixPos;
    for (y = imgHeight - 1; y >= 0; y--) {
        pixPos = y*imgWidth; 
        for (x = 0; x <= imgWidth - 1; x++) {

            red = imageDataStruct.imgPixArray[pixPos+x].r;
            green = imageDataStruct.imgPixArray[pixPos+x].g;
            blue = imageDataStruct.imgPixArray[pixPos+x].b;

            if (red > 255) red = 0; if (red < 0) red = 0;
            if (green > 255) green = 0; if (green < 0) green = 0;
            if (blue > 255) blue = 0; if (blue < 0) blue = 0;

            // Also, it's written in (b,g,r) format...

            fprintf(outfile, "%c", blue);
            fprintf(outfile, "%c", green);
            fprintf(outfile, "%c", red);
        }
        if (extrabytes) {
            for (n = 1; n <= extrabytes; n++) {
               fprintf(outfile, "%c", 0);
            }
        }
    }

    fclose(outfile);
    
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