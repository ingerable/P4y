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

//tp1
void thresholding(Image<uint8_t> &image, const int value);
void negation(Image<uint8_t> &image);
//tp2
void quantize(Image<uint8_t> &image, int k);
void resampleOneDimension(int tab[], int factor);
void resampleOneDimensionBilinear(int tab[], int factor);
Image<uint8_t> resampleNN(Image<uint8_t> &img, int factor);
Image<uint8_t> resampleBilinearInterpolation(Image<uint8_t> &img, int factor);
Image<double> convolve(Image<uint8_t> &img, Image<double> &mask);
//tp3
Image<double> gaussianMask(float sigma);
Image<uint8_t> toUint8(Image<double> &img);
Image<uint8_t> contours(Image<uint8_t> img, Image<double> mask);
//tp4
Image<uint8_t> medianFilter(Image<uint8_t> img, int N);
//tp5
Image<uint8_t> impulseNoise(Image<uint8_t> &img, float p);
Image<uint8_t> noiseGaussian(Image<uint8_t> &img,float avg,float deviation);
double computeMSE(Image<uint8_t> &imgN, Image<uint8_t> &imgO);
void impulseNoiseGraph(Image<uint8_t> &img);
double computeSimilarity(Image<uint8_t> &img, int x1, int y1, int x2, int y2, int D);
Image<uint8_t> computeNLMeans(Image<uint8_t> &img, int windowSize, int patchSize, double h);
#endif /* treatments_h */
