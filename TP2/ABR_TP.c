/*****************************************************************************/
/*   C. PORQUET                     ABR_TP.c                   Novembre 2012 */
/*                      Arbres binaires de recherche                         */
/*****************************************************************************/

#include "ABR_TP.h"
#include "file.h"

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

void parcours_NGD(NOEUD *p){ /* Parcours préfixe */
	parcours(p,true,false,false);
}
void parcours_GND(NOEUD *p){ /* Parcours infixe */
	parcours(p,false,true,false);
}
void parcours_GDN(NOEUD *p){ /* Parcours suffixe */
	parcours(p,false,false,true);
}

/*****************************************************************************/

/* Fonction générique du parcours : permet par l'utilisation de booléens de choisir la méthode de parcours de l'arbre binaire de recherche. */
int parcours(NOEUD *p, bool prefixe, bool infixe, bool suffixe){
		int nb = 0;
		if(p == NULL)
				return 0;

		if(prefixe) printf("%d ",p->valeur);
		nb += parcours(p->gauche,prefixe,infixe,suffixe);
		if(infixe) printf("%d ",p->valeur);
		nb += parcours(p->droit,prefixe,infixe,suffixe);
		if(suffixe) printf("%d ",p->valeur);

		return nb + 1;
}

/* Parcours en largeur : utilise les Files (file.c/h) */
void parcours_largeur(NOEUD *p) {	
		File f;
		NOEUD *node;

		f = enfiler(p, file_vide());
		while(!est_vide(f)) {
				node = defiler2(&f);
				printf("%d ",node->valeur);
				if(node->gauche)
						f = enfiler(node->gauche,f);
				if(node->droit)
						f = enfiler(node->droit,f);
		}


}
/* Retourne le nombre de feuilles d'un arbre. */
int nombre_de_feuilles(NOEUD *p){
		int nb = 0;
		if(p == NULL)
			return 0;

		nb = nombre_de_feuilles(p->gauche) + nombre_de_feuilles(p->droit);

		return nb + (p->gauche == NULL && p->droit == NULL);
}

/* Retourne les feuilles d'un arbre sous la forme d'une file (Appelé aussi "Bordure") */
File bordure(ABR a) {
	File fg,fd;
	fg = file_vide();
	fd = file_vide();

	if(a->gauche)
		fg = bordure(a->gauche);
	if(a->droit){
		fd = bordure(a->droit);
		concat(&fg,&fd);
	}
	if(a->gauche == NULL && a->droit == NULL)
		fg = enfiler(a,fg);

	return fg;
}

/****/

int main() {

		NOEUD *a[3]; /* on peut travailler sur 3 arbres */
		char c;
		int i = 0, j = 10;
		element x;
		File f;

	#ifdef TESTING
		for(i = 1; i < 4; i++, j--) {
			a[0] = insere(a[0],i);
			a[0] = insere(a[0],j);
			a[0] = insere(a[0],i+j);
			a[0] = insere(a[0],i-j);
		}
		affiche_arbre(a[0],1);
		printf("\nPréfixe : ");
	    parcours_NGD(a[0]); 
	    printf("\nInfixe : ");
	    parcours_GND(a[0]);
	    printf("\nSuffixe : ");
	    parcours_GDN(a[0]);
		printf("\nNombre de feuilles : %d",nombre_de_feuilles(a[0]));
		printf("\nParcours prefixe/suffixe :\n");
		parcours(a[0],true,false,true);
	
		printf("\nParcours en largeur : \n");
	    parcours_largeur(a[0]);	

		printf("\nBordure : \n");
		f = bordure(a[0]);

		for(i = 0; i < nombre_de_feuilles(a[0]); i++)
		{
			printf("\nFeuille n°%d : %d",i,defiler2(&f)->valeur);
		}
		printf("\n");

	#endif
	#ifndef TESTING
		do {
				printf("Commande ? "); 
				c = getchar();
				switch(c){
						case 'h' :
								   printf("\nAide : \n");
								   printf("v <nb> : Vider l'arbre <nb>\n");
								   printf("i <value> <nb> : Ajouter <value> à l'arbre <nb>\n");
								   printf("a <nb> : Afficher l'arbre <nb>\n");
								   printf("t <nb> : Parcourir l'arbre <nb> de 3 manières différentes\n");
								   printf("p <nb> <prefixe:1/0> <infixe:1/0> <suffixe:1/0> : Parcourir l'arbre <nb> en affichant les valeurs en lien avec les paramètres suivants.\n");
								   printf("l <nb> : Retourne le nombre de \"feuilles\" dans l'arbre <nb>.\n");
								   printf("w <nb> : Parcours en largeur de l'arbre <nb>\n");
								   printf("q : Quitter.\n");

								   break;
						case 'v' : scanf("%d",&i); a[i] = arbre_vide(); break;     
						case 'i' : scanf("%d %d",&x,&i); a[i] = insere(a[i],x); break;    
						case 'a' : scanf("%d",&i); affiche_arbre(a[i],1); break;           
						case 'q' : exit(0);
						case 't' : 
								   scanf("%d",&i);
								   printf("\nPréfixe : ");
								   parcours_NGD(a[i]); 
								   printf("\nInfixe : ");
								   parcours_GND(a[i]);
								   printf("\nSuffixe : ");
								   parcours_GDN(a[i]);
								   break;
						case 'p' : {
								   int prefixe,infixe,suffixe;
								   scanf("%d %d %d %d",&i,&prefixe,&infixe,&suffixe);
								   printf("Noeuds : %d",parcours(a[i],prefixe > 0,infixe > 0,suffixe > 0));
								   }
								   break;
						case 'l' :
								   scanf("%d",&i);
									printf("\nNombre de feuilles : %d",nombre_de_feuilles(a[i]));
								   break;
						case 'w' :
								   scanf("%d",&i);
								   parcours_largeur(a[i]);
								   break;
				}
				printf("\n");
				c = getchar();
		} while (1);
	#endif

}
/****************************************************************************/ 	


