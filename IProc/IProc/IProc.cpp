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

int IProc::test(){
    std::cout<<"testing...";
    return 0;
}