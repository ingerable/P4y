#include <vector>
#include "image.h"

#ifndef Structel_h
#define Structel_h

struct Couple
{
    int x;
    int y;
};

class Structel
{


private:
  std::vector<Couple> points;

public:
  //Construit un élément structurant avec une liste de points
  Structel(std::vector<Couple> &p);

  //destructeur
  //~Structel();

  Image<uint8_t> dilate(Image<uint8_t> &img) const;

  // construit un élément structurant carré de coté N
  static Structel carre(int n);

  static Structel disque(int r);

};

#endif
