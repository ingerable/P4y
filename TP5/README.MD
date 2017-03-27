# Compte rendu TP5 Jules Van Assche

## Bruit synthétique

### Bruit impulsionnel

La première chose à faire est de génerer un nombre aléatoire compris entre 0 et 1 pour le comparer
à la probabilité passé en paramètre. On utilise rand() pour génerer un nombre aléatoire et on le
ramène entre 0 et 100 avec le modulo pour le diviser par 100 et obtenir un float compris entre 0 et 1.
Génération du nombre entre 0 et 1 :

```c++
if ( (rand()%100)/100.0 < p )
```

Lorsqu'un pixel sera altérée on va décider aléatoirement avec une probabilité de 50%
de sa valeur (0 ou 255)

```c++
if(rand()%2==0)
{
   res(x,y) = 0;
}else{
   res(x,y) = 255;
}
```

Ce qui nous donne au final :

```c++
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
```

On teste avec une image de synthèse avec pour probabilité 0.4 et 0.8 :

```
proba :0.4--------------------
  1 |  2  |  3  |255  |  0  |
--------------------
  6 |  7  |  0  |  0  | 10  |
--------------------
 11 |  0  |  0  | 255  | 15 |
--------------------
 16 |  0  |  0  | 255 | 255 |
--------------------
  0 | 22  | 23  | 24  | 25  |
--------------------
```

```
proba :0.8--------------------
255 | 255 | 255 |  0  |  0  |
--------------------
255 | 255 | 255 |  0  |  0  |
--------------------
  0 | 12  | 255 | 14  |  0  |
--------------------
  0 | 255 |  0  | 19  | 20  |
--------------------
  0 |  0  | 255  |  255 |  0  |
--------------------
```

On regarde maintenant le résultat pour des vraies images :

Probabilité |  0.1 |  0.4 |  0.8 |
|---|---|---|---|---|
|Images | ![impulseNoise](src/imagesCompteRendu/boatImpulseNoise1.png)  | ![impulseNoise](src/imagesCompteRendu/boatImpulseNoise4.png) | ![impulseNoise](src/imagesCompteRendu/boatImpulseNoise8.png) |

### Bruit gaussien

On veut désormais implémenter le bruit gaussien. Il faudra pour cela nous aider de
la classe normal_distribution qui s'ocuppe de la répartion des valeurs pour une moyenne
et un écart type données.
Le protoype de la classe ressemble à ça ;

```c++
Image<uint8_t> noiseGaussian(Image<uint8_t> &img,float avg,float deviation);
```

On va parcourir l'image d'origine puis pour chaque pixel ,nous allons lui attribuer une
nouvelle valeur qui sera sa valeur d'origine + la valeur génerée par la fonction gausienne.
Il faut faire attention à bien ramener la nouvelle valeur à zéro si elle est inférieure à 0,
et ramener la valeur à 255 si elle est supérieure à 255.

```c++
std::default_random_engine generator;
std::normal_distribution<float> distribution(avg, deviation);
```

Après avoir initialisé la distribution on va pouvoir attribuer leur nouvelles valeurs
à chaque pixel. On écrit une fonction qui permet de ramener à 0 ou 255 une valeur qui
serait en dehors de cet ensemble.

```c++
uint8_t truncPixel(uint8_t val)
{
  uint8_t res;

  if(val<0)
  {
    res = 0;
  }else if(val>255)
  {
      res = 255;
  }else{
    res = val;
  }

  return res;
}
```

Ensuite il suffit de récuperer la valeur de la distribution de l'ajouter à la valeur
du pixel courant puis de ramener la valeur si elle est en dehors de l'ensemble.

```c++
for(int y=0; y<img.getDy(); y++)
{
  for(int x=0; x<img.getDx(); x++)
  {
    uint8_t val = (uint8_t) distribution(generator);
    res(x,y) = trunc(val+img(x,y));
  }
}
```

#### Validation et résultats

On test la fonction sur une image de synthèse :

Gaus | Originale |  m = 10 $`\sigma=1`$ |
|---|---|---|---|---|
|Images | ![gauss](src/imagesCompteRendu/imageOriginaleGauss.png)  | ![gauss](src/imagesCompteRendu/gauss10&2.png) |

On voit bien qu'on ajoute en moyenne 10 avec une variance de 2.


Gaus | Originale |  m = 30 $`\sigma=15`$ | m = 60 $`\sigma=30`$ | m = 120 $`\sigma=60`$ |
|---|---|---|---|---|
| Images | ![gauss](src/imagesCompteRendu/boat.png)  | ![gauss](src/imagesCompteRendu/gauss30&15.png) | ![gauss](src/imagesCompteRendu/gauss60&30.png) | ![gauss](src/imagesCompteRendu/gauss120&60.png) |


### Mean Square Error

On veut pouvoir mesurer la différence moyenne entre une image
bruitée et une image non bruitée. On va donc faire la somme de la difference élevée au carré pour chaque pixel de l'image bruitée et chaque pixel de l'image original. On divisera ensuite cette somme par le nombre de pixels dans une des 2 images (peu importe laquelle elles ont le même nombre de pixels).
On va donc utiliser une double boucle pour pouvoir accedéder chaque pixel des 2 images. Ensuite il suffit de réaliser la différence entre le pixel de l'image bruitée et de l'image originale et d'élever au carré :

```c++
for(int x=0; x<imgN.getDx(); x++)
{
  for(int y=0; y<imgN.getDy(); y++)
  {
    sum  += (imgO(x,y)-imgN(x,y)) * (imgO(x,y)-imgN(x,y));
  }
}
```

Puis finalement on divise cette somme par le nombre de pixels des images qui à été préalablement initialisé.

```c++
int NM = imgN.getDx() * imgN.getDx();
...
...
res = sum/NM;
return res;
```

#### Validation

On va tester la fonction sur une image de synthèse avec un bruit impulsionnel (p=0.1), on essaye d'avoir une seule valeur à 255 histoire de pouvoir facilement calculer le MSE à la main et comparer avec ce que la fonction renvoie.

![MSE](src/imagesCompteRendu/MSE.png)

Nous avons qu'une seule valeur qui est différente entre l'image d'origine et l'image bruitée, ce qui veut dire qu'hormis pour cette valeur toutes les différences entre les autres points donneront 0 et ne compteront pas pour le MSE. On réalise juste la différence pour le point différent, on élève cette différence au carré et on divise par le nombre de pixels (ici 25). ((255-1)^2)/25 = 2580
On retombe sur la valeur renvoyé par la fonction.

### Tests

On obtient les résultats suivant pour le bruitage gaussien:

Bruit gaussien | m = 0  et $`\sigma=15`$ | m = 0 et $`\sigma=30`$ |
|---|---|---|---|---|
**Visuel** | ![gaussian](src/imagesCompteRendu/barbaraGaussianNoise015.png)  |![gaussian](src/imagesCompteRendu/barbaraGaussianNoise030.png)   |
**MSE** | **263** | 1552 |

Puis pour le bruitage impulsionnel :

Bruit impulsionnel | p = 0.15 | p = 0.40 |
|---|---|---|---|---|
**Visuel** | ![impulse](src/imagesCompteRendu/barbaraImpulseNoise015.png)  |![impulse](src/imagesCompteRendu/barbaraImpulseNoise040.png)   |
**MSE** | **2999** | 7701 |

On utilise désormais des filtres pour essayer de réduire le bruit :

Avec le filtre median de taille 3 :

Bruit gaussien + filtre median 3 | m = 0  et $`\sigma=15`$ | m = 0 et $`\sigma=30`$ |
|---|---|---|---|---|
**Visuel** | ![gaussian](src/imagesCompteRendu/barbaraGaussianNoise015Median3.png)  |![gaussian](src/imagesCompteRendu/barbaraGaussianNoise030Median3.png)   |
**MSE** | **293** | 454 |

Puis pour le bruitage impulsionnel :

Bruit impulsionnel + filtre median 3| p = 0.15 | p = 0.40 |
|---|---|---|---|---|
**Visuel** | ![impulse](src/imagesCompteRendu/barbaraImpulseNoise015Median3.png)  |![impulse](src/imagesCompteRendu/barbaraImpulseNoise040Median3.png)   |
**MSE** | **354** | 1796 |

Avec le filtre median de taille 7 :

Bruit gaussien + filtre median 7 | m = 0  et $`\sigma=15`$ | m = 0 et $`\sigma=30`$ |
|---|---|---|---|---|
**Visuel** | ![gaussian](src/imagesCompteRendu/barbaraGaussianNoise015Median7.png)  |![gaussian](src/imagesCompteRendu/barbaraGaussianNoise030Median7.png)   |
**MSE** | **169** | **169** |

Bruit impulsionnel + filtre median 7| p = 0.15 | p = 0.40 |
|---|---|---|---|---|
**Visuel** | ![impulse](src/imagesCompteRendu/barbaraImpulseNoise015Median7.png)  |![impulse](src/imagesCompteRendu/barbaraImpulseNoise040Median7.png)   |
**MSE** | **52** | 174 |
