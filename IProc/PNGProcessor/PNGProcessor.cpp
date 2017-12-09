/* 
 * File:   PNGProcessor.cpp
 * Author: heshan
 * 
 * Created on September 16, 2017, 10:37 PM
 */

#include "PNGProcessor.h"

png_bytep *rowPointers;

PNGProcessor::PNGProcessor() { }

PNGProcessor::PNGProcessor(const PNGProcessor& orig) { }

PNGProcessor::~PNGProcessor() {
    free(rowPointers);
}

/**
 * @return image height 
 */
int PNGProcessor::getHeight(){
    return (int)(this->imgHeight);
}

/**
 * @return image width 
 */
int PNGProcessor::getWidth(){
    return (int)(this->imgWidth);
}

/**
 * @param height of the image
 * @return 1
 */
int PNGProcessor::setHeight(int height){
    this->imgHeight = (png_uint_32)height;
    return 1;
}

/**
 * @param width of the image
 * @return 1
 */
int PNGProcessor::setWidth(int width){
    this->imgWidth = (png_uint_32)width;
    return 1;
}

/**
 * @return pixel array
 */
png_bytep* PNGProcessor::getPixelArray(){
    return rowPointers;
}


/**
 * prints the version of the libpng
 * @return 0 
 */
int PNGProcessor::readPNGVersionInfo(){
    
    fprintf(stderr, "*** Compiled with libpng %s; using libpng %s.\n", PNG_LIBPNG_VER_STRING, png_libpng_ver);
    fprintf(stderr, "*** Compiled with zlib %s; using zlib %s.\n", ZLIB_VERSION, zlib_version);
    return 0;
}

/**
 * 
 * Store the the image in an unsigned char array [imageData]
 * 
 * @param path the path to the image
 * @return 0 if read the image without any errors
 * 
 */
int PNGProcessor::readImage(char* path){
    
    png_structp pngPointer;
    png_infop infoPointer;
    unsigned char *imageData;
    
    FILE *infile = fopen(path, "rb");
    
    if(!infile) return 1; // error in output file //
    
    // Checking if the input file is a png file
    unsigned char signatureBytes[8];
    fread(signatureBytes, 1, 8, infile);
    if (!png_check_sig(signatureBytes, 8))
        return 1;   // bad signature //
    
    // Setting up the structs that will hold the basic information of the PNG image.    
    pngPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,NULL);    
    if (!pngPointer)
        return 4;   // out of memory //
    
    infoPointer = png_create_info_struct(pngPointer);
    if (!infoPointer) {
        png_destroy_read_struct(&pngPointer, NULL, NULL);
        return 4;   // out of memory //
    }
    
    // handle libpng errors
    if(setjmp(png_jmpbuf(pngPointer))){
        png_destroy_read_struct(&pngPointer, &infoPointer, NULL);
        return 2;
    }
        
    // set up libpng    
    png_init_io(pngPointer, infile);
    png_set_sig_bytes(pngPointer, 8);
    png_read_info(pngPointer, infoPointer); 
    
    // getting contents of PNG file's IHDR
    png_get_IHDR(
        pngPointer, 
        infoPointer, 
        &imgWidth, 
        &imgHeight, 
        &bitDepth, 
        &colorType, 
        NULL, 
        NULL, 
        NULL
    );
    
    // check the PNG file for background color
    if (!png_get_valid(pngPointer, infoPointer, PNG_INFO_bKGD)) {
        // do nothing
    } else {
        png_get_bKGD(pngPointer, infoPointer, &pBackground);
        if (bitDepth == 16) {
            *red   = pBackground->red   >> 8;
            *green = pBackground->green >> 8;
            *blue  = pBackground->blue  >> 8;
        } else if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8) {
            if (bitDepth == 1)
                *red = *green = *blue = pBackground->gray? 255 : 0;
            else if (bitDepth == 2)   /* i.e., max value is 3 */
                *red = *green = *blue = (255/3) * pBackground->gray;
            else /* bit_depth == 4 */  /* i.e., max value is 15 */
                *red = *green = *blue = (255/15) * pBackground->gray;
        } else {
            *red   = pBackground->red;
            *green = pBackground->green;
            *blue  = pBackground->blue;
        }
    }
    
    // sets up the transformations 
    if (colorType == PNG_COLOR_TYPE_PALETTE)
        png_set_expand(pngPointer);
    if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
        png_set_expand(pngPointer);
    if (png_get_valid(pngPointer, infoPointer, PNG_INFO_tRNS))
        png_set_expand(pngPointer);
    if (colorType == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(pngPointer);
    if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
        png_set_gray_to_rgb(pngPointer);
    if (png_get_valid(pngPointer, infoPointer, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(pngPointer);
    
    // reduce images with 16-bit samples to 8 bits per sample
    if (bitDepth == 16)
        png_set_strip_16(pngPointer);
    
    // expand grayscale images to RGB
    if (colorType == PNG_COLOR_TYPE_GRAY ||
        colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(pngPointer);
    
    // gamma-correction, only if the file contains gamma information itself
    if (png_get_gAMA(pngPointer, infoPointer, &gamma))
        png_set_gamma(pngPointer, displayExponent, gamma);
    
    // get the values for the number of channels and the size of each row in the image
    // allocate memory for the main image buffer
    // set up an array of pointers
    png_uint_32  i, rowBytes;
    rowPointers = new png_bytep[imgHeight];
  
    png_read_update_info(pngPointer, infoPointer);
  
    rowBytes = png_get_rowbytes(pngPointer, infoPointer);

    if ((imageData = (unsigned char *)malloc(rowBytes*imgHeight)) == NULL) {
        png_destroy_read_struct(&pngPointer, &infoPointer, NULL);
        return -1;
    }
  
    for (i = 0;  i < imgHeight;  ++i)
        rowPointers[i] = imageData + i*rowBytes;
    
    // read the entire image into the array that allocated
    png_read_image(pngPointer, rowPointers);
    
    // checks the remainder of the image for correctness
    png_read_end(pngPointer, NULL);
    
    // fill the pixel array and create imageDataStruct
    fillRGBApixelArray();
    
    imageData = NULL;
    free(pngPointer);
    free(infoPointer);
    
    fclose(infile);
    
    return 0;
}

/**
 * 
 * Write the image to the file in given path
 * 
 * @param path the path to the image
 * @return 0 if read the image without any errors
 * 
 */
int PNGProcessor::writeImage(char* path, ImageDataStruct imageDataStruct){
    
    mainprog_info *mainprogPointer;
    png_structp pngPointer;
    png_infop infoPointer;
    unsigned char *imageData;
    int rowBytes;

    FILE *outfile = fopen(path, "wb");
    
    if(!outfile) 
        return 1;  // error in output file //

    pngPointer = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,
        mainprogPointer,  
        NULL,    
        NULL
    );
    
    pngPointer = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPointer) abort();
    
    infoPointer = png_create_info_struct(pngPointer);
    if (!infoPointer) abort();
    
    if (setjmp(png_jmpbuf(pngPointer))) abort();
    
    png_init_io(pngPointer, outfile);
    
    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
      pngPointer,
      infoPointer,
      imageDataStruct.imgWidth, imageDataStruct.imgHeight,
      8,
      PNG_COLOR_TYPE_RGBA,
      PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT
    );
    
    rowPointers = new png_bytep[imageDataStruct.imgHeight];
    rowBytes = png_get_rowbytes(pngPointer, infoPointer);
    
    if ((imageData = (unsigned char *)malloc(rowBytes*imageDataStruct.imgHeight)) == NULL) {
        png_destroy_read_struct(&pngPointer, &infoPointer, NULL);
        return -1;
    }
  
    for (int i = 0;  i < imageDataStruct.imgHeight;  ++i)
        rowPointers[i] = imageData + i*rowBytes;
    
    int pixPos;
    for(int y = 0; y < imageDataStruct.imgHeight; y++) {
//        rowPointers[y] = new png_byte[imageDataStruct.imgWidth];
        png_bytep row = rowPointers[y];
        for(int x = 0; x < imageDataStruct.imgWidth; x++) {
            png_bytep px = &(row[x * 4]);
            pixPos = x+(y*imageDataStruct.imgWidth);
            px[0] = imageDataStruct.imgPixArray[pixPos].r;
            px[1] = imageDataStruct.imgPixArray[pixPos].g;
            px[2] = imageDataStruct.imgPixArray[pixPos].b;
            px[3] = imageDataStruct.imgPixArray[pixPos].a;
        }
    }
    
    png_write_info(pngPointer, infoPointer);
    
    png_write_image(pngPointer, rowPointers);
    png_write_end(pngPointer, NULL);

    if (pngPointer && infoPointer) png_destroy_write_struct(&pngPointer, &infoPointer);
    
    delete imageDataStruct.imgPixArray;
    
    fclose(outfile);
    
    free(imageData);
    free(mainprogPointer);
    
    return 0;
}

/**
 * fill the RGBAPixel array
 * @return 1
 */
int PNGProcessor::fillRGBApixelArray(){
    
    imgDataStruct.imgPixArray = new RGBApixel[imgHeight*imgWidth];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
            
    int pixPos;
    for(int y = 0; y < imgHeight; y++) {
        png_bytep row = rowPointers[y];
        for(int x = 0; x < imgHeight; x++) {
            png_bytep px = &(row[x * 4]);
            pixPos = x+(y*imgWidth);
            imgDataStruct.imgPixArray[pixPos].r = px[0];
            imgDataStruct.imgPixArray[pixPos].g = px[1];
            imgDataStruct.imgPixArray[pixPos].b = px[2];
            imgDataStruct.imgPixArray[pixPos].a = px[3];
        }
    }
    return 1;
}

ImageDataStruct PNGProcessor::getImageDataStruct(){
    return this->imgDataStruct;
}

/**
 * free the pixel array in imageDataStruct
 * @return 1 
 */
int PNGProcessor::freeImageData(){
    imgDataStruct.imgPixArray = NULL;
    return 1;
}
