#include "biblioLC.h"
#include "EntreeSortieLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Parser d'abord chaque ligne,et a chaque ligne parsée,appeler une fonction qui prend une 
chaine et parse la chaine pour int str str*/


Livre* parse_ligne(char* ligne){
    Livre *new = creerLivre(1,"Bondour","doudou");
    int i,j;
    char *stock = malloc(strlen(ligne)+1);
    for (i = 0;ligne[i] != ' ';i++) stock[i] = ligne[i];
    stock[i] = '\0';
    new->num = atoi(stock);
    i++;
    for (j=0;ligne[i] != ' ';i++,j++) stock[j] = ligne[i];
    stock[j] = '\0';
    strcpy(new->titre,stock);
    i++;
    for (j=0;ligne[i] != '\0';i++,j++) stock[j] = ligne[i];
    stock[j] = '\0';
    strcpy(new->auteur,stock);
    free(stock);
    return new;
}

Biblio* charger_n_entrees(char* nomfic,int n){
    Biblio *res = creerBiblio();
    int i,num;
    char titre[40];
    char auteur[40];
    FILE *file = fopen(nomfic,"r");
    for (i=0;i<n;i++){
        if (fscanf(file,"%d %s %s",&num,titre,auteur) != 3) { /* si il n'y pas 3 arguments*/
            break;
        }
        inserer_en_tete(res,num,titre,auteur);
    }
    fclose(file);
    return res;
}

void enregistrer_biblio(Biblio *b,char *nomfic){
    Livre *curr = b->debut;
    FILE *fic = fopen(nomfic,"w");
    while(curr != NULL){
        fprintf(fic,"%d %s %s\n",curr->num,curr->titre,curr->auteur);
        curr = curr->suiv;
    }
    fclose(fic);
}
