//*********************************************************
// Zyler Niece
// Operating Systems
// Programming with Ptheads: Token Identifier
// Mar 6, 2023
// Instuctor: Dr. Michael Scherger
//*********************************************************

//*********************************************************
//
// Includes and Defines
//
//*********************************************************

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_TOKENS 1000
#define MAX_TOKEN_LEN 100

//*********************************************************
//
// Extern Declarations
//
//*********************************************************

// Structure to store token data
typedef struct {
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int count;
} token_data;

// Variable to keep track of the next thread to print
volatile int next_thread = 0;

//*********************************************************
//
// Function Prototypes
//
//*********************************************************

//***************************************************************************
//
// Uppercase Function
//
// This function receives a pointer to a token_data structure and
// checks each token in the token_data structure for uppercase letters.
// If a token contains an uppercase letter, it is printed with a prefix
// of "UPPER: ". The function uses a turn-based system to ensure that
// only one thread is printing at a time.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to a token_data structure containing
// an array of tokens and a count of the number of tokens in the array.
//
// Local Variables
// ---------------
// data token_data* A pointer to the token_data structure passed in
// i int Loop iteration variable
//
// Global Variables
// ----------------
// next_thread int An integer indicating which thread should print next
//
//***************************************************************************

//***************************************************************************
//
// Lowercase Function
//
// This function receives a pointer to a token_data structure and
// checks each token in the token_data structure for lowercase letters.
// If a token contains a lowercase letter, it is printed with a prefix
// of "LOWER: ". The function uses a turn-based system to ensure that
// only one thread is printing at a time.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to a token_data structure containing
// an array of tokens and a count of the number of tokens in the array.
//
// Local Variables
// ---------------
// data token_data* A pointer to the token_data structure passed in
// i int Loop iteration variable
//
// Global Variables
// ----------------
// next_thread int An integer indicating which thread should print next
//
//***************************************************************************

//***************************************************************************
//
// Number Function
//
// This function receives a pointer to a token_data structure and
// checks each token in the token_data structure for numerical values.
// If a token contains a numerical value, it is printed with a prefix
// of "NUMBER: ". The function uses a turn-based system to ensure that
// only one thread is printing at a time.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to a token_data structure containing
// an array of tokens and a count of the number of tokens in the array.
//
// Local Variables
// ---------------
// data token_data* A pointer to the token_data structure passed in
// i int Loop iteration variable
// num int Integer value parsed from token
// sign char Sign character parsed from token
//
// Global Variables
// ----------------
// next_thread int An integer indicating which thread should print next
//
//***************************************************************************

//***************************************************************************
//
// Other Function
//
// This function receives a pointer to a token_data structure and
// checks each token in the token_data structure to make sure they are
// not Uppercase, lowercase or numbers. for numerical values. It will then
// print the token with the prefix OTHER: If a token contains a numerical value,
// it checks if there is also a letter to see if it should print the token.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to a token_data structure containing 
// an array of tokens and a count of the number of tokens in the array.
//
// Local Variables
// ---------------
// data token_data* A pointer to the token_data structure passed in
// i int Loop iteration variable
// num int Integer value parsed from token
//
// Global Variables
// ----------------
// next_thread int An integer indicating which thread should print next
//
//***************************************************************************

// Function to check if the token is an uppercase word
void* uppercase(void* arg) {
    token_data* data = (token_data*)arg;
    for (int i = 0; i < data->count; i++) {
        // Wait for turn
        while (next_thread != 0) {
            sched_yield();
        }

        // Print token
        if (isupper(data->tokens[i][0])) {
            printf("UPPER:  %s\n", data->tokens[i]);
        }

        // Update turn
        next_thread = (next_thread + 1) % 4;
    }
    pthread_exit(NULL);
}

// Function to check if the token is a lowercase word
void* lowercase(void* arg) {
    token_data* data = (token_data*)arg;
    for (int i = 0; i < data->count; i++) {
        // Wait for turn
        while (next_thread != 1) {
            sched_yield();
        }

        // Print token
        if (islower(data->tokens[i][0])) {
            printf("LOWER:  %s\n", data->tokens[i]);
        }

        // Update turn
        next_thread = (next_thread + 1) % 4;
    }
    pthread_exit(NULL);
}

// Function to check if the token is a number
void* number(void* arg) {
    token_data* data = (token_data*)arg;
    for (int i = 0; i < data->count; i++) {
        // Wait for turn
        while (next_thread != 2) {
            sched_yield();
        }

       // Check if token has any letter
        if (strcspn(data->tokens[i], "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == strlen(data->tokens[i])) {
            // Token does not have any letter
            // Print token
            int num;
            char sign;
            if (sscanf(data->tokens[i], "%c%d", &sign, &num) == 2 &&
                (sign == '+' || sign == '-')) {
                printf("NUMBER: %c%d\n", sign, num);
            } else if (sscanf(data->tokens[i], "%d", &num) == 1) {
                printf("NUMBER: %d\n", num);
            }
        }

        // Update turn
        next_thread = (next_thread + 1) % 4;
    }
    pthread_exit(NULL);
}

// Function to check if the token is other (not an uppercase, lowercase or number)
void* other(void* arg) {
    token_data* data = (token_data*)arg;
    for (int i = 0; i < data->count; i++) {
        // Wait for turn
        while (next_thread != 3) {
            sched_yield();
        }

        // Print token
        if (!isupper(data->tokens[i][0]) && !islower(data->tokens[i][0])) {
            int num;
            if (sscanf(data->tokens[i], "%d", &num) != 1) {
                printf("OTHER:  %s\n", data->tokens[i]);
            }
            else if (sscanf(data->tokens[i], "%d", &num) == 1 && strcspn(data->tokens[i], "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != strlen(data->tokens[i])) {
            printf("OTHER:  %s\n", data->tokens[i]);
            }
        }

        // Update turn
        next_thread = (next_thread + 1) % 4;
    }
    pthread_exit(NULL);
}

//*********************************************************
//
// Main Function
//
//*********************************************************
int main(int argc, char* argv[]) {
    // Initialize token data structure
    token_data data;
    data.count = 0;

    // Store tokens in the token data structure
    for (int i = 1; i < argc; i++) {
        if (strlen(argv[i]) > MAX_TOKEN_LEN - 1) {
            fprintf(stderr, "Token is too long.\n");
            exit(1);
        }
        strcpy(data.tokens[data.count], argv[i]);
        data.count++;
    }
    // Initialize threads
    pthread_t t_uppercase, t_lowercase, t_number, t_other;

    // Create threads
    pthread_create(&t_uppercase, NULL, uppercase, (void*)&data);
    pthread_create(&t_lowercase, NULL, lowercase, (void*)&data);
    pthread_create(&t_number, NULL, number, (void*)&data);
    pthread_create(&t_other, NULL, other, (void*)&data);

    // Wait for threads to complete
    pthread_join(t_uppercase, NULL);
    pthread_join(t_lowercase, NULL);
    pthread_join(t_number, NULL);
    pthread_join(t_other, NULL);

    return 0;
}

