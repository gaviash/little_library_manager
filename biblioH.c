#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioH.h"

int fonction_clef(char* auteur){
    int i;
    int sum = 0;
    for (i=0;auteur[i] != '\0';i++){
        sum += auteur[i];
    }
    return sum;
}

int fonction_hachage(int cle,int m){
    float ka = cle*((sqrt(5)-1)/2);
    int rounded_ka = (int)ka;
    return (int)(m*(ka-rounded_ka));
}

LivreH *creer_livre(int num,char *titre,char *auteur){
    LivreH *rep = malloc(sizeof(LivreH));
    rep->clef = fonction_clef(auteur);
    rep->num = num;
    rep->auteur= strdup(auteur); /* Copie ET alloue la memoire necessaire*/
    rep->titre = strdup(titre);
    rep->suivant = NULL;
    return rep;
}

void liberer_livre(LivreH *l){
    free(l->auteur);
    free(l->titre);
    free(l);
}

BiblioH *creer_biblio(int m){
    BiblioH *res = malloc(sizeof(BiblioH));
    res->m = m;
    res->Ne = 0;
    res->T = malloc(m * sizeof(LivreH *));
    for (int i = 0; i < m; i++){
        res->T[i] = NULL;
    }
    return res;
}

void libererBiblio(BiblioH *l){
    /*Utiliser un parcours de tableau pour liberer les linked lists */
    int i;
    LivreH *curr;
    LivreH *buffer;
    for (i=0;i < l->m;i++){
        curr = l->T[i];
        while (curr != NULL){
            buffer = curr;
            curr = curr->suivant;
            liberer_livre(buffer);
        }
    }
    free(l->T);
    free(l);
}

void inserer_en_tete(BiblioH *b,int num,char *titre,char*auteur){
    LivreH* livre = creer_livre(num,titre,auteur);
    int indice_tete = fonction_hachage(livre->clef,b->m);
    LivreH* tete = b->T[indice_tete];
    if (tete != NULL){
        livre ->suivant = tete;
        b->T[indice_tete] = livre;
    } else b->T[indice_tete] = livre;
    b->Ne++;
}

void afficher_livre(LivreH *l){
    printf("Numero : %d, Titre : %s, Auteur : %s\n",l->num,l->titre,l->auteur);
}

void afficher_biblio(BiblioH *b){
    int i;
    LivreH *curr;
    for (i=0; i < b->m ; i++){
        curr = b->T[i];
        while (curr != NULL){
            afficher_livre(curr);
            curr = curr->suivant;
        }
    }
}

LivreH* chercher_par_numero(BiblioH* b,int num){
    int i;
    LivreH* curr;
    for (i=0; i < b->m;i++){
        curr = b->T[i];
        while (curr != NULL){
            if (curr->num == num) return curr;
            curr = curr->suivant;
        }
    }
    return NULL;
}

LivreH* chercher_par_titre(BiblioH *b, char *titre){
    int i;
    LivreH* curr;
    for (i=0; i < b->m ; i++){
        curr = b->T[i];
        while(curr != NULL){
            if (!strcmp(curr->titre,titre)) return curr;
            curr = curr->suivant;
        }
    }
    return NULL;
}

BiblioH* chercher_par_auteur(BiblioH *b, char *auteur){
    BiblioH *res = creer_biblio(1);
    LivreH *curr = b->T[fonction_hachage(fonction_clef(auteur),b->m)];

    while (curr != NULL){
        if (!strcmp(curr->auteur,auteur)) inserer_en_tete(res,curr->num,curr->titre,curr->auteur);
        curr = curr->suivant;
    }
    return res;
}

void supprimer_livre(BiblioH *b,int num,char *titre,char *auteur){
    int index = fonction_hachage(fonction_clef(auteur),b->m);
    LivreH *curr = b->T[index];
    LivreH *prec = NULL; /*Meme logique que dans biblioLC.c*/

    while (curr != NULL){
        if (curr->num == num && !strcmp(auteur,curr->auteur) && !strcmp(titre,curr->titre)){
            b->Ne--;
            if (prec != NULL){
                prec->suivant = curr->suivant;
                liberer_livre(curr);
                break;
            }else{
                prec = curr->suivant;
                b->T[index] = prec;
                free(curr);
                break;
            }
        }
        prec = curr;
        curr = curr->suivant;
    }
}

BiblioH* fusion(BiblioH* un,BiblioH* deux){
    int i;
    LivreH *curr;
    for (i=0; i < deux->m;i++){
        curr = deux->T[i];
        while (curr != NULL){
            inserer_en_tete(un,curr->num,curr->titre,curr->auteur);
            curr = curr->suivant;
        }
    }
    libererBiblio(deux);
    return un;
}


BiblioH* recherche_avec_dup(BiblioH *b){
    /*trouver une maniere d'iterer qui colle avec les hash table*/
    int i;
    BiblioH *res = creer_biblio(b->m);
    LivreH *curr;
    LivreH *parcours_double;
    for (i = 0; i < b->m; i++){
        curr= b->T[i];
        while (curr != NULL){
            parcours_double = b->T[i];
            while (parcours_double != NULL){
                if (!strcmp(curr->auteur,parcours_double->auteur) && !strcmp(curr->titre,parcours_double->titre) && parcours_double != curr){
                    inserer_en_tete(res,parcours_double->num,parcours_double->titre,parcours_double->auteur);
                }
                parcours_double = parcours_double->suivant;
            }
            curr = curr->suivant;
        }
    }
    return res;
}

void test_all_functions() {
    printf("Test de fonction_clef et fonction_hachage...\n");
    int cle = fonction_clef("Auteur");
    int hash = fonction_hachage(cle, 10);
    printf("Clé pour 'Auteur': %d, Index de hachage: %d\n", cle, hash);

    printf("\nCréation de la bibliographie...\n");
    BiblioH *b = creer_biblio(10);

    printf("Insertion des livres...\n");
    inserer_en_tete(b, 1, "Titre1", "Auteur1");
    inserer_en_tete(b, 2, "Titre2", "Auteur2");
    inserer_en_tete(b, 3, "Titre1", "Auteur1"); // doublon pour les tests

    printf("Affichage de la bibliographie:\n");
    afficher_biblio(b);

    printf("\nRecherche par numéro (1):\n");
    LivreH *found = chercher_par_numero(b, 1);
    if (found) afficher_livre(found);
    else printf("Non trouvé\n");

    printf("\nRecherche par titre ('Titre2'):\n");
    found = chercher_par_titre(b, "Titre2");
    if (found) afficher_livre(found);
    else printf("Non trouvé\n");

    printf("\nRecherche par auteur ('Auteur1'):\n");
    BiblioH *by_author = chercher_par_auteur(b, "Auteur1");
    afficher_biblio(by_author);
    libererBiblio(by_author);

    printf("\nSuppression du livre (1, 'Titre1', 'Auteur1')...\n");
    supprimer_livre(b, 2, "Titre2", "Auteur2");
    afficher_biblio(b);

    printf("\nCréation d'une deuxième bibliographie pour la fusion...\n");
    BiblioH *b2 = creer_biblio(10);
    inserer_en_tete(b2, 4, "Titre4", "Auteur4");

    printf("Fusion des bibliographies...\n");
    BiblioH *merged = fusion(b, b2);
    afficher_biblio(merged);

    printf("\nRecherche des doublons...\n");
    BiblioH *dups = recherche_avec_dup(merged);
    afficher_biblio(dups);
    libererBiblio(dups);

    printf("\nLibération de la bibliographie fusionnée...\n");
    libererBiblio(merged);

    printf("Tous les tests terminés.\n");
}
