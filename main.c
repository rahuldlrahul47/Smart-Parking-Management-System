
#include <stdio.h>
#include <string.h>

#define MAX_SLOTS 5
#define MAX_WAITING 20

typedef struct {
    char vehicle[20];
    int occupied;
} ParkingSlot;

ParkingSlot slots[MAX_SLOTS];

char waitingQueue[MAX_WAITING][20];
int front = 0, rear = -1, count = 0;

int findFreeSlot() {
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (!slots[i].occupied)
            return i;
    }
    return -1;
}

int findVehicle(char vehicle[]) {
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (slots[i].occupied &&
            strcmp(slots[i].vehicle, vehicle) == 0)
            return i;
    }
    return -1;
}

int isWaiting(char vehicle[]) {
    for (int i = 0; i < count; i++) {
        int index = (front + i) % MAX_WAITING;
        if (strcmp(waitingQueue[index], vehicle) == 0)
            return 1;
    }
    return 0;
}

void parkVehicle() {
    char vehicle[20];

    printf("Enter vehicle number: ");
    scanf("%19s", vehicle);

    if (findVehicle(vehicle) != -1 || isWaiting(vehicle)) {
        printf("Vehicle already parked or waiting!\n");
        return;
    }

    int slot = findFreeSlot();

    if (slot != -1) {
        strcpy(slots[slot].vehicle, vehicle);
        slots[slot].occupied = 1;

        printf("Vehicle parked in Slot %d\n", slot + 1);
    } else if (count < MAX_WAITING) {
        rear = (rear + 1) % MAX_WAITING;
        strcpy(waitingQueue[rear], vehicle);
        count++;

        printf("Parking full! Vehicle added to waiting queue.\n");
    } else {
        printf("Parking and waiting queue are full!\n");
    }
}

void exitVehicle() {
    char vehicle[20];

    printf("Enter vehicle number to exit: ");
    scanf("%19s", vehicle);

    int slot = findVehicle(vehicle);

    if (slot == -1) {
        printf("Vehicle not found in parking slots.\n");
        return;
    }

    slots[slot].occupied = 0;
    printf("Vehicle %s exited from Slot %d\n",
           vehicle, slot + 1);

    if (count > 0) {
        strcpy(slots[slot].vehicle, waitingQueue[front]);
        slots[slot].occupied = 1;

        printf("Waiting vehicle %s assigned to Slot %d\n",
               waitingQueue[front], slot + 1);

        front = (front + 1) % MAX_WAITING;
        count--;
    } else {
        slots[slot].vehicle[0] = '\0';
    }
}

void displaySlots() {
    printf("\n--- Parking Slot Status ---\n");

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (slots[i].occupied)
            printf("Slot %d: %s\n",
                   i + 1, slots[i].vehicle);
        else
            printf("Slot %d: Available\n", i + 1);
    }
}

void displayQueue() {
    printf("\n--- Waiting Queue ---\n");

    if (count == 0) {
        printf("No vehicles waiting.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        int index = (front + i) % MAX_WAITING;
        printf("%d. %s\n", i + 1, waitingQueue[index]);
    }
}

void searchVehicle() {
    char vehicle[20];

    printf("Enter vehicle number to search: ");
    scanf("%19s", vehicle);

    int slot = findVehicle(vehicle);

    if (slot != -1)
        printf("Vehicle found in Slot %d\n", slot + 1);
    else if (isWaiting(vehicle))
        printf("Vehicle is in the waiting queue.\n");
    else
        printf("Vehicle not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n===============================\n");
        printf(" SMART PARKING MANAGEMENT SYSTEM\n");
        printf("===============================\n");
        printf("1. Park Vehicle\n");
        printf("2. Vehicle Exit\n");
        printf("3. Display Parking Slots\n");
        printf("4. Display Waiting Queue\n");
        printf("5. Search Vehicle\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                parkVehicle();
                break;
            case 2:
                exitVehicle();
                break;
            case 3:
                displaySlots();
                break;
            case 4:
                displayQueue();
                break;
            case 5:
                searchVehicle();
                break;
            case 6:
                printf("Thank you!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 6);

    return 0;
}
