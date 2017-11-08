#include <stdio.h>
#include <stdlib.h>
#include "headers/bibliotheque_ListeChainee.h"

int main()
{
    Bibliotheque b;
    b=NULL;
    printf("Test inserer\n");
    b=inserer(b,"123","Lotr","JRR","Cirdan","1954");
    b=inserer(b,"456","Silmarillon","Tolkien","Anfauglir","1937");
    afficher_tout(b);

    Bibliotheque b1;
    printf("Test rechercher\n");

    b1=rechercher_livre(b,"123");
    afficher(b1);

    printf("Test detruire\n");
    detruire_bibliotheque(b);
    b=NULL;
    afficher_tout(b);

    return 0;
}
