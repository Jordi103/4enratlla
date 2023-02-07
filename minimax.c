#include "minimax.h"


int determinaFills(char tauler[N][N]){
    int numFills, j;
    numFills=0;
    for (j=0; j<N; j++){
        if(determinaFila(tauler, j)>-1){
            numFills++;
        }
    }
    return numFills;
}

Node *creaNode(Node *pare, int numFill){
    Node *p=(Node*)malloc(sizeof(Node));
    p->nivell=pare->nivell+1;
    copiaTauler(p->tauler,pare->tauler);
    int columna; char jugador;
    columna=determinaColumna(p->tauler, numFill);
    if(p->nivell%2==1){
        jugador = ORD;
    } else {
        jugador = HUMA;
    }
    aplicarTirada(p->tauler,columna,jugador);
    if((p->nivell<NIV_MAX)&&(partidaAcabada(p->tauler,jugador)!=1)){
        p->n_fills=determinaFills(p->tauler);
        p->fills=(Node**)malloc(p->n_fills*sizeof(Node*));
    } else {
        p->n_fills=0;
        p->fills=NULL;
        p->valor=heuristica(p->tauler, p->nivell);
    }
    return p;
}

// passem el nivell del pare, aquest nivell és sempre estrictament inferior a NIV_MAX
void creaArbre(Node *pare){
    int i;
    for(i=0; i<pare->n_fills; i++){
        pare->fills[i]=creaNode(pare, i);
//      Si nivell+1=NIV_MAX el pare automaticament tindra n_fills=0
        creaArbre(pare->fills[i]);
    }
}

void esborraArbre(Node *arrel){
    int i;
    for(i=0; i<arrel->n_fills; i++) {
        esborraArbre(arrel->fills[i]);
    }
    if(arrel->n_fills>0){
    	free(arrel->fills);
    } 
    free(arrel);
}

int posicioMaxim(double *v, int n){
	int i,l;
	double M;
    l=0;
	M=v[0];
	for (i=1; i<n; i++){
		if (M<v[i]){
			M=v[i];
            l=i;
		}
	}
	return l;
}

int posicioMinim(double *v, int n){
	int i,l;
	double m;
    l=0;
	m = v[0];
	for (i=1; i<n; i++){
		if(m>v[i]){
			m=v[i];
            l=i;
		}
	}
	return l;
}

Node *minimax(Node *arrel){
	int i,l;
	double *v;
	if (arrel->n_fills==0){
		return arrel;
	} else {
		v = (double*)malloc(arrel->n_fills*sizeof(double));
		for (i=0; i<arrel->n_fills; i++){
			(arrel->fills[i])->valor=minimax(arrel->fills[i])->valor;
			v[i]=(arrel->fills[i])->valor;
		}	
		if (arrel->nivell%2==0){
			l=posicioMaxim(v, arrel->n_fills);
		} else {
		    l=posicioMinim(v, arrel->n_fills);
		}
        free(v);
        return arrel->fills[l];
	}
}

double heuristica(char tauler[N][N], int nivell){
    int h,o; char H, O;
    H=HUMA;
    O=ORD;
    h=partidaAcabada(tauler, H);
    o=partidaAcabada(tauler, O);
    if(h==1){
        return 0+0.01*1./nivell;
    }
    if(o==1){
        return 1-0.01*nivell;
    }
    return 0.5+(0.05*rand())/RAND_MAX;
}
