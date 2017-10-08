/* 
 * File:   writepng.h
 * Author: heshan
 *
 * Created on October 8, 2017, 8:33 PM
 */

#ifndef WRITEPNG_H
#define WRITEPNG_H

typedef struct _mainprog_info {
    double gamma;
    long width;
    long height;
    time_t modtime;
    FILE *infile;
    FILE *outfile;
    void *png_ptr;
    void *info_ptr;
    unsigned char *image_data;
    unsigned char **row_pointers;
    char *title = 0;
    char *author = 0;
    char *desc = 0;
    char *copyright = 0;
    char *email = 0;
    char *url = 0;
    int filter;
    int pnmtype;
    int sample_depth;
    int interlaced;
    int have_bg;
    int have_time;
    int have_text;
    jmp_buf jmpbuf;
    unsigned char bg_red;
    unsigned char bg_green;
    unsigned char bg_blue;
} mainprog_info;
    

#endif /* WRITEPNG_H */

