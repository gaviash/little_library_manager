#ifndef BIBLIOH
#define BIBLIOH

typedef struct livreh{
    int clef;
    int num;
    char *titre;
    char *auteur;
    struct livreh *suivant;
} LivreH;

typedef struct table{
    int Ne; /*nombre d'elements contenus dans la table*/
    int m; /*Taille/contenance possible de la table*/
    LivreH **T; /*Tableau de pointeur -> double pointeur// C'est un tableau qui contient DES listes chainées*/
} BiblioH;


#endif