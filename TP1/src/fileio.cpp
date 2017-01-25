//
//  fileio.cpp
//  tp-P4y
//
//  Created by Benoit Naegel on 27/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "image.h"
#include "fileio.h"

// read binary grayscale PGM 
Image <uint8_t> readPGM(const std::string &inputFile)
{
    // à compléter
}

// write binary greyscale PGM
int writePGM(const Image<uint8_t> &image, const std::string &outputFile)
{
    std::ofstream file(outputFile,std::ios_base::trunc  | std::ios_base::binary);
    if(file.is_open()) {
        std::string line;
        
        int dx=image.getDx();
        int dy=image.getDy();
        int size=dx*dy;
        
        file << "P5\n" << dx << " " << dy << "\n" << "255" ;
        file << "\n";
        
        file.write((char *)image.getData(),size);
        
        file << "\n";
        
        file.close();
    }
    else return -1;
    
    return 0;
}

