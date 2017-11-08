#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "headers/bibliotheque_ListeChainee.h"

Bibliotheque creer_bibliotheque(){
    Bibliotheque b = NULL;
    return b;
}
Bibliotheque inserer(Bibliotheque b, char* isbn, char* titre, char* auteur, char* editeur, char* datePublication)
{
    //creation du maillon a inserer
    Bibliotheque nouveau_maillon;
    nouveau_maillon=malloc(sizeof(struct BibliothequeSt));
    
    //initialisation de ses champs
    nouveau_maillon->isbn = copier_chaine(isbn);
    nouveau_maillon->titre = copier_chaine(titre);
    nouveau_maillon->auteur = copier_chaine(auteur);
    nouveau_maillon->editeur = copier_chaine(editeur);
    nouveau_maillon->datePublication = copier_chaine(datePublication);
    nouveau_maillon->suivant = NULL;

    if(b != NULL)//insertion en tete de liste
    {

        nouveau_maillon->suivant = b;
    }

    return nouveau_maillon;//on retourne le debut de la liste chainee

}

Bibliotheque rechercher_livre(Bibliotheque b, char* isbn)
{
    if(isbn!=NULL)//on verifie l'existence de l'isbn
    {
        while(b!=NULL && strcmp(b->isbn,isbn)!=0)//tant que b n'est pas vide et que l'isbn recherche ne correspond pas au livre actuel
        {
            b=b->suivant;
        }
    }
    else
    {
        b=NULL;//si isbn existe pas, il n'y a pas de livre correspondant
    }

    return b;

}

Bibliotheque rechercher_titre(Bibliotheque b, char prefixe){
    if(b != NULL){
        
    }
}

void detruire_bibliotheque(Bibliotheque b)
{
    if(b!=NULL)
    {
        detruire_bibliotheque(b->suivant);
        free(b->isbn);
        free(b->titre);
        free(b->auteur);
        free(b->datePublication);
        free(b->editeur);
        free(b);
    }
}

void afficher_tout(Bibliotheque b)
{
    if(b!=NULL)
    {
        afficher(b);
        afficher_tout(b->suivant);
    }
    else
    {
        afficher(b);
    }
}

char* copier_chaine(char* chaine_a_copier)
{
    char* copie;

    copie=malloc(sizeof(char)*(strlen(chaine_a_copier)+1));
    strcpy(copie,chaine_a_copier);

    return copie;
}

void afficher(Bibliotheque b)
{
    if(b!=NULL)
    {
        printf("isbn:%s\n\ttitre:%s\n\tauteur:%s\n\tediteur:%s\n\tdate de publication:%s\n",
               b->isbn,b->titre,b->auteur,b->editeur,b->datePublication);
    }
    else{
        printf("\nNULL\n");
    }
}

