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
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

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
          if( ((x-(mask.getDx()/2)+mx)>=0) && ((y-(mask.getDy()/2)+my)>=0) && ((x-(mask.getDx()/2)+mx)<img.getDx()) && ((y-(mask.getDy()/2)+my)<img.getDy()) )
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

  return exp(-(x*x+y*y)/(2*(sigma*sigma)));
}

Image<double> gaussianMask(float sigma)
{
  int N = floor((sigma*6));
  if(N%2==0)
  {
    N = floor((sigma*6)+1);
  }
  double sum=0;

  Image<double> res(N,N);

  for(int y=0; y<res.getDy(); y++)
  {
    for(int x=0; x<res.getDx(); x++)
    {
      res(x,y)=gaussF(x-N/2,y-N/2,sigma);
      sum += res(x,y);
    }
  }

  for(int y=0; y<res.getDy(); y++)
  {
    for(int x=0; x<res.getDx(); x++)
    {
      res(x,y)=res(x,y)/sum;
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


Image<uint8_t> contours(Image<uint8_t> img, Image<double> mask)
{
  Image<uint8_t> res(img.getDx(), img.getDy());
  int weightSum=0;
  //somme des poids positifs
  for(int my = 0; my<mask.getDy(); my++)
  {
    for(int mx = 0; mx<mask.getDx(); mx++)
    {
      if(mask(mx,my)>0)
      {
        weightSum += mask(mx,my);
      }
    }
  }

  for(int y=0; y<img.getDy(); y++)
  {
    for(int x=0; x<img.getDx(); x++)
    {
      int sum=0;
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
      if(sum<0)
      {
        sum = (-sum)/weightSum;
      }else{
        sum = sum/weightSum;
      }
      res(x,y)=sum;

    }
  }
  return res;
}

Image<uint8_t> medianFilter(Image<uint8_t> img, int N)
{
  Image<uint8_t> res(img.getDx(),img.getDy()); // image résultat
  std::vector<uint8_t> list; // liste des valeurs contenus dans la fenêtre
  if(N%2==0)
  {
    N = N+1;
  }
  for(int y=0; y<img.getDy(); y++)
  {
    for(int x=0; x<img.getDx(); x++)
    {
        for(int ny=0; ny<N; ny++)
        {
          for(int nx=0; nx<N; nx++)
          {
            if( ((x-(N/2)+nx)<0) || ((y-(N/2)+ny)<0) || ((x-(N/2)+nx)>=img.getDx()) || ((y-(N/2)+ny)>=img.getDy()) )
            {

            }else{
              list.push_back(img(x+nx-(N/2), y+ny-(N/2)));
              //printf("%d\n",img(x+nx-(N/2), y+ny-(N/2)));
            }
          }
        }
        /*for(int k=0; k<list.size(); k++)
        {
          printf("%d",list[k]);
        }*/
        std::sort (list.begin(), list.end());
        //printf("\n");
        res(x,y)=list.at((list.size()/2)-1);
        list.clear();
      }
    }
      return res;
  }

  Image<uint8_t> impulseNoise(Image<uint8_t> &img, float p)
  {
    Image<uint8_t> res(img.getDx(), img.getDy());
    srand(time(NULL));

    for(int y=0; y<img.getDy(); y++)
    {
      for(int x=0; x<img.getDx(); x++)
      {
        if ( (rand()%100)/100.0 < p )
        {
          if(rand()%2==0)
          {
            res(x,y) = 0;
          }else{
            res(x,y) = 255;
          }
        }
        else
        {
          res(x,y) = img(x,y);
        }
      }
    }
    return res;
  }

  Image<uint8_t> noiseGaussian(Image<uint8_t> &img,float avg,float deviation)
  {
    Image<uint8_t> res(img.getDx(), img.getDy());

    std::default_random_engine generator(time(NULL));
    std::normal_distribution<float> distribution(avg, deviation);

    for(int y=0; y<img.getDy(); y++)
    {
      for(int x=0; x<img.getDx(); x++)
      {
        float val = distribution(generator) + img(x,y);

        if(val<0)
        {
          val = 0;
        }else if(val>255)
        {
            val = 255;
        }

        res(x,y) = (uint8_t) val;
      }
    }
    return res;
  }

  double computeMSE(Image<uint8_t> &imgN, Image<uint8_t> &imgO)
  {
    long NM = imgN.getDx() * imgN.getDx();
    long sum =0;
    double res = 0;
    for(int x=0; x<imgN.getDx(); x++)
    {
      for(int y=0; y<imgN.getDy(); y++)
      {
        sum  += (imgO(x,y)-imgN(x,y))*(imgO(x,y)-imgN(x,y));
      }
    }
    res = double(sum/NM);
    return res;
  }


/*  double computeSimilarity(Image<uint8_t> &img, int x1, int y1, int x2, int y2, int D)
  {
    double res=0.0;
    for(int y=0; y<2*D+1; y++)
    {
      for(int x=0; x<2*D+1; x++)
      {
        if( (x1-D)>=0 && (y1-D)>=0 && (x1+D)<img.getDx() && (y1+D)<img.getDy()  &&   (x2-D)>=0 && (y2-D)>=0 && (x2+D)<img.getDx() && (y2+D)<img.getDy() )
        {
          double value =  (img(x1-D, y1-D) - img(x2-D, y2-D));
          res = res + (value*value);
        }
      }
    }
    //printf("%d\n",res );
    return res;
  }*/

  double computeSimilarity(Image<uint8_t> &img, int x1, int y1, int x2, int y2, int D)
  {
    double res=0.0;
    for(int y=-D; y<D+1; y++)
    {
      for(int x=-D; x<D+1; x++)
      {
        if( (x1+D)>=0 && (y1+D)>=0 && (x1+D)<img.getDx() && (y1+D)<img.getDy()  &&   (x2+D)>=0 && (y2+D)>=0 && (x2+D)<img.getDx() && (y2+D)<img.getDy() )
        {
          double value =  (img(x1+D, y1+D) - img(x2+D, y2+D));
          res = res + (value*value);
        }
      }
    }
    //printf("%d\n",res );
    return res;
  }


double computeWeight(Image<uint8_t> &img, int x1, int y1, int x2, int y2, int D, double h)
{
  return exp( (-computeSimilarity(img, x1, y1, x2, y2, D)) / (h*h) );
}


Image<uint8_t> computeNLMeans(Image<uint8_t> &img, int windowSize, int patchSize, double h)
{
  Image<uint8_t> res(img.getDx(), img.getDy());

  double val;
  double sumWeight;
  double max;
  double tempWeight;

for(int y=0; y<img.getDy(); y++)
{
  for(int x=0; x<img.getDy(); x++)
  {
    // espace de recherche
     val=0.0;
     sumWeight=0.0;
     max=0.0;
     tempWeight=0.0;
    for(int sy=y-windowSize; sy<y+windowSize; sy++)
    {
      for(int sx=x-windowSize; sx<x+windowSize; sx++)
      {
        if( sx>=0 && sx<img.getDx() && sy>=0 && sy<img.getDy() )
        {
          if(sy!=y && sx!=x) // on est sur le point central
          {
            tempWeight = computeWeight(img, x, y, sx, sy, patchSize, h);
            max = std::max(max,tempWeight);
            sumWeight = sumWeight + tempWeight;
            val = val + tempWeight*img(sx,sy);
          }
        }
      }
    }
    sumWeight = sumWeight + max; // on ajoute le poids maximum qui est le poids du point xi=xj
    val = val + max*img(x,y);// puis on l'ajoute à la futur valeur du point courant
    val = val/sumWeight;
    res(x,y) = (uint8_t) val;

  }
}
  return res;
}
