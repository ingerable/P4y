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
#include <string>
#include "image.h"
#include "fileio.h"

// read binary grayscale PGM
Image <uint8_t> readPGM(const std::string &inputFile)
{
  int number_of_lines=0; // nbr de lignes
  std::ifstream myFile(inputFile); // fichier
  std::string line; // ligne courante
  int dx;
  int dy;
  uint8_t *buffer;

    if(myFile.is_open())
    {
      std::getline(myFile,line);
      std::getline(myFile,line);
      std::stringstream sstr(line);
      sstr >> dx >> dy ;
      printf("%d\n",dx );
      printf("%d\n",dy );
      buffer = new uint8_t [dx*dy]; /// on alloue la taille mémoire pour le buffer
      std::getline(myFile,line);
      myFile.read((char *) buffer,dx*dy);
      Image<uint8_t> res(dx,dy,buffer);
      myFile.close();
      return res;
    }

    return 0;
}

// renvoit vrai si les pixels entre les 2 images diffèrenvoit
int compareImages(const Image<uint8_t> &image1, const Image<uint8_t> &image2)
{
  if(image1.getSize()!=image2.getSize())
  {
    std::cout<<"Les images n'ont pas le meme nombre de pixels";
  }else{
  /*  for(int i=0; i<=image1.getSize();i++)
    {

    }*/
    //std::cout<<image1.getData();

  }
std::cout<<image1.getData();
return 1;
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
