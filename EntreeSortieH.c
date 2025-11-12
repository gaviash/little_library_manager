#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioH.h"
#include "EntreeSortieH.h"

BiblioH* charger_n_entrees(char* nomfic,int n){
    BiblioH* res = creer_biblio(n);
    int i,num;
    char titre[40];
    char auteur[40];
    FILE *file = fopen(nomfic,"r");
    for (i=0;i<n;i++){
        if (fscanf(file,"%d %s %s",&num,titre,auteur) != 3){
            break;
        }
        inserer_en_tete(res,num,titre,auteur);
    }
    fclose(file);
    return res;
}

void enregistrer_biblio(BiblioH* b,char *nomfic){
    int i;
    LivreH *curr;
    FILE *fic = fopen(nomfic,"w");
    for (i=0;i<b->m;i++){
        /*Choisir une methode de comptage pour stopper la boucle for/while*/
        /*iterer sur m fois pour la premiere grande boucle et iterer sur la linked list pour chaque bucket*/
        curr = b->T[i];
        while (curr != NULL){
            fprintf(fic,"%d %s %s\n",curr->num,curr->titre,curr->auteur);
            curr = curr->suivant;
        }
    }
    fclose(fic);
}