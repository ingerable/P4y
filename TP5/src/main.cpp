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


    uint8_t buffer[]={
      1,2,3,4,5,
      6,7,8,9,10,
      11,12,13,14,15,
      16,17,18,19,20,
      21,22,23,24,25,
    };


    Image<uint8_t> T(5,5,buffer);


    Image<uint8_t> E = readPGM(fichierPGM);
    //std::cout<<"Image PGM :\n";


    writePGM(impulseNoise(E,0.1),"boatImpulseNoise1.pgm");
    //writePGM(impulseNoise(E,0.8),"boatImpulseNoise8.pgm");

    return 0;
}
