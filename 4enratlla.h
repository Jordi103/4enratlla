# define N 8
# define BUIDA '.'
# define ORD 'O'
# define HUMA 'X'

# define max(x,y) ((x>y)?x:y)
# define min(x,y) ((x>y)?y:x)


char ordinador = ORD;
char huma = HUMA;


void inicialitza_tauler(char tauler[N][N]);
void copiaTauler(char tauler1[N][N], char tauler2[N][N]);
void mostra_tauler(char tauler[N][N]);
int determinaColumna(char tauler[N][N] ,int k);
int determinaFila(char tauler[N][N], int columna);
void aplicarTirada(char tauler[N][N], int columna, char jugador);
int partidaAcabada(char tauler[N][N], char jugador);
int mostraMenu(void);
