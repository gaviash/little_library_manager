#include "biblioLC.h"
#ifndef EntreeSortieLC_H
#define EntreeSortieLC_H
/*Toujours inclure les ifndef dans les fichiers.h*/

/**
 * Ce fichier définit les fonctions pour charger et enregistrer des bibliographies depuis/vers des fichiers.
 * Il fournit des utilitaires pour l'entrée/sortie de données de bibliographie.
 */

/**
 * Charge n entrées depuis un fichier et les insère dans une nouvelle bibliographie.
 * Chaque entrée est lue au format : numéro titre auteur
 * @param nomfic Le nom du fichier à lire.
 * @param n Le nombre d'entrées à charger.
 * @return Une nouvelle bibliographie contenant les n premières entrées valides du fichier.
 */
Biblio* charger_n_entrees(char* nomfic, int n);

/**
 * Enregistre le contenu d'une bibliographie dans un fichier.
 * Chaque livre est écrit sous la forme : numéro titre auteur
 * @param b La bibliographie à enregistrer.
 * @param nomfic Le nom du fichier où enregistrer.
 */
void enregistrer_biblio(Biblio *b, char* nomfic);
/**
 * Parse une ligne de texte pour créer un livre.
 * La ligne doit être au format : numéro titre auteur
 * @param ligne La ligne à parser.
 * @return Un pointeur vers le livre créé, ou NULL en cas d'erreur.
 */
Livre* parse_ligne(char* ligne); /*Fonction inutile puisque je me suis rendu compte ensuite que fscanf existait*/

#endif