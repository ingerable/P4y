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
Image<double> convolve(Image<uint8_t> &img, Image<double> &mask);
Image<double> gaussianMask(float sigma);
Image<uint8_t> toUint8(Image<double> &img);
Image<uint8_t> contours(Image<uint8_t> img, Image<double> mask);
Image<uint8_t> medianFilter(Image<uint8_t> img, int N);

#endif /* treatments_h */
