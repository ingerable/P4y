# Compte rendu TP4

## Filtre médian

Le principe du filtre médian est de remplacer le pixel au centre du filtre
par la médiane de tout les pixels contenus dans le filtre. Ce procédé permet 
de d'améliorer la qualité d'image dégradées. La taille de la fenêtre sera
de taille $`sigma\times sigma`$ avec $`sigma`$ impair pour que le pixel qui va être modifié
puisse être au centre du filtre. On va lister les pixels dans une liste puis trier la 
liste avant de choisir la médiane. La valeur médiane permet de choisir une valeur de pixel 
qui s'accorde bien avec les pixels voisins, la liste étant triée par ordre croissant. Si l'on veux
reconstituer une image il ne faut pas choisir de valeurs trop proches de 0 ou 255.

### Implantation

L'implantation n'est pas très compliqué, nous avons déja implanté et utilisé de nombreux filtres.
Ce qui était un peu plus compliqué était la gestion de la taille du tableau qui varie en fonction
du cas ou l'on se situe (bords haut droit/gauche ... ,bords, "centre"). Car cette fois ci on ne peut
pas remplacer les pixels en dehors de l'image par des 0 car cela fausserait le calcul de la médiane.
On choisit d'utiliser des vecteurs dans ce cas. Les vecteurs agissent comme une pile et comme une liste.
La taille est dynamique et l'on peut "pousser" des objets dans un vecteurs, nous n'avons alors pas à nous 
soucier de la taille. Une fonction de tri est déja implanté pour les vecteurs et il est possible d'accéder à
un objet stocké dans une liste grace à son index ce qui nous permet de trouver facilement la médiane.

```
  if( ((x-(N/2)+nx)<0) || ((y-(N/2)+ny)<0) || ((x-(N/2)+nx)>=img.getDx()) || ((y-(N/2)+ny)>=img.getDy()) )
            { // dans ce cas le pixel est en dehors de l'image on ne fait rien

            }else{
              list.push_back(img(x+nx-(N/2), y+ny-(N/2))); // on pousse la valeur du pixel parcouru dans la liste
            }
          }
        }
        std::sort (list.begin(), list.end()); // tri croissant
        res(x,y)=list.at((list.size()/2)-1); // médiane
        list.clear();
```

## Classe Structel

Pour pouvoir définir une classe représentant un élément structurant nous avons besoin d'un
objet ayant une liste de points définis par des coordonnées. La classe structel aura donc en attributs
un vecteur de ***points***. Les points seront représentés par une structure nommé ***Couple*** qui à pour
attributs 2 entier x et y.

```

struct Couple
{
    int x;
    int y;
};

class Structel
{


private:
  std::vector<Couple> points;

public:
  //Construit un élément structurant avec une liste de points
  Structel(std::vector<Couple> &p);
  // construit un élément structurant carré de coté N
  static Structel carre(int n);

  static Structel disque(int r);

};

```

Je me suis inspiré de la convolution pour implanter la méthode statique qui
retourne un élément structurant carré. On peut utiliser la même méthode pour 
parcourir les pixels voisins pour construire le carré.

```
Structel Structel::carre(int n)
{
  if(n>0)
  {
    std::vector<Couple> points;
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
        std::cout<<point.x<<point.y;
        printf("\n");
      }
    }
  }
  return Structel(points);
}
```

Vérification pour un carré n = 2:

![carreN=2](src/imagesCompteRendu/carre2.png)

On vérifie le résultat en affichant le carré au fur et à mesure de sa construction.

Pour construire le disque de rayon r rien de très compliqué. L'équation de disque
euclidien de rayon r nous est donnée. Il suffit de parcourir un carré de coté R et
de vérifier pour chaque point si il se situe dans le disque.

```
  for(y=-r; y<=r; y++)
      {
        for(x=-r; x<=r; x++)
        {
          if( (pow(x,2)+pow(y,2)) <= pow(r,2) ) // est ce que le point (x,y) est dans le cercle si oui alors
          {
            struct Couple point;
            point.x=x;
            point.y=y;
            points.push_back(point); // on l'ajoute à la liste des points du disque 
            std::cout<<point.x<<point.y; // on vérifie
            printf("\n");
          }
        }
      }
```

Vérification pour un disque R = 2:

![disqueR=2](src/imagesCompteRendu/disqueRayon2.png)

## Méthodes d'érosion et de dilatation

On implante les méthodes d'érosion et de dilatation qui seront des méthodes d'instance
de la classe Structel. 

```c++
  Image<uint8_t> opening(Image<uint8_t> &img);
  Image<uint8_t> closure(Image<uint8_t> &img);
```

Comme décrit dans le sujet de TP on parcours tous les points
(x-i, y-j) pour la dilatation et (x+i, x+j) pour l'érosion
ou (x,y) un point de l'image et (i,j) un point de 
l'élément structurant. Pour la dilatation on cherche le minimum
dans l'ensemble des points parcourus alors que pour l'érosion on
cherche le maximum.

```c++
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
```

Pour chaque pixel de l'image on cherche le maximum
dans l'ensemble des points (x-i, y-j) avec (x,y)
le point de l'image et (i,j) le point de l'élément
structurant. A chaque itération (dans la boucle qui
parcours les points de l'élément structurant) on 
compare le point avec le max, il faut faire 
attention à ne pas compter les points au bord de l'image.

On fait la même chose avec l'érosion sauf que cette fois
ci on fait (x+i, y+j).

```c++
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
```

### Tests érosion dilatation

#### Érosion

On vérifie le résultat de l'érosion pour les 2 éléments structurants
disque et carré. On fait aussi varier la taille des éléments.

Type d'élément|  2 |  4 |  8 | 
|---|---|---|---|---|
***Carré*** | ![erode](src/imagesCompteRendu/erodeLenaCarre2.png)  |![erode](src/imagesCompteRendu/erodeLenaCarre4.png)   | ![erode](src/imagesCompteRendu/erodeLenaCarre8.png)  |
***Disque*** |  ![erode](src/imagesCompteRendu/erodeLenaDisque2.png) | ![erode](src/imagesCompteRendu/erodeLenaDisque4.png)  |  ![erode](src/imagesCompteRendu/erodeLenaDisque8.png) | 

On voit bien que la taille de la zone érodée est proportionnelle à la taille 
de l'élément structurant et que la forme de la zone dépend de l'élement.

#### Dilatation

Type d'élément|  2 |  4 |  8 | 
|---|---|---|---|---|
***Carré*** | ![dilate](src/imagesCompteRendu/dilateLenaCarre2.png)  |![dilate](src/imagesCompteRendu/dilateLenaCarre4.png)   | ![dilate](src/imagesCompteRendu/dilateLenaCarre8.png)  |
***Disque*** |  ![dilate](src/imagesCompteRendu/dilateLenaDisque2.png) | ![dilate](src/imagesCompteRendu/dilateLenaDisque4.png)  |  ![dilate](src/imagesCompteRendu/dilateLenaDisque8.png) |




