//
//  main.cpp
//  tp-P4y
//
//  Created by Benoit Naegel on 31/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include "image.h"
#include "fileio.h"

using namespace P4y;

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << "<in.pgm> <out.pgm> \n";
        exit(EXIT_FAILURE);
    }
    std::string inputFile=argv[1];
    std::string outputFile=argv[2];
    
    Image8b in;
    // lecture
    FileIO::readPGM(inputFile, in);
    
    // écriture
    FileIO::writePGM(in,outputFile);
    
    return 0;
}
