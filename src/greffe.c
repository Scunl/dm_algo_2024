#include "greffe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "saage.h"
#include <stdio.h>

Arbre greffer_arbre(Arbre A, Arbre B) {
    if (A == NULL)
        return B;
    if (B == NULL)
        return A;

    if (strcmp(A->val, B->val) == 0) {
        A->fg = greffer_arbre(A->fg, B->fg);
        A->fd = greffer_arbre(A->fd, B->fd);
        return A;
    } else {
        A->fg = greffer_arbre(A->fg, B);
        A->fd = greffer_arbre(A->fd, B);
        return A;
    }
}

int copie(Arbre *dest, Arbre source) {
    if (source == NULL)
        return 0;

    *dest = alloue_noeud(source->val);
    if (*dest == NULL)
        return 0;

    if (!copie(&((*dest)->fg), source->fg) ||
        !copie(&((*dest)->fd), source->fd)) {
        liberer(dest);
        return 0;
    }

    return 1;
}

int expansion(Arbre *A, Arbre B) {
    if (*A == NULL || B == NULL)
        return 0;

    if (strcmp((*A)->val, B->val) != 0)
        return 0;

    Arbre copie_B = NULL;
    if (!copie(&copie_B, B))
        return 0;

    if (!expansion(&((*A)->fg), copie_B->fg) ||
        !expansion(&((*A)->fd), copie_B->fd)) {
        liberer(&copie_B);
        return 0;
    }

    liberer(&copie_B);
    return 1;
}
