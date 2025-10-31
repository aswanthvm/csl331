#include <stdio.h>

typedef struct {
    int pid, at, bt, pr, ct, tat, wt, completed;
} Process;

int main() {
    int n, time = 0, completed = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].completed = 0;
    }

    while (completed != n) {
        int index = -1, highest_pr = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed && p[i].pr < highest_pr) {
                highest_pr = p[i].pr;
                index = i;
            }
        }

        if (index != -1) {
            time += p[index].bt;
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            p[index].completed = 1;
            completed++;
        } else {
            time++;
        }
    }

    float total_tat = 0, total_wt = 0;
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    return 0;
}
