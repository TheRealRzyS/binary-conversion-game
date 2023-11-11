#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include the time.h header for the time limit function in the game
#include <math.h> // Include the math.h header for pow() function
#include <string.h> // Include the string.h header for strcmp() function

#define MAX_QUESTIONS 100 // Increase the number of questions
#define TIME_LIMIT_SECONDS 120 // Set the time limit in seconds
#define NUM_DIFFICULTY_LEVELS 4 // Number of difficulty levels

const int MAX_DIGITS[] = {2, 3, 4, 5}; // Array for maximum digits for each difficulty level

// Function to generate a random number with up to the specified number of digits
int generateRandomNumber(int maxDigits) {
    int max_value = pow(10, maxDigits) - 1; // Calculate the maximum value using pow() function
    return rand() % max_value; // Generate random numbers with up to the specified number of digits
}

// Function to convert a decimal number to binary
int decimalToBinary(int decimal) {
    int binary = 0, base = 1;

    while (decimal > 0) {
        binary += (decimal % 2) * base;
        decimal >>= 1;
        base *= 10;
    }

    return binary;
}

// Function to start the game
void startGame(int maxDigits) {
    srand(time(0));
    int score = 0;
    time_t startTime = time(NULL); // Get the current time

    printf("You have 2 minutes to answer as many questions as possible.\n");

    while ((time(NULL) - startTime) < TIME_LIMIT_SECONDS) {
        int decimal = generateRandomNumber(maxDigits);
        int correctBinary = decimalToBinary(decimal);
        int userBinary;

        printf("Convert %d to binary: ", decimal);

        // Validate user's input
        if (scanf("%d", &userBinary) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        while (getchar() != '\n'); // Clear the input buffer

        if (userBinary == correctBinary) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is %d.\n", correctBinary);
        }
    }

    printf("Time's up! You got %d questions correct.\n", score);
}

// Main function
int main() {
    int choice;
    char quit[5];

    do {
        printf("Binary Conversion Game\n");
        printf("Choose a difficulty level:\n");
        printf("1. Easy\n");
        printf("2. Medium\n");
        printf("3. Hard\n");
        printf("4. Expert\n");
        
        do {
            printf("Choose your difficulty (1-4): ");
            int status = scanf("%d", &choice);
            while(getchar() != '\n'); // Clear the input buffer
            if (status != 1) {
                printf("Invalid input. Please enter a number.\n");
            } else if (choice < 1 || choice > NUM_DIFFICULTY_LEVELS) {
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
            }
        } while (choice < 1 || choice > NUM_DIFFICULTY_LEVELS);

        int maxDigits = MAX_DIGITS[choice - 1]; // Use the array to set the maximum digits for the selected difficulty level

        startGame(maxDigits);

        do {
            printf("Do you want to play again? (yes/no): ");
            scanf("%4s", quit); // Read only the first 4 characters of the user's input
            if (strcmp(quit, "yes") != 0 && strcmp(quit, "no") != 0) {
                printf("Invalid input. Please enter 'yes' or 'no'.\n");
            }
        } while (strcmp(quit, "yes") != 0 && strcmp(quit, "no") != 0);
    } while (strcmp(quit, "no") != 0);

    return 0;
}
