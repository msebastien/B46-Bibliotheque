#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "bibliotheque_ListeChainee.h"

/**
* @description Cree une bibliotheque vide
*
* @return Une bibliotheque vide
*
* @pre Aucune
* @post Creation de la bibliotheque
* @invariant Aucun
*/
Bibliotheque creer_bibliotheque(){
    return NULL;
}

/**
* @description Insere un livre dans la bibliotheque
* @param (Bibliotheque) b : Une bibliotheque
*		 (char*) isbn : Numero d'ISBN
*		 (char*) titre : titre du livre
*		 (char*) auteur : Le ou les auteurs du livre
*		 (char*) editeur : Le ou les editeurs du livre
*		 (char*) datePublication : La date de publication du livre
* @return La nouvelle bibliotheque obtenue
*
* @pre Tous les parametres existent
* @post La bibliotheque avec le livre ajoute
* @invariant La bibliotheque existe
*/
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

/**
* @description Rechercher un livre dans la bibliotheque
* @param (Bibliotheque) b : Une bibliotheque
*		 (char*) isbn : Numero d'ISBN
* @return Bibliotheque des livres trouves (liste chainee)
*
* @pre Tous les parametres existent
* @post La bibliotheque existe
* @invariant La bibliotheque existe
*/
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

/**
* @description Rechercher des livres par titre
* @param (Bibliotheque) b : Une bibliotheque
*		 (char) prefixe : Chaine de caractere par lequel un titre peut commencer
* @return Les livres dont le titre commence par le prefixe specifie
*
* @pre Tous les parametres existent
* @post La bibliotheque existe
* @invariant La bibliotheque existe
*/
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

/**
* @description Supprimer un livre de la bibliotheque
* @param (Bibliotheque) b : Une bibliotheque
*		 (char*) isbn : Numero d'ISBN
* @return La nouvelle bibliotheque obtenue
*
* @pre Tous les parametres existent.
* @post La bibliotheque sans le livre qui a ete supprime
* @invariant La bibliotheque existe
*/
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
    return debut; //on retourne le debut de chaine;
}

/**
* @description Vide et detruit la bibliotheque
* @param (Bibliotheque) b : Une bibliotheque
*
* @pre La bibliotheque existe
* @post La bibliotheque est vide et memoire desallouee
* @invariant Aucun.
*/
void detruire_bibliotheque(Bibliotheque b)
{
	if(b!=NULL)
    {
        Bibliotheque temporaire;
        while(b!=NULL)
        {
            temporaire=b->suivant;
            liberer_memoire(b);
            b=temporaire;
        }
    }
}

//------------------------------------------------------------------------------------------
// FONCTIONS ANNEXES
//------------------------------------------------------------------------------------------


/**
* @description Affiche l'integralite d'une liste chainee
* @param (Bibliotheque) b : Une bibliotheque
*
*/
void afficher_tout(Bibliotheque b)
{
    while(b != NULL){
        afficher(b);
        b = b->suivant;
    }

    if(b == NULL){
        afficher(b);
    }
}

/**
* @description Copie une chaine de caractere
* @param (char*) chaine_a_copier : Chaine de caractere a copier
* @return Retourne la copie de la chaine de caractere
*/
char* copier_chaine(char* chaine_a_copier)
{
    char* copie;

    copie=malloc(sizeof(char)*(strlen(chaine_a_copier)+1));
    strcpy(copie,chaine_a_copier);

    return copie;
}

/**
* @description Affiche un élément non-nul d'une liste chainee
* @param (Bibliotheque) b : Une bibliotheque
*
*/
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

/**
* @description Libère la mémoire allouee à une bibliotheque
* @param (Bibliotheque) b : Une bibliotheque
* @return Une bibliotheque vide
*/
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

/**
* @description Verifie si un titre est déjà présent dans une bibliotheque
* @param (char*) titre : Titre d'un livre
* @return un booleen (1 si le titre d'un livre existe dans la bibliotheque, 0 dans le cas contraire)
*/
int titre_deja_present(Bibliotheque b, char* titre)
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

