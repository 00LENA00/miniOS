#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;               
    int burst_time;        
    int remaining_time;   
    int run_time;          
    struct Process *next;  
} Process;


void add_process(Process **head, int pid, int burst_time) {

    Process *new_process = (Process *)malloc(sizeof(Process));
    new_process->pid = pid;
    new_process->burst_time = burst_time;
    new_process->remaining_time = burst_time;
    new_process->run_time = 0; 
    new_process->next = NULL;


    if (*head == NULL) {
        *head = new_process;
    } else {
        Process *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_process;
    }
}


void round_robin(Process *head, int quantum) {
    Process *current = head;
    Process *tail = NULL; 
    int total_time = 0; 
    int process_count = 0; 

    while (head) {
    	
        Process *prev = NULL;
        current = head;

        while (current) {
            if (current->remaining_time > 0) {
                int run_for = (current->remaining_time > quantum) ? quantum : current->remaining_time;
                printf("Process %d runs for %d units.\n", current->pid, run_for);
                current->remaining_time -= run_for;
                current->run_time += run_for;
                total_time += run_for;


                if (current->remaining_time == 0) {
                    printf("-> Process %d completed at time %d units.\n", current->pid, total_time);
                    printf("-> Process %d total run time: %d units.\n", current->pid, current->run_time);
                } else {
                    if (tail) {
                        tail->next = current;
                    }
                    tail = current;
                    current = current->next;
                    tail->next = NULL;
                    continue;
                }
            }

            prev = current;
            current = current->next;
	    
            if (prev->remaining_time <= 0) {
                if (prev == head) {
                    head = current;
                }

                else {
                    prev->next = current;
                }
            }      
        }

        if (head == NULL && tail != NULL) {
            head = tail;
            tail = NULL;
        }
    }
}


void free_list(Process *head) {
    Process *current = head;
    Process *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}


int RR() {
    Process *head = NULL;
    
    int num_processes;
    printf("프로세스 수를 입력하세요: ");
    scanf("%d", &num_processes);

    for (int i = 0; i < num_processes; i++) {
        int burst_time;
        printf("프로세스 %d의 burst time을 입력하세요: ", i + 1);
        scanf("%d", &burst_time);
        
        add_process(&head, i + 1, burst_time);
    }

    int quantum = 3;

    round_robin(head, quantum);

    free_list(head);

    return 0;
}
