#ifndef _BIBLIOTHEQUE_LISTE_CHAINEE_H_
#define _BIBLIOTHEQUE_LISTE_CHAINEE_H_ 0


struct MaillonSt {
	char* isbn;
	char* titre;
	char* auteur;
	char* editeur;
	char* datePublication;
	struct MaillonSt* suivant;
};

typedef struct MaillonSt * Bibliotheque;

/**
* @description Cree une bibliotheque vide
*
* @return Une bibliotheque vide
*
* @pre Aucune
* @post Creation de la bibliotheque
* @invariant Aucun
*/
Bibliotheque creer_bibliotheque(void);

/**
* @description Insere un livre dans la bibliotheque
* @param (Biliotheque) b : Une bibliotheque
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
Bibliotheque inserer(Bibliotheque b, char* isbn, char* titre, char* auteur, char* editeur, char* datePublication);

/**
* @description Supprimer un livre de la bibliotheque
* @param (Biliotheque) b : Une bibliotheque
*		 (char*) isbn : Numero d'ISBN
* @return La nouvelle bibliotheque obtenue
*
* @pre Tous les param�tres existent.
* @post La bibliotheque sans le livre qui a ete supprime
* @invariant Aucun.
*/
Bibliotheque supprimer(Bibliotheque b, char* isbn);

/**
* @description Rechercher un livre dans la bibliotheque
* @param (Biliotheque) b : Une bibliotheque
*		 (char*) isbn : Numero d'ISBN
* @return Le livre et sa description
*
* @pre Tous les param�tres existent
* @post La bibliotheque existe
* @invariant La bibliotheque existe
*/
Bibliotheque rechercher_livre(Bibliotheque b, char* isbn);

/**
* @description Rechercher des livres par titre
* @param (Biliotheque) b : Une bibliotheque
*		 (char) prefixe : Chaine de caractere par lequel un titre peut commencer
* @return Les livres dont le titre commence par le prefixe specifie
*
* @pre Tous les param�tres existent
* @post La bibliotheque existe
* @invariant La bibliothque existe
*/
Bibliotheque rechercher_titre(Bibliotheque b, char* prefixe);

/**
* @description Vide et detruit la bibliotheque
* @param (Biliotheque) b : Une bibliotheque
*
* @pre La bibliotheque existe
* @post La bibliotheque est vide et memoire desallouee
* @invariant Aucun
*/
void detruire_bibliotheque(Bibliotheque b);

//------------------------------------------------------------
char* copier_chaine(char* chaine_a_copier);
void afficher_tout(Bibliotheque b);
void afficher(Bibliotheque b);
Bibliotheque liberer_memoire(Bibliotheque b);
int titre_deja_present(Bibliotheque b,char* titre);
int hachage(char* chaine);

#endif
