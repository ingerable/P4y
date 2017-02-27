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
#include "processing.h"
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
  int v = 256/(1<<(8-k))-1; // on divise 256 par 2^k-1, nombre de valeurs de gris
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
        newTab[i]=((newTab[i-(i%factor)]+newTab[i+(factor-(i%factor))])*(factor/(i%factor)));
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
  float x1, x2, y1, y2;
  uint8_t r1, r2;

  for(int y = 0; y < imgZ.getDy(); y++) // on parcourt chaque pixel
  {
    for(int x = 0; x < imgZ.getDx(); x++)
    {
      if(x<img.getDx()-factor)
      {
        imgZ(x,y) = img(x/factor,y/factor);
      }else if(y<img.getDx()-factor)
      {
        imgZ(x,y) = img(x/factor,y/factor);
      }else{
        x1 = x - (x%int(factor)); // pixel gauche
        x2 = x1 + factor; // pixel droite
        y1 = y - (y%int(factor)); // pixel haut
        y2 = y1 + factor; // pixel bas

        r1 = ((x2 - x)/factor)*img(x1/factor,y1/factor) + ((x - x1)/factor)*img(x2/factor,y1/factor);
        r2 = ((x2 - x)/factor)*img(x1/factor,y2/factor) + ((x - x1)/factor)*img(x2/factor,y2/factor);

        imgZ(x,y) = ((y - y1)/factor)*r2 + ((y2 - y)/factor)*r1;
      }
    }
  }
  return imgZ;
}

Image<double> convolve(Image<uint8_t> &img, Image<double> &mask)
{
  Image<double> res(img.getDx(), img.getDy());

  for(int y=0; y<img.getDy(); y++)
  {
    for(int x=0; x<img.getDx(); x++)
    {
        double sum=0;
      for(int my = 0; my<mask.getDy(); my++)
      {
        for(int mx = 0; mx<mask.getDx(); mx++)
        {
          if( ((x-(mask.getDx()/2)+mx)<0) || ((y-(mask.getDy()/2)+my)<0) || ((x-(mask.getDx()/2)+mx)>img.getDx()) || ((y-(mask.getDy()/2)+my)>img.getDy()) )
          {
            sum += 0;
          }else
          {
              sum += mask(mx,my)*img(x+mx-(mask.getDx()/2),y+my-(mask.getDy()/2));
          }
        }
      }
      res(x,y)=sum;
    }
  }
  return res;
}

double gaussF(int x,int y, double sigma)
{
  double res = 0;
  res=exp(-(pow(x,2)+pow(y,2))/(2*pow(sigma,2)));
  return res;
}

Image<double> gaussianMask(float sigma)
{
  int N = 0;
  if( int(6*sigma)%2==0)
  {
    N = int(6*sigma)+1;
  }
  else
  {
    N = 6*sigma;
  }
  double sum=0;

  Image<double> res(N,N);

  for(int y=0; y<N; y++)
  {
    for(int x=0; x<N; x++)
    {
      res(x,y)=gaussF(x,y,sigma);
      sum += res(x,y);
    }
  }

  for(int y=0; y<N; y++)
  {
    for(int x=0; x<N; x++)
    {
      res(x,y)=(res(x,y)/sum);
    }
  }

  return res;
}

Image<uint8_t> toUint8(Image<double> &img)
{
  Image<uint8_t> res(img.getDx(),img.getDy());
  for(int y = 0; y<img.getDy(); y++)
  {
    for(int x = 0; x<img.getDx(); x++)
    {
      res(x,y)=floor(img(x,y));
    }
  }
  return res;
}
