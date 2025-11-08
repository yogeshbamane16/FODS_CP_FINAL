#include <stdio.h>

// Declare functions from each member's file
void run_incident_manager();
void run_task_tracker(); 
void run_resource_manager();
void run_dispatch_coordinator();
void run_route_planner();

// Main menu
void show_main_menu() {
    printf("\n  DISASTER MANAGEMENT SYSTEM");
    printf("\n===============================");
    printf("\n1.  Incident Manager");
    printf("\n2.  Task Tracker"); 
    printf("\n3.  Resource Manager");
    printf("\n4.  Dispatch Coordinator");
    printf("\n5.  Route Planner");
    printf("\n6.  System Status");
    printf("\n0.  Exit");
    printf("\n===============================");
    printf("\nChoose (1-6): ");
}

// System status
void show_system_status() {
    printf("\n--- SYSTEM STATUS ---");
    printf("\n Incident Manager: Ready");
    printf("\n Task Tracker: Ready"); 
    printf("\n Resource Manager: Ready");
    printf("\n Dispatch Coordinator: Ready");
    printf("\n Route Planner: Ready");
    printf("\n All systems operational");
}

// Main function
int main() {
    printf("==========================================");
    printf("\n      DISASTER MANAGEMENT SYSTEM");
    printf("\n         Team Project ");
    printf("\n==========================================");
    
    int choice;
    
    do {
        show_main_menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                run_incident_manager();
                break;
            case 2:
                run_task_tracker();
                break;
            case 3:
                run_resource_manager();
                break;
            case 4:
                run_dispatch_coordinator();
                break;
            case 5:
                run_route_planner();
                break;
            case 6:
                show_system_status();
                break;
            case 0:
                printf("\nThank you for using the system!");
                printf("\nStay safe! 🚨\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 0);
    
    return 0;
}