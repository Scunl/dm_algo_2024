#include "ABR.h"
#include <stdio.h>
#include <stdlib.h>

Arbre alloue_noeud(char *val) {
    Arbre new = (Arbre)malloc(sizeof(Arbre));
    if (!new)
        fprintf(stderr, "Erreur allocation mémoire");
    new->fd = NULL;
    new->fg = NULL;
    new->val = val;

    return new;
}

int main(void) {
    Arbre a = alloue_noeud("implication");
    Arbre b = alloue_noeud("OU");
    (a)->fg = alloue_noeud("OU");
    (b)->fg = alloue_noeud("NÉGATION");
    Arbre new = greffe(a, b);
    printf("%s\n", (new)->val);
    new = (new)->fg;
    new = greffe(a, b);
    printf("%s\n", (new)->val);
    return 0;
}
