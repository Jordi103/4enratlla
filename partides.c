#include "partides.h"



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
