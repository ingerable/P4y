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
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << "<in.pgm> <out.pgm> <S>\n";
        exit(EXIT_FAILURE);
    }
    std::string inputFile=argv[1];
    std::string outputFile=argv[2];
    int S=atoi(argv[3]);
    
    Image8b in;
    FileIO::readPGM(inputFile, in);
    
    for(int y=0; y<in.getHeight(); ++y) {
        for(int x=0; x<in.getWidth(); ++x)
            if(in(x,y) > S)
                in(x,y)=255;
            else in(x,y)=0;
    }
    
    FileIO::writePGM(in,outputFile);
    
    return 0;
}
