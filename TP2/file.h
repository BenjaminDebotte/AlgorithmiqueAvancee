#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "ABR_TP.h"
/* Macros */



/* Définitions */
typedef NOEUD* file_element;

typedef struct cellule {
		file_element	  valeur;
		struct cellule *suivant; 
} Cellule;

typedef struct file { 
		Cellule *t, *q; 
} File;	/* tête queue */

/* Prototypes */
File file_vide(void);
int est_vide(File f);
file_element tete(File f);
File enfiler(file_element e,File f); 
File defiler(File f); 
file_element defiler2(File *f); 
void concat(File *f1, File *f2);
void affiche_file(char *msg, File f);

#endif
