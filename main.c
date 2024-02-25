#include <stdio.h>
#include <stdlib.h>

typedef struct _noeud {
    char *val;
    struct _noeud *fg, *fd;
} Noeud, *Arbre;

Arbre alloue_noeud(char *val) {
    Arbre new = (Arbre)malloc(sizeof(Arbre));
    if (!new)
        fprintf(stderr, "Erreur allocation mémoire");
    new->fd = NULL;
    new->fg = NULL;
    new->val = val;

    return new;
}
/// @brief Fonction effectuant la greffe de l'arbre b vers l'arbre a
/// @param a
/// @param b
/// @return l'arbre G qui est la greffe de a vers b
Arbre greffe(Arbre a, Arbre b) {
    Arbre new = alloue_noeud((b)->val);

    if (a->val == b->val){
    }
    b = (b)->fg;
    a = a->fg;
    (new)->fg = alloue_noeud((b)->val);

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
