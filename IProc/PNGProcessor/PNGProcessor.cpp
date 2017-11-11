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
 * 
 * @return image height 
 */
int PNGProcessor::getHeight(){
    return (int)(this->imgHeight);
}

/**
 * 
 * @return image width 
 */
int PNGProcessor::getWidth(){
    return (int)(this->imgWidth);
}

/**
 * 
 * @param height of the image
 * @return 1
 */
int PNGProcessor::setHeight(int height){
    this->imgHeight = (png_uint_32)height;
    return 1;
}

/**
 * 
 * @param width of the image
 * @return 1
 */
int PNGProcessor::setWidth(int width){
    this->imgWidth = (png_uint_32)width;
    return 1;
}

int PNGProcessor::getPixelArray(){
    //unsigned char * = png_bytep
}


/**
 * 
 * prints the version of the libpng
 * @return 0
 *  
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
    
    // These functions are FICTITIOUS!  They DO NOT EXIST in any
    // version of libpng to date (through 1.0.3). 
    // these will be accepted for libpng version 1.0.4 (and later).
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
    png_byte pChannels = png_get_channels(pngPointer, infoPointer);
  
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
    
    return 0;
}

int PNGProcessor::processImage() {
    for(int y = 0; y < imgHeight; y++) {
        png_bytep row = rowPointers[y];
        for(int x = 0; x < imgHeight; x++) {
            png_bytep px = &(row[x * 4]);
            // Do something awesome for each pixel here...
            //std::cout<<x<<" "<<y<<" = RGBA ("<<px[0]<<" "<<px[1]<<" "<<px[2]<<" "<<px[3]<<")\n";    
            printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
        }
    }
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
int PNGProcessor::writeImage(char* path){
    
    mainprog_info *mainprogPointer;
    png_structp pngPointer;
    png_infop infoPointer;

    FILE *outfile = fopen(path, "wb");
    
    if(!outfile) 
        return 1;  // error in output file //

    pngPointer = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,
        mainprogPointer,  
        NULL,    
        NULL
    );
    if (!pngPointer)
        fclose(outfile);
        return 4;  // out of memory //

    infoPointer = png_create_info_struct(pngPointer);
    if (!infoPointer) 
        png_destroy_write_struct(&pngPointer, NULL);
        fclose(outfile);
        return 4;

    //if (setjmp(png_jmpbuf(pngPointer))) abort();
    
    // handle libpng errors
    if(setjmp(png_jmpbuf(pngPointer))){
        png_destroy_write_struct(&pngPointer, &infoPointer);
        fclose(outfile);
        return 2;
    }

    png_init_io(pngPointer, mainprogPointer->outfile);
    png_set_compression_level(pngPointer, Z_BEST_COMPRESSION);

    int color_type, interlace_type;
  
    if (mainprogPointer->pnmtype == 5)
        color_type = PNG_COLOR_TYPE_GRAY;
    else if (mainprogPointer->pnmtype == 6)
        color_type = PNG_COLOR_TYPE_RGB;
    else if (mainprogPointer->pnmtype == 8)
        color_type = PNG_COLOR_TYPE_RGB_ALPHA;
    else {
        png_destroy_write_struct(&pngPointer, &infoPointer);
        return 11;
    }
  
    interlace_type = mainprogPointer->interlaced? PNG_INTERLACE_ADAM7 : PNG_INTERLACE_NONE;
    
    png_set_IHDR(
        pngPointer, 
        infoPointer, 
        mainprogPointer->width,
        mainprogPointer->height, 
        mainprogPointer->sample_depth,
        color_type, 
        interlace_type,
        PNG_COMPRESSION_TYPE_DEFAULT, 
        PNG_FILTER_TYPE_DEFAULT
    );
    
    if (mainprogPointer->gamma > 0.0)
        png_set_gAMA(pngPointer, infoPointer, mainprogPointer->gamma);
  
    if (mainprogPointer->have_bg) {
        png_color_16  background;
  
        background.red = mainprogPointer->bg_red;
        background.green = mainprogPointer->bg_green;
        background.blue = mainprogPointer->bg_blue;
        png_set_bKGD(pngPointer, infoPointer, &background);
    }
  
    if (mainprogPointer->have_time) {
        png_time  modtime;
  
        png_convert_from_time_t(&modtime, mainprogPointer->modtime);
        png_set_tIME(pngPointer, infoPointer, &modtime);
    }
    
    if (mainprogPointer->have_text) {
        png_text text[6];
        int  num_text = 0;
  
        if (mainprogPointer->have_text) {
            text[num_text].compression = PNG_TEXT_COMPRESSION_NONE;
            char title[] = "Title";
            text[num_text].key = title;
            text[num_text].text = mainprogPointer->title;
            ++num_text;
        
            text[num_text].compression = PNG_TEXT_COMPRESSION_NONE;
            char author[] = "Author";
            text[num_text].key = author;
            text[num_text].text = mainprogPointer->author;
            ++num_text;
        
            text[num_text].compression = PNG_TEXT_COMPRESSION_NONE;
            char desc[] = "Description";
            text[num_text].key = desc;
            text[num_text].text = mainprogPointer->desc;
            ++num_text;
        
            text[num_text].compression = PNG_TEXT_COMPRESSION_NONE;
            char copyright[] = "Copyright";
            text[num_text].key = copyright;
            text[num_text].text = mainprogPointer->copyright;
            ++num_text;
        
            text[num_text].compression = PNG_TEXT_COMPRESSION_NONE;
            char email[] = "E-mail";
            text[num_text].key = email;
            text[num_text].text = mainprogPointer->email;
            ++num_text;
        
            text[num_text].compression = PNG_TEXT_COMPRESSION_NONE;
            char url[] = "URL";
            text[num_text].key = url;
            text[num_text].text = mainprogPointer->url;
            ++num_text;
        }
        png_set_text(pngPointer, infoPointer, text, num_text);
    }

    png_write_info(pngPointer, infoPointer);
    
    png_set_packing(pngPointer);
    
    mainprogPointer->png_ptr = pngPointer;
    mainprogPointer->info_ptr = infoPointer;
    
    if (setjmp(mainprogPointer->jmpbuf)) {
        png_destroy_write_struct(&pngPointer, &infoPointer);
        mainprogPointer->png_ptr = NULL;
        mainprogPointer->info_ptr = NULL;
        return 2;
    }
  
    png_write_image(pngPointer, mainprogPointer->row_pointers);
  
    png_write_end(pngPointer, NULL);
  
    /***
     INTERLACING ????
     */
    
    // Output is 8bit depth, RGBA format.
//    png_set_IHDR(
//        pngPointer,
//        infoPointer,
//        imgWidth, imgHeight,
//        8,
//        PNG_COLOR_TYPE_RGBA,
//        PNG_INTERLACE_NONE,
//        PNG_COMPRESSION_TYPE_DEFAULT,
//        PNG_FILTER_TYPE_DEFAULT
//    );
//    
//    png_write_info(pngPointer, infoPointer);
//
//    // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
//    // Use png_set_filler().
//    //png_set_filler(png, 0, PNG_FILLER_AFTER);
//
//    png_write_image(pngPointer, rowPointers);
//    png_write_end(pngPointer, NULL);
//
//    for(int y = 0; y < imgHeight; y++) {
//      free(rowPointers[y]);
//    }
//    
//    fclose(outfile);
//    return 0;
}