//
//  main.cpp
//  tp-P4y
//
//  Created by Benoit Naegel on 25/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << "<dx> <dy> <fichier.PGM> \n";
        exit(EXIT_FAILURE);
    }
    int dx=atoi(argv[1]);
    int dy=atoi(argv[2]);
    std::string fichierPGM = argv[3];

    Image<uint8_t> A(dx,dy);

    for(int y=0; y<A.getDy(); ++y) {
        for(int x=0; x<A.getDx(); ++x) {
            A(x,y)=(x+y)%10;
        }
    }

    std::cout <<"Image A :\n";
    A.print();

    uint8_t buffer[]={0,1,2,
                     3,4,5,
                     6,7,8,
                     9,10,11};

    Image<uint8_t> B(3,4,buffer);

    std::cout <<"Image B :\n";
    B.print();

    double buffer2[]={0.1,0.2,0.3,
                     0.4,0.5,0.6};

    Image <double> C(3,2,buffer2);
    std::cout <<"Image C :\n";
    C.print();

    Image <uint8_t> D(dx,dy);
    for(int y=0; y<D.getDy(); ++y)
    {
      int mod = 0;
        for(int x=0; x<D.getDx(); ++x)
        {
          D(x,y)=((x+y)%2)*255;
        }
    }
    std::cout <<"Image D :\n";
    D.print();


    Image<uint8_t> E();
    std::cout<<"Image PGM :\n";
    writePGM(readPGM(fichierPGM),"tst.pgm");

    return 0;
}
