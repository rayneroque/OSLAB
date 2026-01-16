#include <iostream>
using namespace std;

int main() {
    int bt[20], wt[20], tat[20], i, n;
    float wtavg = 0.0, tatavg = 0.0;

    // Get number of processes
    cout << "\nEnter the number of processes: ";
    cin >> n;

    // Get burst time for each process
    for (i = 0; i < n; i++) {
        cout <<"\nEnter Burst Time for Process " << i << ": ";
        cin >> bt[i];
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
    cout << "\n\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for (i = 0; i < n; i++) {
        cout << "\n\tP" << i << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i];
    }

    // Display average waiting time and average turnaround time
    cout <<"\nAverage Waiting Time: " << wtavg;
    cout <<"\nAverage Turnaround Time: " << tatavg;

    return 0;
}
