// Profunditat de l'arbre en el minimax
# define NIV_MAX 4

// Mida del tauler
# define N 8

// Tipus de casella en el tauler
# define BUIDA '.'
# define ORD 'O'
# define HUMA 'X'

char ordinador = ORD;
char huma = HUMA;

// Longitud màxima del nom d'una partida
# define LW 20


// Struct per emmagatzemar partides.
// No és un paràmetre de configuració, però és comú a diversos fitxers
// i per això el definim aquí.
typedef struct partida{
	char (*taulers)[N][N];
	int ntorns;
	char nom[LW];
} Partida;

// Definició de Node, en aquest fitxer pel mateix motiu
typedef struct node{
	struct node **fills;
	int n_fills;
    int nivell;
	char tauler[N][N];
	double valor;
} Node;