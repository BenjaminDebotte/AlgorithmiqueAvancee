/*****************************************************************************/
/*   C. PORQUET                     ABR_TP.c                   Novembre 2012 */
/*                      Arbres binaires de recherche                         */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct noeud {
		element valeur;
		struct noeud *gauche, *droit;
} NOEUD, *ABR;


/*****************************************************************************/
NOEUD *arbre_vide() {return NULL; }
/*****************************************************************************/
NOEUD *insere(NOEUD *p, element x){
		if (p == NULL) {
			p = (NOEUD *)malloc(sizeof(NOEUD));
			p->valeur = x;
			p->gauche = NULL;
			p->droit = NULL;
		}
		else if (x == p->valeur) 
			printf("%d est deja dans l'arbre\n",x);
		else if (x < p->valeur)  
			p->gauche = insere(p->gauche,x);
		else 
			p->droit  = insere(p->droit,x);

		return(p);			  
}
/*****************************************************************************/
void affiche_arbre(NOEUD *p, int col){
		int i;
		if (p) {
			affiche_arbre(p->droit,col+1);
			for (i=0;i<col;i++) printf("   ");
			printf("%d\n",p->valeur);
			affiche_arbre(p->gauche,col+1);
		}  	
}
/*****************************************************************************/
int main() {

		NOEUD *a[3]; /* on peut travailler sur 3 arbres */
		char c;
		int i, j;
		element x;
		char nom_fich[20];
		FILE *fich;

		do {
			printf("Commande ? "); 
			c = getchar();
			switch(c){
				case 'v' : scanf("%d",&i); a[i] = arbre_vide(); break;     
				case 'i' : scanf("%d %d",&x,&i); a[i] = insere(a[i],x); break;    
				case 'a' : scanf("%d",&i); affiche_arbre(a[i],1); break;           
				case 'q' : exit(0); 
			}
			printf("\n");
			c = getchar();
		} while (1);
}
/****************************************************************************/ 	


