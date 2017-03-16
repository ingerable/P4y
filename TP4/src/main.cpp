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



    Image<uint8_t> E = readPGM(fichierPGM);
    std::cout<<"Image PGM :\n";


    // TP4
    //writePGM(medianFilter(E,7),"./imagesResultat/median7Lena.pgm");
    /*uint8_t bufferMedian[] = {1,2,3,4,5,6,7,8,9}; // buffer de l'image à tester
    Image<uint8_t> medianTest(3,3,bufferMedian);
    medianFilter(medianTest,3).print();
    medianTest.print();*/
    std::vector<Couple> pB = { {10,10},{9,10},{8,10},{7,10},{6,10},{5,10},
                                    {6,5},{7,5},{8,5},{9,5},{10,5},
                                    {5,9},{5,8},{5,7},{5,6},{5,5},
                                  {10,6},{10,7},{10,8},{10,9} };

   //Structel b = Structel(pB);
   Structel a = Structel::carre(1);
   Structel b = Structel::disque(1);
   writePGM(b.gradient(E),"./imagesResultat/gradMorphoCroix.pgm");

   //writePGM(a.externalGradient(E),"./../images/externalGradientSoil.pgm");
   //Structel::granulometry(E);
    return 0;
}
