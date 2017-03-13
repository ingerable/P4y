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
  Structel();
  //destructeur
  //~Structel();

  Image<uint8_t> erode(Image<uint8_t> &img);
  Image<uint8_t> dilate(Image<uint8_t> &img);
  Image<uint8_t> opening(Image<uint8_t> &img);
  Image<uint8_t> closure(Image<uint8_t> &img);
  Image<uint8_t> internalGradient(Image<uint8_t> &img);
  Image<uint8_t> externalGradient(Image<uint8_t> &img);
  // construit un élément structurant carré de coté 2n+1
  static Structel carre(int n);
  // construit un disque de rayon r
  static Structel disque(int r);

};

#endif
