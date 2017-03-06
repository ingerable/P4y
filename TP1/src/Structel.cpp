
#include <vector>
#include "Structel.h"

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
    int i=0;
    int y;
    int x;
    for(y=0; x<2*n+1; y++)
    {
      for(x=0; x<2*n+1; x++)
      {
        struct Couple point;
        point.x=x-((2*n+1)/2)+1;
        point.y=y-((2*n+1)/2)+1;
        points[i]=point;
        i++;
      }
    }
  }
  return Structel(points);
}

//méthode static renvoyant un disque de rayon r
Structel Structel::disque(int r)
{

}
