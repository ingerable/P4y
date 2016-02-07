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

namespace P4y {

// read binary grayscale PGM 
int FileIO::readPGM(const std::string &inputFile, Image8b &result)
{
    std::ifstream file(inputFile);
    if(file.is_open()) {
        std::string line;
        std::getline(file,line);
        // only binary, greyscale PGM
        if(line=="P5") {
            int width,height,maxValue;
            std::getline(file,line);
            // remove comments beginning by '#'
            while(line[0]=='#') std::getline(file,line);
            std::stringstream ss(line);
            ss >> width >> height;
            std::getline(file,line);
            ss.clear();
            ss.str(line);
            ss>>maxValue;
            std::cout << "Reading header.\nFile "<<inputFile<< "\nwidth "  << width << "\nheight " <<height << "\nmaxValue " << maxValue << "\n";
            int bufSize=width*height;
            char *buffer=new char[bufSize];
            file.read(buffer,bufSize);
            Image8b tmp(width,height,reinterpret_cast<unsigned char*> (buffer));
            result=tmp;
            delete[] buffer;
        }
        else return -1;
        
        file.close();
    }
    else return -1;
    
    return 0;
}

// write binary greyscale PGM
int FileIO::writePGM(P4y::Image8b &image8b, const std::string &outputFile)
{
    std::ofstream file(outputFile,std::ios_base::trunc  | std::ios_base::binary);
    if(file.is_open()) {
        std::string line;
        
        int width=image8b.getWidth();
        int height=image8b.getHeight();
        int size=width*height;
        
        file << "P5\n" << width << " " << height << "\n" << "255" ;
        file << "\n";
        
        file.write(reinterpret_cast<char *> (image8b.getData()),size);
        
        file << "\n";
        
        file.close();
    }
    else return -1;
    
    return 0;
}

    
}

// namespace P4y