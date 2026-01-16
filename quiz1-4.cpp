#include <iostream>
#include <iomanip>
using namespace std;

// This program simulates the Round Robin CPU scheduling algorithm
int main() {
    // Number of processes
    int n = 5;
    // Time quantum and accumulator for total waiting time
    float qt = 20, total = 0;   // time quantum
    // Burst times for each process
    float burst[5] = {50.54f, 10.11f, 33.34f, 2.5f, 101.1f};
    // Temporary array to hold remaining burst times
    float temp[5];
    // Arrays to store waiting and turnaround times
    float wait[5], turnaround[5];
    
    // Copy burst time to temp array
    for (int i = 0; i < n; i++) {
        temp[i] = burst[i];
    }

    // Initialize waiting time
    for (int i = 0; i < n; i++) {
        wait[i] = 0;
    }

    // Current time in the system
    int time = 0;   // current time

    // Round Robin scheduling loop
    while (true) {
        // Flag to check if all processes are done
        bool done = true;
        // Iterate through each process
        for (int i = 0; i < n; i++) {
            if (temp[i] > 0) {
                done = false;
                // If remaining burst time > time quantum, execute for quantum time
                if (temp[i] > qt) {
                    time += qt;
                    temp[i] -= qt;
                } else {
                    // Execute remaining burst time and calculate waiting time
                    time += temp[i];
                    wait[i] = time - burst[i];
                    temp[i] = 0;
                }
            }
        }
        if (done)
            break;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        turnaround[i] = burst[i] + wait[i];
        total += wait[i];
    }

    // Set output to fixed point with 2 decimal places
    cout << fixed << setprecision(2);
    // Print table header
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    // Print details for each process
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t"
             << burst[i] << "\t\t"
             << wait[i] << "\t\t"
             << turnaround[i] << endl;
    }

    // Calculate and print average waiting time
    cout << "\nAverage Waiting Time: " << total / n << endl;

    // Reset total for turnaround time calculation
    total = 0;
    for (int i = 0; i < n; i++)
        total += turnaround[i];

    // Calculate and print average turnaround time
    cout << "Average Turnaround Time: " << total / n << endl;

    return 0;
}