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

//thresholding function with uint8_t picture, parameters are a picture and a thresholding value (0-255)

void thresholding(Image<uint8_t> &image, const int value)
{
  for(int y=0; y<image.getDy(); ++y) // on parcourt les pixels de l'image entrée
  {
      for(int x=0; x<image.getDx(); ++x)
      {
        if(image(x,y)>value) // si la valeur du pixel est supérieur on lui affecte la valeur 255
          {
            image(x,y)=255;
          }else{
            image(x,y)=0; // sinon on lui affecte 0
          }
      }
  }

}
