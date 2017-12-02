/* 
 * File:   JPEGProcessor.cpp
 * Author: heshan
 * 
 * Created on October 5, 2017, 4:02 PM
 */

#include "JPEGProcessor.h"

JPEGProcessor::JPEGProcessor() { }

JPEGProcessor::JPEGProcessor(const JPEGProcessor& orig) { }

JPEGProcessor::~JPEGProcessor() { }

/**
 * @param height of the image
 * @return 1 
 */
int JPEGProcessor::setHeight(int height) {
    this->imgHeight = height;
    return 1;
}

/**
 * @param width of the image
 * @return 1
 */
int JPEGProcessor::setWidth(int width) {
    this->imgWidth = width;
    return 1;
}

/**
 * @return height of the image 
 */
int JPEGProcessor::getHeight() {
    return this->imgHeight;
}

/**
 * @return width of the image 
 */
int JPEGProcessor::getWidth() {
    return this->imgWidth;
}

/**
 * @param filename the path to the image
 * @return 1 if read the image without any errors
 */
int JPEGProcessor::readImage(char * filename) {
  
    struct jpeg_decompress_struct cinfo;

    struct error_mgr jerr;
    FILE * infile;		/* source file */
    JSAMPARRAY buffer;		/* Output row buffer */
    int row_stride;		/* physical row width in output buffer */

    if ((infile = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", filename);
        return 0;
    }

    /* set up the normal JPEG error routines, then override error_exit. */
    cinfo.err = jpeg_std_error(&jerr.pub);
    
    /* Establish the setjmp return context for error_exit to use. */
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return 0;
    }
    
    /* initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);

    /* specify data source (eg, a file) */
    jpeg_stdio_src(&cinfo, infile);

    /* read file parameters with jpeg_read_header() */
    (void) jpeg_read_header(&cinfo, TRUE);
  
    /* set parameters for decompression */

    /* Start decompressor */
    (void) jpeg_start_decompress(&cinfo);
    
    setWidth(cinfo.output_width);
    setHeight(cinfo.output_height);

    /* JSAMPLEs per row in output buffer */
    row_stride = cinfo.output_width * cinfo.output_components;
    /* Make a one-row-high sample array that will go away when done with image */
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
    
    imgDataStruct.imgPixArray = new RGBApixel[imgHeight*imgWidth];
    imgDataStruct.imgHeight = imgHeight;
    imgDataStruct.imgWidth = imgWidth;
    
    int pixPos = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        fillRGBApixelArray(buffer, pixPos, row_stride);
        pixPos+=cinfo.output_width;
    }
    
    /* Finish decompression */
    (void) jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);

    fclose(infile);

    return 1;
}

/**
 * @param filename target fie path
 * @param imageDataStruct pixel array of the image to be written
 * @return 1 if write the image without any errors
 */
int JPEGProcessor::writeImage (char * filename, ImageDataStruct imageDataStruct) {
  
    int quality = 100;  

    struct jpeg_compress_struct cinfo;

    struct jpeg_error_mgr jerr;
    FILE * outfile;		/* target file */
    JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
    JSAMPLE * buffer;           /* array with JSAMPLEs */
    int row_stride;		/* physical row width in image buffer */

    /* allocate and initialize JPEG compression object */
    cinfo.err = jpeg_std_error(&jerr);
    /* initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);

    /* specify data destination */
    if ((outfile = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "can't open %s\n", filename);
        exit(1);
    }
    jpeg_stdio_dest(&cinfo, outfile);
    
    /* set parameters for compression */
    cinfo.image_width = imageDataStruct.imgWidth; 	/* image width and height, in pixels */
    cinfo.image_height = imageDataStruct.imgHeight;
    cinfo.input_components = 3;		/* # of color components per pixel */
    cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
    
    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

    /* Start compressor */
    jpeg_start_compress(&cinfo, TRUE);

    row_stride = imageDataStruct.imgWidth * 3;	/* JSAMPLEs per row in buffer */

    int RGBpixels = imageDataStruct.imgHeight * imageDataStruct.imgWidth;
    buffer = new JSAMPLE[RGBpixels * 3]; 
    int bufferPos = 0;
    for(int pixPos = 0; pixPos < RGBpixels; pixPos++){
        buffer[bufferPos] = imageDataStruct.imgPixArray[pixPos].r;
        buffer[bufferPos+1] = imageDataStruct.imgPixArray[pixPos].g;
        buffer[bufferPos+2] = imageDataStruct.imgPixArray[pixPos].b;
        bufferPos += 3;
    }
  
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = & buffer[cinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    /* Finish compression */
    jpeg_finish_compress(&cinfo);
    /* close the output file. */
    fclose(outfile);
    /* release JPEG compression object */
    jpeg_destroy_compress(&cinfo);

    return 1;
}

/**
 * @param cinfo
 */
void JPEGProcessor::error_exit (j_common_ptr cinfo) {
    (*cinfo->err->output_message) (cinfo);
    /* Return control to the setjmp point */
    longjmp(error_ptr->setjmp_buffer, 1);
}

/**
 * @return ImageDataStruct that contains pixel array and image meta data 
 */
ImageDataStruct JPEGProcessor::getImageDataStruct(){
    return this->imgDataStruct;
}

/**
 * @param buffer that contains decompressed image pixels 
 * @param pixPos pixel position
 * @param row_stride physical row width in image buffer 
 * @return 1 
 */
int JPEGProcessor::fillRGBApixelArray(JSAMPARRAY buffer, int pixPos, int row_stride){
    
    for(int i = 0; i < row_stride; i+=3){
        imgDataStruct.imgPixArray[pixPos].r = (int)buffer[0][i];
        imgDataStruct.imgPixArray[pixPos].g = (int)buffer[0][i+1];
        imgDataStruct.imgPixArray[pixPos].b = (int)buffer[0][i+2];
        imgDataStruct.imgPixArray[pixPos].a = 255;
        pixPos++;
    }
    return 1;
}

/**
 * free the pixel array in imageDataStruct
 * @return 1 
 */
int JPEGProcessor::freeImageData(){
    imgDataStruct.imgPixArray = NULL;
    return 1;
}
