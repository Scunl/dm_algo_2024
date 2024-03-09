typedef struct noeud {
    char * mot;
    struct noeud *fg, *fd;
} Noeud, *Arbre;

Noeud * alloue_noeud(char * mot);
void parcours_infixe(Arbre A);
Noeud * ajout(Arbre *A, char * mot);
Noeud * extrait_max(Arbre *A);
Noeud * suppression(Arbre * A, char * mot);
void libere(Arbre * A);
void dessine(char * nom, Arbre A);
int filtrage(Arbre *A, Arbre filtre, Arbre *utilises);