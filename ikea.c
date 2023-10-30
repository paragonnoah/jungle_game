#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Default maximum aisles value
#define DEFAULT_MAX_AISLES 100

// Create a dynamic array of pointers to char arrays for aisles
char **aisles[DEFAULT_MAX_AISLES];
// Keep track of the length of each aisle
int aisle_lengths[DEFAULT_MAX_AISLES] = {0};

// Function to print the contents of an aisle
void printAisle(int aisle_index) {
    for (int i = 0; i < aisle_lengths[aisle_index]; i++) {
        printf("%c", *(aisles[aisle_index][i]));
    }
    printf("\n");
}

int main() {
    int num_aisles;
    int max_aisles = DEFAULT_MAX_AISLES;  // Initialize the maximum aisles to a default value
    scanf("%d", &num_aisles);

    // Check if num_aisles exceeds the default maximum
    if (num_aisles > DEFAULT_MAX_AISLES) {
        printf("Error: num_aisles exceeds the default maximum (%d)\n", DEFAULT_MAX_AISLES);
        return 1;  // Exit with an error code
    }

    // Update the maximum aisles value based on the input
    max_aisles = num_aisles;

    // Initialize the aisles with empty arrays
    for (int i = 0; i < max_aisles; i++) {
        aisles[i] = (char **)malloc(0);
        aisle_lengths[i] = 0;
    }

    while (1) {
        int command, product_code, aisle_index;
        char product_name;
        if (scanf("%d", &command) == EOF) break;

        if (command == 0) {
            // Print the requested aisle
            scanf("%d", &aisle_index);
            if (aisle_index >= max_aisles) {
                printf("Error: Invalid aisle index\n");
                return 1;  // Exit with an error code
            }
            printAisle(aisle_index);
        } else {
            // Add a new product to an aisle
            scanf("%d %c", &product_code, &product_name);
            aisle_index = product_code % max_aisles;
            int length = aisle_lengths[aisle_index];
            // Expand the aisle array and add the product
            aisles[aisle_index] = (char **)realloc(aisles[aisle_index], (length + 1) * sizeof(char *));
            aisles[aisle_index][length] = (char *)malloc(sizeof(char));
            *(aisles[aisle_index][length]) = product_name;
            aisle_lengths[aisle_index]++;
        }
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < max_aisles; i++) {
        for (int j = 0; j < aisle_lengths[i]; j++) {
            free(aisles[i][j]);
        }
        free(aisles[i]);
    }

    return 0;
}
