#ifndef SAAGE_H
#define SAAGE_H

#include "greffe.h"
#include <stdio.h>

int serialise(FILE *fichier, Arbre A, int niveau);
int deserialise(FILE *fichier, Arbre *A);
FILE *ouvrir_fichier(char *nom_de_fichier);
void fermer_fichier(FILE *fichier);
Arbre charger_arbre(char *nom_fichier);

#endif /* SAAGE_H */
