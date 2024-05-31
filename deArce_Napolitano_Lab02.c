//Written by: Richelle de Arce & Klaire Napolitano 1-BSCS
//Date: 03-35-24

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_SIZE 100 // maximum size of kitchenware

typedef struct Node { // defining Node
    char name[50];
    struct Node *nextNode;
} Node;

// Function Prototypes
void getKitchenware(char* data); // Function to get kitchenware name from user
void PUSH(Node **start, char *data); // Function to add kitchenware to the stack
char* POP(Node** start); // Function to remove the top kitchenware from the stack
bool FULL(Node *start); // Function to check if the stack is full
bool EMPTY(Node *start); // Function to check if the stack is empty
char* TOP(Node** start); // Function to get the top kitchenware without removing it
void MAKENULL(Node **start); // Function to remove all kitchenware from the stack
void printMenu(int* option); // Function to print the menu and get user choice

// Main Function
int main () {
    // Variables
    Node *head = NULL; // Initialize the stack
    char kitchenware[50]; // To store kitchenware name entered by user
    int choice = -1; // User choice for menu

    // Menu
    while (choice != 0) {
        printMenu(&choice); // Display Menu
        system("cls"); // Refresh display
        switch (choice) {
            case 1: // Add kitchenware
                if (FULL(head))
                    printf("\nThe STACK is FULL. Cannot add kitchenware.\n");
                else {
                    getKitchenware(kitchenware);
                    PUSH(&head, kitchenware);
                }
                break;
            case 2: // Wash top kitchenware
                if (EMPTY(head))
                    printf("\nThe STACK is EMPTY. No more kitchenware to wash.\n");
                else
                    printf("%s is being washed.\n", POP(&head));
                break;
            case 3: // Know top kitchenware
                if (EMPTY(head))
                    printf("\nThe STACK is EMPTY. No more kitchenware to wash.\n");
                else
                    printf("%s is next to be washed.\n", TOP(&head));
                break;
            case 4: // Display all washed kitchenware
                printf("Washing all kitchenware:\n");
                if (EMPTY(head))
                    printf("The STACK is EMPTY. No more kitchenware to wash.\n");
                else
                    MAKENULL(&head);
                break;
            case 0: // Exit
                printf("===== Washing machine process has been terminated. =====\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    free(head); // Free allocated memory
    return 0;
}

// Function Definitions

void getKitchenware(char* data) {
    // Get kitchenware name from user
    printf("Kitchenware to be washed: ");
    scanf("%s", data);
    while (getchar() != '\n'); // Clear input buffer
}

void PUSH(Node **start, char *data) {
    // Add kitchenware to the stack
    Node* Newnode = (Node*)malloc(sizeof(Node));
    if (Newnode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(Newnode->name, data);
    Newnode->nextNode = *start;
    *start = Newnode;
}

char* POP(Node** start) {
    // Remove the top kitchenware from the stack
    Node* temp = *start;
    *start = temp->nextNode;
    char* data = (char*)malloc(sizeof(char) * 51); // Allocate memory for the string and null terminator
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(data, temp->name);
    free(temp);
    return data;
}

bool FULL(Node *start) {
    // Check if the stack is full
    int count = 0;
    Node *current = start;
    while (current != NULL) {
        count++;
        current = current->nextNode;
    }
    return count >= MAX_SIZE;
}

bool EMPTY(Node *start) {
    // Check if the stack is empty
    return start == NULL;
}

char* TOP(Node** start) {
    // Get the top kitchenware without removing it
    return (*start)->name;
}

void MAKENULL(Node **start) {
    // Remove all kitchenware from the stack
    while (*start != NULL) {
        Node* temp = *start;
        *start = temp->nextNode;
        printf("%s is being washed\n", temp->name);
        free(temp);
    }
    printf("\n-----------------------------------------------------------------------------------\n");
    printf("\nThe STACK is empty. No kitchenware to wash\n");
    printf("\n-----------------------------------------------------------------------------------\n");
    
}

void printMenu(int* option) {
    // Print the menu and get user choice
    printf("\n===================================================================================");
    printf("\nKitchenware Washing Machine\n"
            "-----------------------------------------------------------------------------------\n"
           "[1] Add kitchenware\n"
           "[2] Wash kitchenware\n"
           "[3] Top kitchenware\n"
           "[4] Wash all\n"
           "[0] Exit\n"
           "\n===================================================================================\n"
           "Enter choice: ");
    scanf(" %d", option);
    while (getchar() != '\n'); // Clear input buffer
}
