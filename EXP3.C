#include <stdio.h>

int main() {
    int bt[20], wt[20], tat[20], i, n;
    float wtavg = 0.0, tatavg = 0.0;

    // Get number of processes
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    // Get burst time for each process
    for (i = 0; i < n; i++) {
        printf("\nEnter Burst Time for Process %d: ", i);
        scanf("%d", &bt[i]);
    }

    // Initial values for the first process
    wt[0] = 0;  // Waiting time for the first process is 0
    tat[0] = bt[0];  // Turnaround time for the first process is its burst time

    // Calculate waiting time and turnaround time for remaining processes
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];  // Waiting time of current process
        tat[i] = tat[i - 1] + bt[i];  // Turnaround time of current process
    }

    // Calculate average waiting time and average turnaround time
    for (i = 0; i < n; i++) {
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Display the results
    printf("\n\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (i = 0; i < n; i++) {
        printf("\n\tP%d\t\t%d\t\t%d\t\t%d", i, bt[i], wt[i], tat[i]);
    }

    // Display average waiting time and average turnaround time
    printf("\nAverage Waiting Time: %f", wtavg / n);
    printf("\nAverage Turnaround Time: %f", tatavg / n);

    return 0;
}
