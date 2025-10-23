#ifndef BIBLIO_LC_H
#define BIBLIO_LC_H

/**
 * Ce fichier définit les structures et les prototypes des fonctions pour la gestion de bibliographie basée sur une liste chaînée.
 */

typedef struct livre{
    int num;
    char *titre;
    char *auteur;
    struct livre *suiv;
}Livre;

typedef struct bibli{
    Livre *debut;
}Biblio;

/**
 * Crée un nouveau livre (Livre) avec le numéro, le titre et l'auteur spécifiés.
 * Alloue de la mémoire pour le livre et duplique les chaînes de titre et d'auteur.
 * @param num Le numéro unique du livre.
 * @param titre Le titre du livre.
 * @param auteur L'auteur du livre.
 * @return Un pointeur vers le Livre nouvellement créé, ou NULL si l'allocation de mémoire échoue.
 */
Livre* creerLivre(int num, char *titre, char *auteur);

/**
 * Libère la mémoire allouée pour un livre (Livre), y compris ses chaînes de titre et d'auteur.
 * @param l Le livre à libérer. Ne doit pas être NULL.
 */
void libererLivre(Livre *l);

/**
 * Crée une nouvelle bibliographie (Biblio) vide.
 * @return Un pointeur vers la Biblio nouvellement créée, ou NULL si l'allocation de mémoire échoue.
 */
Biblio* creerBiblio();

/**
 * Libère la mémoire allouée pour une bibliographie (Biblio) et tous ses livres.
 * @param l La bibliographie à libérer. Ne doit pas être NULL.
 */
void libererBiblio(Biblio *l);

/**
 * Insère un nouveau livre en tête de la bibliographie.
 * @param b La bibliographie dans laquelle insérer. Ne doit pas être NULL.
 * @param num Le numéro du nouveau livre.
 * @param titre Le titre du nouveau livre.
 * @param auteur L'auteur du nouveau livre.
 */
void inserer_en_tete(Biblio *b, int num, char *titre, char *auteur);

/**
 * Affiche les informations d'un livre.
 * @param l Le livre à afficher. Ne doit pas être NULL.
 */
void afficher_livre(Livre *l);

/**
 * Affiche tous les livres de la bibliographie.
 * @param b La bibliographie à afficher. Ne doit pas être NULL.
 */
void afficher_biblio(Biblio *b);

/**
 * Recherche un livre par son numéro dans la bibliographie.
 * @param b La bibliographie dans laquelle rechercher.
 * @param num Le numéro du livre à rechercher.
 * @return Un pointeur vers le livre trouvé, ou NULL si non trouvé.
 */
Livre* chercher_par_numero(Biblio* b, int num);

/**
 * Recherche un livre par son titre dans la bibliographie.
 * @param b La bibliographie dans laquelle rechercher.
 * @param titre Le titre du livre à rechercher.
 * @return Un pointeur vers le livre trouvé, ou NULL si non trouvé.
 */
Livre* chercher_par_titre(Biblio* b, char *titre);

/**
 * Recherche et retourne une nouvelle bibliographie contenant tous les livres d'un auteur donné.
 * @param b La bibliographie source.
 * @param auteur Le nom de l'auteur à rechercher.
 * @return Une nouvelle bibliographie avec les livres de cet auteur, ou une bibliographie vide si aucun livre trouvé.
 */
Biblio* chercher_par_auteur(Biblio *b, char *auteur);

/**
 * Supprime le premier livre de la bibliographie qui correspond aux critères spécifiés (numéro, titre, auteur).
 * @param b La bibliographie dans laquelle supprimer. Ne doit pas être NULL.
 * @param num Le numéro du livre à supprimer.
 * @param titre Le titre du livre à supprimer.
 * @param auteur L'auteur du livre à supprimer.
 */
void supprimer_livre(Biblio *b, int num, char *titre, char *auteur);

/**
 * Fusionne deux bibliographies en ajoutant la deuxième à la fin de la première, puis libère la structure de la deuxième.
 * @param un La première bibliographie (sera modifiée et retournée).
 * @param deux La deuxième bibliographie (sera vidée et libérée).
 * @return Un pointeur vers la bibliographie fusionnée (un).
 */
Biblio* fusion(Biblio* un, Biblio* deux);

/**
 * Recherche et retourne une nouvelle bibliographie contenant tous les livres dupliqués (mêmes titre et auteur) de la bibliographie source.
 * Permet les doublons dans la bibliographie retournée (surcomptage acceptable).
 * @param b La bibliographie source dans laquelle rechercher les dupliqués.
 * @return Une nouvelle bibliographie contenant tous les livres dupliqués, ou une bibliographie vide si aucun dupliqué trouvé.
 */
Biblio* recherche_avec_dup(Biblio *b);

/**
 * Fonction de test pour vérifier les fonctionnalités de recherche, affichage, suppression et fusion de la bibliographie.
 */
void test_fonctions();

#endif // BIBLIO_LC_H

