#include "nth_word_tree.h"
#include <string.h>


static int nbAllocations = 0;

NOEUD* nth_word_tree_empty_tree(void){return NULL;}


NOEUD* nth_word_tree_create_son(NOEUD *p, char x) {
    if(p == NULL)
        return NULL;


    if(p->son != NULL) { /* Il existe déjà un ou des fils : attention à la "fraternité" */
        NOEUD *s = p->son, *beforeNode = NULL;
        FOREACH_BROTHER(s) {
            if(s->valeur < x)
                beforeNode = s; /*  On profite de la boucle pour  mémoriser le noeud précédent celui à ajouter. */
            if(s->valeur == x)
                return s; /* Fils pré-existant */
        }
        /* Le fils n'est pas pré-existant. On ajoute/insère le nouveau noeud dans l'arbre. */
        s = (NOEUD*)malloc(sizeof(NOEUD));
        nbAllocations++;
        s->valeur = x;
        s->son = NULL;
        if(beforeNode != NULL) { /* Insertion */
            s->bro = beforeNode->bro;
            beforeNode->bro = s;

        }
        else { /* Ajout en tête */
            s->bro = p->son;
            p->son = s;
        }
        return s;
    }
    else { /* Pas de fils pré-existant. */

        p->son = (NOEUD*)malloc(sizeof(NOEUD));
        nbAllocations++;

        p->son->son = NULL;
        p->son->bro = NULL;
        p->son->valeur = x;

        return p->son;
    }
}


bool nth_word_tree_search(NOEUD *p, char *w) {
    if(p == NULL || w == NULL)
        return false;

    /* On regarde les noeuds */
    FOREACH_BROTHER(p) {
        if(*w == '\0' && p->valeur == '\0')
            return true;
        if(p->valeur == *w){
            return nth_word_tree_search(p->son,w+1);
        }
    }

    return false;
}

void nth_word_tree_print_tree(NOEUD* p, int col) {
    int i = 0;
    if(p == NULL)
        return ;

    for(i = 0; i < col; i++) printf(" ");

    printf("%c \n",p->valeur);
    nth_word_tree_print_tree(p->son, col + 1);
    nth_word_tree_print_tree(p->bro, col);
}

NOEUD* nth_word_tree_init_tree(void) {
    NOEUD* p;
    nbAllocations++;
    p = (NOEUD*)malloc(sizeof(NOEUD));
    p->son = NULL;
    p->bro = NULL;
    p->valeur = 0xFF;
    return p;
}

NOEUD* nth_word_tree_add_word(NOEUD* p, char *w) {
    if(w == NULL)
        return NULL;
    if(p == NULL)
        return NULL;

    if(*w != '\0') {
        p = nth_word_tree_create_son(p,*w);
        return nth_word_tree_add_word(p,(w+1));
    }
    else { /* Condition d'arrêt : caractère de fin de chaîne */
        return nth_word_tree_create_son(p,'\0');
    }
}


void nth_word_tree_delete_tree(NOEUD* root) {
    /* FREE DE TOUT LES ARBRES */
}

bool nth_word_tree_load_from_file(char* filename, NOEUD* root) {
    FILE* f = NULL;
    char line[150] = {0};
    if(filename == NULL)
        return false;
    if(root == NULL)
        return false;

    f = fopen(filename,"r");
    if(f == NULL)
        return false;
    while (1) {
        if (fgets(line,150, f) == NULL)
            break;
        /* Suppression du 'Newline' */
        line[strcspn(line, "\n")] = '\0';
        nth_word_tree_add_word(root,line);
    }
    fclose(f);
    return true;
}


int main() {
    char input[256] = {0};
    ABR french = NULL, english = NULL;

    french = nth_word_tree_init_tree();
    english = nth_word_tree_init_tree();

    if(french == NULL || english == NULL){
        fprintf(stderr,"Erreur lors de l'allocation des arbres.");
        return 1;
    }

    if(!nth_word_tree_load_from_file("./dico.fr",french)){
        fprintf(stderr,"Erreur lors du chargement du fichier dico.fr.");
        return 1;
    }
    if(!nth_word_tree_load_from_file("./dico.ang",english)){
        fprintf(stderr,"Erreur lors du chargement du fichier dico.ang.");
        return 1;
    }

    printf("Fichiers chargés avec succès (%d allocations <=> %ld kB).",nbAllocations,nbAllocations*sizeof(NOEUD) / 1024);

    while(1){
        char* w;
        bool isFR, isEN;
        printf("\nMot à rechercher : ");
        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = '\0';
        w = input;
        isFR = nth_word_tree_search(french->son,w);
        isEN = nth_word_tree_search(english->son,w);
        if(isFR && isEN)
            printf("\nLe mot %s est présent dans les dictionnaires Anglais et Français.",input);
        else if(!isFR && isEN)
            printf("\nLe mot %s est présent dans le dictionnaire Anglais.",input);
        else if(isFR && !isEN)
            printf("\nLe mot %s est présent dans le dictionnaire Français.",input);
        else
            printf("\nLe mot %s n'est présent dans aucun dictionnaire.",input);
    }


    return 0;
}
