// Scheduling Algorithms
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct Process{
    int pid;
    int at;
    int bt;
    int pr;
    int ct;
    int tat;
    int wt;
};

void sortByAT(struct Process * p, int n){
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(p[i].at > p[j].at){
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void displayProcess(struct Process * p, int n){
    printf("\n\n+----------+----------+----------+----------+----------+----------+----------+");
    printf("\n|   PID    |    AT    |    BT    |    PR    |    CT    |   TAT    |    WT    |");
    printf("\n+----------+----------+----------+----------+----------+----------+----------+");
    for(int i=0; i<n; i++){
        printf("\n| %-8d | %-8d | %-8d | %-8d | %-8d | %-8d | %-8d |", p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\n+----------+----------+----------+----------+----------+----------+----------+");
}

void FCFS(struct Process * p, int n){
    int _ct = 0;
    printf("\n=== First Come First Serve ===");
    printf("\nGantt Chart :");
    printf("\n(0) |");
    for(int i=0; i<n; i++){
        _ct += p[i].bt;
        p[i].ct = _ct;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        printf(" P%d (%d) |", p[i].pid, p[i].ct);
    }
}

void SJF_P(struct Process * p, int n){
    printf("\n=== Shortest Job First (Pre-emptive) ===");
    int TimeGiven[100000] = {0};
    printf("\nGantt Chart :");
    printf("\n(0) |");
    int _t = 0;
    int completed = 0;
    while(completed < n){
        int min_bt = 10000000;
        int ind = -1;
        for(int i=0; i<n; i++){
            if(p[i].at <= _t && p[i].bt < min_bt && TimeGiven[i] != p[i].bt){
                min_bt = p[i].bt;
                ind = i;
            }
        }
        _t++;
        if(ind != -1){
            TimeGiven[ind] ++;
            if(TimeGiven[ind] == p[ind].bt){
                p[ind].ct = _t;
                p[ind].tat = p[ind].ct - p[ind].at;
                p[ind].wt = p[ind].tat - p[ind].bt;
                completed++;
                printf(" P%d (%d) |", p[ind].pid, p[ind].ct);
            }
        }
    }
}

void SJF_NP(struct Process * p, int n){
    printf("\n=== Shortest Job First (Non Pre-emptive) ===");
    int TimeGiven[100000] = {0};
    printf("\nGantt Chart :");
    printf("\n(0) |");
    int _t = 0;
    int completed = 0;
    while(completed < n){
        int min_bt = 10000000;
        int ind = -1;
        for(int i=0; i<n; i++){
            if(p[i].at <= _t && p[i].bt < min_bt && TimeGiven[i] != p[i].bt){
                min_bt = p[i].bt;
                ind = i;
            }
        }
        if(ind != -1){
            p[ind].ct = _t + p[ind].bt;
            _t += p[ind].bt;
            p[ind].tat = p[ind].ct - p[ind].at;
            p[ind].wt = p[ind].tat - p[ind].bt;
            TimeGiven[ind] += p[ind].bt;
            completed++;
            printf(" P%d (%d) |", p[ind].pid, p[ind].ct);
        }
        else{
            _t++;
        }
    }
}

// numerically lowest is the highest priority
void PR_P(struct Process * p, int n){
    printf("\n=== Priority (Pre-emptive) ===");
    printf("\nGantt Chart :");
    printf("\n(0) |");
    int completed = 0;
    int _t = 0;
    int TimeGiven[100000] = {0};
    while(completed < n){
        int ind = -1;
        int max_pr = 10000000;
        for(int i=0; i<n; i++){
            if(p[i].at <= _t && p[i].pr < max_pr && TimeGiven[i] != p[i].bt){
                ind = i;
                max_pr = p[i].pr;
            }
        }
        _t++;
        if(ind != -1){
            TimeGiven[ind] ++;
            if(TimeGiven[ind] == p[ind].bt){
                p[ind].ct = _t;
                p[ind].tat = p[ind].ct - p[ind].at;
                p[ind].wt = p[ind].tat - p[ind].bt;
                completed++;
                printf(" P%d (%d) |", p[ind].pid, p[ind].ct);
            }
        }
    }
}

// numerically lowest is the highest priority
void PR_NP(struct Process * p, int n){
    printf("\n=== Priority (Non pre-emptive) ===");
    printf("\nGantt Chart :");
    printf("\n(0) |");
    int completed = 0;
    int _t = 0;
    int TimeGiven[100000] = {0};
    while(completed < n){
        int ind = -1;
        int max_pr = 10000000;
        for(int i=0; i<n; i++){
            if(p[i].at <= _t && p[i].pr < max_pr && TimeGiven[i] != p[i].bt){
                ind = i;
                max_pr = p[i].pr;
            }
        }
        if(ind != -1){
            p[ind].ct = p[ind].bt + _t;
            _t += p[ind].bt;
            p[ind].tat = p[ind].ct - p[ind].at;
            p[ind].wt = p[ind].tat - p[ind].bt;
            TimeGiven[ind] += p[ind].bt;
            completed++;
            printf(" P%d (%d) |", p[ind].pid, p[ind].ct);
        }
        else{
            _t++;
        }
    }
}

void RR(struct Process * p, int n){
    int tq;
    printf("\nEnter time quantum : ");
    scanf("%d", &tq);
    printf("\n=== Round Robin ===");
    int TimeGiven[100000] = {0};
    printf("\nGantt Chart :");
    printf("\n(0) |");
    int _t = 0;
    int completed = 0;
    int i = 0;
    while(completed < n){
        int found = 0;
        for(int i=0; i<n; i++){
            if(p[i].at <= _t && TimeGiven[i] < p[i].bt){
                found = 1;
                int requiredTime = (p[i].bt - TimeGiven[i] > tq) ? tq : (p[i].bt - TimeGiven[i]);
                TimeGiven[i] += requiredTime;
                _t += requiredTime;
                printf(" P%d (%d) |", p[i].pid, _t);
                if(TimeGiven[i] == p[i].bt){
                    p[i].ct = _t;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }
        if(!found){
            _t++;
        }
    }
}

int main(){
    int n;
    printf("Enter number of processes : ");
    scanf("%d", &n);
    if(n <= 0){
        return 0;
    }
    struct Process * P = (struct Process *) calloc(n, sizeof(struct Process));
    for(int i=0; i<n; i++){
        printf("Enter pid : ");
        scanf("%d", &P[i].pid);
        printf("Enter arrival time : ");
        scanf("%d", &P[i].at);
        printf("Enter burst time : ");
        scanf("%d", &P[i].bt); 
        printf("Enter priority :");
        scanf("%d", &P[i].pr);
    }
    int choice;
    while(1){
        printf("\nEnter choice\n1. FCFS\n2. SJF (NP)\n3. SRTF/SJF (P)\n4. Priority (NP)\n5. Priority (P)\n6. RR\n7. Exit\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                sortByAT(P, n);
                FCFS(P, n);
                displayProcess(P, n);
                break;
            case 2:
                sortByAT(P, n);
                SJF_NP(P, n);
                displayProcess(P, n);
                break;
            case 3:
                sortByAT(P, n);
                SJF_P(P, n);
                displayProcess(P, n);
                break;
            case 4:
                sortByAT(P, n);
                PR_NP(P, n);
                displayProcess(P, n);
                break;
            case 5:
                sortByAT(P, n);
                PR_P(P, n);
                displayProcess(P, n);
                break;
            case 6:
                sortByAT(P, n);
                RR(P, n);
                displayProcess(P, n);
                break;
            case 7:
                _exit(0);
                break;
            default:
                printf("Nope! You're wrong, choose something else");
        }
    }
    return 0;
}