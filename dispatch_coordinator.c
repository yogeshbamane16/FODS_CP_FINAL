#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESPONDERS 50

typedef struct Responder {
    int id;
    char name[50];
    char specialty[30];
    char location[50];
    int distance;
    int skill;
    int available;
} Responder;

// Swap two responders
void swap_responders(Responder* a, Responder* b) {
    Responder temp = *a;
    *a = *b;
    *b = temp;
}

// Sort by distance (QuickSort)
void sort_by_distance(Responder arr[], int low, int high) {
    if (low < high) {
        Responder pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j].distance < pivot.distance) {
                i++;
                swap_responders(&arr[i], &arr[j]);
            }
        }
        swap_responders(&arr[i + 1], &arr[high]);
        int pi = i + 1;
        
        sort_by_distance(arr, low, pi - 1);
        sort_by_distance(arr, pi + 1, high);
    }
}

// Sort by skill (simple bubble sort)
void sort_by_skill(Responder arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].skill < arr[j+1].skill) {
                swap_responders(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Sort by availability
void sort_by_availability(Responder arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].available < arr[j+1].available) {
                swap_responders(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Show responders
void show_responders(Responder arr[], int count, char* sort_type) {
    printf("\n--- Responders Sorted by %s ---\n", sort_type);
    for (int i = 0; i < count; i++) {
        printf("ID: %d | %s | %s | %s | Dist: %d | Skill: %d | Available: %d\n",
               arr[i].id, arr[i].name, arr[i].specialty, arr[i].location,
               arr[i].distance, arr[i].skill, arr[i].available);
    }
}

// Member 4's main function
void run_dispatch_coordinator() {
    printf("\n=== DISPATCH COORDINATOR ===\n");
    
    Responder responders[MAX_RESPONDERS];
    int count = 0;
    
    // Add sample responders
    responders[count++] = (Responder){1, "John Smith", "Medical", "Station A", 8, 9, 85};
    responders[count++] = (Responder){2, "Sarah Johnson", "Rescue", "Station B", 3, 10, 92};
    responders[count++] = (Responder){3, "Mike Chen", "Medical", "Hospital", 12, 8, 78};
    
    int choice;
    
    do {
        printf("\n1. Sort by Distance\n2. Sort by Skill\n3. Sort by Availability\n4. Add Responder\n0. Back\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: {
                Responder temp[MAX_RESPONDERS];
                for (int i = 0; i < count; i++) temp[i] = responders[i];
                sort_by_distance(temp, 0, count-1);
                show_responders(temp, count, "Distance");
                break;
            }
            case 2: {
                Responder temp[MAX_RESPONDERS];
                for (int i = 0; i < count; i++) temp[i] = responders[i];
                sort_by_skill(temp, count);
                show_responders(temp, count, "Skill");
                break;
            }
            case 3: {
                Responder temp[MAX_RESPONDERS];
                for (int i = 0; i < count; i++) temp[i] = responders[i];
                sort_by_availability(temp, count);
                show_responders(temp, count, "Availability");
                break;
            }
            case 4: {
                if (count >= MAX_RESPONDERS) {
                    printf("Maximum responders reached!\n");
                    break;
                }
                Responder new_resp;
                new_resp.id = count + 1;
                
                printf("Name: ");
                fgets(new_resp.name, 50, stdin); new_resp.name[strcspn(new_resp.name, "\n")] = 0;
                printf("Specialty: ");
                fgets(new_resp.specialty, 30, stdin); new_resp.specialty[strcspn(new_resp.specialty, "\n")] = 0;
                printf("Location: ");
                fgets(new_resp.location, 50, stdin); new_resp.location[strcspn(new_resp.location, "\n")] = 0;
                printf("Distance: ");
                scanf("%d", &new_resp.distance);
                printf("Skill (1-10): ");
                scanf("%d", &new_resp.skill);
                printf("Availability (0-100): ");
                scanf("%d", &new_resp.available);
                
                responders[count++] = new_resp;
                printf("Responder added!\n");
                break;
            }
        }
    } while(choice != 0);
}