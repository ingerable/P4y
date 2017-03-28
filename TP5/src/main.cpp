//
//  main.cpp
//  tp-P4y
//
//  Created by Benoit Naegel on 25/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "processing.h"
#include "Structel.h"
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << "<dx> <dy> <fichier.PGM>\n";
        exit(EXIT_FAILURE);
    }
    int dx = atoi(argv[1]);
    int dy = atoi(argv[2]);
    std::string fichierPGM = argv[3];


    /*uint8_t buffer[]={
      1,2,3,4,5,
      6,7,8,9,10,
      11,12,13,14,15,
      16,17,18,19,20,
      21,22,23,24,25,
    };*/

    uint8_t buffer[]={
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,10,5,1,
      1,1,1,5,1,
      1,1,1,5,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,10,5,1,
      1,1,1,5,1,
      1,1,1,5,1,
      1,1,1,1,1,
    };

    /*uint8_t buffer[]={
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
      1,1,1,1,1,
    };*/


    Image<uint8_t> T(10,10,buffer);


    Image<uint8_t> E = readPGM(fichierPGM);
    //std::cout<<"Image PGM :\n";

    //génération d'images

/*
    writePGM(impulseNoise(E,0.15),"barbaraImpulseNoise015Median3.pgm");
    writePGM(impulseNoise(E,0.40),"barbaraImpulseNoise040Median3.pgm");
    writePGM(noiseGaussian(E,0,15),"barbaraGaussianNoise015Median3.pgm");
    writePGM(noiseGaussian(E,0,30),"barbaraGaussianNoise030Median3.pgm");

    std::cout<<"<<<<<<<<<<<<<<<<<<<< MSE bruit image original >>>>>>>>>>>>>>>>>>>>>>>"<<"\n";
    Image <uint8_t> k = impulseNoise(E,0.15);
    std::cout<<"MSE impulse noise 0.15  : "<<computeMSE(k,E)<<"\n";
    k = impulseNoise(E,0.40);
    std::cout<<"MSE impulse noise 0.40  : "<<computeMSE(k,E)<<"\n";
    k = noiseGaussian(E,0,15);
    std::cout<<"MSE gaussian noise 0 & 15  : "<<computeMSE(k,E)<<"\n";
    k = noiseGaussian(E,0,30);
    std::cout<<"MSE gaussian noise 0 & 30 : "<<computeMSE(k,E)<<"\n";


    E = medianFilter(E,3);

    writePGM(medianFilter(impulseNoise(E,0.15),3),"barbaraImpulseNoise015Median3.pgm");
    writePGM(medianFilter(impulseNoise(E,0.40),3),"barbaraImpulseNoise040Median3.pgm");
    writePGM(medianFilter(noiseGaussian(E,0,15),3),"barbaraGaussianNoise015Median3.pgm");
    writePGM(medianFilter(noiseGaussian(E,0,30),3),"barbaraGaussianNoise030Median3.pgm");

    std::cout<<"<<<<<<<<<<<<<<<<<<<< MSE médian 3 >>>>>>>>>>>>>>>>>>>>>>>"<<"\n" ;

     k = medianFilter(impulseNoise(E,0.15),3);
    std::cout<<"MSE impulse noise 0.15 Median 3 : "<<computeMSE(k,E)<<"\n";
    k = medianFilter(impulseNoise(E,0.40),3);
    std::cout<<"MSE impulse noise 0.40 Median 3 : "<<computeMSE(k,E)<<"\n";
    k = medianFilter(noiseGaussian(E,0,15),3);
    std::cout<<"MSE gaussian noise 0 & 15 Median 3 : "<<computeMSE(k,E)<<"\n";
    k = medianFilter(noiseGaussian(E,0,30),3);
    std::cout<<"MSE gaussian noise 0 & 30 Median 3 : "<<computeMSE(k,E)<<"\n";

    E = medianFilter(E,7);

    writePGM(medianFilter(impulseNoise(E,0.15),7),"barbaraImpulseNoise015Median7.pgm");
    writePGM(medianFilter(impulseNoise(E,0.40),7),"barbaraImpulseNoise040Median7.pgm");
    writePGM(medianFilter(noiseGaussian(E,0,15),7),"barbaraGaussianNoise015Median7.pgm");
    writePGM(medianFilter(noiseGaussian(E,0,30),7),"barbaraGaussianNoise030Median7.pgm");

    std::cout<<"<<<<<<<<<<<<<<<<<<<< MSE médian 7 >>>>>>>>>>>>>>>>>>>>>>>"<<"\n";

    k = medianFilter(impulseNoise(E,0.15),7);
    std::cout<<"MSE impulse noise 0.15 Median 7 : "<<computeMSE(k,E)<<"\n";
    k = medianFilter(impulseNoise(E,0.40),7);
    std::cout<<"MSE impulse noise 0.40 Median 7 : "<<computeMSE(k,E)<<"\n";
    k = medianFilter(noiseGaussian(E,0,15),7);
    std::cout<<"MSE gaussian noise 0 & 15 Median 7 : "<<computeMSE(k,E)<<"\n";
    k = medianFilter(noiseGaussian(E,0,30),7);
    std::cout<<"MSE gaussian noise 0 & 30 Median 7 : "<<computeMSE(k,E)<<"\n";

    std::cout<<"<<<<<<<<<<<<<<<<<<<< MSE filtre moyenneur 3 >>>>>>>>>>>>>>>>>>>>>>>"<<"\n";

    double buf[]={
      1.0/9,1.0/9,1.0/9,
      1.0/9,1.0/9,1.0/9,
      1.0/9,1/9,1/9,
      1/9,1/9,1/9,
      1/9,1/9,1/9,
    };
    Image<double> m3(3,3);

    for(int y=0;y<3; y++)
    {
      for(int x=0;x<3; x++)
      {
        m3(x,y) = 1.0/9;
      }
    }

    Image <uint8_t> n = impulseNoise(E,0.15);
    Image <double> l = convolve(n,m3);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseNoise015Moyenneur3.pgm");
    std::cout<<"MSE impulse noise 0.15 Convolve 3 : "<<computeMSE(k,E)<<"\n";
    n = impulseNoise(E,0.15);
    l = convolve(n,m3);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseNoise040Moyenneur3.pgm");
    std::cout<<"MSE impulse noise 0.40 Convolve 3 : "<<computeMSE(k,E)<<"\n";
    n = noiseGaussian(E,0,15);
    l = convolve(n,m3);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseGaussianNoise015Moyenneur3.pgm");
    std::cout<<"MSE gaussian noise 0 & 15 Convolve 3 : "<<computeMSE(k,E)<<"\n";
    n = noiseGaussian(E,0,30);
    l = convolve(n,m3);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseGaussianNoise030Moyenneur3.pgm");
    std::cout<<"MSE gaussian noise 0 & 30 Convolve 3 : "<<computeMSE(k,E)<<"\n";

    std::cout<<"<<<<<<<<<<<<<<<<<<<< MSE filtre moyenneur 7 >>>>>>>>>>>>>>>>>>>>>>>"<<"\n";

    Image<double> m7(7,7);
    for(int y=0;y<7; y++)
    {
      for(int x=0;x<7; x++)
      {
        m7(x,y)=(1.0/49);
      }
    }

    n = impulseNoise(E,0.15);
    l = convolve(n,m7);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseNoise015Moyenneur7.pgm");
    std::cout<<"MSE impulse noise 0.15 Convolve 7 : "<<computeMSE(k,E)<<"\n";
    n = impulseNoise(E,0.15);
    l = convolve(n,m7);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseNoise040Moyenneur7.pgm");
    std::cout<<"MSE impulse noise 0.40 Convolve 7 : "<<computeMSE(k,E)<<"\n";
    n = noiseGaussian(E,0,15);
    l = convolve(n,m7);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseGaussianNoise015Moyenneur7.pgm");
    std::cout<<"MSE gaussian noise 0 & 15 Convolve 7 : "<<computeMSE(k,E)<<"\n";
    n = noiseGaussian(E,0,30);
    l = convolve(n,m7);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseGaussianNoise030Moyenneur7.pgm");
    std::cout<<"MSE gaussian noise 0 & 30 Convolve 7 : "<<computeMSE(k,E)<<"\n";

    std::cout<<"<<<<<<<<<<<<<<<<<<<< MSE filtre gaussien 1 >>>>>>>>>>>>>>>>>>>>>>>"<<"\n";

    Image<double> maskG = gaussianMask(1);


    n = impulseNoise(E,0.15);
    l = convolve(n,maskG);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseNoise015Gauss1.pgm");
    std::cout<<"MSE impulse noise 0.15 Gauss 1 : "<<computeMSE(k,E)<<"\n";
    n = impulseNoise(E,0.40);
    l = convolve(n,maskG);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseNoise040Gauss1.pgm");
    std::cout<<"MSE impulse noise 0.40 Gauss 1 : "<<computeMSE(k,E)<<"\n";
    n = noiseGaussian(E,0,15);
    l = convolve(n,maskG);
    k = toUint8(l);
    writePGM(k,"barbaraGaussianNoise015Gauss1.pgm");
    std::cout<<"MSE gaussian noise 0 & 15 Gauss 1 : "<<computeMSE(k,E)<<"\n";
    n = noiseGaussian(E,0,30);
    l = convolve(n,maskG);
    k = toUint8(l);
    writePGM(k,"barbaraGaussianNoise030Gauss1.pgm");
    std::cout<<"MSE gaussian noise 0 & 30 Gauss 1 : "<<computeMSE(k,E)<<"\n";






    std::cout<<"<<<<<<<<<<<<<<<<<<<< MSE filtre gaussien 2 >>>>>>>>>>>>>>>>>>>>>>>"<<"\n";

    maskG = gaussianMask(2);


    n = impulseNoise(E,0.15);
    l = convolve(n,maskG);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseNoise015Gauss2.pgm");
    std::cout<<"MSE impulse noise 0.15 Gauss 2 : "<<computeMSE(k,E)<<"\n";
    n = impulseNoise(E,0.40);
    l = convolve(n,maskG);
    k = toUint8(l);
    writePGM(k,"barbaraImpulseNoise040Gauss2.pgm");
    std::cout<<"MSE impulse noise 0.40 Gauss 2 : "<<computeMSE(k,E)<<"\n";
    n = noiseGaussian(E,0,15);
    l = convolve(n,maskG);
    k = toUint8(l);
    writePGM(k,"barbaraGaussianNoise015Gauss2.pgm");
    std::cout<<"MSE gaussian noise 0 & 15 Gauss 2 : "<<computeMSE(k,E)<<"\n";
    n = noiseGaussian(E,0,30);
    l = convolve(n,maskG);
    k = toUint8(l);
    writePGM(k,"barbaraGaussianNoise030Gauss2.pgm");
    std::cout<<"MSE gaussian noise 0 & 30 Gauss 2 : "<<computeMSE(k,E)<<"\n";

*/
    //writePGM(computeNLMeans(E,21,7,50.0),"test.pgm");



    //Image<uint8_t> M = computeNLMeans(K,21,3,50.0);
    //writePGM(M,"NLBarbara025.pgm");


    return 0;
}
