#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Resource {
    char name[50];
    char type[30];
    int amount;
    int priority;
    char location[100];
} Resource;

typedef struct ResourceNode {
    Resource data;
    struct ResourceNode* left;
    struct ResourceNode* right;
    int height;
} ResourceNode;

// Get height of node
int get_height(ResourceNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

// Get balance factor
int get_balance(ResourceNode* node) {
    if (node == NULL) return 0;
    return get_height(node->left) - get_height(node->right);
}

// Create new resource node
ResourceNode* create_node(Resource data) {
    ResourceNode* node = (ResourceNode*)malloc(sizeof(ResourceNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotation
ResourceNode* rotate_right(ResourceNode* y) {
    ResourceNode* x = y->left;
    ResourceNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right)) + 1;
    x->height = (get_height(x->left) > get_height(x->right) ? get_height(x->left) : get_height(x->right)) + 1;
    
    return x;
}

// Left rotation
ResourceNode* rotate_left(ResourceNode* x) {
    ResourceNode* y = x->right;
    ResourceNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = (get_height(x->left) > get_height(x->right) ? get_height(x->left) : get_height(x->right)) + 1;
    y->height = (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right)) + 1;
    
    return y;
}

// Add resource to tree
ResourceNode* add_resource(ResourceNode* node, Resource data) {
    if (node == NULL)
        return create_node(data);
    
    if (data.priority > node->data.priority)
        node->left = add_resource(node->left, data);
    else
        node->right = add_resource(node->right, data);
    
    node->height = 1 + (get_height(node->left) > get_height(node->right) ? get_height(node->left) : get_height(node->right));
    
    int balance = get_balance(node);
    
    // Left Left Case
    if (balance > 1 && data.priority > node->left->data.priority)
        return rotate_right(node);
    
    // Right Right Case
    if (balance < -1 && data.priority <= node->right->data.priority)
        return rotate_left(node);
    
    // Left Right Case
    if (balance > 1 && data.priority <= node->left->data.priority) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    
    // Right Left Case
    if (balance < -1 && data.priority > node->right->data.priority) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    
    return node;
}

// Show resources in order (highest priority first)
void show_resources(ResourceNode* root) {
    if (root != NULL) {
        show_resources(root->left);
        printf("%s | %s | %d units | Priority: %d | %s\n",
               root->data.name, root->data.type, root->data.amount,
               root->data.priority, root->data.location);
        show_resources(root->right);
    }
}

// Count total resources
int count_resources(ResourceNode* root) {
    if (root == NULL) return 0;
    return 1 + count_resources(root->left) + count_resources(root->right);
}

// Member 3's main function
void run_resource_manager() {
    printf("\n=== RESOURCE MANAGER ===\n");
    ResourceNode* resource_tree = NULL;
    
    // Add sample resources
    Resource r1 = {"Ambulances", "Medical", 15, 10, "Central Hospital"};
    Resource r2 = {"Fire Trucks", "Emergency", 8, 9, "Fire Station"};
    Resource r3 = {"Medical Kits", "Medical", 200, 8, "Warehouse"};
    
    resource_tree = add_resource(resource_tree, r1);
    resource_tree = add_resource(resource_tree, r2);
    resource_tree = add_resource(resource_tree, r3);
    
    int choice;
    
    do {
        printf("\n1. Add Resource\n2. Show Resources\n3. Count Resources\n0. Back\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: {
                Resource new_res;
                printf("Name: ");
                fgets(new_res.name, 50, stdin); new_res.name[strcspn(new_res.name, "\n")] = 0;
                printf("Type: ");
                fgets(new_res.type, 30, stdin); new_res.type[strcspn(new_res.type, "\n")] = 0;
                printf("Amount: ");
                scanf("%d", &new_res.amount);
                printf("Priority (1-10): ");
                scanf("%d", &new_res.priority);
                getchar();
                printf("Location: ");
                fgets(new_res.location, 100, stdin); new_res.location[strcspn(new_res.location, "\n")] = 0;
                
                resource_tree = add_resource(resource_tree, new_res);
                printf("Resource added!\n");
                break;
            }
            case 2:
                printf("\n--- Resources by Priority ---\n");
                show_resources(resource_tree);
                break;
            case 3:
                printf("Total resources: %d\n", count_resources(resource_tree));
                break;
        }
    } while(choice != 0);
}