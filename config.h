// Profunditat de l'arbre en el minimax
# define LVL_MAX 4

// Mida del tauler
# define N 8

// Tipus de casella en el tauler
# define EMPTY '.'
# define COMPUTER 'O'
# define HUMAN 'X'

//char ordinador = ORD;
//char huma = HUMA;

// Longitud màxima del nom d'una partida
# define LW 20


// Struct per emmagatzemar partides.
// No és un paràmetre de configuració, però és comú a diversos fitxers
// i per això el definim aquí.
typedef struct game{
	char (*boards)[N][N];
	int nturns;
	char name[LW];
} Game;

// Definició de Node, en aquest fitxer pel mateix motiu
typedef struct node{
	struct node **children;
	int n_children;
    int level;
	char board[N][N];
	double value;
} Node;
