#ifndef NTH_WORD_TREE_H
#define NTH_WORD_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




/* Definitions */
#define FOREACH_BROTHER(PTR_IT) for(;PTR_IT != NULL;PTR_IT = PTR_IT->bro)

/* Type de l'arbre binaire */

/**
 * @brief Structure représentative d'un noeud. Un noeud redirige vers un fils correspondant à la suite d'un mot, ou vers un frère qui correspond à une alternative au noeud courant.
 */
typedef struct noeud {
		char valeur;
		struct noeud *son, *bro;
} NOEUD, *ABR;

	/* Prototypes de fonction */

/**
 * @brief Retourne un arbre vide (NULL)
 *
 * @return Pointeur vers NULL
 */
NOEUD* nth_word_tree_empty_tree(void);
/**
 * @brief Créée un fils au noeud p ayant la valeur de 'x'. Si un noeud contenant cette valeur existe déjà, l'adresse du noeud existant sera retournée.
 *
 * @param p Noeud 'père'
 * @param x Valeur à assigner au nouveau noeud.
 *
 * @return Pointeur vers le fils créé
 */
NOEUD* nth_word_tree_create_son(NOEUD *p, char x);
/**
 * @brief Recherche un mot 'w' dans l'arbre 'p'.
 *
 * @param p Arbre
 * @param w Mot à chercher
 *
 * @return True si le mot est présent dans l'arbre.
 */
bool nth_word_tree_search(NOEUD *p, char *w);
/**
 * @brief Affiche l'arbre dans la sortie standard.
 *
 * @param p Arbre
 * @param col Paramètre pour le décalage. À fixer à 0 lors d'un appel.
 */
void nth_word_tree_print_tree(NOEUD* p, int col) ;
/**
 * @brief Alloue un arbre n-aire de mot.
 *
 * @return Pointeur vers le noeud nouvellement alloué.
 */
NOEUD* nth_word_tree_init_tree(void) ;
/**
 * @brief Ajoute un mot à un arbre de mot.
 *
 * @param p Arbre
 * @param w Mot à ajouter
 *
 * @return Pointeur vers p
 */
NOEUD* nth_word_tree_add_word(NOEUD* p, char *w) ;
/**
 * @brief Libère la mémoire en supprimant tout les noeuds de l'arbre.
 *
 * @param root Arbre à libérer
 */
void nth_word_tree_delete_tree(NOEUD* root) ;
/**
 * @brief Charge un dictionnaire de mot à partir d'un fichier 'filename' dans l'arbre 'root'.
 *
 * @param filename Chemin vers un fichier
 * @param root Arbre à compléter
 *
 * @return Vrai si le chargement s'est opéré avec succès.
 */
bool nth_word_tree_load_from_file(char* filename, NOEUD* root);

#endif
