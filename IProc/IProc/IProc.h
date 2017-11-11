/* 
 * File:   IProc.h
 * Author: heshan
 *
 * Created on October 5, 2017, 1:32 PM
 */

#ifndef IPROC_H
#define IPROC_H

#include <cstring>

#include "../PNGProcessor/PNGProcessor.h"
#include "../JPEGProcessor/JPEGProcessor.h"
#include "../PixelProcessor/PixelProcessor.h"
#include "../PixelProcessor/PNGPixelProcessor.h"

class IProc {
public:
    IProc();
    IProc(const IProc& orig);
    virtual ~IProc();
    
    int readImageFormatInfo(std::string);
    
    int setImageFormat();
    int getImageFormat();
    
    int readImage(std::string);
    int writeImage(std::string);
    int writeImage(std::string, std::string);
    
    int resizeImage(int, int);
    
    int testMethod();
    
private:
    
    PNGProcessor pngProc;
    PNGPixelProcessor pngPixProc;
    JPEGProcessor jpegProc;
   
    int imgType; // [1:png, 2:jpeg, 3:---, 4:---]

};

#endif /* IPROC_H */

