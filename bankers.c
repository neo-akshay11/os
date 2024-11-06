#include <stdio.h>
#include <stdbool.h>

#define maxp 10
#define maxr 10

int alloc[maxp][maxr];
int need[maxp][maxr];
int avail[maxr];
int maxi[maxp][maxr];

int n, m;

void calc_need() {
    // Calculate need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxi[i][j] - alloc[i][j];
        }
    }
}

bool is_safe() {
    int work[maxr];
    bool finish[maxp] = {false};
    int safe_seq[maxp];
    int cnt = 0;

    // Initialize work as available resources
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    while (cnt < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == m) {
                    // If all resources for process i are available
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    safe_seq[cnt++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false; // No safe sequence found
        }
    }

    printf("Safe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safe_seq[i]);
    }
    printf("\n");
    return true;
}

void request_res(int pid) {
    int request[maxr];

    printf("Enter the request for P%d:\n", pid);
    for (int i = 0; i < m; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &request[i]);
    }

    // Check if request is valid
    for (int i = 0; i < m; i++) {
        if (request[i] > need[pid][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
        if (request[i] > avail[i]) {
            printf("Resources not available.\n");
            return;
        }
    }

    // Pretend to allocate resources
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    if (is_safe()) {
        printf("Resources allocated to process P%d.\n", pid);
    } else {
        printf("System is not in a safe state after allocation. Rolling back.\n");
        // Rollback allocation
        for (int i = 0; i < m; i++) {
            avail[i] += request[i];
            alloc[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &avail[i]);
    }

    printf("Enter the maximum demand of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &maxi[i][j]);
        }
    }

    printf("Enter the allocation for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &alloc[i][j]);
        }
    }

    calc_need();

    if (is_safe()) {
        int pid;
        printf("Enter process id to request resources (0 to %d): ", n - 1);
        scanf("%d", &pid);

        request_res(pid);
    } else {
        printf("System is not in a safe state initially!\n");
    }

    return 0;
}
