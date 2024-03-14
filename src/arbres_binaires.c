#include "arbres_binaires.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arbre alloue_noeud(char *val) {
    Arbre new = (Arbre)malloc(sizeof(Noeud));
    if (!new) {
        fprintf(stderr, "Erreur allocation mémoire");
        return NULL;
    }

    new->val = (char *)malloc(strlen(val) + 1);
    if (!new->val) {
        fprintf(stderr, "Erreur allocation mémoire");
        free(new);
        return NULL;
    }

    strcpy(new->val, val);

    new->fd = NULL;
    new->fg = NULL;

    return new;
}

void liberer(Arbre *A) {
    if (*A != NULL) {
        liberer(&((*A)->fg));
        liberer(&((*A)->fd));
        free((*A)->val);
        free(*A);
        *A = NULL;
    }
}

Arbre cree_A_1(void) {
    Arbre A = alloue_noeud("A");
    A->fg = alloue_noeud("B");
    A->fd = alloue_noeud("C");
    return A;
}

Arbre cree_A_2(void) {
    Arbre A = alloue_noeud("A");
    A->fg = alloue_noeud("B");
    A->fd = alloue_noeud("C");
    A->fg->fg = alloue_noeud("D");
    return A;
}

Arbre cree_A_3(void) {
    Arbre A = alloue_noeud("A");
    A->fg = alloue_noeud("B");
    A->fd = alloue_noeud("C");
    A->fd->fg = alloue_noeud("D");
    A->fd->fd = alloue_noeud("E");
    return A;
}

int construit_arbre(Arbre *a) {
    char val[100];
    printf("Entrez la valeur du noeud (ou 'NULL' pour terminer) : ");
    scanf("%s", val);
    if (strcmp(val, "NULL") == 0) {
        *a = NULL;
        return 1;
    } else {
        *a = alloue_noeud(val);
        if (*a == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            return 0;
        }
        printf("Saisie du sous-arbre gauche de %s :\n", val);
        if (!construit_arbre(&((*a)->fg))) {
            free(*a);
            return 0;
        }
        printf("Saisie du sous-arbre droit de %s :\n", val);
        if (!construit_arbre(&((*a)->fd))) {
            free(*a);
            return 0;
        }
        return 1;
    }
}

Arbre creer_arbre_recursif() {
    char val[100];
    printf("Valeur du noeud (ou 'NULL' pour terminer) : ");
    scanf("%s", val);

    if (strcmp(val, "NULL") == 0) {
        return NULL;
    } else {
        Arbre nouveau_noeud = alloue_noeud(val);
        printf("Sous-arbre gauche de %s : \n", val);
        nouveau_noeud->fg = creer_arbre_recursif();
        printf("Sous-arbre droit de %s : \n", val);
        nouveau_noeud->fd = creer_arbre_recursif();
        return nouveau_noeud;
    }
}

Arbre creer_arbre_saisie_utilisateur(void) {
    printf("Création d'un arbre par saisie utilisateur : \n");
    printf("Entrez les valeurs des noeuds (NULL pour terminer) : \n");
    return creer_arbre_recursif();
}

void sauvegarder_arbre(Arbre A, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n",
                nom_fichier);
        return;
    }

    sauvegarder_noeud(fichier, A, 0);

    fclose(fichier);
}

void sauvegarder_noeud(FILE *fichier, Arbre A, int niveau) {
    if (A == NULL) {
        fprintf(fichier, "NULL\n");
        return;
    }

    fprintf(fichier, "Valeur : %s\n", A->val);

    fprintf(fichier, "Gauche : ");
    sauvegarder_noeud(fichier, A->fg, niveau + 1);

    fprintf(fichier, "Droite : ");
    sauvegarder_noeud(fichier, A->fd, niveau + 1);
}

Arbre charger_arbre_recursif(FILE *fichier) {
    char ligne[100];

    // Lire la ligne pour la valeur du nœud
    if (fgets(ligne, sizeof(ligne), fichier) == NULL || ligne[0] == '\n') {
        fprintf(stderr, "Erreur: Fin de fichier ou vide.\n");
        return NULL;
    }

    char val[100];
    if (sscanf(ligne, "Valeur : %99[^\n]", val) != 1) {
        fprintf(stderr, "Erreur: Lecture de la valeur du noeud.\n");
        fprintf(stderr, "ligne : %s\n", ligne);
        return NULL;
    }

    printf("Valeur lue : %s\n", val);

    Arbre nouveau_noeud = alloue_noeud(val);
    if (nouveau_noeud == NULL) {
        fprintf(stderr, "Erreur: Allocation de mémoire pour le nœud.\n");
        return NULL;
    }

    if (fgets(ligne, sizeof(ligne), fichier) == NULL || ligne[0] == '\n') {
        fprintf(stderr, "Erreur: Fin de fichier prématurée ou ligne vide pour "
                        "le sous-arbre gauche.\n");
        return NULL;
    }
    if (strncmp(ligne, "Gauche", 6) != 0) {
        fprintf(stderr,
                "Erreur: Formatage incorrect pour le sous-arbre gauche.\n");
        fprintf(stderr, "Contenu de la ligne : %s\n", ligne);
        return NULL;
    }

    printf("Ligne lue pour le sous-arbre gauche : %s\n", ligne);
    printf("Position actuelle dans le fichier après la lecture du sous-arbre "
           "gauche : %ld\n",
           ftell(fichier));

    nouveau_noeud->fg = charger_arbre_recursif(fichier);
    if (nouveau_noeud->fg == NULL && strcmp(val, "NULL") != 0) {
        fprintf(stderr, "Erreur: Lecture du sous-arbre gauche.\n");
        return NULL;
    }

    if (fgets(ligne, sizeof(ligne), fichier) == NULL || ligne[0] == '\n') {
        fprintf(stderr, "Erreur: Fin de fichier prématurée ou ligne vide pour "
                        "le sous-arbre droit.\n");
        return NULL;
    }
    if (strncmp(ligne, "Droite", 6) != 0) {
        fprintf(stderr,
                "Erreur: Formatage incorrect pour le sous-arbre droit.\n");
        fprintf(stderr, "Contenu de la ligne : %s\n", ligne);
        return NULL;
    }

    printf("Ligne lue pour le sous-arbre droit : %s\n", ligne);
    printf("Position actuelle dans le fichier après la lecture du sous-arbre "
           "droit : %ld\n",
           ftell(fichier));

    // Charger le sous-arbre droit
    nouveau_noeud->fd = charger_arbre_recursif(fichier);
    if (nouveau_noeud->fd == NULL && strcmp(val, "NULL") != 0) {
        fprintf(stderr, "Erreur: Lecture du sous-arbre droit.\n");
        return NULL;
    }

    return nouveau_noeud;
}

Arbre charger_arbre(char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return NULL;
    }

    Arbre A = charger_arbre_recursif(fichier);
    fclose(fichier);
    return A;
}

Arbre creer_noeud(const char *val) {
    Arbre n = (Arbre)malloc(sizeof(Arbre));
    if (n != NULL) {
        size_t length = strlen(val) + 1;
        n->val = (char *)malloc(length);
        if (n->val != NULL) {
            strncpy(n->val, val, length);
            n->fg = NULL;
            n->fd = NULL;
        } else {
            free(n);
            n = NULL;
        }
    }
    return n;
}

Arbre construire_arbre(FILE *fichier) {
    char buffer[100];
    if (fscanf(fichier, "%s", buffer) != 1) {
        return NULL;
    }

    if (strcmp(buffer, "0") == 0) {
        return NULL;
    } else {
        char val[100];
        fscanf(fichier, "%s", val);
        Arbre n = creer_noeud(val);
        n->fg = construire_arbre(fichier);
        n->fd = construire_arbre(fichier);
        return n;
    }
}

void afficher_arbre(Arbre racine, int niveau) {
    if (racine == NULL) {
        printf("NULL\n");
        return;
    }

    printf("Valeur : %s\n", racine->val);

    printf("  Gauche :\n");
    afficher_arbre(racine->fg, niveau + 1);

    printf("  Droite :\n");
    afficher_arbre(racine->fd, niveau + 1);
}