#include <iostream>
using namespace std;

int main() {
    int n, tq;
    int at[10], bt[10], rem[10];
    int ct[10], tat[10], wt[10];

    int time = 0, completed = 0;
    float avgTAT = 0, avgWT = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nProcess P" << i + 1 << endl;
        cout << "Arrival Time: ";
        cin >> at[i];
        cout << "Burst Time: ";
        cin >> bt[i];
        rem[i] = bt[i];
    }

    cout << "\nEnter Time Quantum: ";
    cin >> tq;

    // Round Robin Scheduling
    while (completed < n) {
        bool executed = false;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0) {
                executed = true;

                if (rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    ct[i] = time;
                    completed++;
                }
            }
        }

        // If no process executed, move time forward
        if (!executed) {
            time++;
        }
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgTAT += tat[i];
        avgWT += wt[i];

        cout << "P" << i + 1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << endl;
    }

    cout << "\nAverage Turnaround Time = " << avgTAT / n;
    cout << "\nAverage Waiting Time = " << avgWT / n << endl;

    return 0;
}
