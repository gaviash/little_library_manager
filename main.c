#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"
#include "EntreeSortieLC.h"

void menu(){
    /*L'utilisateur va commencer un precisant un fichier qui va devenir la bibliotheque basique*/
    printf(" \nListe des commandes : \n");
    printf("- 0 : Arret du programme\n");
    printf("- 1 : Afficher/Rechercher un livre\n");
    printf("- 2 : Afficher la bibliotheque\n");
    printf("- 3 : Inserer en tete de la bibliotheque\n");
    printf("- 4 : Supprimer un livre\n");
    printf("- 5 : Ajouter une bibliotheque\n");
    printf("- 6 : Rechercher les doublons\n");
    printf("- 7 : Enregistrer la bibliotheque dans un fichier\n");
    printf("Action : ");
}

int main(int argc,char **argv){
    Biblio *res = charger_n_entrees(argv[1],atoi(argv[2]));
    Biblio *recep_fusion;
    /*test_fonctions();*/
    int rep;
    Livre *recep;
    char *titre;
    char *auteur;
    do{
        menu();
        scanf("%d",&rep);
        switch (rep){
            case 0 :
                printf("Arret");
                exit(1);
            case 1 :
                printf("Par numero(1) ou par titre(2) ? (0 pour revenir au menu) : ");
                scanf("%d",&rep);
                if (rep==0) break;
                else if (rep==1){
                    printf("Entrez le numero du livre : ");
                    scanf("%d",&rep);
                    recep = chercher_par_numero(res,rep);
                    afficher_livre(recep); /*On pourrait tout faire sur une ligne mais c'est plus lisible comme ca*/
                    break; 
                } else{
                    printf("Entrez le titre du livre,en majuscules : ");
                    scanf("%s",titre);
                    recep = chercher_par_titre(res,titre);
                    afficher_livre(recep);
                    break;
                }
                case 2 :
                    afficher_biblio(res);
                    break;
                case 3 :
                    printf("Ecrivez dans ce format : <Numero> <TITRE> <auteur> : ");
                    scanf("%d %s %s",&rep,titre,auteur);
                    inserer_en_tete(res,rep,titre,auteur);
                    break;
                case 4 :
                    printf("Ecrivez dans ce format : <Numero> <TITRE> <auteur> : ");
                    scanf("%d %s %s",&rep,titre,auteur);
                    supprimer_livre(res,rep,titre,auteur);
                case 5 :
                    printf("Entrez le nom de votre fichier, suivi du nombre de lignes : ");
                    scanf("%s %d",titre,&rep);
                    recep_fusion = charger_n_entrees(titre,rep);
                    res = fusion(res,recep_fusion);
                    break;
                case 6 :
                    recep_fusion=recherche_avec_dup(res);
                    afficher_biblio(recep_fusion);
                    libererBiblio(recep_fusion);
                    break;
                case 7 :
                    printf("Entrez le nom de votre fichier :  ");
                    scanf("%s",titre);
                    enregistrer_biblio(res,titre);
                    break;
        }
    } while (1);
}

