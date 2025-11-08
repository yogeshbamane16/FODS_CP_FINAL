#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 100

typedef struct Task {
    int id;
    char team[50];
    char description[100];
    char location[50];
    int time_needed;
    time_t start_time;
    char status[20];
} Task;

typedef struct TaskQueue {
    Task tasks[MAX_TASKS];
    int front;
    int rear;
    int count;
} TaskQueue;

// Create empty queue
TaskQueue* create_queue() {
    TaskQueue* q = (TaskQueue*)malloc(sizeof(TaskQueue));
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    return q;
}

// Check if queue is empty
int is_empty(TaskQueue* q) {
    return q->count == 0;
}

// Check if queue is full
int is_full(TaskQueue* q) {
    return q->count == MAX_TASKS;
}

// Add task to queue
void add_task(TaskQueue* q, Task task) {
    if (is_full(q)) {
        printf("Queue full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_TASKS;
    q->tasks[q->rear] = task;
    q->count++;
}

// Get next task from queue
Task get_next_task(TaskQueue* q) {
    Task task = q->tasks[q->front];
    q->front = (q->front + 1) % MAX_TASKS;
    q->count--;
    return task;
}

// Show all tasks in queue
void show_tasks(TaskQueue* q) {
    if (is_empty(q)) {
        printf("No tasks waiting.\n");
        return;
    }
    
    printf("\n--- Pending Tasks ---\n");
    printf("Total: %d\n\n", q->count);
    
    int index = q->front;
    for (int i = 0; i < q->count; i++) {
        Task t = q->tasks[index];
        printf("ID: %d | %s | %s | %s | %d mins\n",
               t.id, t.team, t.description, t.location, t.time_needed);
        index = (index + 1) % MAX_TASKS;
    }
}

// Member 2's main function
void run_task_tracker() {
    printf("\n=== TASK TRACKER ===\n");
    TaskQueue* task_queue = create_queue();
    int next_id = 1;
    
    // Add sample tasks
    Task t1 = {next_id++, "Alpha Team", "Rescue operations", "Downtown", 45, time(NULL), "Pending"};
    Task t2 = {next_id++, "Medical Team", "First aid", "Hospital", 30, time(NULL), "Pending"};
    add_task(task_queue, t1);
    add_task(task_queue, t2);
    
    int choice;
    
    do {
        printf("\n1. Add Task\n2. Process Next Task\n3. Show Tasks\n0. Back\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: {
                if (is_full(task_queue)) {
                    printf("Queue full!\n");
                    break;
                }
                
                Task new_task;
                new_task.id = next_id++;
                
                printf("Team: ");
                fgets(new_task.team, 50, stdin); new_task.team[strcspn(new_task.team, "\n")] = 0;
                printf("Description: ");
                fgets(new_task.description, 100, stdin); new_task.description[strcspn(new_task.description, "\n")] = 0;
                printf("Location: ");
                fgets(new_task.location, 50, stdin); new_task.location[strcspn(new_task.location, "\n")] = 0;
                printf("Time needed (mins): ");
                scanf("%d", &new_task.time_needed);
                
                new_task.start_time = time(NULL);
                strcpy(new_task.status, "Pending");
                
                add_task(task_queue, new_task);
                printf("Task added to queue!\n");
                break;
            }
            case 2:
                if (is_empty(task_queue)) {
                    printf("No tasks to process!\n");
                } else {
                    Task next = get_next_task(task_queue);
                    printf("Processing: %s by %s\n", next.description, next.team);
                }
                break;
            case 3:
                show_tasks(task_queue);
                break;
        }
    } while(choice != 0);
}