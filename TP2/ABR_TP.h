#ifndef ABR_TP_H
#define ABR_TP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


	/* Definitions */

/* Type de l'arbre binaire */
typedef int element;

typedef struct noeud {
		element valeur;
		struct noeud *gauche, *droit;
} NOEUD, *ABR;

	/* Prototypes de fonction */
NOEUD *arbre_vide(void);
NOEUD *insere(NOEUD *p, element x);
void affiche_arbre(NOEUD *p, int col);

void parcours_NGD(NOEUD *p); /* Parcours préfixe */
void parcours_GND(NOEUD *p); /* Parcours infixe */
void parcours_GDN(NOEUD *p); /* Parcours suffixe */

int nombre_de_feuilles(NOEUD *p);

int parcours(NOEUD *p, bool prefixe, bool infixe, bool suffixe);

void parcours_largeur(NOEUD *p);


#endif
