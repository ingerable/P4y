
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
        std::cout<<point.x << point.y;
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
          }
        }
      }
    }
  return Structel(points);
}

Image<uint8_t> Structel::erode(Image<uint8_t> &img)
{
  std::vector<Couple> points = this->points; // on passe par un tableau intermediaire

  Image<uint8_t> res(img.getDx(), img.getDy());
  for(int y=0; y<img.getDy(); y++)
  {
    for(int x=0; x<img.getDx(); x++)
    {
        uint8_t min=255; // on initialise le minimum
        for(int pt=0; pt<points.size(); pt++) // on cherche la valeur minimum des points "recouvert" par l'élément
        {
          if( ((x+points[pt].x)<img.getDx()) && ((y+points[pt].y)<img.getDy()) && ((y+points[pt].y)>=0) && ((x+points[pt].x)>=0) )//bords de l'image
          {
            if( img(x+points[pt].x, y+points[pt].y)<min)
            {
              min = img(x+points[pt].x, y+points[pt].y);
            }
          }
        }
        res(x,y) = min;
    }
  }
  return res;
}


Image<uint8_t> Structel::dilate(Image<uint8_t> &img)
{
  std::vector<Couple> points = this->points; // on passe par un tableau intermediaire
  Image<uint8_t> res(img.getDx(), img.getDy());
  for(int y=0; y<img.getDy(); y++)
  {
    for(int x=0; x<img.getDx(); x++)
    {
        uint8_t max=0; // on initialise le maximum
        for(int pt=0; pt<points.size(); pt++) // on cherche la valeur minimum des points "recouvert" par l'élément
        {
            if( ((x-points[pt].x)<img.getDx()) && ((y-points[pt].y)<img.getDy()) && ((y-points[pt].y)>=0) && ((x-points[pt].x)>=0) )//bords de l'image
            {
              if( img(x-points[pt].x, y-points[pt].y)>max)
              {
                max = img(x-points[pt].x, y-points[pt].y);
              }
            }
        }
        res(x,y) = max;
    }
  }
  return res;
}

Image<uint8_t> Structel::opening(Image<uint8_t> &img)
{
  Image<uint8_t> res(img.getDx(), img.getDy());
  res = this->erode(img);
  res = this->dilate(res);
  return res;
}

Image<uint8_t> Structel::closure(Image<uint8_t> &img)
{
  Image<uint8_t> res(img.getDx(), img.getDy());
  res = this->dilate(img);
  res = this->erode(res);
  return res;
}

Image<uint8_t> Structel::gradient(Image<uint8_t> &img)
{
  Image<uint8_t> res(img.getDx(), img.getDy());
  Image<uint8_t> dilated(img.getDx(), img.getDy());
  Image<uint8_t> eroded(img.getDx(), img.getDy());

  dilated = this->dilate(img);
  eroded = this->erode(img);

  for(int y=0; y<img.getDy(); y++)
  {
    for(int x=0; x<img.getDx(); x++)
    {
      res(x,y)=dilated(x,y)-eroded(x,y);
    }
  }
  return res;
}

Image<uint8_t> Structel::internalGradient(Image<uint8_t> &img)
{
  Image<uint8_t> res(img.getDx(), img.getDy());
  Image<uint8_t> eroded(img.getDx(), img.getDy());

  eroded = this->erode(img);

  for(int y=0; y<img.getDy(); y++)
  {
    for(int x=0; x<img.getDx(); x++)
    {
      res(x,y)=img(x,y)-eroded(x,y);
    }
  }
  return res;
}

Image<uint8_t> Structel::externalGradient(Image<uint8_t> &img)
{
  Image<uint8_t> res(img.getDx(), img.getDy());
  Image<uint8_t> dilated(img.getDx(), img.getDy());

  dilated = this->dilate(img);

  for(int y=0; y<img.getDy(); y++)
  {
    for(int x=0; x<img.getDx(); x++)
    {
      res(x,y)=dilated(x,y)-img(x,y);
    }
  }
  return res;
}

Image<uint8_t> Structel::allOrNothing(Image<uint8_t> &img, Structel a, Structel b)
{
  Image<uint8_t> eroded(img.getDx(), img.getDy());
  eroded = a.erode(img);
  Image<uint8_t> dilated(img.getDx(), img.getDy());
  dilated = b.dilate(img);
  Image<uint8_t> res(img.getDx(), img.getDy());

  for(int y=0; y<img.getDy(); y++)
  {
    for(int x=0; x<img.getDx(); x++)
    {
      if(eroded(x,y)-dilated(x,y)<=0)
      {
        res(x,y)=0;
      }else{
        res(x,y)=eroded(x,y)-dilated(x,y);
      }
    }
  }
  return res;
}

  void Structel::granulometry(Image<uint8_t> &img)
  {
    long weight;
    for(int i=1; i<=10; i++)
    {
      weight = 0;
      Structel elem = Structel::disque(i);
      Image<uint8_t> inter(img.getDx(), img.getDy()); //image intermediaire
      inter = elem.opening(img); // ouverture

      for(int y=0; y<img.getDy(); y++) // calcul du poids
      {
        for(int x=0; x<img.getDx(); x++)
        {
          weight += inter(x,y);
        }
      }
      printf("%s %d %ld\n","taille de l'élément ",i, weight );
    }


  }
