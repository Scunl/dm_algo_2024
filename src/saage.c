#include "saage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

FILE *ouvrir_fichier(char *nom_de_fichier) {
    return fopen(nom_de_fichier, "a");
}

int serialise(FILE *fichier, Arbre A) {
    if (fichier == NULL || A == NULL)
        return 0;

    fprintf(fichier, "%s\n", A->val);
    if (!serialise(fichier, A->fg))
        return 0;
    if (!serialise(fichier, A->fd))
        return 0;

    return 1;
}

void fermer_fichier(FILE *fichier) {
    if (fichier != NULL)
        fclose(fichier);
}

int deserialise(char *nom_de_fichier, Arbre *A) {
    FILE *fichier = fopen(nom_de_fichier, "r");
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

    (*A)->val = (char *)malloc(
        strlen(val) + 1); // Alloue de la mémoire pour la chaîne de caractères
    if ((*A)->val == NULL) {
        free(*A);
        fclose(fichier);
        return 0;
    }

    strcpy((*A)->val,
           val); // Copie la chaîne de caractères dans le champ val de l'arbre

    if (!deserialise(nom_de_fichier, &((*A)->fg))) {
        free((*A)->val);
        free(*A);
        fclose(fichier);
        return 0;
    }

    if (!deserialise(nom_de_fichier, &((*A)->fd))) {
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