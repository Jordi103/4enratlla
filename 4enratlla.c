#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "config.h"

#include "4enratlla.h"
#include "minimax.h"


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

Partida *jugar_partida(void){
    int i;
    char tauler[N][N];
    Node *arrel;
    Partida *P;
    P=(Partida*)malloc(sizeof(Partida));
    P->taulers=(char(*)[N][N])malloc(N*N*sizeof(char[N][N]));
    P->ntorns=0;
    inicialitza_tauler(tauler);
    char opcio_inicial;
    printf("Voleu fer la primera tirada?[s/n]\n");
    scanf("%c",&opcio_inicial); getchar();
    if (opcio_inicial==110){
        aplicarTirada(tauler, rand()%8, ORD);
        copiaTauler(P->taulers[0], tauler);
        P->ntorns++;
    }
    system("clear");
    mostra_tauler(tauler);
    while(1){
        printf("Pròxima tirada?[1-8]\n");
        scanf("%d", &i); getchar();
        printf("\n");
        aplicarTirada(tauler, max(0,min(i-1,7)), HUMA);
        system("clear");
        mostra_tauler(tauler);
        copiaTauler(P->taulers[P->ntorns], tauler); P->ntorns++;
        if(partidaAcabada(tauler,HUMA)==1){
            printf("Has guanyat!\n");
            mostra_tauler(tauler);
            break;
        }
        arrel = (Node*)malloc(sizeof(Node));
        copiaTauler(arrel->tauler,tauler);
        arrel->nivell=0;
        arrel->n_fills=determinaFills(tauler);
        arrel->fills=(Node**)malloc(arrel->n_fills*sizeof(Node*));
        creaArbre(arrel);
        copiaTauler(tauler, minimax(arrel)->tauler);
        esborraArbre(arrel);
        copiaTauler(P->taulers[P->ntorns], tauler); P->ntorns++;
        system("clear");
        mostra_tauler(tauler);
        if(partidaAcabada(tauler,ORD)==1){
            printf("Guanya l'ordinador.\n");
            break;
        }
    }
    getchar();
    return P;
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


// antic partides
void escriuTauler(FILE *fitxer, char tauler[N][N]){
	int i, j;
	for (i=0; i<N; i++){
		for(j=0; j<N; j++){
			fprintf(fitxer, "%c",tauler[i][j]);
		}
	}
	fprintf(fitxer, " \n");
}

void llegeixTauler(FILE *fitxer, char tauler[N][N]){
	int i, j; char linia[N*N];
	fscanf(fitxer, "%s", linia);
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			tauler[i][j]=linia[i*N+j];
		}
	}
}

void escriuPartida(FILE *fitxer, Partida *P){
	char c;
	while(fscanf(fitxer, "%c", &c)!=EOF);
	fprintf(fitxer, "# \n");
	fprintf(fitxer, "%s \n", P->nom);
	fprintf(fitxer, "%d \n", P->ntorns);
	int i;
	for (i=0; i<P->ntorns; i++){
		escriuTauler(fitxer, P->taulers[i]);
	}
}

Partida *llegeixPartida(FILE *fitxer){
	Partida *P;
	P=(Partida*)malloc(sizeof(Partida));
	fscanf(fitxer, "%s", P->nom); 
	fscanf(fitxer, "%d", &(P->ntorns));
	P->taulers=(char(*)[N][N])malloc(P->ntorns*sizeof(char[N][N]));
	int k;
	for(k=0; k<P->ntorns; k++){
		llegeixTauler(fitxer, P->taulers[k]);
	}
	return P;
}

void veurePartida(Partida *P){
	int k;
	for(k=0; k<P->ntorns; k++){
		system("clear");
		printf("%s\n",P->nom);
		printf("Tirada %d de %d.\n", k+1, P->ntorns);
		mostra_tauler(P->taulers[k]);
		getchar();
	}
}

void llegeixNoms(FILE *fitxer){
    char c, nom[LW];
    int s;
    rewind(fitxer);
    printf("Partides enregistrades:\n");
    do {
        s=fscanf(fitxer, "%c", &c);
        if(c=='#'){
            fscanf(fitxer, "%s", nom);
            printf("%s\n", nom);
        }
    } while (s!=EOF);
}

Partida *trobaPartida(FILE *fitxer, char nom[LW]){
    char c;
    int s;
    Partida *P;
    rewind(fitxer);
    do {
        s=fscanf(fitxer, "%c", &c);
        if(c=='#'){
            P=llegeixPartida(fitxer);
            if(comparaCadenes(nom, P->nom)==0){
                return P;
            }
            free(P);
        }
    } while(s!=EOF);
    printf("No s'ha trobat la partida \"%s\".\n", nom);
    printf("Introduiu un nom de partida vàlid.\n");
    scanf("%s", nom); getchar();
    P=trobaPartida(fitxer, nom);
    return P;
}
 
int len(char *str){
    int i=0;
    while (str[i]!='\0'){
        i++;
    }
    return i;
}

int comparaCadenes(char *cad1, char *cad2){
    int i, l1, l2;
    l1=len(cad1);
    l2=len(cad2);
    if(l1!=l2){
        return 1;
    }
    for (i=0; i<l1; i++){
        if (cad1[i]!=cad2[i]){
            return 1;
        }
    }
    return 0;
}

void copiaCadena(char *cad1, char *cad2, int n){
    int i;
    for (i=0; i<n; i++){
        cad1[i]=cad2[i];
    }
}

int nomValid(FILE *fitxer, char nom[LW]){
    char c;
    int s;
    Partida *P;
    rewind(fitxer);
    do {
        s=fscanf(fitxer, "%c", &c);
        if(c=='#'){
            P=llegeixPartida(fitxer);
            if(comparaCadenes(nom, P->nom)==0){
                return 1;
            }
            free(P);
        }
    } while(s!=EOF);
    return 0;
}


