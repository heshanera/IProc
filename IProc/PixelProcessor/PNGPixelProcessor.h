/* 
 * File:   PNGPixelProcessor.h
 * Author: heshan
 *
 * Created on October 30, 2017, 11:27 PM
 */

#ifndef PNGPIXELPROCESSOR_H
#define PNGPIXELPROCESSOR_H

#include <sys/types.h>
#include <png.h>
#include "PixelProcessor.h"

class PNGPixelProcessor : public PixelProcessor {
public:
    PNGPixelProcessor();
    PNGPixelProcessor(const PNGPixelProcessor& orig);
    virtual ~PNGPixelProcessor();
    
    u_int* resize(int, int, int, int, png_bytep*);
    
private:

};

#endif /* PNGPIXELPROCESSOR_H */

