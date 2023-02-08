#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "config.h"

#include "4enratlla.h"
#include "minimax.h"


int main(){
    srand(time(NULL));
    FILE *filename;
    filename=fopen("games.dat", "r");
    if(filename==NULL){
        filename=fopen("games.dat", "w");
        printf("Could not find \"games.dat\", created it right now.\n");
        getchar();
    }
    fclose(filename);

    while(show_menu()!=1);

    return 0;
}

void initialize_board(char board[N][N]){
    int i,j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            board[i][j]=EMPTY;
        }
    }
}

// copia board 2 a board 1
void copy_board(char board1[N][N], char board2[N][N]){
    int i,j;
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            board1[i][j] = board2[i][j];
        }
    }
}

void show_board(char board[N][N]){
    int i,j;
    for(i=0; i<N; i++){
    	printf("%d ", i+1);
    }
    printf("\n");
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%c ", board[i][j]);
        } 
        printf("\n");
    }
    printf("\n");
}


// Trobar la k-essima columna lliure
int determine_column(char board[N][N], int k){
    int j,colLliure;
    colLliure=-1;
    j=0;
    while ((j<N) && (colLliure<=k)){
        if(board[0][j]==EMPTY){
            colLliure++;
        }
        if(colLliure==k){
            return j;
        }
        j++;
    }
    return -1;
}
        

int determine_row(char board[N][N], int columna){
    int i;
    for (i=0; i<N; i++){
        if(board[i][columna]!=EMPTY){
            return i-1;
        }
    }
    return N-1;
}
    
// char jugador= COMPUTER,JGDR
void apply_roll(char board[N][N], int columna, char jugador){
    int fila;
    fila=determine_row(board, columna);
    board[fila][columna]=jugador;
}





int game_finished(char board[N][N], char jugador){
    int i, j, k, ratxa;
//  Mirem per files
    for (i=0; i<N; i++){
        ratxa=0;
        for (j=0; j<N; j++){
            if(board[i][j]==jugador){
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
            if(board[i][j]==jugador){
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
            if(board[i+k][i-k]==jugador){
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
            if(board[i+1-k][i+k]==jugador){
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
            if(board[N-1-i+k][i+k]==jugador){
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
            if(board[N-1-i+k][i+1+k]==jugador){
                ratxa+=1;
                if(ratxa==4){
                    return 1;
                }
            } else {
                ratxa=0;
            }
        }
    }
//  Mirem si hi ha alguna casella buida al board.
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(board[i][j]==EMPTY){
                return 0;
            }
        }
    }
    return 1;
}

Game *play_game(void){
    int i;
    char board[N][N];
    Node *root;
    Game *G;
    G=(Game *)malloc(sizeof(Game));
    G->boards=(char(*)[N][N])malloc(N*N*sizeof(char[N][N]));
    G->nturns=0;
    initialize_board(board);
    char initial_option;
    printf("Voleu fer la primera tirada?[s/n]\n");
    scanf("%c",&initial_option); getchar();
    if (initial_option==110){
        apply_roll(board, rand()%8, COMPUTER);
        copy_board(G->boards[0], board);
        G->nturns++;
    }
    system("clear");
    show_board(board);
    while(1){
        printf("Pròxima tirada?[1-8]\n");
        scanf("%d", &i); getchar();
        printf("\n");
        apply_roll(board, max(0,min(i-1,7)), HUMAN);
        system("clear");
        show_board(board);
        copy_board(G->boards[G->nturns], board); G->nturns++;
        if(game_finished(board,HUMAN)==1){
            printf("Has guanyat!\n");
            show_board(board);
            break;
        }
        root = (Node*)malloc(sizeof(Node));
        copy_board(root->board,board);
        root->level=0;
        root->n_children=determine_children(board);
        root->children=(Node**)malloc(root->n_children*sizeof(Node*));
        new_tree(root);
        copy_board(board, minimax(root)->board);
        delete_tree(root);
        copy_board(G->boards[G->nturns], board); G->nturns++;
        system("clear");
        show_board(board);
        if(game_finished(board,COMPUTER)==1){
            printf("Guanya l'ordinador.\n");
            break;
        }
    }
    getchar();
    return G;
}


int show_menu(void){
    int i;
    Game *G;
    char c, name[LW];
    FILE *games;
    games=fopen("games.dat", "r+");
    system("clear");
	printf("========================4ENRATLLA=========================\n");
	printf("1. Jugar partida nova.\n");
	printf("2. Veure partida anterior.\n");
    printf("\n0. Sortir.\n");
    scanf("%d", &i); getchar();
    system("clear");
    if (i==1){
        G=play_game();
        printf("Voleu enregistrar la partida?[s/n]\n");
        scanf("%c", &c); getchar();
        if(c=='s'){
            printf("Doneu-li un name 20 o menys caràcters:\n");
            scanf("%s", name); getchar();
            while(valid_name(games, name)==1){
                printf("Si us plau introduiu un name no utilitzat. Els names en ús són:\n");
                read_names(games);
                scanf("%s", name); getchar();
            }
            copy_string(G->name, name, len(name));
            write_game(games, G);
        }
        free(G);
    }
    if(i==2){
        read_names(games);
        printf("\nQuina partida voleu veure? \n");
        scanf("%s", name); getchar();
        G=find_game(games, name);
        watch_game(G);
        free(G);
    }
    if(i==0){
        return 1;
    }
    fclose(games);
    return 0;
}


// antic partides
void write_board(FILE *filename, char board[N][N]){
	int i, j;
	for (i=0; i<N; i++){
		for(j=0; j<N; j++){
			fprintf(filename, "%c",board[i][j]);
		}
	}
	fprintf(filename, " \n");
}

void read_board(FILE *filename, char board[N][N]){
	int i, j; char linia[N*N];
	fscanf(filename, "%s", linia);
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			board[i][j]=linia[i*N+j];
		}
	}
}

void write_game(FILE *filename, Game *G){
	char c;
	while(fscanf(filename, "%c", &c)!=EOF);
	fprintf(filename, "# \n");
	fprintf(filename, "%s \n", G->name);
	fprintf(filename, "%d \n", G->nturns);
	int i;
	for (i=0; i<G->nturns; i++){
		write_board(filename, G->boards[i]);
	}
}

Game *read_game(FILE *filename){
	Game *G;
	G=(Game*)malloc(sizeof(Game));
	fscanf(filename, "%s", G->name); 
	fscanf(filename, "%d", &(G->nturns));
	G->boards=(char(*)[N][N])malloc(G->nturns*sizeof(char[N][N]));
	int k;
	for(k=0; k<G->nturns; k++){
		read_board(filename, G->boards[k]);
	}
	return G;
}

void watch_game(Game *G){
	int k;
	for(k=0; k<G->nturns; k++){
		system("clear");
		printf("%s\n",G->name);
		printf("Tirada %d de %d.\n", k+1, G->nturns);
		show_board(G->boards[k]);
		getchar();
	}
}

void read_names(FILE *filename){
    char c, name[LW];
    int s;
    rewind(filename);
    printf("Partides enregistrades:\n");
    do {
        s=fscanf(filename, "%c", &c);
        if(c=='#'){
            fscanf(filename, "%s", name);
            printf("%s\n", name);
        }
    } while (s!=EOF);
}

Game *find_game(FILE *filename, char name[LW]){
    char c;
    int s;
    Game *G;
    rewind(filename);
    do {
        s=fscanf(filename, "%c", &c);
        if(c=='#'){
            G=read_game(filename);
            if(compare_strings(name, G->name)==0){
                return G;
            }
            free(G);
        }
    } while(s!=EOF);
    printf("No s'ha trobat la partida \"%s\".\n", name);
    printf("Introduiu un name de partida vàlid.\n");
    scanf("%s", name); getchar();
    G=find_game(filename, name);
    return G;
}
 
int len(char *str){
    int i=0;
    while (str[i]!='\0'){
        i++;
    }
    return i;
}

int compare_strings(char *cad1, char *cad2){
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

void copy_string(char *cad1, char *cad2, int n){
    int i;
    for (i=0; i<n; i++){
        cad1[i]=cad2[i];
    }
}

int valid_name(FILE *filename, char name[LW]){
    char c;
    int s;
    Game *G;
    rewind(filename);
    do {
        s=fscanf(filename, "%c", &c);
        if(c=='#'){
            G=read_game(filename);
            if(compare_strings(name, G->name)==0){
                return 1;
            }
            free(G);
        }
    } while(s!=EOF);
    return 0;
}


