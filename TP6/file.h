#ifndef FILE_H
#define FILE_H

#include <stdio.h>

typedef int element;

typedef struct cellule {
		element	  valeur;
		struct cellule *suivant; } Cellule;

		typedef struct file {
				Cellule *t, *q; } File;	/* tête queue */

File file_vide(void);
int est_vide(File f);
int size_file(File f);
element tete(File f);
File enfiler(element e,File f);
File defiler(File f);
element defiler2(File *f)	/* ATTENTION: la File est modifi?e */;
void concat(File *f1, File *f2);
void affiche_file(char *msg, File f);

#endif
