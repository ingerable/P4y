# Traitement d'images en C++

# Principe des TP 

- Durant la séance de TP, faire des `commits` réguliers, à bon escient et commentés de manière pertinente. 
- À la fin de la séance, faire un `push` de votre travail

# Séance 1

Séance de prise en main des outils `git`, du langage C++, de la lecture/écriture d'images au format PGM, des manipulations simples de pixels.

### Travail demandé :

- analyser la classe `Image` 
- compiler et exécuter le programme `main.cpp`
- modifier la fonction `main()` de manière à construire une image type damier (un pixel blanc, un pixel noir, etc.)
- la fonction `writePGM` du fichier `fileio.cpp` écrit une image de type `Image<uint8_t>` dans un fichier PGM ; écrire la fonction `readPGM` permettant de lire une image PGM dont le nom est passé en paramètre et qui retourne l'image de type `Image<uint8_t>` correspondante
- écrire un programme qui prend en paramètres le nom de l'image d'entrée, le nom de l'image de sortie, une valeur de seuil, et qui effectue un seuillage sur l'image d'entrée et écrit le résultat
- même chose que précédemment, mais le programme calcule le négatif de l'image d'entrée

## Annexe 1 : notions de base en C++

### Structure d'un programme
- similaire au C : fichiers .h et .cpp
- les classes et fonctions définies dans un fichier foo.cpp sont déclarées dans un fichier foo.h (c'est une bonne pratique)

### Classes génériques (ou templates)
- elles sont paramétrées par un type
- elles sont séparées en général en deux fichiers : un fichier .h qui contient leur déclaration, et un fichier .hpp qui contient leur définition
- **les classes templates ne sont pas compilées**, elles sont uniquement incluses dans le fichier source .cpp qui les utilise.
- Exemple: 
	- la classe `Image` est paramétrée par un type, le type des valeurs de ses pixels
	- le fichier `main.cpp` inclut le fichier `image.h` 

### Compilation
- les fichiers .cpp sont compilés en fichiers objets .o
- les fichiers objets sont liés pour construire l'exécutable
- la compilation séparée (qui s'appuie généralement sur un Makefile) permet de recompiler uniquement les fichiers nécessaires
- le fichier `main.cpp` se compile de la manière suivante :

```sh
g++ main.cpp -o TP1
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
Accès par :

```cpp
foo::A myClass;
``` 
ou

```cpp
using namespace foo; 
A myClass;
```

#### Librairie standard
Namespace `std`

Exemple, fonction d'affichage sur la sortie standard :

```cpp
std::cout << "Hello world !\n";
```

#### Flux (stream)
- un flux est une abstraction qui transforme une variable ou un objet en une séquence d'octets et vice-versa
- l'opérateur `<<` transforme des objets en séquence d'octets. Exemple, la fonction d'affichage sur la sortie standard :
	
```cpp
std::cout << "Hello world !\n";
```
transforme la chaîne de caractères `"Hello world !\n"` en une séquence d'octets envoyés sur la sortie standard (équivalent du `printf` en C).

- Autre exemple :

```cpp
int i=42; double j=3.14;
std::cout << "i= " << i << " j= " << j << "\n";
```
concatène la chaîne `"i= "`, le contenu de la variable entière `i`, la chaîne `" j= "`, le contenu de la variable `j` de type `double`, le caractère `"\n"` et envoie le tout sous forme de séquence d'octets à la sortie standard

- l'opérateur `>>` transforme une séquence d'octets en objets ou variables. Exemple, la fonction de saisie (équivalent du `scanf` en C) :

	```cpp
	int x; double y;
	std::cin >> x >> y;
	```
	transforme la séquence d'octets de l'entrée standard (caractères saisis par l'utilisateur) en une variable de type `int ` et une variable de type `double`.
- la notion de flux est générique, elle peut désigner aussi bien l'entrée ou la sortie standard, qu'un fichier, une socket, ou autre...



#### Portée des variables 

- variable locale (ou automatique) :

```cpp
A myClass(...);
```
`myClass` est détruit (et son destructeur est appelé) à la fin du bloc courant.

- pointeur :

```cpp
A *myClass=new myClass(...);
```
`myClass` est une variable pointeur (c'est-à-dire une adresse) qui pointe sur une zone mémoire allouée. Cette zone mémoire survit au bloc courant, mais pas la variable pointeur. 
La destruction de la zone mémoire ne peut se faire qu'avec un `delete`

- variable globale : déclarée en dehors de toute fonction, sa portée est l'unité de compilation (le fichier courant...).


## Annexe 2 : lire et écrire dans un fichier en C++

- http://www.cplusplus.com/doc/tutorial/files/
- `std::ifstream` et `std::ofstream` pour ouvrir un fichier en lecture, en écriture
- `std::string` : type de base pour les string en C++
- `std::getline(file,line)` : récupère dans la string line la ligne suivante du fichier file
- `std::stringstream sstr(line)` : construit un flux à partir d'une variable de type `string` (le flux contient la séquence d'octets contenue dans la chaîne de caractères)
- `sstr >> x >> y` : convertit les octets du flux en deux entiers `x` et `y`
- méthodes `read()` et `write()` des classes `std::ifstream`, `std::ofstream`, `std::fstream` pour lire ou écrire des données binaires non structurées (séquence d'octets)

## Annexe 3 : manipulation des images
- sous Linux la commande `convert` d'ImageMagick rend bien des services (`man convert`)
- vous pouvez notamment convertir une image d'un format à un autre 
	- Exemple : `convert toto.jpg toto.pgm`
- le logiciel `ImageJ` est relativement léger et permet de lire un grand nombre de format d'images (notamment le format `pgm`). 







