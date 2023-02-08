#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "config.h"
#include "4enratlla.h"
#include "minimax.h"


int determine_children(char board[N][N]){
    int n_children, j;
    n_children=0;
    for (j=0; j<N; j++){
        if(determine_row(board, j)>-1){
            n_children++;
        }
    }
    return n_children;
}

Node *new_node(Node *parent, int child_num){
    Node *p=(Node*)malloc(sizeof(Node));
    p->level=parent->level+1;
    copy_board(p->board,parent->board);
    int column; char player;
    column=determine_column(p->board, child_num);
    if(p->level%2==1){
        player = COMPUTER;
    } else {
        player = HUMAN;
    }
    apply_roll(p->board,column,player);
    if((p->level<LVL_MAX)&&(game_finished(p->board,player)!=1)){
        p->n_children=determine_children(p->board);
        p->children=(Node**)malloc(p->n_children*sizeof(Node*));
    } else {
        p->n_children=0;
        p->children=NULL;
        p->value=heuristic(p->board, p->level);
    }
    return p;
}

// passem el level del parent, aquest level és sempre estrictament inferior a LVL_MAX
void new_tree(Node *parent){
    int i;
    for(i=0; i<parent->n_children; i++){
        parent->children[i]=new_node(parent, i);
//      Si level+1=LVL_MAX el parent automaticament tindra n_children=0
        new_tree(parent->children[i]);
    }
}

void delete_tree(Node *root){
    int i;
    for(i=0; i<root->n_children; i++) {
        delete_tree(root->children[i]);
    }
    if(root->n_children>0){
    	free(root->children);
    } 
    free(root);
}

int argmax(double *v, int n){
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

int argmin(double *v, int n){
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

Node *minimax(Node *root){
	int i,l;
	double *v;
	if (root->n_children==0){
		return root;
	} else {
		v = (double*)malloc(root->n_children*sizeof(double));
		for (i=0; i<root->n_children; i++){
			(root->children[i])->value=minimax(root->children[i])->value;
			v[i]=(root->children[i])->value;
		}	
		if (root->level%2==0){
			l=argmax(v, root->n_children);
		} else {
		    l=argmin(v, root->n_children);
		}
        free(v);
        return root->children[l];
	}
}

double heuristic(char board[N][N], int level){
    int h,o; char H, O;
    H=HUMAN;
    O=COMPUTER;
    h=game_finished(board, H);
    o=game_finished(board, O);
    if(h==1){
        return 0+0.01*1./level;
    }
    if(o==1){
        return 1-0.01*level;
    }
    return 0.5+(0.05*rand())/RAND_MAX;
}
