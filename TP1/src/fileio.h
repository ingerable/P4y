//
//  fileio.h
//  tp-P4y
//
//  Created by Benoit Naegel on 27/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#ifndef fileio_h
#define fileio_h

namespace P4y {

class FileIO {
public:
    static int readPGM(const std::string &inputFile, Image8b &result);
    static int writePGM(Image8b &image8b, const std::string &outputFile);
};
    
    
} // namespace P4y

#endif /* fileio_h */
