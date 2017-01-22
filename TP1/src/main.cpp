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
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << "<dx> <dy>\n";
        exit(EXIT_FAILURE);
    }
    int dx=atoi(argv[1]);
    int dy=atoi(argv[2]);
    
    Image<uint8_t> A(dx,dy);
    
    for(int y=0; y<A.getDy(); ++y) {
        for(int x=0; x<A.getDx(); ++x) {
            A(x,y)=(x+y)%10;
        }
    }
    
    A.print();

    uint8_t buffer[]={0,1,2,
                     3,4,5,
                     6,7,8,
                     9,10,11};
    Image<uint8_t> B(3,4,buffer);
    
    B.print();
    
    return 0;
}
