#include <iostream>
#include <iomanip>
using namespace std;

// This program simulates the Shortest Job First (SJF) CPU scheduling algorithm.
// It sorts processes by their burst times, calculates waiting and turnaround times,
// and displays the results along with averages.

int main() {
    int n = 5; // Number of processes
    int pid[5] = {1, 2, 3, 4, 5};  // Process IDs
    float burst[5] = {50.54f, 10.11f, 33.34f, 2.5f, 101.1f};  // Burst times for each process
    float waiting[5], turnaround[5]; // Arrays to store waiting and turnaround times
    float total = 0; // Variable for calculating totals

    // Sort processes by burst time in ascending order (Shortest Job First)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (burst[i] > burst[j]) {
                
                // swap burst time
                float temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                // swap process id
                int tempId = pid[i];
                pid[i] = pid[j];
                pid[j] = tempId;
            }
        }
    }

    // Calculate waiting time for each process
    // First process has waiting time 0, others wait for previous processes to finish
    waiting[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting[i] = waiting[i - 1] + burst[i - 1];
    }

    // Calculate turnaround time for each process
    // Turnaround time = waiting time + burst time
    for (int i = 0; i < n; i++) {
        turnaround[i] = waiting[i] + burst[i];
    }

    // Display the results in a table format
    cout << fixed << setprecision(2);
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t"
             << burst[i] << "\t\t"
             << waiting[i] << "\t\t"
             << turnaround[i] << endl;
    }

    // Calculate and display average waiting time
    total = 0;
    for (int i = 0; i < n; i++)
        total += waiting[i];
    cout << "\nAverage Waiting Time: " << total / n << endl;

    // Calculate and display average turnaround time
    total = 0;
    for (int i = 0; i < n; i++)
        total += turnaround[i];
    cout << "Average Turnaround Time: " << total / n << endl;

    return 0;
}