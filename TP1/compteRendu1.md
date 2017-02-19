# VAN ASSCHE Jules OS2

## Damier

On initialise une image de dimension dx dy puis on parcours chaque pixel de cette image
en lui affectant alternativement 0 ou 255.
```C++
Image <uint8_t> D(dx,dy);
    for(int y=0; y<D.getDy(); ++y)
    {
      int mod = 0;
        for(int x=0; x<D.getDx(); ++x)
        {
          D(x,y)=((x+y)%2)*255;
        }
    }
```

## Quantize

Quantifier consiste à réduire le nombre de niveaux de gris (dans notre cas) d'une image
en fonction d'un facteur k.
On commence par définir le nouveau ***nombre de niveaux de gris*** qui sera 256/2^k.
```C++
int v = 256/(1<<(8-k))-1;
```
Ensuite on affecte une nouvelle valeur à chaque pixel qui sera compris dans l'intervalle [0,256/2^k] 
et qui sera bien entendu dépendant de son ancienne valeur.

```C++
double px1 = image(x,y)/(256/v);
image(x,y) = (px1*255)/(floor(255/(k<<2)));
```


## Redimensionnement tableau une dimension NN

On souhaite redimensionner une image d'un facteur n
On commence par créer la nouvelle image (ici tableau 1D) puis on la remplit tout les ***n fois***

```C++
  int newTab[5*factor];
  int j=0;

  for(int k=0;k<5*factor;k++) 
  {
    if(k%factor==0)
    {
      newTab[k]=tab[j];
      j++;
    }else{
      newTab[k]=0;
    }
  }
```
Les valeurs qui ne sont pas encore calculées sont initialisées à 0.
Ensuite on parcours une nouvelle fois en cherchant le voisin le plus proche à chaque itération.
```C++
  for(int i=0;i<5*factor;i++) // pour chaque élément du nouveau tableau
  {
    if(i%factor!=0) // on ne traite pas les valeurs de l'ancienne image
    {
      if((i-(i%factor))>(i+(factor-(i%factor)))) // on compare la distance du voisin de droite et du voisin de gauche
      {
        newTab[i]=newTab[i+(factor-(i%factor))]; // on prends la valeur du voisin de droite
      }else{
        newTab[i]=newTab[i-(i%factor)]; // on prends la valeur du voisin de gauche
      }
    }
```

**i-(i%factor)** permet de determiner la position du voisin de gauche
tandis que **i+(factor-(i%factor))** permet de determiner la position du voisin de droite
ensuite il suffit de comparer les 2 et de choisir le plus proche.

Résultat avec le tableau fourni dans l'énoncé : 
![resultat NN1D](https://git.unistra.fr/j.vanassche/P4y/tree/master/tests/oneDimensionNN.png)

## Seuillage

L'opération de seuillage consiste à affecter les valeurs 255 ou 0 aux pixels 
en fonction de leurs valeurs par rapport à une certaine valeur de seuil.
Si valeurPixel>seuil le pixel prends la valeur 255 sinon 0.

* **Image d'origine**
![Image d'origine](./src/lena.pgm)

* Seuillage avec pour **seuil 128**
![Seuillage 128](https://git.unistra.fr/j.vanassche/P4y/tree/master/TP1/src/resultats/seuillage128.pgm)

* Seuillage avec pour **seuil 200**
![Seuillage 200](./src/resultats/seuillage200.pgm)

* Seuillage avec pour **seuil 50**
![Seuillage 50](./src/resultats/seuillage50.pgm)


## Negatif

Pour faire le négatif d'une image il faut soustraire la valeur de chaque pixel à 255.

![Negatif](./src/resultats/negatif.pgm)

## ResampleNN

Cette fois ci on veut redimensionner une image (2D).  On parcours de nouveau
l'image à l'aide d'une double boucle.

```C++
for(int y = 0; y < imgZ.getDy(); y++) // on parcourt chaque pixel
  {
    for(int x = 0; x < imgZ.getDx(); x++)
    {//on choisit le pixel le plus proche dans l'image d'origine
      imgZ(x,y)=img(int(float(x)/factor), int(float(y)/factor));
    }
  }
```
Cette fois ci on utilise une méthode plus simple, on divise par le facteur pour retomber 
sur le pixel de l'image d'origine. L'arrondi permet de trouver le pixel le plus proche.
* **Image d'origine**
![Image d'origine](./src/lena.pgm)
 
* Redimensionnement **facteur 2**
![ResampleNN 2](./src/resultats/resampleNN2.PGM)

* Redimensionnement **facteur 4**
![ResampleNN 4](./src/resultats/resampleNN4.PGM)

* Redimensionnement **facteur 8**
![ResampleNN 2](./src/resultats/resampleNN8.PGM)

**Test avec une image de synthèse 2D (résultat visible à l'oeil nu)**

![resultat NN1D](https://git.unistra.fr/j.vanassche/P4y/tree/master/tests/resampleNN.png)

## Resample Bilinear Interpolation

Pour l'interpolation bilinéaire nous devons utiliser 4 pixels voisins
et effectuer 2 interpolations linéaires 2 pixels par 2 pixels.

![interpolation](https://i.stack.imgur.com/a9ssZ.png)

On trouve d'abord les 4 pixels voisins lors de chaque itération mais avant cela il faut faire attention
à ne pas être au bord droit de l'image (pas de voisin de droite) ou encore à la dernière ligne
(pas de voisin inférieur)
```C++
  if(x<img.getDx()-factor)
      {
        imgZ(x,y) = img(x/factor,y/factor);
      }else if(y<img.getDx()-factor)
      {
        imgZ(x,y) = img(x/factor,y/factor);
      }
```
Si aucune des précedentes conditions n'a été validée on passe au cas général
en commencant par chercher les **4 pixels voisins** :

```C++
        x1 = x - (x%int(factor)); // pixel gauche
        x2 = x1 + factor; // pixel droite
        y1 = y - (y%int(factor)); // pixel haut
        y2 = y1 + factor; // pixel bas
```
Ensuite on réalise les 2 interpolations linéaires : 
```C++
        r1 = ((x2 - x)/factor)*img(x1/factor,y1/factor) + ((x - x1)/factor)*img(x2/factor,y1/factor);
        r2 = ((x2 - x)/factor)*img(x1/factor,y2/factor) + ((x - x1)/factor)*img(x2/factor,y2/factor);
```

Puis on calcule la valeur interpolée :
```C++
    imgZ(x,y) = ((y - y1)/factor)*r2 + ((y2 - y)/factor)*r1;
```



