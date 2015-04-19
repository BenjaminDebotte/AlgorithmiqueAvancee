#include <stdio.h>
#include <stdlib.h>
#include "file.h"

typedef struct t_cellule {
    int extremite;
    struct t_cellule *suivant;
} T_CELLULE; /* Cellule */

typedef struct t_ladj	{
    int nbsom, nbar;
    char ** nodeName;
    int *date_tot,*date_tard,*duree,*previousNodeArray;
    T_CELLULE **tabPred,**tabSuc,**ordreTopo;
} T_LADJ; /* listes d'adjacence */
/*----------------------------------------------------------------------------*/
T_CELLULE *creer_cellule(int extr,T_CELLULE *suiv){
    T_CELLULE *p;

    p = (T_CELLULE *)malloc(sizeof(T_CELLULE));
    if (p == NULL) exit(-1);
    p->extremite = extr;
    p->suivant = suiv;
    return p;
}
/*----------------------------------------------------------------------------*/
void affiche_liste(T_CELLULE *p){
    while (p){
        printf("< %d > ",p->extremite);
        p = p->suivant;
    };
    printf("\n");
}
/*----------------------------------------------------------------------------*/
T_LADJ init_ladj(int nsom, int nar){
    T_LADJ g;

    g.nbar = nar;
    g.nbsom = nsom;
    g.tabSuc = (T_CELLULE **)calloc(nsom,sizeof(T_CELLULE *));
    g.tabPred = (T_CELLULE **)calloc(nsom,sizeof(T_CELLULE *));
    g.ordreTopo = (T_CELLULE **)calloc(1,sizeof(T_CELLULE *));
    g.nodeName = (char **)calloc(nsom,sizeof(char *));
    g.date_tard = (int*)calloc(nsom,sizeof(int));
    g.date_tot = (int*)calloc(nsom,sizeof(int));
    g.previousNodeArray =  (int*)calloc(nsom,sizeof(int));
    g.duree = (int*)calloc(nsom,sizeof(int));
    if (g.tabSuc == NULL ) exit(-1);
    return g;
}
/*----------------------------------------------------------------------------*/
void affiche_graphe(T_LADJ g){
    int i;

    for (i=0; i<g.nbsom; i++){
        printf("Numero : %d - Nom : %s - Duree: %d \n",i,g.nodeName[i],g.duree[i]);
        if (g.tabSuc[i]){
            printf("[Successeurs de %d] ",i);
            affiche_liste(g.tabSuc[i]);
        }
        if (g.tabPred[i]){
            printf("[Prédecesseurs de %d] ",i);
            affiche_liste(g.tabPred[i]);
        }

    }
    printf("\n\n");
}
/*----------------------------------------------------------------------------*/
T_LADJ inverse(T_LADJ g){
    T_LADJ g_inverse;
    int i;
    T_CELLULE *p, *q;

    g_inverse = init_ladj(g.nbsom,g.nbar);
    for (i=0; i<g.nbsom; i++){
        p = g.tabSuc[i];
        while (p){
            q = creer_cellule(i,g_inverse.tabSuc[p->extremite]);
            g_inverse.tabSuc[p->extremite] = q; /* on empile */
            p = p->suivant;
        }
    }
    return g_inverse;
}
/*----------------------------------------------------------------------------*/
void marquageTopologique(T_LADJ g){
    int i,iOrder = 0;
    File f = file_vide();
    T_CELLULE *currentCell = NULL;


    for(i = 0; i<g.nbsom; i++){
        if(g.previousNodeArray[i] == 0){
            f = enfiler(i,f);
        }
    }

    while(!est_vide(f)){
        currentCell = g.tabSuc[tete(f)];
        g.ordreTopo[iOrder] = creer_cellule(tete(f),currentCell);
        iOrder++;
        f = defiler(f);
        while(currentCell){
            g.previousNodeArray[currentCell->extremite]--;
            if(g.previousNodeArray[currentCell->extremite]==0)
                f = enfiler(currentCell->extremite,f);
            currentCell = currentCell->suivant;
        }

    }
}


T_LADJ charge_graphe(char *filename){
    T_LADJ g;
    int nsom, nar;
    FILE *fp;
    int i, ori, ext,numSommet,duree;
    char* nom;
    T_CELLULE *p,*q;

    fp = fopen(filename,"rt");
    if (fp == NULL) exit(-1);
    fscanf(fp,"%d %d",&nsom,&nar);
    g = init_ladj(nsom,nar);

    for (i=0; i<nar; i++){
        fscanf(fp,"%d %d",&ori,&ext);
        p = creer_cellule(ext,g.tabSuc[ori]);
        q = creer_cellule(ori,g.tabPred[ext]);
        g.previousNodeArray[ext]++;
        g.tabSuc[ori] = p;  /*Successeur*/
        g.tabPred[ext] = q; /*Predecesseur*/
    }
    for (i=0; i<nsom; i++){
        nom = calloc(10,sizeof(char));
        fscanf(fp,"%d %d %s",&numSommet,&duree,nom);
        g.duree[numSommet]=duree;
        g.nodeName[numSommet]=nom;
    }
    fclose(fp);
    return g;
}


void dateTot(T_LADJ g){
    int i,tmpDate;
    T_CELLULE *sommet,*tmp;

    marquageTopologique(g);

    for(i=0;i<g.nbsom;i++){
        tmpDate = 0;
        sommet = g.ordreTopo[i];
        if(g.tabPred[i] == NULL){
            g.date_tot[i] = 0;
        }
        else{
            tmp = g.tabPred[i];
            while(tmp){
                if(tmpDate<g.date_tot[tmp->extremite] + g.duree[tmp->extremite]){
                    tmpDate = g.date_tot[tmp->extremite] + g.duree[tmp->extremite];
                }
                tmp = tmp->suivant;
            }
            g.date_tot[i] = tmpDate;
        }
    }
}
/*----------------------------------------------------------------------------*/
void dateTard(T_LADJ g){
    int i,tmpDate;
    T_CELLULE *sommet,*tmp;

    marquageTopologique(g);

    for(i=g.nbsom-1;i>=0;i--){
        sommet = g.ordreTopo[i];
        if(g.tabSuc[i] == NULL){
            g.date_tard[i] = g.date_tot[i];
        }
        else{
            tmpDate = g.date_tard[g.nbsom-1];
            tmp = g.tabSuc[i];
            while(tmp){
                if(tmpDate > g.date_tard[tmp->extremite] - g.duree[i]){
                    tmpDate = g.date_tard[tmp->extremite] - g.duree[i];
                }
                tmp = tmp->suivant;
            }
            g.date_tard[i] = tmpDate;
        }
    }
}


int main(int argc, char **argv)
{
    T_LADJ  g;
    int i;
    g = charge_graphe("mpm.txt");
    affiche_graphe(g);

    marquageTopologique(g);
    dateTot(g);
    dateTard(g);

    for(i=0;i<g.nbsom;i++)
    {
        printf("\n-----------------------------");
        printf("\nSommet %d ( %s ) ",g.ordreTopo[i]->extremite,g.nodeName[g.ordreTopo[i]->extremite]);
        printf("\nDate tot: %d, Date tard : %d \n",g.date_tot[i],g.date_tard[i]);
        printf("Marge: %d \n",g.date_tard[i]-g.date_tot[i]);
        if(g.date_tard[i]-g.date_tot[i] == 0)
            printf("\t/!\\ Tache critique /!\\\n");
    }

    printf("\n\nFin des tâches : %d \n\n",g.date_tot[g.nbsom-1]);



    return 0;
}
