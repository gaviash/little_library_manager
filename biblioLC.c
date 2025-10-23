#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"
#include "EntreeSortieLC.h"
/*Regarder les raccourcis pour makefile type $@ et $^*/

Livre* creerLivre(int num,char *titre,char *auteur){
    Livre *new = malloc(sizeof(Livre));
    new->num = num;
    new->auteur = strdup(auteur);
    new->titre = strdup(titre);
    new->suiv = NULL;
    return new;
}
void libererLivre(Livre *l){
    free(l->auteur);
    free(l->titre);
    free(l);
}

Biblio* creerBiblio(){
    Biblio* new = malloc(sizeof(Biblio));
    new->debut = NULL;
    return new;
}
void libererBiblio(Biblio *l){
    Livre *curr = l->debut;
    Livre *pred;
    while(curr != NULL){
        pred = curr;
        curr = curr->suiv;
        libererLivre(pred);
    }
    free(l);
}

void inserer_en_tete(Biblio *b,int num,char *titre,char *auteur){
    Livre *new_el = creerLivre(num,titre,auteur);
    new_el->suiv = b->debut;
    b->debut = new_el;
}

void afficher_livre(Livre *l){
    printf("Numero : %d, Titre : %s, Auteur : %s\n",l->num,l->titre,l->auteur);
}

void afficher_biblio(Biblio *b){
    Livre *curr = b->debut;
    while(curr != NULL){
        afficher_livre(curr);
        curr = curr->suiv;
    }
}

Livre* chercher_par_numero(Biblio* b,int num){
    Livre *curr = b->debut;
    while(curr != NULL && curr ->num != num) curr=curr->suiv;
    return curr;
}

Livre* chercher_par_titre(Biblio* b,char *titre){
    Livre *curr = b->debut;
    while(curr != NULL && strcmp(curr->titre,titre)) curr=curr->suiv;
    return curr;
}

Biblio* chercher_par_auteur(Biblio *b,char *auteur){
    Livre *curr = b->debut;
    Biblio *res = creerBiblio();
    while(curr != NULL){
        if (!strcmp(curr->auteur,auteur)){
            inserer_en_tete(res,curr->num,curr->titre,curr->auteur);
        }
        curr=curr->suiv;
    }
    return res;
}

void supprimer_livre(Biblio *b,int num,char *titre,char *auteur){
    Livre* curr = b->debut;
    Livre* prec = NULL; /*Initialiser a null permet de reconnaitre le premier cas,ou l'on doit rattacher au debut de la bibliotheque*/
    while(curr != NULL){
        if (curr->num == num && !strcmp(curr->titre,titre) && !strcmp(curr->auteur,auteur)){
            if (prec != NULL){
                prec->suiv = curr->suiv;
                libererLivre(curr);
                break;
            }else {
                b->debut = curr->suiv;
                libererLivre(curr);
                break;
            }
        }
        prec = curr;
        curr = curr->suiv;

    }
}

Biblio* fusion(Biblio* un,Biblio* deux){
    Livre *curr = un->debut;
    if (curr == NULL){
        un->debut = deux->debut;
    } else {
        while (curr->suiv != NULL) curr=curr->suiv;
        curr->suiv = deux->debut;
    }
    free(deux);
    return un;
}

Biblio* recherche_avec_dup(Biblio *b){
    Biblio *res = creerBiblio();
    Livre *curr = b->debut;
    Livre *parcours_double = b->debut;
    while (curr != NULL){
        while(parcours_double != NULL){
            if (!strcmp(curr->titre,parcours_double->titre) && !strcmp(curr->auteur,parcours_double->auteur) && curr != parcours_double){
                inserer_en_tete(res,parcours_double->num,parcours_double->titre,parcours_double->auteur);
            }
            parcours_double=parcours_double->suiv;
        }
        curr=curr->suiv;
        parcours_double=b->debut;
    }
    return res;

}


/* Fonction de test pour vérifier les fonctionnalités de recherche, affichage, suppression et fusion */
void test_fonctions() {
    printf("=== Test des fonctions de bibliographie ===\n");

    // Créer une bibliographie et ajouter des livres
    Biblio *b = creerBiblio();
    inserer_en_tete(b, 1, "Titre1", "Auteur1");
    inserer_en_tete(b, 2, "Titre2", "Auteur2");
    inserer_en_tete(b, 3, "Titre3", "Auteur3");
    inserer_en_tete(b, 4, "Titre4", "Auteur4");

    printf("Bibliographie initiale :\n");
    afficher_biblio(b);

    // Test des fonctions de recherche
    printf("\n=== Tests de recherche ===\n");
    Livre *livre_num = chercher_par_numero(b, 2);
    if (livre_num) {
        printf("Livre trouvé par numéro 2 : ");
        afficher_livre(livre_num);
    } else {
        printf("Livre avec numéro 2 non trouvé.\n");
    }

    Livre *livre_titre = chercher_par_titre(b, "Titre3");
    if (livre_titre) {
        printf("Livre trouvé par titre 'Titre3' : ");
        afficher_livre(livre_titre);
    } else {
        printf("Livre avec titre 'Titre3' non trouvé.\n");
    }

    Biblio *bib_auteur = chercher_par_auteur(b, "Auteur1");
    printf("Livres de 'Auteur1' :\n");
    afficher_biblio(bib_auteur);
    libererBiblio(bib_auteur);

    // Test de suppression
    printf("\n=== Test de suppression ===\n");
    printf("Avant suppression du livre (2, 'Titre2', 'Auteur2') :\n");
    afficher_biblio(b);
    supprimer_livre(b, 2, "Titre2", "Auteur2");
    printf("Après suppression :\n");
    afficher_biblio(b);

    // Test de fusion
    printf("\n=== Test de fusion ===\n");
    Biblio *b2 = creerBiblio();
    inserer_en_tete(b2, 5, "Titre5", "Auteur4");
    inserer_en_tete(b2, 6, "Titre6", "Auteur5");
    printf("Bibliographie b :\n");
    afficher_biblio(b);
    printf("Bibliographie b2 :\n");
    afficher_biblio(b2);

    Biblio *b_fusion = fusion(b, b2);
    printf("Après fusion (b + b2) :\n");
    afficher_biblio(b_fusion);

    // Libérer la mémoire
    libererBiblio(b_fusion);
    printf("\n=== Fin des tests ===\n");
}
