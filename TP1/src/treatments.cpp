//
//  treatments.cpp
//  tp-P4y
//
//  Classe contenant les fonctions de traitements d'image
//
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "image.h"
#include "treatments.h"
#include <math.h>

//thresholding function with uint8_t picture, parameters are a picture and a thresholding value (0-255)

void thresholding(Image<uint8_t> &image, const int value)
{
  for(int y=0; y<image.getDy(); ++y) // on parcourt les pixels de l'image entrée
  {
      for(int x=0; x<image.getDx(); ++x)
      {
        if(image(x,y)>value) // si la valeur du pixel est supérieur on lui affecte la valeur 255
          {
            image(x,y)=255;
          }else{
            image(x,y)=0; // sinon on lui affecte 0
          }
      }
  }
}

//negate a picture

void negation(Image<uint8_t> &image)
{
  for(int y=0; y<image.getDy(); ++y) // on parcourt les pixels de l'image entrée
  {
      for(int x=0; x<image.getDx(); ++x)
      {
        image(x,y)=255-image(x,y);
      }
  }
}

void quantize(Image<uint8_t> &image, int k)
{
  int v = 256/(2<<(7-k)); // on divise 256 par 2^k-1, nombre de valeurs de gris
  printf("%s%d\n","nbr de valeurs:",v );
  for(int y=0; y<image.getDy(); ++y) // on parcourt les pixels de l'image entrée
  {
      for(int x=0; x<image.getDx(); ++x)
      {
        double px1 = image(x,y)/(256/v);
        image(x,y) = (px1*255)/(floor(255/(k<<2)));
      }
  }
}

void resampleOneDimension(int tab[], int factor)
{
  int newTab[5*factor];
  int j=0;

  for(int k=0;k<5*factor;k++) // on remplit le tableau une première fois avec les valeurs de l'ancien tableau, on initialise les autres valeurs à 0
  {
    if(k%factor==0)
    {
      newTab[k]=tab[j];
      j++;
    }else{
      newTab[k]=0;
    }
  }

  for(int i=0;i<5*factor;i++) // pour chaque élément du nouveau tableau
  {
    if(i%factor!=0) // on ne traite pas les valeurs initiale
    {
      if((i-(i%factor))>(i+(factor-(i%factor)))) // on compare la distance du voisin de droite et du voisin de gauche
      {
        newTab[i]=newTab[i+(factor-(i%factor))]; // on prends la valeur du voisin de droite
      }else{
        newTab[i]=newTab[i-(i%factor)]; // on prends la valeur du voisin de gauche
      }
    }
    std::ostringstream oss;
    oss<<"["<<newTab[i]<<"]";
    std::cout<<oss.str();
  }
}

void resampleOneDimensionBilinear(int tab[], int factor)
{
  int newTab[5*factor];
  int j=0;
  for(int k=0;k<5*factor;k++) // on remplit le tableau une première fois avec les valeurs de l'ancien tableau, on initialise les autres valeurs à 0
  {
    if(k%factor==0)
    {
      newTab[k]=tab[j];
      j++;
    }else{
      newTab[k]=0;
    }
  }

  for(int i=0;i<5*factor;i++) // pour chaque élément du nouveau tableau
  {
    if(i%factor!=0) // on ne traite pas les valeurs initiale
    {
      if(i!=(5*factor-1))//cas de la dernière valeur (pas de voisin de droite)
      {
        newTab[i]=((newTab[i-(i%factor)]+newTab[i+(factor-(i%factor))])/factor); // on prends la valeur du voisin de gauche
      }else{
        newTab[i]=newTab[i-1];
      }

    }
    std::ostringstream oss;
    oss<<"["<<newTab[i]<<"]";
    std::cout<<oss.str();
  }
}

Image<uint8_t> resampleNN(Image<uint8_t> &img, int factor)
{
  // nouvelle image
  Image<uint8_t> imgZ(img.getDx()*factor ,img.getDy()*factor);
  for(int y = 0; y < imgZ.getDy(); y++) // on parcourt chaque pixel
  {
    for(int x = 0; x < imgZ.getDx(); x++)
    {//on choisit le pixel le plus proche dans l'image d'origine
      imgZ(x,y)=img(int(float(x)/factor), int(float(y)/factor));
    }
  }
  return imgZ;
}

Image<uint8_t> resampleBilinearInterpolation(Image<uint8_t> &img, int factor)
{
  //nouvelle image
  Image<uint8_t> imgZ(img.getDx()*factor ,img.getDy()*factor);
  for(int y = 0; y < imgZ.getDy(); y++) // on parcourt chaque pixel
  {
    for(int x = 0; x < imgZ.getDx(); x++)
    {
      uint8_t xG = img(x/factor,y/factor); // pixel gauche
      uint8_t xD = img(int((x+1)/factor),y/factor); // pixel droit
      uint8_t yH = img(x/factor,y/factor); // pixel haut
      uint8_t yB = img(x/factor,int((y+1)/factor)); // pixel bas
      imgZ(x,y) = (int((xG+xD)/2),int((yH+yB)/2)); // moyenne des pixels voisins pour chaque axe
    }
  }
  return imgZ;
}
