#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define MAX_NAME 50

typedef struct Incident {
    char id[20];
    char name[MAX_NAME];
    char location[100];
    char severity[20];
    int priority;
    struct Incident* next;
} Incident;

typedef struct HashTable {
    Incident* table[TABLE_SIZE];
    int count;
} HashTable;

// Create new hash table
HashTable* create_table() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Simple hash function
unsigned int hash(const char* key) {
    unsigned int hash_value = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash_value = (hash_value * 31 + key[i]) % TABLE_SIZE;
    }
    return hash_value;
}

// Add new incident
void add_incident(HashTable* ht, char* id, char* name, char* location, char* severity, int priority) {
    unsigned int index = hash(id);
    
    Incident* new_incident = (Incident*)malloc(sizeof(Incident));
    strcpy(new_incident->id, id);
    strcpy(new_incident->name, name);
    strcpy(new_incident->location, location);
    strcpy(new_incident->severity, severity);
    new_incident->priority = priority;
    new_incident->next = NULL;
    
    if (ht->table[index] == NULL) {
        ht->table[index] = new_incident;
    } else {
        Incident* current = ht->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_incident;
    }
    ht->count++;
}

// Find incident by ID
Incident* find_incident(HashTable* ht, char* id) {
    unsigned int index = hash(id);
    Incident* current = ht->table[index];
    
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Show all incidents
void show_all_incidents(HashTable* ht) {
    printf("\n--- All Incidents ---\n");
    printf("Total: %d\n\n", ht->count);
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        Incident* current = ht->table[i];
        while (current != NULL) {
            printf("ID: %s | %s | %s | %s | Priority: %d\n",
                   current->id, current->name, current->location,
                   current->severity, current->priority);
            current = current->next;
        }
    }
}

// Show hash table stats
void show_stats(HashTable* ht) {
    int collisions = 0;
    int max_chain = 0;
    int used_buckets = 0;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->table[i] != NULL) {
            used_buckets++;
            int chain_length = 0;
            Incident* current = ht->table[i];
            while (current != NULL) {
                chain_length++;
                current = current->next;
            }
            if (chain_length > 1) collisions += (chain_length - 1);
            if (chain_length > max_chain) max_chain = chain_length;
        }
    }
    
    printf("\n--- Hash Table Stats ---\n");
    printf("Total Incidents: %d\n", ht->count);
    printf("Used Buckets: %d\n", used_buckets);
    printf("Collisions: %d\n", collisions);
    printf("Longest Chain: %d\n", max_chain);
}

// Member 1's main function
void run_incident_manager() {
    printf("\n=== INCIDENT MANAGER ===\n");
    HashTable* incidents = create_table();
    
    // Add sample incidents
    add_incident(incidents, "INC001", "Building Fire", "Downtown", "High", 8);
    add_incident(incidents, "INC002", "Medical Emergency", "Hospital", "Critical", 9);
    add_incident(incidents, "INC003", "Road Accident", "Highway", "Medium", 5);
    
    int choice;
    char search_id[20];
    
    do {
        printf("\n1. Add Incident\n2. Find Incident\n3. Show All\n4. Stats\n0. Back\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: {
                char id[20], name[50], location[100], severity[20];
                int priority;
                
                printf("Incident ID: ");
                fgets(id, 20, stdin); id[strcspn(id, "\n")] = 0;
                printf("Name: ");
                fgets(name, 50, stdin); name[strcspn(name, "\n")] = 0;
                printf("Location: ");
                fgets(location, 100, stdin); location[strcspn(location, "\n")] = 0;
                printf("Severity: ");
                fgets(severity, 20, stdin); severity[strcspn(severity, "\n")] = 0;
                printf("Priority: ");
                scanf("%d", &priority);
                
                add_incident(incidents, id, name, location, severity, priority);
                printf("Incident added!\n");
                break;
            }
            case 2:
                printf("Search ID: ");
                fgets(search_id, 20, stdin); search_id[strcspn(search_id, "\n")] = 0;
                Incident* found = find_incident(incidents, search_id);
                if (found) {
                    printf("Found: %s at %s\n", found->name, found->location);
                } else {
                    printf("Not found!\n");
                }
                break;
            case 3:
                show_all_incidents(incidents);
                break;
            case 4:
                show_stats(incidents);
                break;
        }
    } while(choice != 0);
}