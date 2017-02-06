# Séance 2

Thèmes abordés :  quantification, rééchantillonnage, interpolation.

## Quantification
On appelle quantification le processus consistant à réduire le nombre de valeurs dans une image.

Écrire la fonction ``quantize`` qui quantifie une image 8 bits passée en paramètre d'un facteur $`2^k`$, avec $`k`$ passé en paramètre. Après quantification, le nombre de valeurs de l'image est divisé par $`2^k`$, et l'image est normalisée : les niveaux de gris sont "étirés" dans l'intervalle $`[0,255]`$.

Par exemple, pour $`k=7`$, on obtient une image à deux valeurs (image binaire) : les pixels ayant une intensité inférieure à 128 dans l'image originale auront une intensité de 0 dans l'image d'arrivée ; les pixels ayant une intensité supérieure à 128 auront une intensité de 255 dans l'image d'arrivée.


## Redimensionnement
On appelle redimensionnement (ou rééchantillonnage) d'une image le fait de changer sa taille, soit en enlevant des échantillons (sous-échantillonnage) soit en en ajoutant (sur-échantillonnage).

On souhaite écrire une fonction permettant de rééchantillonner une image d'un facteur $`r`$  en conservant le rapport hauteur/largeur de l’image. Deux types de méthodes d'interpolation seront implantés : la méthode du plus proche voisin et la méthode de l'interpolation bilinéaire.

Soit l'image 1D suivante :

```
----------------
  1| 3| 5| 7| 9|
----------------
```


Pour $`r=2`$, la longueur de l'image est multipliée par 2 :

```
------------------------------------
  1| . | 3| . | 5| . | 7| . | 9| . |
------------------------------------
```

La méthode du plus proche voisin affecte aux points à valeur inconnue la valeur du voisin le plus proche :

```
----------------------------------------
 1 | 1 | 3 | 3 | 5 | 5 | 7 | 7 | 9 | 9 | 
----------------------------------------
```

Ici comme $`r=2`$, les points sont à égales distance des deux voisins, on adopte donc une convention. Ici le plus "proche" est à gauche.

La méthode de l'interpolation linéaire affecte aux points à valeur inconnue une valeur obtenue par interpolation linéaire entre les voisins gauche et droit :

```
----------------------------------------
 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 9 | 
----------------------------------------
```

Autre exemple en 2D pour $`r=2`$ : 

```
Image A : 
--------
  0| 10|
--------
 10|  0|
--------

Image B (nearest neighbor) : 
----------------
  0| 10| 10| 10|
----------------
 10|  0|  0|  0|
----------------
 10|  0|  0|  0|
----------------
 10|  0|  0|  0|
----------------

Image B (bilinear interpolation) : 
----------------
  0|  5| 10| 10|
----------------
  5|  5|  5|  5|
----------------
 10|  5|  0|  0|
----------------
 10|  5|  0|  0|
----------------
```


Le dernier point situé sur le bord de l'image n'a pas de voisin à droite : on adopte donc une convention. Ici, on recopie la valeur du seul voisin existant.

1. Travailler d'abord sur une image synthétique à une dimension et reproduire les exemples ci-dessus.
2. Écrire la fonction ``resampleNN`` qui rééchantillonne une image d'un facteur donné en paramètre par la méthode du plus proche voisin.
3. Écrire la fonction ``resampleBilinearInterpolation`` qui rééchantillonne une image d'un facteur donné en paramètre par la méthode de l'interpolation bilinéaire.