#include <stdlib.h>

#include "config.h"


int determinaFills(char tauler[N][N]);
Node *creaNode(Node *pare, int numFill);
void creaArbre(Node *arrel);
void esborraArbre(Node *arrel);
int posicioMaxim(double *v, int n);
int posicioMinim(double *v, int n);
Node *minimax(Node *arrel);
double heuristica(char tauler[N][N], int nivell);
