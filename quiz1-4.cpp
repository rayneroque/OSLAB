#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n = 5;
    float qt = 20, total = 0;   // time quantum
    float burst[5] = {50.54f, 10.11f, 33.34f, 2.5f, 101.1f};
    float temp[5];
    float wait[5], turnaround[5];
    
    // Copy burst time to temp array
    for (int i = 0; i < n; i++) {
        temp[i] = burst[i];
    }

    // Initialize waiting time
    for (int i = 0; i < n; i++) {
        wait[i] = 0;
    }

    int time = 0;   // current time

    // Round Robin scheduling
    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (temp[i] > 0) {
                done = false;
                if (temp[i] > qt) {
                    time += qt;
                    temp[i] -= qt;
                } else {
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

    cout << fixed << setprecision(2);
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t"
             << burst[i] << "\t\t"
             << wait[i] << "\t\t"
             << turnaround[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << total / n << endl;

    total = 0;
    for (int i = 0; i < n; i++)
        total += turnaround[i];

    cout << "Average Turnaround Time: " << total / n << endl;

    return 0;
}