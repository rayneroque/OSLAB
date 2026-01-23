#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Structure to store process information
struct process {
    int pid;           // Process ID
    int at;            // Arrival Time
    int bt;            // Burst Time
    int ct;            // Completion Time
    int tt;            // Turnaround Time
    int wt;            // Waiting Time
};

// Calculate recommended time quantum (average of burst times)
float getRecommendedTQ(vector<int> burstTimes) {
    int sum = 0;
    for (int i = 0; i < burstTimes.size(); i++) {
        sum = sum + burstTimes[i];
    }
    return sum / (float)burstTimes.size();
}

// Print results table
void printTable(string name, vector<process> procs) {
    cout << "\n========== " << name << " ==========" << endl;
    cout << left << setw(8) << "PID" << setw(10) << "AT" << setw(10) << "BT" 
         << setw(10) << "CT" << setw(10) << "TT" << setw(10) << "WT" << endl;
    cout << string(60, '-') << endl;
    
    float sumTT = 0, sumWT = 0;
    for (int i = 0; i < procs.size(); i++) {
        cout << left << setw(8) << procs[i].pid 
             << setw(10) << procs[i].at 
             << setw(10) << procs[i].bt 
             << setw(10) << procs[i].ct 
             << setw(10) << procs[i].tt 
             << setw(10) << procs[i].wt << endl;
        sumTT = sumTT + procs[i].tt;
        sumWT = sumWT + procs[i].wt;
    }
    
    cout << string(60, '-') << endl;
    cout << "Average TT: " << fixed << setprecision(2) << sumTT / procs.size() << endl;
    cout << "Average WT: " << fixed << setprecision(2) << sumWT / procs.size() << endl;
}

// Round Robin Scheduling Algorithm
void roundRobin(vector<process> procs, int tq) {
    int n = procs.size();
    vector<int> remaining(n);
    
    // Copy burst times to remaining time
    for (int i = 0; i < n; i++) {
        remaining[i] = procs[i].bt;
    }
    
    int time = 0;
    int completed = 0;
    int idx = 0;
    
    // Keep scheduling until all processes are done
    while (completed < n) {
        // Skip processes that are already done
        while (idx < n && remaining[idx] == 0) {
            idx = idx + 1;
        }
        
        // If we passed all processes, go back to the beginning
        if (idx >= n) {
            idx = 0;
            while (idx < n && remaining[idx] == 0) {
                idx = idx + 1;
            }
        }
        
        if (idx < n) {
            // Run process for time quantum or until it finishes
            if (remaining[idx] <= tq) {
                time = time + remaining[idx];
                remaining[idx] = 0;
                completed = completed + 1;
            } else {
                time = time + tq;
                remaining[idx] = remaining[idx] - tq;
            }
            
            procs[idx].ct = time;
        }
        
        idx = idx + 1;
    }
    
    // Calculate turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        procs[i].tt = procs[i].ct - procs[i].at;
        procs[i].wt = procs[i].tt - procs[i].bt;
    }
    
    string title = "ROUND ROBIN (TQ: " + to_string(tq) + ")";
    printTable(title, procs);
}

// Shortest Job First Scheduling Algorithm
void shortestJobFirst(vector<process> procs) {
    int n = procs.size();
    vector<bool> done(n, false);
    int time = 0;
    
    // Schedule n processes
    for (int i = 0; i < n; i++) {
        int smallest = -1;
        int smallestBT = 9999;
        
        // Find process with smallest burst time that has arrived
        for (int j = 0; j < n; j++) {
            if (done[j] == false && procs[j].at <= time && procs[j].bt < smallestBT) {
                smallest = j;
                smallestBT = procs[j].bt;
            }
        }
        
        // If no process has arrived yet, jump to next arrival
        if (smallest == -1) {
            for (int j = 0; j < n; j++) {
                if (done[j] == false && procs[j].at > time) {
                    time = procs[j].at;
                    smallest = j;
                    break;
                }
            }
        }
        
        // Execute the selected process
        time = time + procs[smallest].bt;
        procs[smallest].ct = time;
        procs[smallest].tt = procs[smallest].ct - procs[smallest].at;
        procs[smallest].wt = procs[smallest].tt - procs[smallest].bt;
        done[smallest] = true;
    }
    
    printTable("SHORTEST JOB FIRST (SJF)", procs);
}

// Shortest Remaining Time First Scheduling Algorithm
void shortestRemainingTimeFirst(vector<process> procs) {
    int n = procs.size();
    vector<int> remaining(n);
    vector<bool> done(n, false);
    
    // Copy burst times to remaining time
    for (int i = 0; i < n; i++) {
        remaining[i] = procs[i].bt;
    }
    
    int time = 0;
    int completed = 0;
    
    // Keep scheduling until all processes are done
    while (completed < n) {
        // Find process with smallest remaining time that has arrived
        int smallest = -1;
        int smallestRT = 9999;
        
        for (int i = 0; i < n; i++) {
            if (done[i] == false && procs[i].at <= time && remaining[i] < smallestRT) {
                smallest = i;
                smallestRT = remaining[i];
            }
        }
        
        // If no process has arrived, jump to next arrival
        if (smallest == -1) {
            for (int i = 0; i < n; i++) {
                if (done[i] == false && procs[i].at > time) {
                    time = procs[i].at;
                    smallest = i;
                    break;
                }
            }
        }
        
        // Execute for 1 unit of time
        remaining[smallest] = remaining[smallest] - 1;
        time = time + 1;
        
        // If process is done, mark it
        if (remaining[smallest] == 0) {
            procs[smallest].ct = time;
            procs[smallest].tt = procs[smallest].ct - procs[smallest].at;
            procs[smallest].wt = procs[smallest].tt - procs[smallest].bt;
            done[smallest] = true;
            completed = completed + 1;
        }
    }
    
    printTable("SHORTEST REMAINING TIME FIRST (SRTF)", procs);
}

int main() {
    // Declare arrival times for each process
    vector<int> arrivalTimes = {4, 2, 3, 6, 1, 5, 8, 7};
    
    // Declare burst times for each process
    vector<int> burstTimes = {53, 43, 18, 16, 44, 73, 99, 27};
    
    int n = arrivalTimes.size();
    
    // Create process list - initialize with empty values
    vector<process> processes;
    for (int i = 0; i < n; i++) {
        process p;
        p.pid = i + 1;
        p.at = arrivalTimes[i];
        p.bt = burstTimes[i];
        p.ct = 0;
        p.tt = 0;
        p.wt = 0;
        processes.push_back(p);
    }
    
    // Step 1: Calculate the recommended time quantum
    float recommendedTQ = getRecommendedTQ(burstTimes);
    cout << "\n===== RECOMMENDED TIME QUANTUM =====" << endl;
    cout << "Recommended TQ (Average of Burst Times): " << fixed << setprecision(2) << recommendedTQ << endl;
    
    // Step 2: Run Round Robin Algorithm
    roundRobin(processes, (int)recommendedTQ);
    
    // Step 3: Run Shortest Job First Algorithm
    shortestJobFirst(processes);
    
    // Step 4: Run Shortest Remaining Time First Algorithm
    shortestRemainingTimeFirst(processes);
    
    return 0;
}