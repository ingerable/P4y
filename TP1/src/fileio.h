//
//  fileio.h
//  tp-P4y
//
//  Created by Benoit Naegel on 27/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#ifndef fileio_h
#define fileio_h

#include <iostream>
#include <cstdint>
#include "image.h"

Image<uint8_t> readPGM(const std::string &inputFile);
int writePGM(const Image<uint8_t> &image8b, const std::string &outputFile);


#endif /* fileio_h */
