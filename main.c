#include <stdio.h>
#include <stdlib.h>
#include "bibliotheque_ListeChainee.h"


int main()
{
    Bibliotheque b;
    b=NULL;
    
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
