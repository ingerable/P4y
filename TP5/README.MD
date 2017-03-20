# Compte rendu TP5 Jules Van Assche

## Bruit synthétique

La première chose à faire est de génerer un nombre aléatoire compris entre 0 et 1 pour le comparer
à la probabilité passé en paramètre. On utilise rand() pour génerer un nombre aléatoire et on le 
ramène entre 0 et 100 avec le modulo pour le diviser par 100 et obtenir un float compris entre 0 et 1.
Génératin du nombre entre 0 et 1 :

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


On teste avec une image de synthèse avec pour probabilité 0.4 et 0.8 :

proba :0.4--------------------
  1|  2|  3|255|  0|
--------------------
  6|  7|  0|  0| 10|
--------------------
 11|  0|  0|255| 15|
--------------------
 16|  0|  0|255|255|
--------------------
  0| 22| 23| 24| 25|
--------------------

proba :0.8--------------------
255|255|255|  0|  0|
--------------------
255|255|255|  0|  0|
--------------------
  0| 12|255| 14|  0|
--------------------
  0|255|  0| 19| 20|
--------------------
  0|  0|255|255|  0|
--------------------

On regarde maintenant le résultat pour des vraies images :

Probabilité |  0.1 |  0.4 |  0.8 | 
|---|---|---|---|---|
![impulseNoise](src/imagesCompteRendu/boatImpulseNoise1.png)  | ![impulseNoise](src/imagesCompteRendu/boatImpulseNoise4.png) | ![impulseNoise](src/imagesCompteRendu/boatImpulseNoise8.png) |


