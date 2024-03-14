#ifndef ARBRES_BINAIRES_H
#define ARBRES_BINAIRES_H

#include <stdio.h>

typedef struct _noeud {
    char *val;
    struct _noeud *fg, *fd;
} Noeud, *Arbre;

Arbre alloue_noeud(char *s);
void liberer(Arbre *A);
Arbre cree_A_1(void);
Arbre cree_A_2(void);
Arbre cree_A_3(void);
int construit_arbre(Arbre *a);

Arbre creer_arbre_saisie_utilisateur(void);
Arbre charger_arbre(char *nom_fichier);
Arbre construire_arbre(FILE *fichier);
Arbre creer_noeud(const char *val);
void afficher_arbre(Arbre racine, int niveau);
void sauvegarder_noeud(FILE *fichier, Arbre A, int niveau);
void sauvegarder_arbre(Arbre A, const char *nom_fichier);

#endif /* ARBRES_BINAIRES_H */
