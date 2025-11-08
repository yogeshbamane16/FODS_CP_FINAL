#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_PLACES 20
#define INFINITY INT_MAX

typedef struct Place {
    char name[30];
    int id;
} Place;

typedef struct RoadMap {
    int distances[MAX_PLACES][MAX_PLACES];
    Place places[MAX_PLACES];
    int place_count;
} RoadMap;

// Create empty roadmap
RoadMap* create_roadmap() {
    RoadMap* map = (RoadMap*)malloc(sizeof(RoadMap));
    map->place_count = 0;
    
    for (int i = 0; i < MAX_PLACES; i++) {
        for (int j = 0; j < MAX_PLACES; j++) {
            map->distances[i][j] = (i == j) ? 0 : INFINITY;
        }
    }
    return map;
}

// Add place to roadmap
void add_place(RoadMap* map, char* name) {
    if (map->place_count < MAX_PLACES) {
        strcpy(map->places[map->place_count].name, name);
        map->places[map->place_count].id = map->place_count;
        map->place_count++;
    }
}

// Add road between places
void add_road(RoadMap* map, int from, int to, int distance) {
    if (from < map->place_count && to < map->place_count) {
        map->distances[from][to] = distance;
        map->distances[to][from] = distance;
    }
}

// Find shortest path using Dijkstra
void find_shortest_path(RoadMap* map, int start, int end) {
    int dist[MAX_PLACES];
    int visited[MAX_PLACES] = {0};
    int previous[MAX_PLACES];
    
    for (int i = 0; i < map->place_count; i++) {
        dist[i] = INFINITY;
        previous[i] = -1;
    }
    dist[start] = 0;
    
    for (int count = 0; count < map->place_count - 1; count++) {
        int min_dist = INFINITY;
        int current = -1;
        
        // Find nearest unvisited place
        for (int i = 0; i < map->place_count; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                current = i;
            }
        }
        
        if (current == -1) break;
        visited[current] = 1;
        
        // Update distances to neighbors
        for (int i = 0; i < map->place_count; i++) {
            if (!visited[i] && map->distances[current][i] != INFINITY &&
                dist[current] != INFINITY &&
                dist[current] + map->distances[current][i] < dist[i]) {
                dist[i] = dist[current] + map->distances[current][i];
                previous[i] = current;
            }
        }
    }
    
    if (dist[end] == INFINITY) {
        printf("No route found!\n");
        return;
    }
    
    printf("Shortest path from %s to %s: %d km\n", 
           map->places[start].name, map->places[end].name, dist[end]);
    
    // Show path
    int path[MAX_PLACES];
    int path_count = 0;
    int current = end;
    
    while (current != -1) {
        path[path_count++] = current;
        current = previous[current];
    }
    
    printf("Route: ");
    for (int i = path_count - 1; i >= 0; i--) {
        printf("%s", map->places[path[i]].name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

// Show all places
void show_places(RoadMap* map) {
    printf("\n--- Available Places ---\n");
    for (int i = 0; i < map->place_count; i++) {
        printf("%d. %s\n", i, map->places[i].name);
    }
}

// Member 5's main function
void run_route_planner() {
    printf("\n=== ROUTE PLANNER ===\n");
    RoadMap* city_map = create_roadmap();
    
    // Add sample places
    add_place(city_map, "Danger Zone");
    add_place(city_map, "Main Street");
    add_place(city_map, "Hospital");
    add_place(city_map, "Safe Zone");
    
    // Add sample roads
    add_road(city_map, 0, 1, 5);
    add_road(city_map, 1, 2, 3);
    add_road(city_map, 1, 3, 8);
    add_road(city_map, 2, 3, 6);
    
    int choice;
    
    do {
        printf("\n1. Find Shortest Route\n2. Show Places\n3. Add Place\n4. Add Road\n0. Back\nChoice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: {
                int start, end;
                show_places(city_map);
                printf("Start place ID: ");
                scanf("%d", &start);
                printf("End place ID: ");
                scanf("%d", &end);
                find_shortest_path(city_map, start, end);
                break;
            }
            case 2:
                show_places(city_map);
                break;
            case 3: {
                char name[30];
                printf("Place name: ");
                getchar();
                fgets(name, 30, stdin); name[strcspn(name, "\n")] = 0;
                add_place(city_map, name);
                printf("Place added!\n");
                break;
            }
            case 4: {
                int from, to, dist;
                show_places(city_map);
                printf("From ID: ");
                scanf("%d", &from);
                printf("To ID: ");
                scanf("%d", &to);
                printf("Distance: ");
                scanf("%d", &dist);
                add_road(city_map, from, to, dist);
                printf("Road added!\n");
                break;
            }
        }
    } while(choice != 0);
}