/*****************************************************************************/
/* C.PORQUET                 genere_graphe_0.c                 Décembre 2007 */
/*                     Générateur automatique de graphes                     */
/*                  Les sommets sont numérotés à partir de 0                 */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "file.h"

/* Variables pour les parcours. */
#define UNVISITED   0
#define PENDING     1
#define VISITED     2

#define MAXSOMMET 	250
#define MAXVALUATION 	20.0
#define MAXSUCC		10

typedef struct {
    int *composantes_connexes;
    int nbComposantes;
} compo_connexes_str_t;

typedef struct {
    int nbsom;
    int nbarc;
    float **matrice; /* matrice d'adjacence */
    char *nodeStatus;
    compo_connexes_str_t con_info;
} graphe;

typedef struct {
    int *pere;
    int nbelements;
    int nbclasses; } t_ens;

/*****************************************************************************/
void init_graphe(int nbs, int nba, graphe *g)
{
    int i/*,j*/;

    g->nbsom = nbs; g->nbarc = nba;
    g->matrice = (float **)calloc(g->nbsom,sizeof(float*));
    for (i=0;i<g->nbsom;i++)
    { g->matrice[i] = (float *)calloc(g->nbsom,sizeof(float));
        /* for (j=0; j<g->nbsom; j++) g->matrice[i][j] = 0.;
           inutile avec calloc */
    }
}
/*****************************************************************************/
void cree_graphe_oriente_value(char *nom_fich, int nbs, int nba)
    /* format du fichier :
       nbsommets nbarcs
       aretes sous forme de triplets origine extremité valuation                 */
{
    FILE *fich;
    graphe g;
    int ori, ext;
    float val;
    int iarc;

    fich = fopen(nom_fich,"wt");

    fprintf(fich,"%d %d\n",nbs,nba);

    init_graphe(nbs,nba,&g);

    /* génération d'arcs aléatoires */
    for (iarc = 1; iarc <= nba ; iarc++)
    {do {ori = random()%nbs;
            ext = random()%nbs; }
    while (g.matrice[ori][ext]);
    /* pour ne pas générer 2 fois le meme arc */

    do val = (random()%(int)(10*MAXVALUATION))/10.; while (val == 0.0);
    /* pour n'avoir qu'une décimale */
    g.matrice[ori][ext] = val;
    fprintf(fich,"%d %d %5.1f\n",ori,ext,val);
    }

    fclose(fich);
}
/*****************************************************************************/
void cree_graphe_oriente_non_value(char *nom_fich, int nbs, int nba)
    /* format du fichier :
       nbsommets nbarcs
       aretes sous forme de triplets origine extremité                           */
{
    FILE *fich;
    graphe g;
    int ori, ext;
    int iarc;

    fich = fopen(nom_fich,"wt");

    fprintf(fich,"%d %d\n",nbs,nba);

    init_graphe(nbs,nba,&g);

    /* génération d'arcs aléatoires */
    for (iarc = 1; iarc <= nba ; iarc++)
    {
        do {
            ori = random()%nbs;
            ext = random()%nbs;
        }
        while (g.matrice[ori][ext]);
        /* pour ne pas générer 2 fois le meme arc */

        g.matrice[ori][ext] = 1;
        fprintf(fich,"%d %d\n",ori,ext);
    }

    fclose(fich);
}
/*****************************************************************************/
void cree_graphe_non_oriente_value(char *nom_fich, int nbs, int nba)
    /* format du fichier :
       nbsommets nbaretes
       aretes sous forme de triplets origine extremité valuation                 */
{ FILE *fich;
    graphe g;
    int ori, ext;
    float val;
    int iare;

    fich = fopen(nom_fich,"wt");

    fprintf(fich,"%d %d\n",nbs,nba);

    init_graphe(nbs,nba,&g);

    /* génération d'aretes aléatoires */
    for (iare = 1; iare <= nba ; iare++)
    {do {ori = random()%nbs;
            ext = random()%nbs; }
    while ((ori == ext)||(g.matrice[ori][ext]));
    /* pour interdire les boucles et ne pas générer 2 fois la meme arete */

    do val = (random()%(int)(10*MAXVALUATION))/10.; while (val == 0.0);
    /* pour n'avoir qu'une décimale */
    g.matrice[ori][ext] = g.matrice[ext][ori] = val;
    fprintf(fich,"%d %d %5.1f\n",ori,ext,val);
    }

    fclose(fich);
}
/*****************************************************************************/
void cree_graphe_non_oriente_non_value(char *nom_fich, int nbs, int nba)
    /* format du fichier :
       nbsommets nbaretes
       aretes sous forme de triplets origine extremité                           */
{ FILE *fich;
    graphe g;
    int ori, ext;
    int iare;

    fich = fopen(nom_fich,"wt");

    fprintf(fich,"%d %d\n",nbs,nba);

    init_graphe(nbs,nba,&g);

    /* génération d'aretes aléatoires */
    for (iare = 1; iare <= nba ; iare++)
    {do {ori = random()%nbs;
            ext = random()%nbs; }
    while ((ori == ext)||(g.matrice[ori][ext]));
    /* pour interdire les boucles et ne pas générer 2 fois la meme arete */

    g.matrice[ori][ext] = g.matrice[ext][ori] = 1;
    fprintf(fich,"%d %d\n",ori,ext);
    }

    fclose(fich);
}
/*****************************************************************************/
void cree_graphe_topo_value(char *nom_fich, int nbs, int nba)
    /* format du fichier :
       nbsommets nbarcs
       arcs sous forme de triplets origine extremité valuation                  */
{ FILE *fich;
    graphe g;
    int ori, ext;
    float val;
    int iarc;

    fich = fopen(nom_fich,"wt");

    fprintf(fich,"%d %d\n",nbs,nba);

    init_graphe(nbs,nba,&g);

    /* on s'assure d'abord d'avoir au moins un arc bien orienté
       du type origine -> origine+1 */

    for (iarc=0; iarc <nbs-1 ; iarc++)
    {ori = iarc;
        ext = iarc+1;
        do val = (random()%(int)(10*MAXVALUATION))/10.; while (val == 0.0);
        /* pour n'avoir qu'une décimale */

        g.matrice[ori][ext]=val;
        fprintf(fich,"%d %d %5.1f\n",ori,ext,val);
    }

    /* ensuite, on complète avec des arcs aléatoires */
    for (iarc=nbs; iarc <= nba ; iarc++)
    {do {ori = random()%nbs;
            ext = random()%nbs; }
    while ((ori == 0)||(ori == nbs - 1)
            ||(ext <= ori)   /* pour assurer la "bonne" orientation des arcs */
            ||(g.matrice[ori][ext]));
    /* pour ne pas générer 2 fois le meme arc */

    do val = (random()%(int)(10*MAXVALUATION))/10.; while (val == 0.0);
    /* pour n'avoir qu'une décimale */

    g.matrice[ori][ext]=val;
    fprintf(fich,"%d %d %5.1f\n",ori,ext,val);
    }

    fclose(fich);
}
/*****************************************************************************/
void cree_graphe_topo_non_value(char *nom_fich, int nbs, int nba)
    /* format du fichier :
       nbsommets nbarcs
       arcs sous forme de triplets origine extremité valuation                  */
{ FILE *fich;
    graphe g;
    int ori, ext;
    int iarc;

    fich = fopen(nom_fich,"wt");

    fprintf(fich,"%d %d\n",nbs,nba);

    init_graphe(nbs,nba,&g);

    /* on s'assure d'abord d'avoir au moins un arc bien orienté
       du type origine -> origine+1 */

    for (iarc=0; iarc < nbs-1 ; iarc++)
    {ori = iarc;
        ext = iarc+1;

        g.matrice[ori][ext]=1;
        fprintf(fich,"%d %d\n",ori,ext);
    }

    /* ensuite, on complète avec des arcs aléatoires */
    for (iarc=nbs; iarc <= nba ; iarc++)
    {do {ori = random()%nbs;
            ext = random()%nbs; }
    while ((ori == 0)||(ori == nbs - 1)
            ||(ext <= ori)   /* pour assurer la "bonne" orientation des arcs */
            ||(g.matrice[ori][ext]));
    /* pour ne pas générer 2 fois le meme arc */

    g.matrice[ori][ext]=1;
    fprintf(fich,"%d %d\n",ori,ext);
    }

    fclose(fich);
}
/*****************************************************************************/
void init_ens(int dim, t_ens *ens)
{int i;

    ens->pere =(int *)calloc(dim, sizeof(int));
    ens->nbelements = ens->nbclasses = dim;
    for (i=0;i<ens->nbelements;i++) ens->pere[i]=-1;
}
/*****************************************************************************/
int trouver(int x, t_ens *ens)
    /* recherche de la classe de x avec compression de chemins */
{if (ens->pere[x] < 0) return x;
    else return (ens->pere[x]=trouver(ens->pere[x],ens));
}
/*****************************************************************************/
void reunir(int r1, int r2, t_ens *ens)
    /* reunion ponderee de la plus petite classe dans la plus grande */
{if (r1 != r2)
    {if (ens->pere[r1] <= ens->pere[r2])
        {ens->pere[r1] += ens->pere[r2];
            ens->pere[r2] = r1;}
        else 	{ens->pere[r2] += ens->pere[r1];
            ens->pere[r1] = r2; }

        ens->nbclasses--; }
    /* sinon rien a faire */
}
/*****************************************************************************/
void cree_graphe_connexe_non_value(char *nom_fich, int nbs, int nba)
    /* format du fichier :
       nbsommets nbaretes
       aretes sous forme de triplets origine extremité                           */
{ FILE *fich;
    graphe g;
    t_ens e;
    int ori, ext;
    int i, rori, rext;

    fich = fopen(nom_fich,"wt");

    fprintf(fich,"%d %d\n",nbs,nba);

    init_graphe(nbs,nba,&g);
    init_ens(nbs,&e);

    /* génération aléatoire de nbs-1 aretes pour assurer la connexité du graphe */
    while (e.nbclasses > 1)
    {do {ori = random()%nbs;
            ext = random()%nbs;
            rori = trouver(ori,&e);
            rext = trouver(ext,&e);
        }
    while ((ori == ext)||(g.matrice[ori][ext])||(rori == rext));
    /* pour interdire les boucles et ne pas générer 2 fois la meme arete */

    g.matrice[ori][ext] = g.matrice[ext][ori] = 1;
    reunir(rori,rext,&e);
    fprintf(fich,"%d %d\n",ori,ext);
    }

    /* on complète à nba avec des aretes aléatoires */
    for (i = nbs; i <= nba ; i++)
    {do {ori = random()%nbs;
            ext = random()%nbs; }
    while ((ori == ext)||(g.matrice[ori][ext]));
    /* pour interdire les boucles et ne pas générer 2 fois la meme arete */

    g.matrice[ori][ext] = g.matrice[ext][ori] = 1;
    fprintf(fich,"%d %d\n",ori,ext);
    }

    fclose(fich);
}
/*****************************************************************************/
void cree_graphe_connexe_value(char *nom_fich, int nbs, int nba)
    /* format du fichier :
       nbsommets nbaretes
       aretes sous forme de triplets origine extremité                           */
{ FILE *fich;
    graphe g;
    t_ens e;
    int ori, ext;
    int i, rori, rext;
    float val;

    fich = fopen(nom_fich,"wt");

    fprintf(fich,"%d %d\n",nbs,nba);

    init_graphe(nbs,nba,&g);
    init_ens(nbs,&e);

    /* génération aléatoire de nbs-1 aretes pour assurer la connexité du graphe */
    while (e.nbclasses > 1)
    {
        do {
            ori = random()%nbs;
            ext = random()%nbs;
            rori = trouver(ori,&e);
            rext = trouver(ext,&e);
        }
        while ((ori == ext)||(g.matrice[ori][ext])||(rori == rext));
        /* pour interdire les boucles et ne pas générer 2 fois la meme arete */

        do {
            val = (random()%(int)(10*MAXVALUATION))/10.;
        }
        while (val == 0.0);
        /* pour n'avoir qu'une décimale */
        g.matrice[ori][ext] = g.matrice[ext][ori] = val;
        reunir(rori,rext,&e);
        fprintf(fich,"%d %d %5.1f\n",ori,ext,val);
    }

    /* on complète à nba avec des aretes aléatoires */
    for (i = nbs; i <= nba ; i++){
        do {
            ori = random()%nbs;
            ext = random()%nbs;
        }
        while ((ori == ext)||(g.matrice[ori][ext]));
    /* pour interdire les boucles et ne pas générer 2 fois la meme arete */

        do {
            val = (random()%(int)(10*MAXVALUATION))/10.;
        } while (val == 0.0);
    /* pour n'avoir qu'une décimale */
        g.matrice[ori][ext] = g.matrice[ext][ori] = val;
        fprintf(fich,"%d %d %5.1f\n",ori,ext,val);
    }

    fclose(fich);
}
/*****************************************************************************/
void charge_graphe_non_oriente_non_value(char *filename, graphe *g) {
    FILE* fich = NULL;
    int nbLine = 0;
    int matriceX,matriceY;

    if(filename == NULL || g == NULL){
        fprintf(stderr,"Erreur NULL\n");
return;
    }

    fich = fopen(filename, "rt"); /* t apporte la précision que le fichier à lire est un fichier texte */

    if(fich == NULL){
        fprintf(stderr,"Erreur NULL\n");
        return;
    }

    fscanf(fich,"%d %d",&g->nbsom,&g->nbarc);

    /* Allocation */
    g->matrice = (float**)calloc(g->nbsom,sizeof(float*));
    if(g->matrice == NULL){
        fprintf(stderr,"Erreur NULL\n");
        return;
    }

    for(nbLine = 0; nbLine < g->nbsom; nbLine++){
        g->matrice[nbLine] = (float*)calloc(g->nbsom,sizeof(float));
        if(g->matrice[nbLine] == NULL){
            fprintf(stderr,"Erreur NULL\n");
            return;
        }
    }

    /* Remplissage de la matrice */

    for(nbLine = g->nbarc; nbLine >= 0; nbLine--){
        fscanf(fich,"%d %d",&matriceX,&matriceY);
        g->matrice[matriceX][matriceY] = 1;
        g->matrice[matriceY][matriceX] = 1; /* Symétrie car non-orienté */
    }

    fclose(fich);

}


void afficher_graph(const graphe *g) {
    int X,Y;

    if(g == NULL)
        return;


    printf("# ");
    for(X = 0; X < g->nbsom; X++)
        printf("%d ",X);
    printf("\n");
    for(X = 0; X < g->nbsom; X++) {
        printf("%d ",X);
        for(Y = 0; Y < g->nbsom; Y++) {
            printf("%d ",(int)g->matrice[X][Y]); /* Affichage sous forme entière */
        }
        printf("\n");
    }

}




int visite_profondeur_graph_non_oriente_non_value(graphe *g, int nbSommet) {
    int cur_y;
    int nbNoeud = 0;

    if(nbSommet < 0)
        return 0;
    if(g->nodeStatus == NULL)
        return 0;

    g->nodeStatus[nbSommet] = PENDING;

    printf("Noeud prefixe : %d\n",nbSommet);
    for(cur_y = 0; cur_y < g->nbsom; cur_y++) {
        if(g->matrice[nbSommet][cur_y] == 0)
            continue;
        if(g->nodeStatus[cur_y] == UNVISITED){
            nbNoeud += visite_profondeur_graph_non_oriente_non_value(g,cur_y);
        }
    }
    g->nodeStatus[nbSommet] = VISITED;

    nbNoeud++;

    g->con_info.composantes_connexes[nbSommet] = g->con_info.nbComposantes;

    printf("Noeud suffixe : %d\n",nbSommet);
    return nbNoeud;
}

bool parcours_profondeur_graph_non_oriente_non_value(graphe *g) {

    int cur_x = 0;
    int nbNoeud = 0;

    if(g == NULL)
        return false;

    g->con_info.nbComposantes = 0;
    g->con_info.composantes_connexes = (int*)calloc(g->nbsom,sizeof(int));

    /* Initialisation */
    g->nodeStatus = (char*)calloc(g->nbsom,sizeof(char)); /* Allocation à 0 <=> UNVISITED */
    if(g->nodeStatus == NULL)
        return false;

    for(cur_x = 0; cur_x < g->nbsom; cur_x++) {
        if(g->nodeStatus[cur_x] == UNVISITED){
            g->con_info.nbComposantes++;
            nbNoeud += visite_profondeur_graph_non_oriente_non_value(g,cur_x);
        }
    }

    printf("Nombre de noeuds visites : %d\n",nbNoeud);
    free(g->nodeStatus);
    g->nodeStatus = NULL;

    return g->con_info.nbComposantes == 1;
}



int visite_largeur_graph_non_oriente_non_value(graphe *g, int nbSommet) {

    int cur_y;
    int nbNoeud = 0;
    File f;


    if(nbSommet < 0)
        return 0;
    if(g->nodeStatus == NULL)
        return 0;

    g->nodeStatus[nbSommet] = PENDING;

    f = file_vide();
    f = enfiler(nbSommet,f);
    while(!est_vide(f)){
        int nbSommet = tete(f);
        for(cur_y = 0; cur_y < g->nbsom; cur_y++) {
            if(g->matrice[nbSommet][cur_y] == 0)
                continue;
            if(g->nodeStatus[cur_y] != UNVISITED)
                continue;

            g->nodeStatus[cur_y] = PENDING;
            f = enfiler(cur_y,f);

        }
        f = defiler(f);
        g->nodeStatus[nbSommet] = VISITED;
        printf("Noeud visité : %d\n",nbSommet);
        g->con_info.composantes_connexes[nbSommet] = g->con_info.nbComposantes;
        nbNoeud++;
    }
    return nbNoeud;
}

bool parcours_largeur_graph_non_oriente_non_value(graphe *g) {
    int nbNoeud = 0, cur_x = 0;

    if(g == NULL)
        return false;

    g->con_info.nbComposantes = 0;
    g->con_info.composantes_connexes = (int*)calloc(g->nbsom,sizeof(int));

    /* Initialisation */
    g->nodeStatus = (char*)calloc(g->nbsom,sizeof(char)); /* Allocation à 0 <=> UNVISITED */
    if(g->nodeStatus == NULL)
        return false;

    for(cur_x = 0; cur_x < g->nbsom; cur_x++) {
        if(g->nodeStatus[cur_x] == UNVISITED){
            g->con_info.nbComposantes++;
            nbNoeud += visite_largeur_graph_non_oriente_non_value(g,cur_x);
        }
    }


    printf("Nombre de noeuds visites : %d\n",nbNoeud);
    free(g->nodeStatus);
    g->nodeStatus = NULL;

    return g->con_info.nbComposantes == 1;

}


/*****************************************************************************/


int main() {
    graphe g;
    int i;

    charge_graphe_non_oriente_non_value("./graphe_alea.txt",&g);

    afficher_graph(&g);

    printf("Parcours en profondeur : \n");
    parcours_profondeur_graph_non_oriente_non_value(&g);
    printf("\nNombre de composants : %d\n",g.con_info.nbComposantes);

    for(i = 0; i < g.nbsom; i++) {
        printf("%d |",i);
    }
    printf("\n");
    for(i = 0; i < g.nbsom; i++) {
        printf("%d |",g.con_info.composantes_connexes[i]);
    }
    printf("\n");
    free(g.con_info.composantes_connexes);

    printf("Parcours en largeur: \n");
    parcours_largeur_graph_non_oriente_non_value(&g);
    printf("\nNombre de composants : %d\n",g.con_info.nbComposantes);

    for(i = 0; i < g.nbsom; i++) {
        printf("%d |",i);
    }
    printf("\n");
    for(i = 0; i < g.nbsom; i++) {
        printf("%d |",g.con_info.composantes_connexes[i]);
    }
    printf("\n");

    free(g.con_info.composantes_connexes);
    return 0;
}
/*
int main(int argc, char *argv[]){
    int nbs, nba;
    char nom_fichier[100];
    int type_graphe;
    int alea;

    void (*fonction[8])(char *,int,int)= {cree_graphe_oriente_value,
        cree_graphe_oriente_non_value,
        cree_graphe_non_oriente_value,
        cree_graphe_connexe_value,
        cree_graphe_non_oriente_non_value,
        cree_graphe_connexe_non_value,
        cree_graphe_topo_value,
        cree_graphe_topo_non_value
    };

    srandom(time(NULL));

    strcpy(nom_fichier,((argc == 1) ? "graphe_alea.txt" : argv[1]));

    printf("Quel type de graphe voulez-vous generer ?\n");
    printf("\t1 - graphe oriente value\n");
    printf("\t2 - graphe oriente non value\n");
    printf("\t3 - graphe non oriente value\n");
    printf("\t4 - graphe non oriente value connexe\n");
    printf("\t5 - graphe non oriente non value\n");
    printf("\t6 - graphe non oriente non value connexe\n");
    printf("\t7 - graphe oriente value possedant un marquage topologique\n");
    printf("\t8 - graphe oriente non value possedant un marquage topologique ? ");
    scanf("%d",&type_graphe);

    printf("Generation aleatoire du nombre de sommets et d'arcs/aretes - 1/0 ? ");
    scanf("%d",&alea);

    if (!alea) {printf("Nombre de sommets - Nombre d'arcs/aretes ? ");
        scanf("%d %d",&nbs,&nba); }
    else       {do nbs = random()%MAXSOMMET;     while (nbs==0);
        do nba = nbs*(random()%MAXSUCC); while (nba < nbs); }


    (fonction[type_graphe - 1])(nom_fichier,nbs,nba);

    printf("Graphe genere : %s (%d sommets - %d arcs/aretes)\n",
            nom_fichier,nbs,nba);

}
*/
/****************************************************************************/
