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


int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << "<in.pgm> <out.pgm> \n";
        exit(EXIT_FAILURE);
    }
    std::string inputFile=argv[1];
    std::string outputFile=argv[2];
    
    Image<uint8_t> in=readPGM(inputFile);
    writePGM(in,outputFile);
    
    return 0;
}
