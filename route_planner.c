#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLACES 20

typedef struct Place {
    char name[30];
    char type[20];
} Place;

typedef struct Road {
    int from;
    int to;
    int distance;
} Road;

typedef struct EmergencyMap {
    Place locations[MAX_PLACES];
    Road roads[MAX_PLACES * MAX_PLACES];
    int location_count;
    int road_count;
} EmergencyMap;

// Create empty map
EmergencyMap* create_emergency_map() {
    EmergencyMap* map = (EmergencyMap*)malloc(sizeof(EmergencyMap));
    map->location_count = 0;
    map->road_count = 0;
    return map;
}

// Add emergency location
void add_location(EmergencyMap* map, char* name, char* type) {
    if (map->location_count < MAX_PLACES) {
        strcpy(map->locations[map->location_count].name, name);
        strcpy(map->locations[map->location_count].type, type);
        map->location_count++;
        printf("%s location '%s' added! (ID: %d)\n", type, name, map->location_count);
    }
}

// Add road between locations
void add_road(EmergencyMap* map, int from_id, int to_id, int distance) {
    if (from_id < 1 || from_id > map->location_count || to_id < 1 || to_id > map->location_count) {
        printf("Invalid location IDs!\n");
        return;
    }
    if (distance <= 0) {
        printf("Distance must be positive!\n");
        return;
    }
    
    from_id--;
    to_id--;
    
    map->roads[map->road_count].from = from_id;
    map->roads[map->road_count].to = to_id;
    map->roads[map->road_count].distance = distance;
    map->road_count++;
    
    printf("Road added: %s <-> %s (%d km)\n", 
           map->locations[from_id].name, map->locations[to_id].name, distance);
}

// Show all locations
void show_locations(EmergencyMap* map) {
    printf("\n--- EMERGENCY LOCATIONS ---\n");
    if (map->location_count == 0) {
        printf("No locations added yet!\n");
        return;
    }
    
    for (int i = 0; i < map->location_count; i++) {
        printf("%d. %s [%s]\n", i+1, map->locations[i].name, map->locations[i].type);
    }
    
    if (map->road_count > 0) {
        printf("\nRoad Connections: %d\n", map->road_count);
        for (int i = 0; i < map->road_count; i++) {
            printf("%s <-> %s (%d km)\n",
                   map->locations[map->roads[i].from].name,
                   map->locations[map->roads[i].to].name,
                   map->roads[i].distance);
        }
    }
}

// AUTOMATICALLY find and display the shortest route
void find_shortest_route(EmergencyMap* map) {
    if (map->location_count < 2) {
        printf("Need at least 2 locations!\n");
        return;
    }
    
    if (map->road_count == 0) {
        printf("No roads added!\n");
        return;
    }
    
    // Find the road with shortest distance
    int shortest_index = -1;
    int shortest_distance = 1000000; // Large number
    
    for (int i = 0; i < map->road_count; i++) {
        if (map->roads[i].distance < shortest_distance) {
            shortest_distance = map->roads[i].distance;
            shortest_index = i;
        }
    }
    
    // Display the shortest route automatically
    if (shortest_index != -1) {
        printf("SHORTEST ROUTE: %s <-> %s (%d km)\n", 
               map->locations[map->roads[shortest_index].from].name,
               map->locations[map->roads[shortest_index].to].name,
               shortest_distance);
    }
}

// Add location with user input
void add_location_interactive(EmergencyMap* map) {
    char name[30], type[20];
    
    printf("\nEnter location name: ");
    while (getchar() != '\n');
    fgets(name, 30, stdin); 
    name[strcspn(name, "\n")] = 0;
    
    printf("Enter type (Danger/Safe/Hospital/Shelter): ");
    fgets(type, 20, stdin); 
    type[strcspn(type, "\n")] = 0;
    
    add_location(map, name, type);
}

// Add road with user input
void add_road_interactive(EmergencyMap* map) {
    if (map->location_count < 2) {
        printf("Need at least 2 locations!\n");
        return;
    }
    
    printf("Available Locations:\n");
    for (int i = 0; i < map->location_count; i++) {
        printf("%d. %s [%s]\n", i+1, map->locations[i].name, map->locations[i].type);
    }
    
    int from_id, to_id, distance;
    printf("\nEnter FROM location ID: ");
    scanf("%d", &from_id);
    printf("Enter TO location ID: ");
    scanf("%d", &to_id);
    printf("Enter distance (km): ");
    scanf("%d", &distance);
    
    add_road(map, from_id, to_id, distance);
}

// Main route planner function
void run_route_planner() {
    printf("\n=== EMERGENCY EVACUATION PLANNER ===\n");
    EmergencyMap* emergency_map = create_emergency_map();
    
    int choice;
    
    do {
        printf("\n1. Find Shortest Route\n");
        printf("2. Show All Locations & Roads\n");
        printf("3. Add Emergency Location\n");
        printf("4. Add Road Connection\n");
        printf("0. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: find_shortest_route(emergency_map); break;
            case 2: show_locations(emergency_map); break;
            case 3: add_location_interactive(emergency_map); break;
            case 4: add_road_interactive(emergency_map); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);
    
    free(emergency_map);
}
