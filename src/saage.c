#include "saage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *ouvrir_fichier(char *nom_de_fichier) {
    return fopen(nom_de_fichier, "w");
}

int serialise(FILE *fichier, Arbre A, int niveau) {
    if (fichier == NULL)
        return 0;

    if (A == NULL) {
        fprintf(fichier, "%*sValeur : NULL\n", niveau * 4, "");
    } else {
        fprintf(fichier, "%*sValeur : %s\n", niveau * 4, "", A->val);
        printf("%*sValeur : %s\n", niveau * 4, "", A->val);
        fprintf(fichier, "%*sGauche : \n", niveau * 4, "");
        serialise(fichier, A->fg, niveau + 1);
        fprintf(fichier, "%*sDroite : \n", niveau * 4, "");
        serialise(fichier, A->fd, niveau + 1);
    }

    return 1;
}

void fermer_fichier(FILE *fichier) {
    if (fichier != NULL)
        fclose(fichier);
}

int deserialise(FILE *fichier, Arbre *A) {
    if (fichier == NULL)
        return 0;

    char val[100];
    if (fgets(val, 100, fichier) == NULL) {
        fclose(fichier);
        return 0;
    }

    *A = (Arbre)malloc(sizeof(Arbre));
    if (*A == NULL) {
        fclose(fichier);
        return 0;
    }

    (*A)->val = (char *)malloc(strlen(val) + 1);
    if ((*A)->val == NULL) {
        free(*A);
        fclose(fichier);
        return 0;
    }

    strcpy((*A)->val, val);

    if (!deserialise(fichier, &((*A)->fg))) {
        free((*A)->val);
        free(*A);
        fclose(fichier);
        return 0;
    }

    if (!deserialise(fichier, &((*A)->fd))) {
        free((*A)->val);
        free((*A)->fg);
        free(*A);
        fclose(fichier);
        return 0;
    }

    fclose(fichier);
    return 1;
}

Arbre charger_noeud(FILE *fichier) {
    char ligne[100];
    if (fgets(ligne, sizeof(ligne), fichier) == NULL ||
        strcmp(ligne, "NULL\n") == 0) {
        return NULL;
    }

    char *valeur = strchr(ligne, ':') + 2; // Avance jusqu'au début de la valeur
    valeur[strlen(valeur) - 1] = '\0'; // Supprime le saut de ligne à la fin

    Arbre A = alloue_noeud(valeur);

    fgets(ligne, sizeof(ligne), fichier); // Lecture de "Gauche : "
    A->fg = charger_noeud(fichier);

    fgets(ligne, sizeof(ligne), fichier); // Lecture de "Droite : "
    A->fd = charger_noeud(fichier);

    return A;
}