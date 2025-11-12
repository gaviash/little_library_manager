#include "biblioH.h"
#ifndef ENTREESORTIEH
#define ENTREESORTIEH

/**
 * @brief Charge les n premieres entrees d'un fichier dans une bibliotheque avec hachage.
 *
 * Ouvre le fichier specifie, lit jusqu'a n lignes au format "num titre auteur",
 * et insere chaque livre dans la bibliotheque via inserer_en_tete.
 * S'arrete si le fichier contient moins de n entrees ou en cas d'erreur de lecture.
 *
 * @param nomfic Nom du fichier a charger.
 * @param n Nombre maximum d'entrees a charger.
 * @return Pointeur vers la bibliotheque chargee, ou NULL en cas d'erreur.
 */
BiblioH* charger_n_entrees(char* nomfic, int n);

/**
 * @brief Enregistre le contenu de la bibliotheque dans un fichier.
 *
 * Parcourt toutes les listes chainees de la table de hachage et ecrit chaque livre
 * dans le fichier au format "num titre auteur\n".
 *
 * @param b Pointeur vers la bibliotheque a enregistrer.
 * @param nomfic Nom du fichier de sortie.
 */
void enregistrer_biblio(BiblioH* b, char *nomfic);

#endif
