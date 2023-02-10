// Maximum tree depth for minimax
# define LVL_MAX 4

// Board size
# define N 8

// type of cell in board
# define EMPTY '.'
# define COMPUTER 'O'
# define HUMAN 'X'


// Maximum length for the name of a game
# define LW 20


// not configuration, here because it is common
typedef struct game{
	char (*boards)[N][N];
	int nturns;
	char name[LW];
} Game;

typedef struct node{
	struct node **children;
	int n_children;
    int level;
	char board[N][N];
	double value;
} Node;
