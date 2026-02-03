// HAMMOUDI DJAOUAD ABDERRAHMANE G02 Security
// Kaarouche Mohamed Djamel Eddine G02 Security

#include <stdio.h>
#include <string.h>

#define MAX 20

int nb_states;
int nb_symbols;
int trans[MAX][MAX][MAX]; // transitions
int t_size[MAX][MAX];

int new_trans[MAX][MAX][MAX];
int new_size[MAX][MAX];

int eps_clos[MAX][MAX]; // epsilon closure
int clos_size[MAX];

char symbols[MAX];

int final[MAX];
int nb_final;
int new_final[MAX];
int nb_new_final;

void read_nfa() {
    char line[100];
    int i, j, s;
    
    printf("Nombre d'etats: ");
    scanf("%d", &nb_states);
    
    printf("Nombre de symboles: ");
    scanf("%d", &nb_symbols);
    
    printf("Entrer les symboles:\n");
    for (i = 0; i < nb_symbols; i++)
        scanf(" %c", &symbols[i]);
    
    for (i = 0; i < nb_states; i++)
        for (j = 0; j <= nb_symbols; j++)
            t_size[i][j] = 0;
    
    getchar();
    printf("Entrer les transitions:\n");
    
    for (i = 0; i < nb_states; i++) {
        for (j = 0; j <= nb_symbols; j++) {
            if (j == 0)
                printf("Etat %d, epsilon: ", i);
            else
                printf("Etat %d, %c: ", i, symbols[j-1]);
            
            fgets(line, 100, stdin);
            line[strcspn(line, "\n")] = 0;
            
            if (strlen(line) == 0)
                continue;
            
            char *p = line;
            while (*p) {
                if (*p >= '0' && *p <= '9') {
                    sscanf(p, "%d", &s);
                    trans[i][j][t_size[i][j]++] = s;
                    while (*p >= '0' && *p <= '9') p++;
                } else p++;
            }
        }
    }
    
    printf("Nombre d'etats finaux: ");
    scanf("%d", &nb_final);
    
    printf("Etats finaux: ");
    for (i = 0; i < nb_final; i++)
        scanf("%d", &final[i]);
}

void calc_epsilon_closure() {
    int i, j, k;
    
    for (i = 0; i < nb_states; i++) {
        int vis[MAX] = {0};
        int q[MAX], f = 0, r = 0;
        
        q[r++] = i;
        vis[i] = 1;
        
        while (f < r) {
            int curr = q[f++];
            for (k = 0; k < t_size[curr][0]; k++) {
                int next = trans[curr][0][k];
                if (!vis[next]) {
                    vis[next] = 1;
                    q[r++] = next;
                }
            }
        }
        
        clos_size[i] = 0;
        for (j = 0; j < nb_states; j++)
            if (vis[j])
                eps_clos[i][clos_size[i]++] = j;
    }
}

void calc_new_transitions() {
    int i, a, c, t, k;
    
    for (i = 0; i < nb_states; i++)
        for (a = 1; a <= nb_symbols; a++)
            new_size[i][a] = 0;
    
    for (i = 0; i < nb_states; i++) {
        for (a = 1; a <= nb_symbols; a++) {
            int added[MAX] = {0};
            
            for (c = 0; c < clos_size[i]; c++) {
                int st = eps_clos[i][c];
                
                for (t = 0; t < t_size[st][a]; t++) {
                    int dest = trans[st][a][t];
                    
                    for (k = 0; k < clos_size[dest]; k++) {
                        int d = eps_clos[dest][k];
                        if (!added[d]) {
                            added[d] = 1;
                            new_trans[i][a][new_size[i][a]++] = d;
                        }
                    }
                }
            }
        }
    }
}

void calc_new_final() {
    int i, j, k;
    nb_new_final = 0;
    
    for (i = 0; i < nb_states; i++) {
        int ok = 0;
        for (j = 0; j < clos_size[i]; j++) {
            int st = eps_clos[i][j];
            for (k = 0; k < nb_final; k++) {
                if (st == final[k]) {
                    ok = 1;
                    break;
                }
            }
            if (ok) break;
        }
        if (ok)
            new_final[nb_new_final++] = i;
    }
}

void print_result() {
    int i, a, k;
    
    printf("\n--- NFA sans epsilon ---\n\n");
    
    printf("Etat\t");
    for (a = 1; a <= nb_symbols; a++)
        printf("%c\t", symbols[a-1]);
    printf("\n");
    
    for (i = 0; i < nb_states; i++) {
        printf("%d\t", i);
        for (a = 1; a <= nb_symbols; a++) {
            if (new_size[i][a] == 0) {
                printf("{}\t");
            } else {
                printf("{");
                for (k = 0; k < new_size[i][a]; k++) {
                    printf("%d", new_trans[i][a][k]);
                    if (k < new_size[i][a] - 1) printf(",");
                }
                printf("}\t");
            }
        }
        printf("\n");
    }
    
    printf("\nEtats finaux: {");
    for (i = 0; i < nb_new_final; i++) {
        printf("%d", new_final[i]);
        if (i < nb_new_final - 1) printf(", ");
    }
    printf("}\n");
}

int main() {
    read_nfa();
    calc_epsilon_closure();
    calc_new_transitions();
    calc_new_final();
    print_result();
    return 0;
}