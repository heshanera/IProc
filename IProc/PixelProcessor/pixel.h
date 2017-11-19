/* 
 * File:   pixel.h
 * Author: heshan
 *
 * Created on November 19, 2017, 5:33 PM
 */

#ifndef PIXEL_H
#define PIXEL_H

#ifdef __cplusplus
extern "C" {
#endif

struct RGBApixel {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;
};

#ifdef __cplusplus
}
#endif

#endif /* PIXEL_H */

