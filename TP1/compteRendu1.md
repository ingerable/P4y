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
On commence par définir le nouveau nombre de valeurs de gris qui sera 256/2^k.
Ensuite on affecte une nouvelle valeur à chaque pixel qui sera compris dans l'intervalle [0,256/2^k] 
et qui sera bien entendu dépendant de son ancienne valeur.

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


* **Image d'origine**
![Image d'origine](./src/lena.pgm)
 
* Redimensionnement **facteur 2**
![ResampleNN 2](./src/resultats/resampleNN2.PGM)

* Redimensionnement **facteur 4**
![ResampleNN 4](./src/resultats/resampleNN4.PGM)

* Redimensionnement **facteur 8**
![ResampleNN 2](./src/resultats/resampleNN8.PGM)







