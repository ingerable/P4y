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
    Image <uint8_t> error;
    std::ifstream file(inputFile);
    if(file.is_open()) {
        std::string line;
        std::getline(file,line);
        // only binary, greyscale PGM
        if(line=="P5") {
            int dx,dy,maxValue;
            std::getline(file,line);
            // remove comments beginning by '#'
            while(line[0]=='#') 
                std::getline(file,line);
            std::stringstream ss(line);
            ss >> dx >> dy;
            std::getline(file,line);
            ss.clear();
            ss.str(line);
            ss>>maxValue;
            std::cout << "Reading header.\nFile "<<inputFile<< "\ndx : "  << dx << "\ndy : " <<dy << "\nmaxValue : " << maxValue << "\n";
            int size=dx*dy;
            uint8_t *buffer=new uint8_t[size];
            file.read((char *)buffer,size);
            Image <uint8_t> result(dx,dy,buffer);
            delete[] buffer;
            return result;
            
        }
        file.close();
    }
   
    return error;
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
