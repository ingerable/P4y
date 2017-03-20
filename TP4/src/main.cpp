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
    //std::cout<<"Image PGM :\n";


    // TP4
    //writePGM(medianFilter(E,7),"./imagesResultat/median7Lena.pgm");
    /*uint8_t bufferMedian[] = {1,2,3,4,5,6,7,8,9}; // buffer de l'image à tester
    Image<uint8_t> medianTest(3,3,bufferMedian);
    medianFilter(medianTest,3).print();
    medianTest.print();*/


    writePGM(medianFilter(E,3),"./lenaMedian3.pgm");
    writePGM(medianFilter(E,5),"./lenaMedian5.pgm");
    writePGM(medianFilter(E,8),"./lenaMedian8.pgm");





    return 0;
}
