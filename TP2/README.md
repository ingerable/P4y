# Semaine 2

Interpolation, rééchantillonnage, quantification.

## Redimensionnement
On appelle redimensionnement (ou rééchantillonnage) d'une image le fait de changer sa taille, soit en enlevant des échantillons (sous-échantillonnage) soit en en ajoutant (sur-échantillonnage).

On va écrire un programme permettant de rééchantillonner une image en considèrant que le redimensionnement conservera le rapport hauteur/largeur de l’image (autrement dit l’image ne sera pas déformée). Soient $r \in \mathbb{R}^+$ le facteur (ou ratio) de redimensionnement, $l,h\in \mathbb{N}$ la largeur et la hauteur de l'image. Après redimensionnement, l’image aura une largeur de $l * r$ et une hauteur de $h *r$.


Deux types de méthodes d'interpolation seront implantés : par plus proche voisin et par interpolation bilinéaire.

1. Écrire une fonction ``subsample`` qui sous-échantillonne une image d'un facteur donné en paramètres (avec l'une des deux méthodes citées précédemment, le type étant passé en paramètre de la fonction); 
2. Écrire une fonction ``oversample`` qui sur-échantillonne une image d'un facteur donné en paramètres (avec l'une des deux méthodes citées précédemment, le type étant passé en paramètre de la fonction).

## Quantification
On appelle quantification le processus consistant à réduire le nombre de couleurs/niveaux de gris d'une image.

Écrire la fonction ``quantize`` qui quantifie une image 8 bits passée en paramètre d'un facteur $2^k$, avec $k$ passé en paramètre. Après quantification, le nombre de niveaux de gris de l'image est divisé par $2^k$, et l'image est normalisée : les niveaux de gris sont rééchelonnés dans l'intervalle $[0,255]$.

Par exemple, pour $k=7$, on obtient une image binaire : les pixels ayant une intensité inférieure à $128$ dans l'image originale ont une intensité de $0$ dans l'image d'arrivée ; les pixels ayant une intensité supérieure à $128$ ont une intensité de $255$ dans l'image d'arrivée.