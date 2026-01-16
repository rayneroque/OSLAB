#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n = 5;
    int pid[5] = {1, 2, 3, 4, 5};
    float burst[5] = {50.54f, 10.11f, 33.34f, 2.5f, 101.1f};
    float waiting[5], turnaround[5];
    float total = 0;

    // Sort processes by burst time (SJF)
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

    // Waiting time calculation
    waiting[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting[i] = waiting[i - 1] + burst[i - 1];
    }

    // Turnaround time calculation
    for (int i = 0; i < n; i++) {
        turnaround[i] = waiting[i] + burst[i];
    }

    // Display results
    cout << fixed << setprecision(2);
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t"
             << burst[i] << "\t\t"
             << waiting[i] << "\t\t"
             << turnaround[i] << endl;
    }

    // Average waiting time
    total = 0;
    for (int i = 0; i < n; i++)
        total += waiting[i];
    cout << "\nAverage Waiting Time: " << total / n << endl;

    // Average turnaround time
    total = 0;
    for (int i = 0; i < n; i++)
        total += turnaround[i];
    cout << "Average Turnaround Time: " << total / n << endl;

    return 0;
}