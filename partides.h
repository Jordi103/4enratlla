# define LW 20

typedef struct partida{
	char (*taulers)[N][N];
	int ntorns;
	char nom[LW];
} Partida;


Partida *jugar_partida(void);
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