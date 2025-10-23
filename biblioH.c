#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioH.h"

int fonction_clef(char* auteur){
    int i;
    int sum = 0;
    for (i=0;auteur[i] != '\0';i++){
        sum += auteur[i];
    }
    return sum;
}

LivreH *creer_livre(int num,char *titre,char *auteur){
    LivreH *rep = malloc(sizeof(LivreH));
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
