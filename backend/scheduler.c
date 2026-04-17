// Initial working scheduler logic implemented

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

int main() {

    struct Process processes[MAX];
    int numberOfProcesses;

    // ---------- INPUT FILE ----------
    FILE *inputFile = fopen("..\\data\\input.txt", "r");

    if (inputFile == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    fscanf(inputFile, "%d", &numberOfProcesses);

    for (int i = 0; i < numberOfProcesses; i++) {
        fscanf(inputFile, "%d %d %d %d",
               &processes[i].processId,
               &processes[i].arrivalTime,
               &processes[i].burstTime,
               &processes[i].priority);

        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].isCompleted = 0;
    }

    fclose(inputFile);

    // ---------- VARIABLES ----------
    int currentTime = 0;
    int completedProcesses = 0;

    int ganttChart[1000];
    int ganttIndex = 0;

    // ---------- MAIN LOOP ----------
    while (completedProcesses < numberOfProcesses) {

        int highestPriority = -1;
        int selectedProcessIndex = -1;

        for (int i = 0; i < numberOfProcesses; i++) {
            if (processes[i].arrivalTime <= currentTime &&
                processes[i].remainingTime > 0) {

                if (processes[i].priority > highestPriority) {
                    highestPriority = processes[i].priority;
                    selectedProcessIndex = i;
                }
            }
        }

        if (selectedProcessIndex == -1) {
            currentTime++;
            continue;
        }

        // Execute
        processes[selectedProcessIndex].remainingTime--;
        ganttChart[ganttIndex++] = processes[selectedProcessIndex].processId;
        currentTime++;

        // Aging + Waiting Time
        for (int i = 0; i < numberOfProcesses; i++) {
            if (i != selectedProcessIndex &&
                processes[i].arrivalTime <= currentTime &&
                processes[i].remainingTime > 0) {

                processes[i].priority++;
                processes[i].waitingTime++;
            }
        }

        // Completion
        if (processes[selectedProcessIndex].remainingTime == 0) {
            processes[selectedProcessIndex].turnaroundTime =
                currentTime - processes[selectedProcessIndex].arrivalTime;

            completedProcesses++;
        }
    }

    // ---------- OUTPUT FILE ----------
    FILE *outputFile = fopen("..\\data\\output.txt", "w");

    if (outputFile == NULL) {
        printf("Error opening output file\n");
        return 1;
    }

    fprintf(outputFile, "Final Results:\n");
    fprintf(outputFile, "PID\tWT\tTAT\n");

    for (int i = 0; i < numberOfProcesses; i++) {
        fprintf(outputFile, "%d\t%d\t%d\n",
                processes[i].processId,
                processes[i].waitingTime,
                processes[i].turnaroundTime);
    }

    fprintf(outputFile, "\nExecution Order (Gantt Chart):\n");

    fprintf(outputFile, "Time: ");
    for (int i = 0; i < ganttIndex; i++) {
        fprintf(outputFile, "%d ", i);
    }
    fprintf(outputFile, "\n");

    for (int i = 0; i < ganttIndex; i++) {
        fprintf(outputFile, "P%d ", ganttChart[i]);
    }
    fprintf(outputFile, "\n");

    fclose(outputFile);

    printf("Output saved successfully\n");

    return 0;
}