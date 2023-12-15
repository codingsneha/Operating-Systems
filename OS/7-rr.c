#include <stdio.h>
#include <stdlib.h>

struct process {
    int p, art, but, wtt, tat, rnt;
};

void readInputFromFile(const char *filename, struct process a[], int *pro, int *ts) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d\n", pro);
    fscanf(file, "%d\n", ts);

    for (int i = 0; i < *pro; i++) {
        fscanf(file, "%d%d", &a[i].art, &a[i].but);
        a[i].p = i;
        a[i].rnt = a[i].but;
    }

    fclose(file);
}

void roundRobinScheduling(struct process a[], int pro, int ts) {
    int time = 0, remain = pro;

    printf("Gantt Chart\n");
    printf("0");

    while (remain > 0) {
        int found = 0;

        for (int i = 0; i < pro; i++) {
            if (a[i].rnt > 0 && a[i].art <= time) {
                found = 1;

                int execute_time = (a[i].rnt < ts) ? a[i].rnt : ts;
                time += execute_time;
                a[i].rnt -= execute_time;

                printf(" -> [P%d] <- %d", a[i].p+1, time);

                if (a[i].rnt == 0) {
                    remain--;
                    a[i].tat = time - a[i].art;
                    a[i].wtt = time - a[i].art - a[i].but;
                }
            }
        }

        if (!found) {
            // No process is available, CPU is idle
            time++;
            printf(" -> IDLE <- %d", time);
        }
    }
}

void writeOutputToFile(const char *filename, struct process a[], int pro, float avgwt, float avgtt) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Pro\tArTi\tBuTi\tTaTi\tWtTi\n");

    for (int i = 0; i < pro; i++) {
        fprintf(file, "P%d\t%d\t%d\t%d\t%d\n", a[i].p, a[i].art, a[i].but, a[i].tat, a[i].wtt);
    }

    fprintf(file, "Average Waiting Time : %.2f\n", avgwt);
    fprintf(file, "Average Turnaround Time : %.2f\n", avgtt);

    fclose(file);
}

int main() {
    int pro, ts;
    struct process a[100];
    float avgwt = 0, avgtt = 0;

    readInputFromFile("input.txt", a, &pro, &ts);
    roundRobinScheduling(a, pro, ts);

    printf("\n");
    printf("Pro\tArTi\tBuTi\tTaTi\tWtTi\n");

    for (int i = 0; i < pro; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", a[i].p+1, a[i].art, a[i].but, a[i].tat, a[i].wtt);
        avgwt += a[i].wtt;
        avgtt += a[i].tat;
    }

    avgwt = avgwt / pro;
    avgtt = avgtt / pro;
    printf("Average Waiting Time : %.2f\n", avgwt);
    printf("Average Turnaround Time : %.2f\n", avgtt);

    writeOutputToFile("output.txt", a, pro, avgwt, avgtt);

    return 0;
}
