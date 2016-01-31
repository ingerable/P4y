//
//  image.h
//  tp-P4y
//
//  Created by Benoit Naegel on 25/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#ifndef image_h
#define image_h

namespace P4y {

class Image8b {
    /// classe stockant une image 8 bits (256 valeurs)
    
private:
    int width;
    int height;
    int size;
    unsigned char *data;
    
public:
    /// construit une image de taille (width,height)  (par défaut 0)
    Image8b(int width=0, int height=0);
    /// construit une image de taille (width,height) avec le buffer data
    Image8b(int width, int height, unsigned char *data);
    
    /// constructeur de copie, permettant d'écrire Image B; Image A(B);
    Image8b(const Image8b& image8b);
    
    /// opérateur d'affectation permettant d'écrire Image B; Image A=B;
    Image8b& operator=(const Image8b&);
    
    ///destructeur : instructions pour désallouer les ressources de la classe (ici, le pointeur data)
    ~Image8b();
    int getWidth();
    int getHeight();
    int getSize();
    unsigned char *getData();
    
    /// affiche sur la sortie standard la valeur des pixels de l'image
    void print();
    
    /// surcharge de l'opérateur () permettant d'écrire une valeur à la position (x,y) : A(x,y)=v
    unsigned char &operator()(const int &x, const int &y);
    /// surcharge de l'opérateur () permettant de lire une valeur à la position (x,y) : v=A(x,y)
    unsigned char operator()  (const int &x, const int &y) const;
};

} // namespace P4y

#endif /* image_h */
