# Compte Rendu TP3 P4y

## Convolution

La convolution consiste à calculer la valeur de chaque pixel à l'aide d'un masque donnée. 
Le masque est centrée sur le pixel, la valeur du pixel au centre est égal à la somme des produits de chaque pixel voisin par la valeur du masque au coordonnée de ce même pixel (le pixel voisin).

![Illustration](https://git.unistra.fr/j.vanassche/P4y/blob/master/TP3/ImagesCompteRendu/convolution.png)

Le masque sera une image de type double.

La première chose à faire est de parcourir chaque pixel de l'image de départ avec une double
boucle. Ensuite il s'agit de parcourir les pixels voisins au pixel courant. Le masque étant aussi
une image on peut procéder à l'aide d'une double boucle.

```
for(int my = 0; my<mask.getDy(); my++)
      {
        for(int mx = 0; mx<mask.getDx(); mx++)
        {
          if( ((x-(mask.getDx()/2)+mx)<0) || ((y-(mask.getDy()/2)+my)<0) || 
		((x-(mask.getDx()/2)+mx)>img.getDx()) || ((y-(mask.getDy()/2)+my)>img.getDy()) )
          {
            sum += 0;
          }else
          {
              sum += mask(mx,my)*img(x+mx-(mask.getDx()/2),y+my-(mask.getDy()/2));
          }
        }
      }
```
Il faut aussi faire attention aux valeurs en dehors de l'image ,en effet lorsque l'on parcours
le masque il se peut que l'on se situe en dehors de l'image la condition suivante permet de faire
attention aux cas ou l'on sort de l'image (gauche/droite/haut/bas), ce qui nous fais un total de 4 conditions.

```
if( ((x-(mask.getDx()/2)+mx)<0) || ((y-(mask.getDy()/2)+my)<0) || 
((x-(mask.getDx()/2)+mx)>img.getDx()) || ((y-(mask.getDy()/2)+my)>img.getDy()) )

```

Si l'on se situe dans l'image on peut alors calculer la valeur du pixel voisin et l'ajouter à la somme.
Pour cela on multiplie le pixel voisin par le coefficient du masque en mx my.

``` 
sum += mask(mx,my)*img(x+mx-(mask.getDx()/2),y+my-(mask.getDy()/2));
```

Il faut faire attention à bien calculer la position du pixel voisin.

![LissageM1](https://git.unistra.fr/j.vanassche/P4y/blob/master/TP3/ImagesCompteRendu/LissageM1.png)
![LissageM2](https://git.unistra.fr/j.vanassche/P4y/blob/master/TP3/ImagesCompteRendu/LissageM1.png)

##Masque gaussien


