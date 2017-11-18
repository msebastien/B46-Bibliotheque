#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bibliotheque_ArbreBinaire.h"



/**
* @description Cree une bibliotheque vide
*
* @return Une bibliotheque vide
*
* @pre Aucune
* @post Creation de la bibliotheque
* @invariant Aucun
*/
Bibliotheque creer_bibliotheque()
{
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
    Bibliotheque nouveau_maillon;
    nouveau_maillon=b;

    if(b==NULL)//on a atteint un bout de l'arbre
    {
        nouveau_maillon=malloc(sizeof(struct BibliothequeSt));//creation d'un nouveau noeud

        //initialisation des champs
        nouveau_maillon->isbn=copier_chaine(isbn);
        nouveau_maillon->titre=copier_chaine(titre);
        nouveau_maillon->auteur=copier_chaine(auteur);
        nouveau_maillon->editeur=copier_chaine(editeur);
        nouveau_maillon->datePublication=copier_chaine(datePublication);

        //initialisation des pointeurs
        nouveau_maillon->fils_gauche=NULL;
        nouveau_maillon->fils_droit=NULL;
        b = nouveau_maillon;
    }
    else if(strcmp(isbn,b->isbn)<0)//si (nouveau_maillon->isbn) < (b->isbn)
    {
        //il faut inserer ce noeud a gauche car celui-ci est plus petit que le noeud actuel
        b->fils_gauche = inserer(b->fils_gauche,isbn,titre,auteur,editeur,datePublication);
    }
    else
    {
        b->fils_droit = inserer(b->fils_droit,isbn,titre,auteur,editeur,datePublication);
    }

    return nouveau_maillon;
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
Bibliotheque supprimer(Bibliotheque b,char* isbn)
{
    Bibliotheque resultat=b;

    if(b==NULL)//on est arrive au bout sans avoir trouve le livre a suppr
    {
        resultat=b;
    }
    else if(strcmp(b->isbn,isbn)==0)//on tombe sur le livre a suppr
    {
        if(b->fils_gauche==NULL&&b->fils_droit==NULL)//si c'est une feuille
        {
            resultat=liberer_memoire(b);//on supprime notre noeud et on retourne NULL pour indiquer au precedent que c'est une feuille
        }
        else if(b->fils_gauche!=NULL&&b->fils_droit==NULL)//si le noeud a suppr n'a qu'un seul fils a gauche
        {
            resultat=b->fils_gauche;//on renvoie au maillon precedent le maillon juste apres celui a suppr
            liberer_memoire(b);
        }
        else if(b->fils_droit!=NULL&&b->fils_gauche==NULL)//si le noeud n' a qu'un soeul fils a droite
        {
            resultat=b->fils_droit;
            liberer_memoire(b);
        }
        else// si il y a 2 fils en dessous du noeud a suppr
        {
            Bibliotheque max_a_gauche=chercher_max(b->fils_gauche);//on recupere un pointeur sur notre noeud qui va remplacer celui a suppr

            Bibliotheque maillon_raccord=NULL;
            maillon_raccord=copier_maillon(max_a_gauche,maillon_raccord);//on copie le max de l'abre a gauche dans le maillon raccord

            //vu qu'on a copie le maillon, on peut le supprimer dans notre fils gauche
            //on peut rappeler la fonction supprimer car elle va forcement renvoyer vers un des precedents if
            //etant donne que le max_a_gauche est forcement une feuille ou avec un seul fils
            supprimer(b->fils_gauche,max_a_gauche->isbn); 

            maillon_raccord->fils_gauche=b->fils_gauche;
            maillon_raccord->fils_droit=b->fils_droit;

            liberer_memoire(b);

            resultat=maillon_raccord;
        }
    }

    else
    {
        b->fils_droit=supprimer(b->fils_droit,isbn);
        b->fils_gauche=supprimer(b->fils_gauche,isbn);
    }

    return resultat;
}


/**
* @description Rechercher un livre dans la bibliotheque
* @param (Bibliotheque) b : Une bibliotheque
*		 (char*) isbn : Numero d'ISBN
* @return Le livre et sa description
*
* @pre Tous les parametres existent
* @post La bibliotheque existe
* @invariant La bibliotheque existe
*/
Bibliotheque rechercher_livre(Bibliotheque b, char* isbn)
{
    if(b!=NULL)
    {
        if(strcmp(b->isbn,isbn)>0)//b->isbn > isbn
        {
            b=rechercher_livre(b->fils_gauche,isbn);
        }
        else if(strcmp(b->isbn,isbn)<0)
        {
            b=rechercher_livre(b->fils_droit,isbn);
        }else{
            Bibliotheque a = NULL;
            b=copier_maillon(b, a);
        }
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
    Bibliotheque resultat=NULL;

    if(b!=NULL)
    {
        //on effectue la recherche dans les enfants on insere cette recherche dans notre arbre de resultat
        //et on supprime dans l'arbre a inserer les titres deja present dans resultat
        resultat=inserer_arbre(resultat,rechercher_titre(b->fils_droit,prefixe));
        resultat=inserer_arbre(resultat,supprimer_doublon(rechercher_titre(b->fils_gauche,prefixe),resultat));
        
        if(strncmp(b->titre,prefixe,sizeof(char)*strlen(prefixe))==0&&!titre_deja_present(resultat,b->titre))
        {//si le titre actuel a le prefixe et qu'il n'est pas deja dans notre recensement des titres
            resultat=inserer_un_maillon(resultat,b);//on cree un arbre avec un seul maillon qui contient le titre correspondant
        }
    }
    else
    {
        resultat=NULL;
    }

    return resultat;
}

Bibliotheque supprimer_doublon(Bibliotheque auxiliaire,Bibliotheque originale)
{
    Bibliotheque resultat=auxiliaire;
    if(auxiliaire!=NULL&&originale!=NULL)
    {
        resultat->fils_gauche=supprimer_doublon(auxiliaire->fils_gauche,originale);//on parcourt notre arbre auxiliaire
        resultat->fils_droit=supprimer_doublon(auxiliaire->fils_droit,originale);
        if(titre_deja_present(originale,resultat->titre))//on regarde si le noeud actuel est deja présent dans arbre original
        {
            //si oui on le supprime dans notre arbre auxiliaire
            resultat=supprimer(resultat,resultat->isbn);
        }
    }

    return resultat;
}

void detruire_bibliotheque(Bibliotheque b)

{

    if(b!=NULL)

    {

        detruire_bibliotheque(b->fils_gauche);

        detruire_bibliotheque(b->fils_droit);

        liberer_memoire(b);

    }

}


//------------------------------------------------------------------------------------------
// FONCTIONS ANNEXES
//------------------------------------------------------------------------------------------


/**
* @description Affiche l'integralite d'un arbre binaire de recherche
* @param (Bibliotheque) b : Une bibliotheque
*
*/
void afficher_tout(Bibliotheque b)
{
    if(b!=NULL)
    {
        afficher(b);

        printf("\nfils_gauche\n>>>\n");
        afficher_tout(b->fils_gauche);
        printf("\n<<<\n");

        printf("\nfils_droit\n>>>");
        afficher_tout(b->fils_droit);
        printf("\n<<<\n");
    }
    else
    {
        afficher(b);
    }
}


/**
* @description Affiche un élément non-nul d'un arbre bianire de recherche
* @param (Bibliotheque) b : Une bibliotheque
*
*/
void afficher(Bibliotheque b)
{
    if(b!=NULL)
    {
        printf("isbn:%s\n\ttitre:%s\n\tauteur:%s\n\tediteur:%s\n\tdate de publication:%s\n",
               b->isbn,b->titre,b->auteur,b->editeur,b->datePublication);
    }
    else{
        //printf("NULL");
    }
}


/**
* @description Libère la mémoire allouee à une bibliotheque
* @param (Bibliotheque) b : Une bibliotheque
* @return Une bibliotheque vide
*/
Bibliotheque liberer_memoire(Bibliotheque b)
{
    if (b!=NULL)
    {
        free(b->isbn);
        free(b->titre);
        free(b->auteur);
        free(b->editeur);
        free(b->datePublication);
        free(b);

        b=NULL;
    }
    return b;
}



/**
* @description Insère un arbre (maillon + fils gauche et fils droit)
* @param (Bibliotheque) b : Une bibliotheque
*		 (Bibliotheque) a_inserer : Arbre à inserer
* @return La nouvelle bibliotheque obtenue
*/
Bibliotheque inserer_arbre(Bibliotheque b,Bibliotheque a_inserer)
{
    if(a_inserer!=NULL)
    {
        b=inserer_un_maillon(b,a_inserer);
        b=inserer_arbre(b,a_inserer->fils_gauche);
        b=inserer_arbre(b,a_inserer->fils_droit);
    }

    return b;
}

/**
* @description Verifie si un titre est déjà présent dans une bibliotheque
* @param (char*) titre : Titre d'un livre
* @return un booleen (1 si le titre d'un livre existe dans la bibliotheque, 0 dans le cas contraire)
*/
int titre_deja_present(Bibliotheque b,char* titre)
{
    int resultat;

    if(b==NULL)
    {
        resultat=0;
    }
    else if(strcmp(titre,b->titre)==0) //s'il y a le titre
    {
        resultat=1; //oui il y a deja le titre
    }
    else
    {
        int droit=titre_deja_present(b->fils_gauche,titre);//on regarde si il y a le titre recherche a gauche
        int gauche=titre_deja_present(b->fils_droit,titre);//ou a droite

        if(droit||gauche)// si le titre est present a droite ou a gauche
        {
            resultat=1;
        }
        else
        {
            resultat=0;
        }

    }
    return resultat;
}


/**
* @description Insère un maillon dans un arbre
* @param (Bibliotheque) b : Une bibliotheque
*		 (Bibliotheque) a_inserer : Arbre à inserer
* @return La nouvelle bibliotheque obtenue
*/
Bibliotheque inserer_un_maillon(Bibliotheque b, Bibliotheque a_inserer)
{
    if(a_inserer!=NULL)
    {
        b=inserer(b,a_inserer->isbn,a_inserer->titre,a_inserer->auteur,a_inserer->editeur,a_inserer->datePublication);
    }

    return b;
}



/**
* @description Copie les valeurs d'un noeud d'un arbre
* @param (Bibliotheque) b : Bibliotheque du maillon a copier
*		 (Bibliotheque) copie : Bibliotheque contenant la copie du maillon
* @return La nouvelle bibliotheque obtenue
*/
Bibliotheque copier_maillon(Bibliotheque a_copier, Bibliotheque copie)
{
    if(a_copier!=NULL&&copie==NULL)//on copie dans un nouveau noeud on ecrase pas de noeud
    {
        copie=malloc(sizeof(struct BibliothequeSt));
        
        copie->isbn=copier_chaine(a_copier->isbn);
        copie->titre=copier_chaine(a_copier->titre);
        copie->auteur=copier_chaine(a_copier->auteur);
        copie->editeur=copier_chaine(a_copier->editeur);
        copie->datePublication=copier_chaine(a_copier->datePublication);
        copie->fils_gauche=NULL;
        copie->fils_droit=NULL;
    }

    return copie;
}



/**
* @description Cherche le noeud avec la valeur maximum
* @param (Bibliotheque) b : Bibliotheque
* @return Retourne le noeud avec le plus grand isbn contenu dans la bibliotheque
*/
Bibliotheque chercher_max(Bibliotheque b)
{
    Bibliotheque resultat;

    if(b==NULL||b->fils_droit==NULL)//si on est sur le dernier noeud a droite
    {
        resultat=b;//on renvoie le noeud actuel;
    }
    else
    {
        resultat=chercher_max(b->fils_droit);
    }

    return resultat;
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

