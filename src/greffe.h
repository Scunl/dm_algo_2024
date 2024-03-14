#ifndef GREFFE_H
#define GREFFE_H
#include "arbres_binaires.h"

int copie(Arbre *dest, Arbre source);
int expansion(Arbre *A, Arbre B);
Arbre greffer_arbre(Arbre A, Arbre B);

#endif /* GREFFE_H */
