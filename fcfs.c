#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int bt[n], at[n], wt[n], tat[n];
    wt[0] = 0;
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d (Arrival Time, Burst Time): ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }
    // Calculate waiting time and turnaround time
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];  // Waiting time calculation
        if (wt[i] < at[i]) wt[i] = at[i] - wt[i - 1]; // Adjust for arrival time
    }

    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];  // Turnaround time calculation
    }
    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    return 0;
}
