#include <stdio.h>
#define TQ 5  // Time Quantum

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void roundRobinScheduling(Process processes[], int n) 
{
    int time = 0;              // Current time
    int completed = 0;         // Number of completed processes
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) 
    {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed < n) 
    {
        for (int i = 0; i < n; i++) 
        {
            // Skip process if it's already completed or not yet arrived
            if (processes[i].remaining_time == 0 || processes[i].arrival_time > time) 
            {

                continue;
            }

            // Execute the process for TQ or remaining time
            if (processes[i].remaining_time > TQ) 
            {
                time += TQ;
                processes[i].remaining_time -= TQ;
            } 
            else 
            {
                time += processes[i].remaining_time;
                processes[i].remaining_time = 0;
                processes[i].completion_time = time;
                processes[i].turnaround_time = time - processes[i].arrival_time;
                processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

                total_waiting_time += processes[i].waiting_time;
                total_turnaround_time += processes[i].turnaround_time;
                completed++;
            }
        }
    }

    // Print process details
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() 
{
    int n;

    // Get number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Get process details
    for (int i = 0; i < n; i++) 
    {
        printf("\nEnter arrival time and burst time for process %d:\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    // Perform Round Robin Scheduling
    roundRobinScheduling(processes, n);

    return 0;
}
