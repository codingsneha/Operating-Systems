#include <stdio.h>

void calculateTimes(int n, int burst_time[], int arrival_time[]) {
    int wait_time[n], completion_time[n], turnaround_time[n];

    wait_time[0] = 0;
    completion_time[0] = burst_time[0];
    turnaround_time[0] = completion_time[0] - arrival_time[0];

    for (int i = 1; i < n; i++) {
        wait_time[i] = completion_time[i - 1] - arrival_time[i];
        if (wait_time[i] < 0)
            wait_time[i] = 0;
        completion_time[i] = completion_time[i - 1] + burst_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }

    float avg_wait_time = 0, avg_turnaround_time = 0;
    printf("\nProcess\tBurst Time\tArrival Time\tWait Time\tCompletion Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], wait_time[i], completion_time[i], turnaround_time[i]);
        avg_wait_time += wait_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_wait_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Wait Time: %.2f", avg_wait_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n], arrival_time[n];

    printf("Enter burst time and arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
    }

    calculateTimes(n, burst_time, arrival_time);

    return 0;
}
