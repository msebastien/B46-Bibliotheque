#include <stdio.h>
#include <stdlib.h>

#include "bibliotheque_ListeChainee.h"

#define TAILLE_MAX 1000
#define TAILLE_CHAMPS 200

Bibliotheque genererBibliotheque(Bibliotheque b){
    b = NULL;
    FILE* fichier = NULL;
    fichier = fopen("B46_openlibrary_test.dat", "r+");
    char entree[TAILLE_MAX] = "";


    if (fichier != NULL)
    {
        while (fgets(entree, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            int i = 0, j = 0, k = 0, l = 0, m = 0;
            char isbn[TAILLE_CHAMPS];
            char titre[TAILLE_CHAMPS];
            char auteur[TAILLE_CHAMPS];
            char editeur[TAILLE_CHAMPS];
            char datePublication[TAILLE_CHAMPS];
            
            while(entree[i] != '|'){
                isbn[i] = entree[i];
                i++;
                isbn[i] = '\0';
            }
            i++;
            while(entree[i] != '|'){
                titre[j] = entree[i];
                j++;
                titre[j] = '\0';
                i++;
            }
            i++;
            while(entree[i] != '|'){
                auteur[k] = entree[i];
                k++;
                auteur[k] = '\0';
                i++;
            }
            i++;
            while(entree[i] != '|'){
                editeur[l] = entree[i];
                l++;
                editeur[l] = '\0';
                i++;
            }
            i++;
            while(entree[i] != '\0'){
                datePublication[m] = entree[i];
                m++;
                datePublication[m] = '\0';
                i++;
            }

            b = inserer(b, isbn, titre, auteur, editeur, datePublication);
             
        }
   
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier B46_openlibrary_test.dat\n");
    }
    
    
    fclose(fichier); // On ferme le fichier

    return b;
}

int main()
{
    Bibliotheque b;
    b=NULL;

    b = genererBibliotheque(b);
    
    // Test de inserer()
    printf("Test inserer\n");
    b=inserer(b,"123","Lotr","JRR","Cirdan","1954");
    b=inserer(b,"456","Silmarillon","Tolkien","Anfauglir","1937");
    afficher_tout(b);

    // Test de rechercher_livre()
    Bibliotheque b1;
    printf("Test rechercher_livre\n");
    b1 = rechercher_livre(b,"123");
    afficher(b1);

    // Test de rechercher_titre()
    Bibliotheque b2;
    printf("Test rechercher_titre\n");
    b2 = rechercher_titre(b, "Sil");
    afficher_tout(b2);

    // Test de supprimer()
    Bibliotheque b3;
    printf("Test supprimer\n");
    b3 = supprimer(b, "456");
    afficher_tout(b3);

    // Test detruire_bibliotheque()
    printf("Test detruire_bibliotheque\n");
    detruire_bibliotheque(b);
    b=NULL;
    afficher_tout(b);

    return 0;
}
