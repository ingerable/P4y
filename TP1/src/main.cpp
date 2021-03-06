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
    /*int seuil = atoi(argv[4]);
    int k = atoi(argv[5]);
    int f = atoi(argv[6]);*/

    Image<uint8_t> A(dx,dy);

    for(int y=0; y<A.getDy(); ++y) {
        for(int x=0; x<A.getDx(); ++x) {
            A(x,y)=(x+y)%10;
        }
    }

    std::cout <<"Image A :\n";
    A.print();

    uint8_t buffer[]={0,1,2,
                     3,4,5,
                     6,7,8,
                     9,10,11};

    Image<uint8_t> B(3,4,buffer);

    std::cout <<"Image B :\n";
    B.print();

    double buffer2[]={0.1,0.2,0.3,
                     0.4,0.5,0.6};

    Image <double> C(3,2,buffer2);
    std::cout <<"Image C :\n";
    C.print();

    Image <uint8_t> D(dx,dy);
    for(int y=0; y<D.getDy(); ++y)
    {
      int mod = 0;
        for(int x=0; x<D.getDx(); ++x)
        {
          D(x,y)=((x+y)%2)*255;
        }
    }
    std::cout <<"Image D :\n";
    D.print();


    Image<uint8_t> E = readPGM(fichierPGM);
    std::cout<<"Image PGM :\n";
    //writePGM(readPGM(fichierPGM),"tst.pgm");

    thresholding(E,10);
    writePGM(E,"./seuillageGaussContours5.pgm");

    //E = readPGM(fichierPGM);
    //negation(E);
    //writePGM(E,"./resultats/negatif.pgm");

    //E = readPGM(fichierPGM);
    //quantize(E,k);
    //writePGM(E,"./resultats/quantize"+std::to_string(k)+".pgm");

    /*E = resampleBilinearInterpolation(E,2);
    E.print();
    E = Image<uint8_t>(5,5,bufferQ);
    E.print();
    E = resampleBilinearInterpolation(E,2);
    E.print();*/

    //writePGM(resampleBilinearInterpolation(E,f),"./resultats/resampleBI"+std::to_string(f)+".PGM");
    //E = readPGM(fichierPGM);
    //E = resampleNN(E,2);
    //E.print();


    // TP3
    //double bufZ[] ={1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,};  //M1
    //double bufZ[] ={1.0/16,2.0/16,1.0/16,2.0/16,4.0/16,2.0/16,1.0/16,2.0/16,1.0/16};  //M2
    //double bufZ[] ={0,-1,0,-1,5,-1,0,-1,0};  //M3
    //double bufZ[] ={-1,-1,-1,-1,9,-1,-1,-1,-1};  //M4
    //double bufZ[] ={-1,0,1,-2,0,2,-1,0,1};  //Sx
    //Image<double> mask(3,3,bufZ);
    //Image<double> maskG = gaussianMask(3.0);
    //Image<double> resD = convolve(E,maskG);
    //Image<uint8_t> res = toUint8(resD);
    //Image<double> resDD = convolve(res,mask);

    //Image<uint8_t> resF = contours(res,mask);
    //writePGM(toUint8(resDD),"../../TP3/LenaGaussRehaussementContours3.pgm");

    /*
    Image<double> res = convolve(B,mask);
    res.print();
    Image<double> res = gaussianMask(0.8);
    res.print();*/

    // TP4
    //writePGM(medianFilter(E,3),"./resultatTP4/median"+fichierPGM+".pgm");
    /*uint8_t bufferMedian[] = {1,2,3,4,5,6,7,8,9}; // buffer de l'image à tester
    Image<uint8_t> medianTest(3,3,bufferMedian);
    medianFilter(medianTest,3).print();
    medianTest.print();*/


    return 0;
}
