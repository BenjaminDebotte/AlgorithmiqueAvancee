/* NOTE : voir Photo téléphone
 * OBJ : Ajouter un tableau qui tient compte du nombre de noeud prédécesseur dans T_LADJ.
 * */



/******************************************************************************/
/* C. PORQUET                    L_ADJ.c                            Mars 2004 */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "file.h"

typedef struct t_cellule{
    int extremite;
    float valuation;
    struct t_cellule *suivant;
} T_CELLULE;

typedef struct t_ladj	/* listes d'adjacence */{
    int nbsom, nbar;
    T_CELLULE **tab;
    int *previousNodeArray; /* Corélation index | nb de noeuds prédécesseurs  */
} T_LADJ;
/*----------------------------------------------------------------------------*/
T_CELLULE *creer_cellule(int extr, float val, T_CELLULE *suiv){
    T_CELLULE *p;

    p = (T_CELLULE *)malloc(sizeof(T_CELLULE));
    if (p == NULL) exit(-1);
    p->extremite = extr;p->valuation = val; p->suivant = suiv;
    return p;
}
/*----------------------------------------------------------------------------*/
void affiche_liste(T_CELLULE *p){
    while (p)
    {printf("<%5d - %5.1f>\t",p->extremite,p->valuation);
        p = p->suivant; };
    printf("\n");
}
/*----------------------------------------------------------------------------*/
T_LADJ init_ladj(int nsom, int nar) /* allocation dynamique et initialisation */{
    T_LADJ g;

    g.nbsom = nsom; g.nbar = nar;
    g.tab = (T_CELLULE **)calloc(nsom,sizeof(T_CELLULE *));
    if (g.tab == NULL) exit(-1);
    g.previousNodeArray = (int*)calloc(nsom,sizeof(int));
    if (g.previousNodeArray == NULL){
        free(g.tab);
        exit(-1);
    }
    return g;
}
/*----------------------------------------------------------------------------*/
void affiche_graphe(T_LADJ g){
    int i;

    for (i=0;i<g.nbsom;i++){
        if (g.tab[i]) {
            printf("Successeurs de %d : ",i);
            affiche_liste(g.tab[i]);
        }
    }
    printf("\n|");
    if(g.previousNodeArray){
        for(i = 0; i < g.nbsom; i++)
            printf(" %d |",i);
        printf("\n|");
        for(i = 0; i < g.nbsom; i++)
            printf(" %d |",g.previousNodeArray[i]);
    }
    printf("\n");
}
/*----------------------------------------------------------------------------*/
bool marquageTopologique(T_LADJ *g){
    if (g == NULL)
        return false;

    File fileTopo, fileSommet;
    int i;
    int tempSommet;
    bool topoPossible = true;

    fileTopo = file_vide();
    fileSommet = file_vide();

    while (size_file(fileTopo) != g->nbsom) {
        /* 1 - Recherche des sommets sans prédecesseurs */
        for (i = 0; i < g->nbsom; i++) {
            if (g->previousNodeArray[i] == 0) {
                fileSommet = enfiler(i, fileSommet);
            }
        }

        if (est_vide(fileSommet)) {
            topoPossible = false;
            break;
        }

        /* 2 - Reconstruction du graphe */


    }
    return true; /* UNFINISHED. */
}

    T_LADJ charge_graphe(char *nom_fichier){
        T_LADJ g;
        int nsom, nar;
        FILE *fp;
        int i, ori, ext;
        float val;
        T_CELLULE *p;

        fp = fopen(nom_fichier,"rt");
        if (fp == NULL) exit(-1);
        fscanf(fp,"%d %d",&nsom,&nar);
        g = init_ladj(nsom,nar);
        for (i=0;i<nar;i++){
            /* ori : valeur du noeud actuel
             * ext : valeur du noeud suivant
             * val : valuation */
            fscanf(fp,"%d %d %f",&ori,&ext,&val);
            p = creer_cellule(ext,val,g.tab[ori]);
            g.tab[ori] = p;  /* on empile */
        }
        for(i=0; i<nsom;i++){
            p = g.tab[i];
            while(p != NULL){
                g.previousNodeArray[p->extremite]++;
                p = p->suivant;
            }
        }

        fclose(fp);
        return g;
    }
    /*----------------------------------------------------------------------------*/
    T_LADJ inverse(T_LADJ g){
        T_LADJ g_inverse;
        int i;
        T_CELLULE *p, *q;

        g_inverse = init_ladj(g.nbsom,g.nbar);
        for (i=0; i<g.nbsom; i++)
        {p = g.tab[i];
            while (p)
            {q = creer_cellule(i,p->valuation,g_inverse.tab[p->extremite]);
                g_inverse.tab[p->extremite] = q; /* on empile */
                p = p->suivant;
            }
        }
        return g_inverse;
    }
    /******************************************************************************/
    int main(int argc, char **argv){
        T_LADJ g;
        /* T_LADJ g_inverse; */

        if (argc!=2){
            /* printf("\nUsage : ./GraphOri <file>.");
               exit(-1);
               */
            g = charge_graphe("graph_ex.txt");
        } else {
            g = charge_graphe(argv[1]);
        }
        affiche_graphe(g);
        marquageTopologique(&g);

        /* g_inverse = inverse(g);
           affiche_graphe(g_inverse); */

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

      Successeurs de 0 : <    1 -   3.0>
      Successeurs de 1 : <    4 -   1.0>      <    3 -   2.0> <    1 -   6.0>
      Successeurs de 3 : <    4 -   2.0>      <    0 -   2.0>
      Successeurs de 4 : <    3 -   7.0>
      Successeurs de 5 : <    2 -   1.0>

      Successeurs de 0 : <    3 -   2.0>
      Successeurs de 1 : <    1 -   6.0>      <    0 -   3.0>
      Successeurs de 2 : <    5 -   1.0>
      Successeurs de 3 : <    4 -   7.0>      <    1 -   2.0>
      Successeurs de 4 : <    3 -   2.0>      <    1 -   1.0>

     *******************************************************************************/
