#include <stdio.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} ps;

void calculateTimes(ps processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;
    
    total_waiting_time += processes[0].waiting_time;
    total_turnaround_time += processes[0].turnaround_time;
    
    for (int i = 1; i < n; i++) {
        processes[i].completion_time = processes[i-1].completion_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

void printProcessDetails(ps processes[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }
}

int main() {
    int n;
    
    // Get number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    ps processes[n];
    
    // Get ps details
    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time and burst time for ps %d:\n", i+1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }
    
    // Calculate times and print ps details
    calculateTimes(processes, n);
    printProcessDetails(processes, n);

    return 0;
}
