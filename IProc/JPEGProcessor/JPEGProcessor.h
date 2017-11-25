/* 
 * File:   JPEGProcessor.h
 * Author: heshan
 *
 * Created on October 5, 2017, 4:02 PM
 */

#ifndef JPEGPROCESSOR_H
#define JPEGPROCESSOR_H

#include <stdio.h>
#include <setjmp.h>
#include "jpeglib.h"

class JPEGProcessor {
public:
    JPEGProcessor();
    JPEGProcessor(const JPEGProcessor& orig);
    virtual ~JPEGProcessor();
private:

};

#endif /* JPEGPROCESSOR_H */

