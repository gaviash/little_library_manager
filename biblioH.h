#ifndef BIBLIOH
#define BIBLIOH

/**
 * @brief Structure representant un livre dans la bibliotheque avec hachage.
 *
 * Cette structure contient les informations d'un livre : cle de hachage, numero,
 * titre, auteur, et un pointeur vers le livre suivant dans la liste chainee.
 */
typedef struct livreh{
    int clef;          /**< Cle de hachage calculee a partir de l'auteur */
    int num;           /**< Numero unique du livre */
    char *titre;       /**< Titre du livre (chaine allouee dynamiquement) */
    char *auteur;      /**< Auteur du livre (chaine allouee dynamiquement) */
    struct livreh *suivant; /**< Pointeur vers le livre suivant dans la liste */
} LivreH;

/**
 * @brief Structure representant la bibliotheque avec table de hachage.
 *
 * Cette structure gere une table de hachage avec chainage pour stocker les livres.
 * Chaque entree de la table est une liste chainee de livres.
 */
typedef struct table{
    int Ne;            /**< Nombre d'elements contenus dans la table */
    int m;             /**< Taille/contenance possible de la table (nombre de buckets) */
    LivreH **T;        /**< Tableau de pointeurs vers les listes chainees de livres */
} BiblioH;

/**
 * @brief Calcule la cle de hachage a partir du nom de l'auteur.
 *
 * @param auteur Chaine de caracteres representant le nom de l'auteur.
 * @return La somme des codes ASCII des caracteres de l'auteur.
 */
int fonction_clef(char* auteur);

/**
 * @brief Calcule l'indice de hachage dans la table.
 *
 * Utilise la methode de multiplication pour le hachage.
 *
 * @param cle La cle de hachage (obtenue via fonction_clef).
 * @param m La taille de la table de hachage.
 * @return L'indice dans la table (entre 0 et m-1).
 */
int fonction_hachage(int cle, int m);

/**
 * @brief Cree un nouveau livre avec les informations fournies.
 *
 * Alloue dynamiquement la memoire pour le livre et copie les chaines titre et auteur.
 *
 * @param num Numero unique du livre.
 * @param titre Titre du livre.
 * @param auteur Auteur du livre.
 * @return Pointeur vers le livre cree, ou NULL en cas d'erreur d'allocation.
 */
LivreH *creer_livre(int num, char *titre, char *auteur);

/**
 * @brief Libere la memoire allouee pour un livre.
 *
 * Desalloue les chaines titre et auteur, puis la structure elle-meme.
 *
 * @param l Pointeur vers le livre a liberer.
 */
void liberer_livre(LivreH *l);

/**
 * @brief Cree une nouvelle bibliotheque avec une table de hachage de taille m.
 *
 * Alloue la memoire pour la structure BiblioH et le tableau de pointeurs T.
 *
 * @param m Taille de la table de hachage (nombre de buckets).
 * @return Pointeur vers la bibliotheque creee, ou NULL en cas d'erreur d'allocation.
 */
BiblioH *creer_biblio(int m);

/**
 * @brief Libere toute la memoire allouee pour la bibliotheque.
 *
 * Parcourt toutes les listes chainees dans la table et libere chaque livre,
 * puis desalloue le tableau T et la structure BiblioH.
 *
 * @param l Pointeur vers la bibliotheque a liberer.
 */
void libererBiblio(BiblioH *l);

/**
 * @brief Insere un livre en tete de la liste chainee dans le bucket approprie.
 *
 * Calcule l'indice de hachage, cree le livre, et l'insere en tete de la liste
 * du bucket correspondant. Incremente le compteur d'elements Ne.
 *
 * @param b Pointeur vers la bibliotheque.
 * @param num Numero du livre.
 * @param titre Titre du livre.
 * @param auteur Auteur du livre.
 */
void inserer_en_tete(BiblioH *b, int num, char *titre, char *auteur);

/**
 * @brief Affiche les informations d'un livre.
 *
 * @param l Pointeur vers le livre a afficher.
 */
void afficher_livre(LivreH *l);

/**
 * @brief Affiche tous les livres de la bibliotheque.
 *
 * @param b Pointeur vers la bibliotheque a afficher.
 */
void afficher_biblio(BiblioH *b);

/**
 * @brief Recherche un livre par son numero.
 *
 * @param b Pointeur vers la bibliotheque.
 * @param num Numero du livre a rechercher.
 * @return Pointeur vers le livre trouve, ou NULL si non trouve.
 */
LivreH* chercher_par_numero(BiblioH* b,int num);

/**
 * @brief Recherche un livre par son titre.
 *
 * @param b Pointeur vers la bibliotheque.
 * @param titre Titre du livre a rechercher.
 * @return Pointeur vers le livre trouve, ou NULL si non trouve.
 */
LivreH* chercher_par_titre(BiblioH *b, char *titre);

/**
 * @brief Recherche tous les livres d'un auteur.
 *
 * @param b Pointeur vers la bibliotheque.
 * @param auteur Auteur des livres a rechercher.
 * @return Nouvelle bibliotheque contenant les livres de l'auteur.
 */
BiblioH* chercher_par_auteur(BiblioH *b, char *auteur);

/**
 * @brief Supprime un livre de la bibliotheque.
 *
 * @param b Pointeur vers la bibliotheque.
 * @param num Numero du livre a supprimer.
 * @param titre Titre du livre a supprimer.
 * @param auteur Auteur du livre a supprimer.
 */
void supprimer_livre(BiblioH *b,int num,char *titre,char *auteur);

/**
 * @brief Fusionne deux bibliotheques en ajoutant les livres de la deuxieme dans la premiere.
 *
 * @param un Pointeur vers la premiere bibliotheque.
 * @param deux Pointeur vers la deuxieme bibliotheque (sera liberee).
 * @return Pointeur vers la premiere bibliotheque fusionnee.
 */
BiblioH* fusion(BiblioH* un,BiblioH* deux);

/**
 * @brief Recherche les livres en double dans la bibliotheque.
 *
 * @param b Pointeur vers la bibliotheque.
 * @return Nouvelle bibliotheque contenant les livres en double.
 */
BiblioH* recherche_avec_dup(BiblioH *b);

void test_all_functions();

#endif
