#include "arbres_binaires.h"
#include "greffe.h"
#include "saage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s -E fichier.saage\n", argv[0]);
        printf("       %s -G s.saage g.saage\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-E") == 0) {
        if (argc != 3) {
            printf("Usage: %s -E fichier.saage\n", argv[0]);
            return 1;
        }
        Arbre arbre = creer_arbre_saisie_utilisateur();
        if (arbre == NULL) {
            printf("Erreur lors de la création de l'arbre.\n");
            return 1;
        }

        // Sauvegarde de l'arbre dans un fichier
        afficher_arbre(arbre, 0);
        FILE *fichier = ouvrir_fichier(argv[2]);
        if (!serialise(fichier, arbre, 1)) {
            printf(
                "Erreur lors de la sauvegarde de l'arbre dans le fichier.\n");
            liberer(&arbre);
            return 1;
        }

        printf("L'arbre a été sauvegardé avec succès dans le fichier %s.\n",
               argv[2]);

        liberer(&arbre);
        fermer_fichier(fichier);
    }
    else if (strcmp(argv[1], "-G") == 0) {
        if (argc != 4) {
            printf("Usage: %s -G s.saage g.saage\n", argv[0]);
            return 1;
        }
        Arbre arbre_source = charger_arbre(argv[2]);
        if (arbre_source == NULL) {
            printf("Erreur lors de la lecture de l'arbre source.\n");
            return 1;
        }
        Arbre greffon = charger_arbre(argv[3]);
        if (greffon == NULL) {
            printf("Erreur lors de la lecture du greffon.\n");
            liberer(&arbre_source);
            return 1;
        }
        Arbre resultat = greffer_arbre(arbre_source, greffon);
        if (resultat == NULL) {
            printf("Erreur lors de la greffe des arbres.\n");
            liberer(&arbre_source);
            liberer(&greffon);
            return 1;
        }
        serialise(ouvrir_fichier(argv[1]), resultat, 1);
        liberer(&arbre_source);
        liberer(&greffon);
        liberer(&resultat);
    } else {
        printf("Usage: %s -E fichier.saage\n", argv[0]);
        printf("       %s -G s.saage g.saage\n", argv[0]);
        return 1;
    }

    return 0;
}
