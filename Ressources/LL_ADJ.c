/******************************************************************************/
/* C. PORQUET                    LL_ADJ.c                           Mars 2004 */
/* Stratégie : les sommets sont empilés dans la liste des sommets,            */ 
/*             les arcs sont empilés dans leur liste de successeurs           */
/* On accède au graphe par un pointeur sur la liste des sommets               */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct Cell_arc;

typedef struct Cell_som {int sommet;
                         struct Cell_arc *psucc;
                         struct Cell_som *suivant; } cell_som;


typedef struct Cell_arc {cell_som *pextrem;
                         float valuation;
                         struct Cell_arc *suivant; } cell_arc;

/*----------------------------------------------------------------------------*/	
cell_som *creer_sommet(int som, cell_som *suiv)
{cell_som *p;
 
 p = (cell_som *)malloc(sizeof(cell_som));
 if (p == NULL) exit(-1);
 p->sommet = som; p->psucc = NULL; p->suivant = suiv;
 return p;}
/*----------------------------------------------------------------------------*/	
cell_arc *creer_arc(float val, cell_arc *suiv, cell_som *pext)
{cell_arc *p;
 
 p = (cell_arc *)malloc(sizeof(cell_arc));
 if (p == NULL) exit(-1);
 p->valuation = val; p->pextrem = pext; p->suivant = suiv;
 return p;}
/*----------------------------------------------------------------------------*/
void affiche_successeurs(cell_arc *psuc)
{cell_arc *p;
 p = psuc;
 while (p) 
       {printf("<%d-%f>\t",p->pextrem->sommet,p->valuation);
        p = p->suivant; };
 printf("\n"); }
/*----------------------------------------------------------------------------*/		
void affiche_graphe(cell_som *graphe)
{cell_som *p;
 p = graphe;
 while (p)
       {printf("Successeurs de %d : ",p->sommet);
        affiche_successeurs(p->psucc);
	p = p->suivant;
       }
 printf("\n"); }
/*----------------------------------------------------------------------------*/
cell_som *cherche(int som, cell_som *graphe)
/* recherche d'un sommet dans la liste des sommets */
{cell_som *p;
 p = graphe;
 while (p) if (p->sommet == som) return p;
           else p = p->suivant;

 return NULL; }
/*----------------------------------------------------------------------------*/
cell_som *charge_graphe(char *nom_fichier)
{cell_som *graphe, *pori, *pext; 
 cell_arc *parc;             
 int nsom, narc;
 FILE *fp;
 int i, ori, ext;
 float val;
  
 fp = fopen(nom_fichier,"rt");
 if (fp == NULL) exit(-1);
 fscanf(fp,"%d %d",&nsom,&narc);
 graphe = NULL;
 for (i=0;i<narc;i++)
     {fscanf(fp,"%d %d %f",&ori,&ext,&val);
      pori = cherche(ori,graphe); 
      if (!pori) 
         {pori = creer_sommet(ori,graphe); graphe = pori; } /* on empile */
      pext = cherche(ext,graphe);
      if (!pext) 
         {pext = creer_sommet(ext,graphe); graphe = pext; } /* on empile */
      parc = creer_arc(val,pori->psucc,pext); 
      pori->psucc = parc; /* on empile */
     }  
 fclose(fp);
 return graphe; }
/******************************************************************************/
main(int argc, char **argv)
{cell_som *graphe;
 
 if (argc!=2) exit(-1);
 
 graphe = charge_graphe(argv[1]);
 affiche_graphe(graphe);
 
}
/*******************************************************************************
Trace d'execution sur le fichier :
6
8
0 1 3
1 1 6
1 3 2
1 4 1
3 0 2
3 4 2
4 3 7
5 2 1

Successeurs de 2 : 
Successeurs de 5 : <2-1.000000>
Successeurs de 4 : <3-7.000000>
Successeurs de 3 : <4-2.000000> <0-2.000000>
Successeurs de 1 : <4-1.000000> <3-2.000000>    <1-6.000000>
Successeurs de 0 : <1-3.000000>
	
*******************************************************************************/

