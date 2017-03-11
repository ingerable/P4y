
#include <vector>
#include "Structel.h"
#include <string>
#include <iostream>
#include <math.h>

Structel::Structel(std::vector<Couple> &p)
{
  this->points=p;
}

//méthode static renvoyant un carré de coté 2n+1
Structel Structel::carre(int n)
{
  std::vector<Couple> points;
  if(n>0)
  {
    int y;
    int x;
    for(y=0; y<2*n+1; y++)
    {
      for(x=0; x<2*n+1; x++)
      {
        struct Couple point;
        point.x=x-((2*n+1)/2);
        point.y=y-((2*n+1)/2);
        points.push_back(point);
        std::cout<<point.x<<point.y;
        printf("\n");
      }
    }
  }
  return Structel(points);
}

Structel Structel::disque(int r)
{
std::vector<Couple> points;
  if(r>0)
  {
    int x;
    int y;
      for(y=-r; y<=r; y++)
      {
        for(x=-r; x<=r; x++)
        {
          if( (pow(x,2)+pow(y,2)) <= pow(r,2) )
          {
            struct Couple point;
            point.x=x;
            point.y=y;
            points.push_back(point);
            std::cout<<point.x<<point.y;
            printf("\n");
          }
        }
      }
    }
  return Structel(points);
}

Image<uint8_t> dilate(Image<uint8_t> &img)
{
  Image<uint8_t> res(img.getDx(), img.getDy());




  return res;
}
