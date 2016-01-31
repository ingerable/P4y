//
//  main.cpp
//  tp-P4y
//
//  Created by Benoit Naegel on 25/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include "image.h"
#include "fileio.h"

using namespace P4y;

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << "<width> <height>\n";
        exit(EXIT_FAILURE);
    }
    int width=atoi(argv[1]);
    int height=atoi(argv[2]);
    
    Image8b A(width,height);
    
    for(int y=0; y<A.getHeight(); y++) {
        for(int x=0; x<A.getWidth(); x++) {
            A(x,y)=(x+y)%256;
        }
    }
    
    A.print();
    
    return 0;
}
