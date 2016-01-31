//
//  image.cpp
//  tp-P4y
//
//  Created by Benoit Naegel on 25/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#include "image.h"
#include <iostream>

namespace P4y {
    
Image8b::Image8b(int width, int height):data(0)
{
    if(width>=0 && height>=0) {
        this->width=width;
        this->height=height;
        this->size=width*height;
        this->data=new unsigned char[width*height];
    }
}
    
Image8b::Image8b(int width, int height, unsigned char *data)
{
    if(width>=0 && height>=0) {
        this->width=width;
        this->height=height;
        this->size=width*height;
        this->data=new unsigned char[width*height];
        memcpy(this->data, data, size);
    }
}

Image8b::Image8b(const Image8b &image8b)
{
    this->width=image8b.width;
    this->height=image8b.height;
    this->size=image8b.size;
    this->data=new unsigned char[width*height];
    for(int i=0; i<width*height; ++i) {
        this->data[i]=image8b.data[i];
    }
    
}
    
Image8b &Image8b::operator=(const Image8b &image8b)
{
    if(this!=&image8b)
    {
        if(this->data!=0) {
            delete[] data;
            data=0;
        }
        this->width=image8b.width;
        this->height=image8b.height;
        this->size=width*height;
        this->data=new unsigned char[width*height];
        for(int i=0; i<this->size; i++) {
            this->data[i]=image8b.data[i];
        }
    }
    return *this;
}
    
Image8b::~Image8b()
{
    if(data!=0)
    {
        delete[] data;
    }
}

int Image8b::getWidth()
{
    return width;
}

int Image8b::getHeight()
{
    return height;
}
    
int Image8b::getSize()
{
    return size;
}
    
unsigned char* Image8b::getData()
{
    return data;
}
    
void Image8b::print()
{
    
    for(int x=0; x<width; x++) {
        std::cout.width(3);
        std::cout << "----";
    }
    std::cout << "\n";
    
    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            std::cout.width(3);
            std::cout << (int)(*this)(x,y) << "|";
        }
        std::cout << "\n";
        for(int x=0; x<width; x++) {
            std::cout.width(3);
            std::cout << "----";
        }
        std::cout << "\n";
    }
}
    
    
unsigned char &Image8b::operator()(const int &x, const int &y)
{
    return data[y*width+x];
}
    
unsigned char Image8b::operator() (const int &x, const int &y) const
{
    return data[y*width+x];
}
    
    
} // namespace P4y