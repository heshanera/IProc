/* 
 * File:   IProc.cpp
 * Author: heshan
 * 
 * Created on October 5, 2017, 1:32 PM
 */

#include <iostream>
#include "IProc.h"

IProc::IProc() {
}

IProc::IProc(const IProc& orig) {
}

IProc::~IProc() {
}

int IProc::testMethod(){
    
    std::cout<<"start testing...\n\n";
    
    PNGProcessor pngProc;
    pngProc.readPNGVersionInfo();
    
    std::cout<<"\n\nstart testing...";
    
    return 0;
}