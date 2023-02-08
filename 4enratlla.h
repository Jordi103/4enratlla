

# define max(x,y) ((x>y)?x:y)
# define min(x,y) ((x>y)?y:x)


// antic 4enratlla
void inicialitza_tauler(char tauler[N][N]);
void copiaTauler(char tauler1[N][N], char tauler2[N][N]);
void mostra_tauler(char tauler[N][N]);
int determinaColumna(char tauler[N][N] ,int k);
int determinaFila(char tauler[N][N], int columna);
void aplicarTirada(char tauler[N][N], int columna, char jugador);
int partidaAcabada(char tauler[N][N], char jugador);
int mostraMenu(void);

// antic partides
void escriuTauler(FILE *fitxer, char tauler[N][N]);
void llegeixTauler(FILE *fitxer, char tauler[N][N]);
void escriuPartida(FILE *fitxer, Partida *P);
Partida *llegeixPartida(FILE *fitxer);
void veurePartida(Partida *P);
void llegeixNoms(FILE *fitxer);
Partida *trobaPartida(FILE *fitxer, char nom[LW]);
int len(char *str);
int comparaCadenes(char *cad1, char *cad2);
void copiaCadena(char *cad1, char *cad2, int n);
int nomValid(FILE *fitxer, char nom[LW]);
