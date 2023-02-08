

# define max(x,y) ((x>y)?x:y)
# define min(x,y) ((x>y)?y:x)


// antic 4enratlla
void initialize_board(char board[N][N]);
void copy_board(char board1[N][N], char board2[N][N]);
void show_board(char board[N][N]);
int determine_column(char board[N][N] ,int k);
int determine_row(char board[N][N], int column);
void apply_roll(char board[N][N], int column, char player);
int game_finished(char board[N][N], char player);
Game *play_game(void);
int show_menu(void);

// antic partides
void write_board(FILE *filename, char board[N][N]);
void read_board(FILE *filename, char board[N][N]);
void write_game(FILE *filename, Game *G);
Game *read_game(FILE *filename);
void watch_game(Game *P);
void read_names(FILE *filename);
Game *find_game(FILE *filename, char name[LW]);
int len(char *str);
int compare_strings(char *str1, char *str2);
void copy_string(char *str1, char *str2, int n);
int valid_name(FILE *filename, char name[LW]);
