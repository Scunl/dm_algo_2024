#include "ABR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _noeud {
    char *val;
    struct _noeud *fg, *fd;
} Noeud, *Arbre;

int copie(Arbre *dest, Arbre source) {
    if (!source)
        return 1;
    dest = alloue_noeud(source->val);
    if (!dest)
        return 0;
    return copie(dest, source->fd) && copie(dest, source->fg);
}

int main(int argc, char const *argv[]) {
    return 0;
}
