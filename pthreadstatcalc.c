//*********************************************************
// Zyler Niece
// Operating Systems
// Programming with Ptheads: Threaded Statistics Calculator
// Mar 6, 2023
// Instuctor: Dr. Michael Scherger
//*********************************************************

//*********************************************************
//
// Includes and Defines
//
//*********************************************************

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

#define MAX_NUMBERS 1000

//*********************************************************
//
// Extern Declarations
//
//*********************************************************

int num_count;

double min_val, max_val, mean_val, median_val, mode_val, std_dev_val;

//*********************************************************
//
// Function Prototypes
//
//*********************************************************

//***************************************************************************
//
// Compute Min Function
//
// This function receives a void pointer to an array of integers and computes
// the minimum value of the array. The function first initializes min_val to the
// first value in the array, and then loops through the remaining values to find
// the smallest value.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to an array of integers.
//
// Local Variables
// ---------------
// numbers int* A pointer to the array of integers passed in.
// min_val int The smallest value in the numbers array.
// i int Loop iteration variable used to iterate over the numbers array.
//
// Global Variables
// ----------------
// num_count int An integer specifying the length of the numbers array.
//
//***************************************************************************

//***************************************************************************
//
// Compute Max Function
//
// This function receives a void pointer to an array of integers and computes
// the maximum value of the array. The function first initializes max_val to the
// first value in the array, and then loops through the remaining values to find
// the largest value.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to an array of integers.
//
// Local Variables
// ---------------
// numbers int* A pointer to the array of integers passed in.
// max_val int The largest value in the numbers array.
// i int Loop iteration variable used to iterate over the numbers array.
//
// Global Variables
// ----------------
// num_count int An integer specifying the length of the numbers array.
//
//***************************************************************************

//***************************************************************************
//
// Compute Mean Function
//
// This function receives a pointer to an array of integers and calculates the
// mean value of the numbers in the array.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to an array of integers.
//
// Local Variables
// ---------------
// numbers int* A pointer to the array of integers passed in
// sum double The sum of all the integers in the array
// i int Loop iteration variable
//
// Global Variables
// ----------------
// mean_val double The mean value of the numbers in the array
//
//***************************************************************************

//***************************************************************************
//
// Compute Median Function
//
// This function receives a void pointer to an array of integers and computes
// the median value (middle value) of the array. The function first creates a
// copy of the input array and sorts it in ascending order using a nested loop
// with a bubble sort algorithm. It then computes the median value based on
// whether the length of the array is odd or even.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to an array of integers.
//
// Local Variables
// ---------------
// numbers int* A pointer to the array of integers passed in.
// sorted int[] An array used to store a sorted copy of the numbers array.
// i int Loop iteration variable used to copy the numbers array to the sorted array.
// j int Loop iteration variable used in nested loop to perform bubble sort.
// temp int A temporary variable used to swap values during the bubble sort.
// median_val float The value of the median (middle value) of the sorted array.
//
// Global Variables
// ----------------
// num_count int An integer specifying the length of the numbers array.
//
//***************************************************************************

//***************************************************************************
//
// Compute Mode Function
//
// This function receives a void pointer to an array of integers and computes
// the mode (most frequently occurring value) in the array. The function uses
// a frequency array to keep track of the frequency of each number in the array.
// The mode is the number with the highest frequency in the frequency array.
// If there are multiple numbers with the same frequency, the function chooses
// the first one it encounters.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to an array of integers.
//
// Local Variables
// ---------------
// numbers int* A pointer to the array of integers passed in.
// freq int[] An array used to keep track of the frequency of each number in the numbers array.
// max_freq int The highest frequency found in the numbers array.
// mode_val int The value of the mode (most frequently occurring number).
// i int Loop iteration variable.
// j int Loop iteration variable used in nested loop.
//
// Global Variables
// ----------------
// None.
//
//***************************************************************************


//***************************************************************************
//
// Compute Standard Deviation Function
//
// This function receives a void pointer to an array of integers and computes
// the standard deviation of the array. The function first calculates the mean
// value of the array using the previously computed mean_val global variable.
// It then loops through the array, subtracting the mean from each value and
// squaring the difference. The sum of these squares is then divided by the
// number of elements in the array minus one, and the square root of this
// result is assigned to the std_dev_val global variable.
//
// Function Parameters
// -------------------
// arg void pointer A pointer to an array of integers.
//
// Local Variables
// ---------------
// numbers int* A pointer to the array of integers passed in.
// sum double A running sum used to compute the sum of squared differences.
// mean double The mean value of the numbers array.
// i int Loop iteration variable used to iterate over the numbers array.
//
// Global Variables
// ----------------
// num_count int An integer specifying the length of the numbers array.
// mean_val double The mean value of the numbers array, computed by the
// compute_mean function.
// std_dev_val double The standard deviation of the numbers array, computed
// by this function.
//
//***************************************************************************

void* compute_min(void* arg) {
    int *numbers = (int *) arg;
    min_val = numbers[0];
    for (int i = 1; i < num_count; i++) {
        if (numbers[i] < min_val) {
            min_val = numbers[i];
        }
    }
    pthread_exit(NULL);
}

void* compute_max(void* arg) {
    int *numbers = (int *) arg;
    max_val = numbers[0];
    for (int i = 1; i < num_count; i++) {
        if (numbers[i] > max_val) {
            max_val = numbers[i];
        }
    }
    pthread_exit(NULL);
}

void* compute_mean(void* arg) {
    int *numbers = (int *) arg;
    double sum = 0.0;
    for (int i = 0; i < num_count; i++) {
        sum += numbers[i];
    }
    mean_val = sum / num_count;
    pthread_exit(NULL);
}

void* compute_median(void* arg) {
    int *numbers = (int *) arg;
    int sorted[num_count];
    for (int i = 0; i < num_count; i++) {
        sorted[i] = numbers[i];
    }
    for (int i = 0; i < num_count - 1; i++) {
        for (int j = i + 1; j < num_count; j++) {
            if (sorted[i] > sorted[j]) {
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    if (num_count % 2 == 0) {
        median_val = (sorted[num_count / 2 - 1] + sorted[num_count / 2]) / 2.0;
    } else {
        median_val = sorted[num_count / 2];
    }
    pthread_exit(NULL);
}

void* compute_mode(void* arg) {
    int *numbers = (int *) arg;
    int freq[num_count];
    for (int i = 0; i < num_count; i++) {
        freq[i] = 0;
    }
    int max_freq = 0;
    for (int i = 0; i < num_count; i++) {
        for (int j = i; j < num_count; j++) {
            if (numbers[j] == numbers[i]) {
                freq[i]++;
            }
        }
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            mode_val = numbers[i];
        }
    }
    if (max_freq == 1) {
        mode_val = -1; // indicates no mode
    }
    pthread_exit(NULL);
}

void* compute_std_dev(void* arg) {
    int *numbers = (int *) arg;
    double sum = 0.0, mean = mean_val;
    for (int i = 0; i < num_count; i++) {
        sum += (numbers[i] - mean) * (numbers[i] - mean);
    }
    std_dev_val = sqrt(sum / (num_count - 1));
    pthread_exit(NULL);
}

//*********************************************************
//
// Main Function
//
//*********************************************************


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <integer1> [<integer2> ... <integerN>]\n", argv[0]);
        return 1;
    }
// Parse the integers provided in the command-line arguments and store them in an array.
int input_size = argc - 1;
int numbers[MAX_NUMBERS];
for (int i = 0; i < input_size; i++) {
    char *endptr;
    errno = 0;
    long val = strtol(argv[i + 1], &endptr, 10);
    // Check for invalid input.
    if (endptr == argv[i + 1] || *endptr != '\0' || errno == ERANGE) {
        printf("Invalid input: %s\n", argv[i + 1]);
        return 1;
    }
    // Check that the input is within the range of integers.
    if (val < INT_MIN || val > INT_MAX) {
        printf("Input out of range: %s\n", argv[i + 1]);
        return 1;
    }
    numbers[i] = (int) val;
}

// Create 6 threads, one for each statistical computation function.
pthread_t threads[6];
int rc;
num_count = input_size;

    rc = pthread_create(&threads[0], NULL, compute_min, (void *) numbers);
    if (rc) {
        fprintf(stderr, "Error creating min thread: %d\n", rc);
        return 1;
    }

    rc = pthread_create(&threads[1], NULL, compute_max, (void *) numbers);
    if (rc) {
        fprintf(stderr, "Error creating max thread: %d\n", rc);
        return 1;
    }

    rc = pthread_create(&threads[2], NULL, compute_mean, (void *) numbers);
    if (rc) {
        fprintf(stderr, "Error creating mean thread: %d\n", rc);
        return 1;
    }

    rc = pthread_create(&threads[3], NULL, compute_median, (void *) numbers);
    if (rc) {
        fprintf(stderr, "Error creating median thread: %d\n", rc);
        return 1;
    }

    rc = pthread_create(&threads[4], NULL, compute_mode, (void *) numbers);
    if (rc) {
        fprintf(stderr, "Error creating mode thread: %d\n", rc);
        return 1;
    }

    rc = pthread_create(&threads[5], NULL, compute_std_dev, (void *) numbers);
    if (rc) {
        fprintf(stderr, "Error creating std dev thread: %d\n", rc);
        return 1;
    }

    for (int i = 0; i < 6; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            fprintf(stderr, "Error joining thread %d: %d\n", i, rc);
            return 1;
        }
    }
    //Print the 6 Answers from the Computations
    printf("MIN:        %d\n", (int) min_val);
    printf("MAX:        %d\n", (int) max_val);
    printf("MEAN:       %.3f\n", mean_val);
    printf("MEDIAN:     %.1f\n", median_val);
    if (mode_val == -1) {
        printf("MODE:       NO MODE\n");
    } else {
        printf("MODE:       %.0f\n", mode_val);
    }
    printf("STD. DEV.:  %.3f\n", std_dev_val);

    return 0;
}