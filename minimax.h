
int determine_children(char board[N][N]);
Node *new_node(Node *parent, int child_number);
void new_tree(Node *root);
void delete_tree(Node *root);
int argmax(double *v, int n);
int argmin(double *v, int n);
Node *minimax(Node *root);
double heuristic(char board[N][N], int level);
