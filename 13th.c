#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                allocation[i] = j;
                blockSizes[j] -= processSizes[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                if (bestIndex == -1 || blockSizes[j] < blockSizes[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blockSizes[bestIndex] -= processSizes[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                if (worstIndex == -1 || blockSizes[j] > blockSizes[worstIndex]) {
                    worstIndex = j;
                }
            }
        }

        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSizes[worstIndex] -= processSizes[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSizes[MAX_BLOCKS], processSizes[MAX_PROCESSES];
    int m, n;

    // Input memory block sizes
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSizes[i]);
    }

    // Input process sizes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter sizes of processes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSizes[i]);
    }

    // Call allocation strategies
    int blockSizesFirstFit[MAX_BLOCKS];
    int blockSizesBestFit[MAX_BLOCKS];
    int blockSizesWorstFit[MAX_BLOCKS];

    // Create copies of blockSizes for each strategy
    for (int i = 0; i < m; i++) {
        blockSizesFirstFit[i] = blockSizes[i];
        blockSizesBestFit[i] = blockSizes[i];
        blockSizesWorstFit[i] = blockSizes[i];
    }

    firstFit(blockSizesFirstFit, m, processSizes, n);
    bestFit(blockSizesBestFit, m, processSizes, n);
    worstFit(blockSizesWorstFit, m, processSizes, n);

    return 0;
}
