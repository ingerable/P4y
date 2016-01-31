# Traitement d'images en C++

Séance de prise en main des outils git, du langage C++, de la lecture/écriture d'image au format PGM, des manipulations de pixels.

Travail demandé :
- analyser la classe Image8b 
- compiler et exécuter le programme main.cpp
- modifier la fonction main() de manière à construire une image type damier (un pixel blanc, un pixel noir, etc.)
- écrire une fonction permettant de lire un fichier au format PGM binaire et de créer l'image correspondante
- écrire une fonction permettant d'écrire une image dans une fichier au format PGM binaire 
- écrire un programme qui prend en paramètres le nom de l'image d'entrée, le nom de l'image de sortie, une valeur de seuil, et qui effectue un seuillage sur l'image d'entrée et écrit le résultat
- même chose que précédemment, mais le programme calcule le négatif de l'image d'entrée

## Annexe 1 : notions de base en c++

### Structure d'un programme
- fichiers .h et .cpp
- les classes et fonctions définies dans un fichier foo.cpp sont déclarées généralement dans un fichier foo.h

### Compilation
- les fichiers .cpp sont compilés en fichiers objets .o
- les fichiers objets sont liés pour construire l'exécutable
- la compilation séparée (qui s'appuie généralement sur un Makefile) permet de recompiler uniquement le fichier .cpp nécessaire
- le TP1 se compile de la manière suivante :

```sh
g++ main.cpp image.cpp -o TP1
```
### Documentation
- http://www.cplusplus.com
- http://en.cppreference.com/w/

### Notions de base
#### Espaces de nom :
```cpp
namespace foo {
	class A {}
	...
}
```
Accès par:
```cpp
foo::A myClass;
``` 
ou
```cpp
using namespace foo; 
A myClass;
``

#### Librairie standard
Namespace std
Fonction d'affichage sur la sortie standard :
```cpp
std::cout << "Hello world !\n";
```

#### Portée des variables 
Soit la classe A.
Trois types :
-automatique
```cpp
A myClass(...);
```
myClass est détruit (son destructeur est appelé) à la fin du bloc courant.

-dynamique
```cpp
A *myClass=new myClass(...);
```
myClass est un pointeur alloué qui survit au bloc courant, sa destruction ne peut se faire qu'avec un delete

-statique


## Annexe 2 : lire et écrire dans un fichier en C++

- std::ifstream et std::ofstream pour ouvrir un fichier en lecture, en écriture
- std::string : type de base pour les string en C++
- std::getline(file,line) : récupère dans la string line la ligne suivante du fichier file
- std::stringstream sstr(line) : construit un flux à partir d'une string
- sstr >> x >> y : écrit de manière structurée à partir du flux dans les entiers x et y 







