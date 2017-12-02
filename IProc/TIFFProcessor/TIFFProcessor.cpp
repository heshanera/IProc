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
  
    TIFF* tif = TIFFOpen(filename, "w");
    
    if(tif){
        uint32 imagelength, imagewidth;
        uint8 * buf;
        uint32 row, col;
        uint16 config, nsamples;
        imagewidth = imageDataStruct.imgWidth ;
        imagelength = imageDataStruct.imgHeight ;
        config = PLANARCONFIG_CONTIG ;
        nsamples = 4;

        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, imagelength);
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, imagewidth);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, nsamples);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_LZW) ;
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8) ;
        TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif, imagewidth*nsamples));

        int pixPos = 0;
        buf = new uint8 [imagewidth*nsamples] ;
        for (row = 0; row < imagelength; row++){
            for(col=0; col < imagewidth; col++){
                buf[col*nsamples+0] = static_cast<uint8> (imageDataStruct.imgPixArray[pixPos].r);
                buf[col*nsamples+1] = static_cast<uint8> (imageDataStruct.imgPixArray[pixPos].g);
                buf[col*nsamples+2] = static_cast<uint8> (imageDataStruct.imgPixArray[pixPos].b);
                buf[col*nsamples+3] = static_cast<uint8> (imageDataStruct.imgPixArray[pixPos].a);
                pixPos++;
            }
            if (TIFFWriteScanline(tif, buf, row) != 1 ) break;
        }
        _TIFFfree(buf);
        TIFFClose(tif);
    }
    
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
    int rasterPos = npixels-imgWidth;
    int row = imgHeight-1;
    int offset = 0;
    for(int pixPos = 0; pixPos < npixels; pixPos++){
        if ((pixPos+1)%imgWidth==0) offset = imgWidth;
        else offset = 0;
        imgDataStruct.imgPixArray[pixPos].r = raster[rasterPos+offset] & 0xFF;
        raster[rasterPos] >>= 8;
        imgDataStruct.imgPixArray[pixPos].g = raster[rasterPos+offset] & 0xFF;
        raster[rasterPos] >>= 8;
        imgDataStruct.imgPixArray[pixPos].b = raster[rasterPos+offset] & 0xFF;
        raster[rasterPos] >>= 8;
        imgDataStruct.imgPixArray[pixPos].a = raster[rasterPos+offset] & 0xFF;  
        rasterPos++;
        if ((rasterPos+1)%imgWidth == 0) {
            row--;
            rasterPos = imgWidth*row-1;
        }
    }   
    return 1;
}

/**
 * free the pixel array in imageDataStruct
 * @return 1 
 */
int TIFFProcessor::freeImageData(){
    imgDataStruct.imgPixArray = NULL;
    return 1;
}

