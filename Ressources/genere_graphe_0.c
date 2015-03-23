/*****************************************************************************/
/* C.PORQUET                 genere_graphe_0.c                 Décembre 2007 */ 
/*                     Générateur automatique de graphes                     */
/*                  Les sommets sont numérotés à partir de 0                 */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSOMMET 	250
#define MAXVALUATION 	20.0
#define MAXSUCC		10

typedef struct {
           int nbsom;
           int nbarc;
	   float **matrice; /* matrice d'adjacence */
	   } graphe;

typedef struct {	
	 int *pere;
	 int nbelements;
	 int nbclasses; } t_ens;	 

/*****************************************************************************/
void init_graphe(int nbs, int nba, graphe *g)
{ int i,j;

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
{ FILE *fich; 
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
{ FILE *fich; 
  graphe g;
  int ori, ext;
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
      {do {ori = random()%nbs;
           ext = random()%nbs; 
	   rori = trouver(ori,&e);
	   rext = trouver(ext,&e);
	   }
       while ((ori == ext)||(g.matrice[ori][ext])||(rori == rext));
       /* pour interdire les boucles et ne pas générer 2 fois la meme arete */
      
       do val = (random()%(int)(10*MAXVALUATION))/10.; while (val == 0.0);
       /* pour n'avoir qu'une décimale */
       g.matrice[ori][ext] = g.matrice[ext][ori] = val;
       reunir(rori,rext,&e);        
       fprintf(fich,"%d %d %5.1f\n",ori,ext,val);
      } 
      
  /* on complète à nba avec des aretes aléatoires */   
   for (i = nbs; i <= nba ; i++)
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

int main(int argc, char *argv[])
{int nbs, nba;
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
/****************************************************************************/ 	
