#include "ABR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Noeud *alloue_noeud(char *mot) {
    Noeud *n = (Noeud *)malloc(sizeof(Noeud));
    if (n != NULL) {
        n->mot = strdup(mot);
        n->fg = NULL;
        n->fd = NULL;
    }
    return n;
}

void parcours_infixe(Arbre A) {
    if (A != NULL) {
        parcours_infixe(A->fg);
        printf("%s\n", A->mot);
        parcours_infixe(A->fd);
    }
}

Noeud *ajout(Arbre *A, char *mot) {
    if (!*A) {
        *A = alloue_noeud(mot);
        return *A;
    } else {
        int cmp = strcmp(mot, (*A)->mot);
        if (cmp < 0) {
            return ajout(&((*A)->fg), mot);
        } else if (cmp > 0) {
            return ajout(&((*A)->fd), mot);
        } else {
            return NULL;
        }
    }
}

Noeud *extrait_max(Arbre *A) {
    if (*A == NULL) {
        return NULL;
    } else if ((*A)->fd == NULL) {
        Noeud *n = *A;
        *A = (*A)->fg;
        return n;
    } else {
        return extrait_max(&((*A)->fd));
    }
}

Noeud *suppression(Arbre *A, char *mot) {
    if (*A == NULL) {
        return NULL;
    } else {
        int cmp = strcmp(mot, (*A)->mot);
        if (cmp < 0) {
            return suppression(&((*A)->fg), mot);
        } else if (cmp > 0) {
            return suppression(&((*A)->fd), mot);
        } else {
            Noeud *n = *A;
            if ((*A)->fg == NULL) {
                *A = (*A)->fd;
            } else if ((*A)->fd == NULL) {
                *A = (*A)->fg;
            } else {
                Noeud *max_fg = extrait_max(&((*A)->fg));
                max_fg->fg = (*A)->fg;
                max_fg->fd = (*A)->fd;
                *A = max_fg;
            }
            return n;
        }
    }
}

void liberer(Arbre *A) {
    if (*A != NULL) {
        libere(&((*A)->fg));
        libere(&((*A)->fd));
        free((*A)->mot);
        free(*A);
        *A = NULL;
    }
}

void ecrireDebut(FILE *f) {
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "    node [ shape = record , height = .1 ]\n");
    fprintf(f,
            "    edge [ tailclip = false , arrowtail = dot , dir = both ];\n");
}

void ecrireFin(FILE *f) {
    fprintf(f, "}\n");
}

void ecrireArbre(FILE *f, Arbre A) {
    fprintf(f, "n%p [label =\"<gauche> | <valeur> %s | <droit>\"];\n",
            (void *)A, A->mot);

    if (A->fg) {
        ecrireArbre(f, A->fg);
        fprintf(f, "n%p: gauche : c -> n%p: valeur;\n", (void *)A,
                (void *)A->fg);
    }

    if (A->fd) {
        ecrireArbre(f, A->fd);
        fprintf(f, "n%p: droit : c -> n%p: valeur;\n", (void *)A,
                (void *)A->fd);
    }
}

void dessine(char *nom, Arbre A) {
    FILE *f = fopen(nom, "w");
    if (f == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
    }

    if (!f)
        return;

    ecrireDebut(f);
    ecrireArbre(f, A);
    ecrireFin(f);

    fclose(f);
    char commande[100];
    sprintf(commande, "dot -Tpdf %s -o %s.pdf", nom, nom);
    system(commande);
}

int cree_arbre(char *nom, Arbre *A) {
    char buffer[512];
    char separators[] = " \n,;:.?!\"()-’'";
    char *token;
    FILE *fichier = fopen(nom, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    while (fgets(buffer, 512, fichier) != NULL) {
        token = strtok(buffer, separators);
        while (token != NULL) {
            ajout(A, token);
            token = strtok(NULL, separators);
        }
    }
    fclose(fichier);
    return 1;
}

int main(int argc, char *argv[]) {
    Arbre a = NULL;
    cree_arbre("filtre.txt", &a);
    dessine("fichier", a);
    suppression(&a, "arbre");
    dessine("fichier2", a);
    libere(&a);
    libere(&a);
    return 0;
}
