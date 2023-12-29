#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_QUESTIONS 100
#define TIME_LIMIT_SECONDS 120
#define NUM_DIFFICULTY_LEVELS 3
#define BUFFER_SIZE 1024

const int MAX_DIGITS[] = {1, 2, 4};

// Generates a random number with up to the specified number of digits
int generateRandomNumber(int maxDigits) {
    int max_value = (int) pow(10, maxDigits) - 1;
    max_value = (max_value > 1024) ? 1024 : max_value;
    return rand() % (max_value + 1);
}

// Converts a decimal number to a binary string
void decimalToBinary(int decimal, char *binaryStr) {
    char temp[BUFFER_SIZE];
    int tempIndex = 0;

    while (decimal > 0) {
        temp[tempIndex++] = (decimal % 2) + '0';
        decimal /= 2;
    }
    temp[tempIndex] = '\0';

    // Reverse the string as the binary representation is calculated in reverse
    int leftIndex, rightIndex;
    for (leftIndex = 0, rightIndex = tempIndex - 1; leftIndex < rightIndex; leftIndex++, rightIndex--) {
        char ch = temp[leftIndex];
        temp[leftIndex] = temp[rightIndex];
        temp[rightIndex] = ch;
    }
    strcpy(binaryStr, temp);
}

// Validates if input is a binary number
int isBinary(const char *str) {
    while (*str) {
        if (*str != '0' && *str != '1') return 0;
        str++;
    }
    return 1;
}

// Starts the game with the given maximum digits
void startGame(int maxDigits) {
    srand(time(0));
    int score = 0;
    time_t startTime = time(NULL);
    printf("You have 2 minutes to answer as many questions as possible.\n");

    while ((time(NULL) - startTime) < TIME_LIMIT_SECONDS) {
        int decimal = generateRandomNumber(maxDigits);
        char correctBinary[BUFFER_SIZE];
        decimalToBinary(decimal, correctBinary);
        char userBinary[BUFFER_SIZE];

        printf("Convert %d to binary: ", decimal);
        fgets(userBinary, BUFFER_SIZE, stdin);
        userBinary[strcspn(userBinary, "\n")] = 0; // Remove newline character

        if (strcmp(userBinary, correctBinary) == 0) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is %s.\n", correctBinary);
        }
    }

    printf("Time's up! You got %d questions correct.\n", score);
}

// Main function
int main() {
    char choiceStr[BUFFER_SIZE];
    int choice;
    char quit[BUFFER_SIZE];

    do {
        printf("Binary Conversion Game\nChoose a difficulty level:\n1. Easy\n2. Medium\n3. Hard\n");

        do {
            printf("Choose your difficulty (1-3): ");
            fgets(choiceStr, BUFFER_SIZE, stdin);
            choice = atoi(choiceStr);
            if (choice < 1 || choice > NUM_DIFFICULTY_LEVELS) {
                printf("Invalid choice. Please enter a number between 1 and 3.\n");
            }
        } while (choice < 1 || choice > NUM_DIFFICULTY_LEVELS);

        startGame(MAX_DIGITS[choice - 1]);

        do {
            printf("Do you want to play again? (yes/no): ");
            fgets(quit, sizeof(quit), stdin);
            quit[strcspn(quit, "\n")] = 0; // Remove newline character
            if (strcmp(quit, "yes") != 0 && strcmp(quit, "no") != 0) {
                printf("Invalid input. Please enter 'yes' or 'no'.\n");
            }
        } while (strcmp(quit, "yes") != 0 && strcmp(quit, "no") != 0);
    } while (strcmp(quit, "no") != 0);

    return 0;
}
