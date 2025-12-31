// HAMMOUDI DJAOUAD ABDERRAHMANE G02 Security
// Kaarouche Mohamed Djamel Eddine G02 Security

#include <stdio.h>
#include <string.h>

#define MAX 20

int n; 
int m;

int nt[MAX][MAX][MAX];    
int nt_size[MAX][MAX];      
int nt1[MAX][MAX][MAX];   
int nt1_size[MAX][MAX];     

int closure[MAX][MAX];     
int closure_size[MAX];      

char alphabets[MAX];     

void readTable() {
    char line[100];
    int i, j, temp;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols (excluding epsilon): ");
    scanf("%d", &m);

    printf("Enter input symbols:\n");
    for (i = 0; i < m; i++)
        scanf(" %c", &alphabets[i]);

    // Initialize sizes
    for (i = 0; i < n; i++)
        for (j = 0; j <= m; j++)
            nt_size[i][j] = 0;

    getchar();
    printf("Enter transitions for each state (space separated, empty = no transitions):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j <= m; j++) {
            printf("State %d, symbol %s: ", i, j==0?"ε":(char[]){alphabets[j-1],0});
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = 0; 

            nt_size[i][j] = 0; 

            if (strlen(line) == 0)  
                continue;

            char *p = line;
            while (*p) {
                if (*p >= '0' && *p <= '9') {
                    sscanf(p, "%d", &temp);
                    nt[i][j][nt_size[i][j]++] = temp;
                    while (*p >= '0' && *p <= '9') p++;
                } else p++;
            }
        }
    }
}
void computeClosures() {
    for (int i = 0; i < n; i++) {
        int vis[MAX] = {0};
        int queue[MAX], front=0, rear=0;

        queue[rear++] = i;
        vis[i] = 1;

        while (front < rear) {
            int s = queue[front++];
            for (int k = 0; k < nt_size[s][0]; k++) {
                int t = nt[s][0][k];
                if (!vis[t]) {
                    vis[t] = 1;
                    queue[rear++] = t;
                }
            }
        }

        closure_size[i] = 0;
        for (int j = 0; j < n; j++)
            if (vis[j])
                closure[i][closure_size[i]++] = j;
    }
}
void computeNewTransitions() {
    for (int i = 0; i < n; i++)
        for (int j = 1; j <= m; j++)
            nt1_size[i][j] = 0;

    for (int i = 0; i < n; i++) {
        for (int a = 1; a <= m; a++) {
            int used[MAX] = {0};
            for (int c = 0; c < closure_size[i]; c++) {
                int s = closure[i][c];
                for (int t = 0; t < nt_size[s][a]; t++) {
                    int dest = nt[s][a][t];
                    for (int k = 0; k < closure_size[dest]; k++) {
                        int d = closure[dest][k];
                        if (!used[d]) {
                            used[d] = 1;
                            nt1[i][a][nt1_size[i][a]++] = d;
                        }
                    }
                }
            }
        }
    }
}
void printNewTable() {
    printf("\nNFA without epsilon transitions:\n");
    printf("State\t");
    for (int a = 1; a <= m; a++)
        printf("%c\t", alphabets[a-1]);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t", i);
        for (int a = 1; a <= m; a++) {
            if (nt1_size[i][a] == 0)
                printf("{}\t");
            else {
                printf("{");
                for (int k = 0; k < nt1_size[i][a]; k++)
                    printf("%d ", nt1[i][a][k]);
                printf("}\t");
            }
        }
        printf("\n");
    }
}
int main() {
    readTable();
    computeClosures();
    computeNewTransitions();
    printNewTable();
    return 0;
}
