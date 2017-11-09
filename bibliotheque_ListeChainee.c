#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "bibliotheque_ListeChainee.h"

Bibliotheque creer_bibliotheque(){
    return NULL;
}

Bibliotheque inserer(Bibliotheque b, char* isbn, char* titre, char* auteur, char* editeur, char* datePublication)
{
    //creation du maillon a inserer
    Bibliotheque nouveau_maillon;
    nouveau_maillon=malloc(sizeof(struct MaillonSt));
    
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
        b=NULL; //si isbn existe pas, il n'y a pas de livre correspondant
    }

    return b;

}

Bibliotheque rechercher_titre(Bibliotheque b,char* prefixe)
{
    Bibliotheque resultat;
    resultat=NULL;

    if(prefixe!=NULL)//on verifie l'existence du titre
    {
        while(b!=NULL)//tant que b n'est pas vide et que le recherché ne correspond pas au livre actuel
        {
            if(strncmp(b->titre, prefixe, strlen(prefixe)*sizeof(char)) == 0 && !titre_deja_present(resultat,b->titre))
                // si le prefixe est le meme et que le titre n'existe pas deja dans notre selection
            {
                resultat=inserer(resultat,b->isbn,b->titre,b->auteur,b->editeur,b->datePublication);
            }
            b=b->suivant;
        }
    }

    return resultat;
}

Bibliotheque supprimer(Bibliotheque b, char* isbn)
{
    Bibliotheque debut;
    debut=b;
    if(b!=NULL) //si la chaine n'est pas deja vide
    {
        if(strcmp(b->isbn,isbn)==0) //si l'element a supprimer est en premiere position et la chaine est pas vide
        {

            Bibliotheque sauvegardeTemporaire;
            sauvegardeTemporaire=b->suivant;//on enregistre ce vers quoi pointe le maillon a supprimer
            liberer_memoire(b);//on libere le maillon a suppr
            b=sauvegardeTemporaire;
            debut=b;
        }
        else
        {
            while(b->suivant!=NULL)//on cherche jusqu'au bout de la chaine
            {
                if(strcmp(b->suivant->isbn,isbn)==0)//si on tombe sur le maillon a supprimer
                {
                    Bibliotheque sauvegardeTemporaire;
                    sauvegardeTemporaire=b->suivant->suivant;//on enregistre ce vers quoi pointe le maillon a supprimer
                    liberer_memoire(b->suivant);//on libere le maillon a suppr
                    b->suivant=sauvegardeTemporaire;//on raccorde le maillon precedent vers ce quoi pointait le maillon supprime
                    break;
                }
                b=b->suivant;
            }
        }
    }
    return debut;//on retourne le debut de chaine;
}

void detruire_bibliotheque(Bibliotheque b)
{
    if(b!=NULL)
    {
        detruire_bibliotheque(b->suivant);
        liberer_memoire(b);
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
        printf("ISBN:%s\n\tTITRE:%s\n\tAUTEUR:%s\n\tEDITEUR:%s\n\tDATE PUBLICATION:%s\n",
               b->isbn,b->titre,b->auteur,b->editeur,b->datePublication);
    }
    else{
        printf("\nNULL\n");
    }
}

Bibliotheque liberer_memoire(Bibliotheque b)
{
    if(b!=NULL)
    {
        free(b->isbn);
        free(b->titre);
        free(b->auteur);
        free(b->datePublication);
        free(b->editeur);
        free(b);
    }
    return NULL;
}

int titre_deja_present(Bibliotheque b,char* titre)
{
    int resultat=0;

    while(b!=NULL)
    {


        if(strcmp(titre,b->titre)==0)//si le titre est le meme que le livre actuel
        {
            resultat=1;
            break;
        }
        b=b->suivant;
    }

    return resultat;
}

