#include "ABR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copie(Arbre *dest, Arbre source) {
    if (!source)
        return 1;
    dest = alloue_noeud(source->val);
    if (!dest)
        return 0;
    return copie(&((*dest)->fg), source->fg) && copie(&((*dest)->fd), source->fd);
}

int expansion(Arbre * A, Arbre B) {
    
}

int main(int argc, char const *argv[]) {
    return 0;
}
