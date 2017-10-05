/* 
 * File:   IProc.h
 * Author: heshan
 *
 * Created on October 5, 2017, 1:32 PM
 */

#ifndef IPROC_H
#define IPROC_H

#include "../libiproc.h" 

class IProc {
public:
    IProc();
    IProc(const IProc& orig);
    virtual ~IProc();
    int test();
private:

};

#endif /* IPROC_H */

