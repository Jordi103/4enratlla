#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "4enratlla.h"
#include "minimax.c"
#include "partides.c"


int main(){
    srand(time(NULL));
    FILE *fitxer;
    fitxer=fopen("partides.dat", "r");
    if(fitxer==NULL){
        fitxer=fopen("partides.dat", "w");
        printf("No s'ha trobat el fitxer \"partides.dat\",  s'ha creat automàticament.\n");
        getchar();
    }
    fclose(fitxer);

    while(mostraMenu()!=1);

    return 0;
}

void inicialitza_tauler(char tauler[N][N]){
    int i,j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            tauler[i][j]=BUIDA;
        }
    }
}

// copia tauler 2 a tauler 1
void copiaTauler(char tauler1[N][N], char tauler2[N][N]){
    int i,j;
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            tauler1[i][j] = tauler2[i][j];
        }
    }
}

void mostra_tauler(char tauler[N][N]){
    int i,j;
    for(i=0; i<N; i++){
    	printf("%d ", i+1);
    }
    printf("\n");
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%c ", tauler[i][j]);
        } 
        printf("\n");
    }
    printf("\n");
}


// Trobar la k-essima columna lliure
int determinaColumna(char tauler[N][N], int k){
    int j,colLliure;
    colLliure=-1;
    j=0;
    while ((j<N) && (colLliure<=k)){
        if(tauler[0][j]==BUIDA){
            colLliure++;
        }
        if(colLliure==k){
            return j;
        }
        j++;
    }
    return -1;
}
        

int determinaFila(char tauler[N][N], int columna){
    int i;
    for (i=0; i<N; i++){
        if(tauler[i][columna]!=BUIDA){
            return i-1;
        }
    }
    return N-1;
}
    
// char jugador= ORD,JGDR
void aplicarTirada(char tauler[N][N], int columna, char jugador){
    int fila;
    fila=determinaFila(tauler, columna);
    tauler[fila][columna]=jugador;
}


        




int partidaAcabada(char tauler[N][N], char jugador){
    int i, j, k, ratxa;
//  Mirem per files
    for (i=0; i<N; i++){
        ratxa=0;
        for (j=0; j<N; j++){
            if(tauler[i][j]==jugador){
                ratxa += 1;
                if(ratxa==4){
                    return 1;
                }
            } else {
                ratxa=0;
            }
        }
    }
//  Mirem per columnes
    for (j=0; j<N; j++){
        ratxa=0;
        for (i=0; i<N; i++){
            if(tauler[i][j]==jugador){
                ratxa+=1;
                if(ratxa==4){
                    return 1;
                }
            } else {
                ratxa=0;
            }
        }
    }
//  Mirem les diagonals 
    for (i=0; i<N; i++){
        ratxa=0;
        for(k=max(-i,1-N+i); k<=min(i,N-i-1); k++){
            if(tauler[i+k][i-k]==jugador){
                ratxa+=1;
                if(ratxa==4){
                    return 1;
                }
            } else {
                ratxa=0;
            }
        }
    }
//  Mateixa direcció, una casella desplaçada
    for (i=0; i<N; i++){
        ratxa=0;
        for(k=max(2-N+i,-i); k<=min(N-1-i,i+1); k++){
            if(tauler[i+1-k][i+k]==jugador){
                ratxa+=1;
                if(ratxa==4){
                    return 1;
                }
            } else {
                ratxa=0;
            }
        }
    }

    for (i=0; i<N; i++){
        ratxa=0;
        for(k=max(1-N+i,-i); k<=min(i,N-1-i); k++){
            if(tauler[N-1-i+k][i+k]==jugador){
                ratxa+=1;
                if(ratxa==4){
                    return 1;
                }
            } else {
                ratxa=0;
            }
        }
    }
    for (i=0; i<N; i++){
        ratxa=0;
        for(k=max(1-N+i,-i-1); k<=min(i,N-2-i); k++){
            if(tauler[N-1-i+k][i+1+k]==jugador){
                ratxa+=1;
                if(ratxa==4){
                    return 1;
                }
            } else {
                ratxa=0;
            }
        }
    }
//  Mirem si hi ha alguna casella buida al tauler.
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(tauler[i][j]==BUIDA){
                return 0;
            }
        }
    }
    return 1;
}

int mostraMenu(void){
    int i;
    Partida *P;
    char c, nom[LW];
    FILE *partides;
    partides=fopen("partides.dat", "r+");
    system("clear");
	printf("========================4ENRATLLA=========================\n");
	printf("1. Jugar partida nova.\n");
	printf("2. Veure partida anterior.\n");
    printf("\n0. Sortir.\n");
    scanf("%d", &i); getchar();
    system("clear");
    if (i==1){
        P=jugar_partida();
        printf("Voleu enregistrar la partida?[s/n]\n");
        scanf("%c", &c); getchar();
        if(c=='s'){
            printf("Doneu-li un nom 20 o menys caràcters:\n");
            scanf("%s", nom); getchar();
            while(nomValid(partides, nom)==1){
                printf("Si us plau introduiu un nom no utilitzat. Els noms en ús són:\n");
                llegeixNoms(partides);
                scanf("%s", nom); getchar();
            }
            copiaCadena(P->nom, nom, len(nom));
            escriuPartida(partides, P);
        }
        free(P);
    }
    if(i==2){
        llegeixNoms(partides);
        printf("\nQuina partida voleu veure? \n");
        scanf("%s", nom); getchar();
        P=trobaPartida(partides, nom);
        veurePartida(P);
        free(P);
    }
    if(i==0){
        return 1;
    }
    fclose(partides);
    return 0;
}
