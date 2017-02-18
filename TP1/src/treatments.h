//
//  treatments.h
//  tp-P4y
//
//
//
//
#ifndef treatments_h
#define treatments_h

#include <iostream>
#include <cstdint>
#include "image.h"

void thresholding(Image<uint8_t> &image, const int value);
void negation(Image<uint8_t> &image);
void quantize(Image<uint8_t> &image, int k);
void resampleOneDimension(int tab[], int factor);
void resampleOneDimensionBilinear(int tab[], int factor);
Image<uint8_t> resampleNN(Image<uint8_t> &img, int factor);
Image<uint8_t> resampleBilinearInterpolation(Image<uint8_t> &img, int factor);

#endif /* treatments_h */
