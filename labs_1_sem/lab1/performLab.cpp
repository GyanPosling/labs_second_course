#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "performLab.h"
#include "StringWorker.h"

char* initString(const char* prompt) {
    printf("%s", prompt);
    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), stdin)) return NULL;
    buffer[strcspn(buffer, "\n")] = 0;
    char* result = (char*)malloc(strlen(buffer) + 1);
    strcpy(result, buffer);
    return result;
}

int getValidInput(int min, int max) {
    int num;
    char symbol;
    while (1) {
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input!\nTry again: ");
            continue;
        }
        if (sscanf(buffer, "%d %c", &num, &symbol) != 1) {
            printf("Invalid input! Please enter a number.\nTry again: ");
            continue;
        }
        if (num < min || num > max) {
            printf("The number is not within the range [%d, %d]!\nTry again: ", min, max);
            continue;
        }
        return num;
    }
}

void drawMenu() {
    printf("\n+---------------------------+\n");
    printf("| 1. Print strings          |\n");
    printf("| 2. Get intersection       |\n");
    printf("| 3. Clear and re-enter     |\n");
    printf("| 0. Exit                   |\n");
    printf("+---------------------------+\n");
    printf("Your choice: ");
}

void performTask() {
    char* d1 = initString("Enter first string: ");
    char* d2 = initString("Enter second string: ");
    StringWorker worker(d1, d2);
    free(d1);
    free(d2);

    int choice;
    do {
        drawMenu();
        choice = getValidInput(0, 3);
        if (choice == 1) {
            worker.printStrings();
        } else if (choice == 2) {
            char* inter = worker.getIntersection();
            if (inter) {
                printf("Intersection: %s\n", inter);
                delete[] inter;
            } else {
                printf("No intersection.\n");
            }
        } else if (choice == 3) {
            worker.clearStrings();
            d1 = initString("Enter first string: ");
            d2 = initString("Enter second string: ");
            worker.setFirstString(d1);
            worker.setSecondString(d2);
            free(d1);
            free(d2);
        }
    } while (choice != 0);
}
