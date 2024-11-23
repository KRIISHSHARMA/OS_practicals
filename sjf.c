#include <stdio.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

// simple bubblr sort 
void sortByBurstTime(Process processes[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processes[j].burst_time > processes[j + 1].burst_time) 
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}


void calculateTimes(Process processes[], int n) 
{
    int current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) 
    {
        if (current_time < processes[i].arrival_time) 
        {
            current_time = processes[i].arrival_time; // Adjust current time if the CPU is idle
        }
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        current_time = processes[i].completion_time;

        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}


void printProcessDetails(Process processes[], int n) 
{
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }
}

int main() 
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    
    for (int i = 0; i < n; i++) 
    {
        processes[i].process_id = i + 1;
        printf("\nEnter arrival time and burst time for process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    
    sortByBurstTime(processes, n);   
    calculateTimes(processes, n);
    printProcessDetails(processes, n);

    return 0;
}
