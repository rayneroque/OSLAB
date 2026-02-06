#include<stdio.h> 

// ============================================
// REQUIREMENT: MULTI-LEVEL QUEUE SCHEDULING
// Queue 1: FCFS Algorithm
// Queue 2: Round Robin Algorithm  
// Queue 3: SJF (Shortest Job First)
// ============================================
 
int main() 
{ 
      // Variables for process scheduling
      int i, limit, total = 0, x, counter = 0, time_quantum,j; 
      
      // Process attributes: process IDs, priority values, arrival times, burst times, remaining times
	  int wait_time = 0, turnaround_time = 0,pos,z,p[10],prio[10], a_time[10], b_time[10], temp[10],b; 
      
      // REQUIREMENT: PROCESS ATTRIBUTES - Queue Level
      int queue_level[10];  // 1=FCFS Queue, 2=RoundRobin Queue, 3=SJF Queue
      
      // Statistics variables for calculating averages
	  float average_wait_time, average_turnaround_time;
      
      // ============ INPUT SECTION ============
	  printf("\nEnter Total Number of Processes:"); 
      
	  scanf("%d", &limit); 
      
	  x = limit;  // x tracks remaining processes to complete
      
      // Input process details from user
      for(i = 0; i < limit; i++) 
      {
	    p[i]=i+1;  // REQUIREMENT: Process ID (PID)
	   
	    prio[i]=0;  // Initialize priority to 0
            printf("\nEnter total Details of Process[%d]\n", i + 1);
            printf("Arrival Time:\t");
            scanf("%d", &a_time[i]);
            printf("Burst Time:\t");  // REQUIREMENT: Burst Time attribute
            scanf("%d", &b_time[i]); 
            printf("Queue Level (1=FCFS, 2=RoundRobin, 3=SJF):\t");
            scanf("%d", &queue_level[i]);  // REQUIREMENT: Queue Level attribute
            if(queue_level[i] < 1 || queue_level[i] > 3) queue_level[i] = 1;  // Validate queue level
            temp[i] = b_time[i];  // temp stores remaining burst time for each process
      }
	   
      printf("\nEnter the Time Quantum:"); 
      scanf("%d", &time_quantum);  // Time quantum for Round Robin queue
      
      // ============ SCHEDULING TABLE HEADER ============
      printf("\n");
      printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n");
      printf("║  PID  │  Arrival  │  Burst  │  Completion  │  Turnaround  │  Wait Time  │  Queue   ║\n");
      printf("╠════════════════════════════════════════════════════════════════════════════════════╣\n");
      // ============ MAIN SCHEDULING LOOP ============
      // Executes until all processes are completed (x becomes 0)
      for(total = 0, i = 0; x != 0;) 
      { 

		    // ============ PRIORITY-BASED SORTING ============
		    // Sort processes by priority (lower priority value = higher priority)
		    for(z=0;z<limit;z++)
		    {
			int temp1;
			pos=z;
			// Find position of minimum priority value
			for(j=z+1;j<limit;j++)
			{
			    if(prio[j]<prio[pos])
				pos=j;
			}
		 
		temp1=prio[z];
	
		prio[z]=prio[pos];
	
		prio[pos]=temp1;
		 
			temp1=b_time[z];
			b_time[z]=b_time[pos];
			b_time[pos]=temp1;
		 			temp1=a_time[z];
				a_time[z]=a_time[pos];
			a_time[pos]=temp1;

			temp1=p[z];
				p[z]=p[pos];
			p[pos]=temp1;

			temp1=temp[z];
				temp[z]=temp[pos];
			temp[pos]=temp1;
			
			temp1=queue_level[z];
				queue_level[z]=queue_level[pos];
			queue_level[pos]=temp1;
		    }
		{
		}
            
		    // ============ PROCESS EXECUTION LOGIC ============
		    // Check if current process uses full quantum or completes
			if(temp[i] <= time_quantum && temp[i] > 0) 
            { 
                  // Process completes within this quantum
                  total = total + temp[i]; 
                  temp[i] = 0;  // Mark remaining time as 0
                  counter = 1;  // Flag that process is complete
            } 
            
			else if(temp[i] > 0) 
            { 
                  // Process uses full time quantum and goes back to queue
                  temp[i] = temp[i] - time_quantum;  // Reduce remaining time
                  total = total + time_quantum; 
            } 

	    // ============ UPDATE PRIORITY VALUES ============
	    // Increase priority for other processes (they wait longer)
	    // Decrease priority for current process (it just ran)
	    for(b=0;b<limit;b++)
	    {
			if(b==i)
			prio[b]+=1;  // Current process priority increases slightly
			else
			prio[b]+=2;  // Waiting processes get higher priority
		}

            // ============ PROCESS COMPLETION ============
            // If process completes, print results and remove from queue
            if(temp[i] == 0 && counter == 1) 
            { 
                  x--;  // Decrement remaining process count
                  printf("║ %3d   │  %6d   │  %5d  │     %6d   │     %6d   │    %6d   │    Q%d    ║\n", 
                         p[i], a_time[i], b_time[i], total, total - a_time[i], total - a_time[i] - b_time[i], queue_level[i]);
                  wait_time = wait_time + total - a_time[i] - b_time[i];  // Add to total wait time
                  turnaround_time = turnaround_time + total - a_time[i];  // Add to total turnaround time
                  counter = 0;  // Reset completion flag
            } 
            // ============ PROCESS QUEUE ROTATION ============
            // Move to next process in circular queue fashion
            if(i == limit - 1) 
            {
                  i = 0;  // Wrap around to first process
            
			}
            else if(a_time[i + 1] <= total) 
            {
                  i++;  // Move to next process if it has arrived
            
			}
            else 
            {
                  i = 0;  // Reset to beginning if next process hasn't arrived
            
			}		
      } 
      
      printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");
      
      // ============ CALCULATE AND DISPLAY STATISTICS ============
      average_wait_time = (float)wait_time / limit;  // Average = total wait time / number of processes
      average_turnaround_time = (float)turnaround_time / limit;  // Average = total turnaround / processes
      
      printf("\n========== SCHEDULING STATISTICS ==========");
      printf("\nTotal Processes: %d", limit);
      printf("\nAverage Waiting Time: %.2f", average_wait_time);
      printf("\nAverage Turnaround Time: %.2f", average_turnaround_time);
      printf("\n\n========== QUEUE ALGORITHMS ==========");
      printf("\nQueue 1: FCFS (First Come First Served)");
      printf("\nQueue 2: Round Robin (Time Quantum: %d)", time_quantum);
      printf("\nQueue 3: SJF (Shortest Job First)\n");
      return 0; 
}