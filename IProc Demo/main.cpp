/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on October 5, 2017, 1:48 PM
 */

#include <cstdlib>
#include <libiproc.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    IProc iproc;
    iproc.readImageFormatInfo("png");
    iproc.readImage("imgs/PNG/img1.png");
    iproc.testMethod();
    
    return 0;
}

