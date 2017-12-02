/* 
 * File:   TIFFProcessor.cpp
 * Author: heshan
 * 
 * Created on December 2, 2017, 9:28 AM
 */

#include "TIFFProcessor.h"

TIFFProcessor::TIFFProcessor() { }

TIFFProcessor::TIFFProcessor(const TIFFProcessor& orig) { }

TIFFProcessor::~TIFFProcessor() { }

/**
 * @param height of the image
 * @return 1 
 */
int TIFFProcessor::setHeight(int height) {
    this->imgHeight = height;
    return 1;
}

/**
 * @param width of the image
 * @return 1
 */
int TIFFProcessor::setWidth(int width) {
    this->imgWidth = width;
    return 1;
}

/**
 * @return height of the image 
 */
int TIFFProcessor::getHeight() {
    return this->imgHeight;
}

/**
 * @return width of the image 
 */
int TIFFProcessor::getWidth() {
    return this->imgWidth;
}

/**
 * @param filename the path to the image
 * @return 1 if read the image without any errors
 */
int TIFFProcessor::readImage(char * filename) {
  
    TIFF* tif = TIFFOpen(filename, "r");
    if (tif) {
	uint32 w, h;
	size_t npixels;
	uint32* raster;

	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
        imgHeight = h;
        imgWidth = w;
	npixels = w * h;
	raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
	if (raster != NULL) {
	    if (TIFFReadRGBAImage(tif, w, h, raster, 0)) {
                fillRGBApixelArray(raster,npixels);
            }
	    _TIFFfree(raster);
	}
	TIFFClose(tif);
    }
    return 1;
}

/**
 * @param filename target fie path
 * @param imageDataStruct pixel array of the image to be written
 * @return 1 if write the image without any errors
 */
int TIFFProcessor::writeImage (char * filename, ImageDataStruct imageDataStruct) {
  
    TIFF* tif = TIFFOpen("foo.tif", "w");
    TIFFClose(tif);
    
    return 1;
}

/**
 * @return ImageDataStruct that contains pixel array and image meta data 
 */
ImageDataStruct TIFFProcessor::getImageDataStruct(){
    return this->imgDataStruct;
}

/**
 * @param buffer that contains decompressed image pixels 
 * @param pixPos pixel position
 * @param row_stride physical row width in image buffer 
 * @return 1 
 */
int TIFFProcessor::fillRGBApixelArray(uint32* raster, int npixels){
    
    imgDataStruct.imgPixArray = new RGBApixel[npixels];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
    
    for(int pixPos = 0; pixPos < npixels; pixPos++){
        for(int i = 0; i < 4; i++){
            raster[pixPos] & 0xFF;
            raster[pixPos] >>= 8;
        }
    }
    return 1;
}

