#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
};

void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void calculateAverages(int n, struct Process *processes) {
    float totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].completion_time - processes[i].arrival_time - 		processes[i].burst_time;
    }
    float avgWaitingTime = totalWaitingTime / n; // calculate avg.
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
}


void sortProcesses(int n, struct Process *processes) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void NPsrtf(int n, struct Process *processes) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        int shortestProcess = i;

        // Find the shortest remaining time process among the arrived processes
        for (int j = i + 1; j < n && processes[j].arrival_time <= currentTime; j++) {
            if (processes[j].burst_time < processes[shortestProcess].burst_time) {
                shortestProcess = j;
            }
        }

        // Execute the shortest remaining time process
        printf("Time %d: Process %d is running\n", currentTime, processes[shortestProcess].id);
        currentTime += processes[shortestProcess].burst_time;
        processes[shortestProcess].remaining_time = 0;
        processes[shortestProcess].completion_time = currentTime;
	sleep(processes[shortestProcess].burst_time);
        printf("Time %d: Process %d completed\n", currentTime, processes[shortestProcess].id);
        
    }
    calculateAverages(n,processes);
}

void Psrtf(int n, struct Process *processes) {
    int currentTime = 0;

    while (1) {
        int minRemainingTime = INT_MAX;
        int shortestProcess = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= currentTime) {
                if (processes[i].remaining_time < minRemainingTime) {
                    minRemainingTime = processes[i].remaining_time;
                    shortestProcess = i;
                }
            }
        }

        if (shortestProcess == -1) {
            break; // All processes are done
        }

        // Execute the shortest remaining time process
        printf("Time %d: Process %d is running\n", currentTime, processes[shortestProcess].id);
        processes[shortestProcess].remaining_time--;

        // Update current time
        currentTime++;
	sleep(processes[shortestProcess].burst_time);
        // Check if the process is completed
        if (processes[shortestProcess].remaining_time == 0) {
            processes[shortestProcess].completion_time = currentTime;
            printf("Time %d: Process %d completed\n", currentTime, processes[shortestProcess].id);
        }
    }
    calculateAverages(n,processes);
}

void run_preemtive(){
 int n;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Get individual arrival times and burst times
    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort processes based on arrival time
    sortProcesses(n, processes);

    // Run SRTF
    Psrtf(n, processes);
}
void runNon_preemtive(){
int n;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Get individual arrival times and burst times
    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort processes based on arrival time
    sortProcesses(n, processes);

    // Run SRTF
    NPsrtf(n, processes);
}

int main() {
    //run();
    int choice;
    printf("Wellcome to shortest-remaining-time-first program\n");
    while(choice != 3){
    printf("1 - preemtive shortest-remaining-time-first\n");
    printf("2 - non-preemtive shortest-remaining-time-first\n");
    printf("3 - Exit\n");
    printf("please enter the number of the operation : ");
    scanf("%d",&choice);
    if(choice == 1){
    run_preemtive();
    }
    else if(choice == 2){
    runNon_preemtive();
    }
    else if(choice == 3){
    printf("thank you to use our program");
    break;
    }
  }
  return 0;
    
}

