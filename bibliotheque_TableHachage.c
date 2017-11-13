#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "bibliotheque_TableHachage.h"

unsigned int hachage(char* chaine){ // Hachage polynomial

    unsigned int h = 0, p=11111;
    double c = 42;
    
    // Etape 1 - hachage
    for (int i = 0 ; chaine[i] != '\0' ; i++)
    {
        h += (unsigned int) chaine[i] * (unsigned int)(pow(c, (double)i));
    }

    // Etape 2 - Compression pour avoir un nombre compris entre 0 et TAILLE_TABLE pour servir d'indice à la table
    return ((unsigned int)fabs(h) % p) % TAILLE_TABLE;
}

Bibliotheque creer_bibliotheque(){
    Bibliotheque b;
    
    b = malloc(sizeof(struct BibliothequeSt));
    
    b->taille = TAILLE_TABLE;
    b->table = malloc( sizeof(Liste) * b->taille);
  
    for(int i = 0; i<TAILLE_TABLE;i++){
        b->table[i] = NULL;
    }

    return b;
}

Bibliotheque inserer(Bibliotheque b, char* isbn, char* titre, char* auteur, char* editeur, char* datePublication){
        int indice = hachage(isbn);
        
        if(b != NULL){
            b->table[indice] = inserer_dans_liste(b->table[indice], isbn, titre, auteur, editeur, datePublication);
        }
    return b;
}

Bibliotheque rechercher_livre(Bibliotheque b, char* isbn){
    Bibliotheque resultat;
    resultat = creer_bibliotheque();
    
    if(b != NULL){
        unsigned int indice = hachage(isbn);

        resultat->table[indice] = rechercher_livre_dans_liste(b->table[indice], isbn);
    }

    return resultat;
}

Bibliotheque rechercher_titre(Bibliotheque b, char* prefixe){
    Bibliotheque resultat;
    int i;
    resultat = creer_bibliotheque();

    if(b != NULL && prefixe != NULL){
        for( i =0; i<b->taille; i++){ // On se déplace dans la bibliothèque
            if(b->table[i]!=NULL)
            {
                resultat->table[i] = supprimer_doublon(resultat,rechercher_titre_dans_liste(b->table[i], prefixe));

            }
        }

    }
    return resultat;
}

Bibliotheque supprimer(Bibliotheque b, char* isbn){
    unsigned int h = hachage(isbn);
    if(b!=NULL){
        b->table[h]=supprimer_dans_liste(b->table[h],isbn);
    }
    return b;
}

void detruire_bibliotheque(Bibliotheque b)
{
    if(b!=NULL)
    {
        for(int i=0;i < b->taille;i++)
        {
            detruire_Liste(b->table[i]);//on supprime chaque liste
            b->table[i]=NULL;

        }
        //on supprime le tableau
        free(b->table);

        //ensuite on supprime le pointeur sur notre structure de hachage
        free(b);
    }
}

//------------------------------------------------------------------------------------------
// FONCTIONS ANNEXES + REUTILISATION FONCTIONS LISTES CHAINEES
//------------------------------------------------------------------------------------------

Liste supprimer_dans_liste(Liste l, char* isbn)
{
    Liste debut;
    debut=l;
    if(l!=NULL) //si la chaine n'est pas deja vide
    {
        if(strcmp(l->isbn,isbn)==0) //si l'element a supprimer est en premiere position et la chaine est pas vide
        {

            Liste sauvegardeTemporaire;
            sauvegardeTemporaire=l->suivant; //on enregistre ce vers quoi pointe le maillon a supprimer
            liberer_memoire(l); //on libere le maillon a suppr
            l=sauvegardeTemporaire;
            debut=l;
        }
        else
        {
            while(l->suivant!=NULL)//on cherche jusqu'au bout de la chaine
            {
                if(strcmp(l->suivant->isbn,isbn)==0)//si on tombe sur le maillon a supprimer
                {
                    Liste sauvegardeTemporaire;
                    sauvegardeTemporaire=l->suivant->suivant;//on enregistre ce vers quoi pointe le maillon a supprimer
                    liberer_memoire(l->suivant);//on libere le maillon a suppr
                    l->suivant=sauvegardeTemporaire;//on raccorde le maillon precedent vers ce quoi pointait le maillon supprime
                    break;
                }
                l=l->suivant;
            }
        }
    }
    return debut;//on retourne le debut de chaine;
}

Liste supprimer_doublon(Bibliotheque b, Liste l)
{
    Liste debut=l;
        if(b!=NULL)
    {
        while(l!=NULL)//on parcourt notre liste dans laquelle il y a des titres uniques
        {
            int i;
            for(i=0;i<b->taille;i++)//on verifie que notre table de hachage ne contient pas le titre actuel de la liste
            {
                if(titre_deja_present_dans_liste(b->table[i],l->titre))//si il le contient deja on coupe le for et on supprime
                {
                    debut=supprimer_dans_liste(debut,l->isbn);
                }
            }
            l=l->suivant;
        }
    }
    return debut;
}

Liste rechercher_titre_dans_liste(Liste l, char* prefixe){
    Liste resultat;
    resultat=NULL;

    if(prefixe!=NULL)//on verifie l'existence du titre
    {
        while(l!=NULL)//tant que b n'est pas vide et que le recherché ne correspond pas au livre actuel
        {
            if(strncmp(l->titre, prefixe, strlen(prefixe)*sizeof(char)) == 0 && !titre_deja_present_dans_liste(resultat,l->titre))
                // si le prefixe est le meme et que le titre n'existe pas deja dans notre selection
            {
                resultat=inserer_dans_liste(resultat,l->isbn,l->titre,l->auteur,l->editeur,l->datePublication);
            }
            l=l->suivant;
        }
    }

    return resultat;
}

Liste inserer_dans_liste(Liste l, char* isbn, char* titre, char* auteur, char* editeur, char* datePublication){
    //creation du maillon a inserer
    Liste nouveau_maillon;
    nouveau_maillon=malloc(sizeof(struct MaillonSt));
    
    //initialisation de ses champs
    nouveau_maillon->isbn = copier_chaine(isbn);
    nouveau_maillon->titre = copier_chaine(titre);
    nouveau_maillon->auteur = copier_chaine(auteur);
    nouveau_maillon->editeur = copier_chaine(editeur);
    nouveau_maillon->datePublication = copier_chaine(datePublication);
    nouveau_maillon->suivant = NULL;

    if(l != NULL)//insertion en tete de liste
    {

        nouveau_maillon->suivant = l;
    }

    return nouveau_maillon;//on retourne le debut de la liste chainee

}

void detruire_Liste(Liste l){
    if(l!=NULL)
    {
        Liste temporaire;
        while(l!=NULL)
        {
            temporaire=l->suivant;
            liberer_memoire(l);
            l=temporaire;
            
        }
    }
}

Liste rechercher_livre_dans_liste(Liste l, char* isbn)
{
    if(isbn!=NULL)//on verifie l'existence de l'isbn
    {
        while(l!=NULL && strcmp(l->isbn,isbn)!=0)//tant que b n'est pas vide et que l'isbn recherche ne correspond pas au livre actuel
        {
            l=l->suivant;
        }
    }
    else
    {
        l=NULL; //si isbn existe pas, il n'y a pas de livre correspondant
    }

    return l;

}

char* copier_chaine(char* chaine_a_copier)
{
    char* copie;

    copie=malloc(sizeof(char)*(strlen(chaine_a_copier)+1));
    strcpy(copie,chaine_a_copier);

    return copie;
}

void afficher_tout(Bibliotheque b){
    if(b != NULL){
        for(int i=0; i < b->taille; i++){
            printf("==CASE %d==\n", i);
            afficherListe_tout(b->table[i]);
        }
    }else{
        printf("NULL\n");
    }
}

void afficher(Bibliotheque b){
    if(b != NULL)
    {
        for(int i=0; i < b->taille; i++)
        {
            if(b->table[i] != NULL)
            {
                printf("==CASE %d==\n", i);
                afficherListe_tout(b->table[i]);
            } 
        }
    }else{
        printf("NULL\n");
    }
    
}

void afficherListe_tout(Liste l)
{
    if(l!=NULL)
    {
        afficherListeElement(l);
        afficherListe_tout(l->suivant);
    }
    else
    {
        afficherListeElement(l);
    }
}

void afficherListeElement(Liste l)
{
    if(l!=NULL)
    {
        printf("ISBN:%s\n\tTITRE:%s\n\tAUTEUR:%s\n\tEDITEUR:%s\n\tDATE PUBLICATION:%s\n",
               l->isbn,l->titre,l->auteur,l->editeur,l->datePublication);
    }
    else{
        printf("\nNULL\n");
    }
}

Liste liberer_memoire(Liste l)
{
    if(l!=NULL)
    {
        free(l->isbn);
        free(l->titre);
        free(l->auteur);
        free(l->datePublication);
        free(l->editeur);
        free(l);
    }
    return NULL;
}

int titre_deja_present_dans_liste(Liste l, char* titre){
    int resultat=0;

    while(l!=NULL)
    {


        if(strcmp(titre,l->titre)==0)//si le titre est le meme que le livre actuel
        {
            resultat=1;
            break;
        }
        l=l->suivant;
    }

    return resultat;
}

int titre_deja_present(Bibliotheque b,char* titre){ //savoir si le titre est deja inclus dans la table
    int deja_present=0;
    if(b!=NULL)
    {
        for(int i=0;i < b->taille;i++)
        {
            if(titre_deja_present_dans_liste(b->table[i],titre))
            {
                deja_present=1;
                break;
            }
        }
    }
    return deja_present;
}

