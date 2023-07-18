//*********************************************************
// Zyler Niece
// Operating Systems
// Programming with Ptheads: Thread Arrays
// Mar 6, 2023
// Instuctor: Dr. Michael Scherger
//*********************************************************

//*********************************************************
//
// Includes and Defines
//
//*********************************************************

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//*********************************************************
//
// Extern Declarations
//
//*********************************************************

//struct to hold data to be passed to a thread
typedef struct str_thdata {
    int thread_no;
    char message[100];
} thdata;

//*********************************************************
//
// Function Prototypes
//
//*********************************************************

//********************************************************************
//
// Print Message Function
//
// This function is a thread function that prints a message along with
// the thread number.
//
// Function Parameters
// -------------------
// ptr void pointer to thread data structure of type thdata
//
// Local Variables
// ---------------
// data thdata* pointer to thread data structure
//
//*******************************************************************

//Prints thread number and message
void print_message_function(void *ptr) {
    thdata *data;
    data = (thdata *) ptr; /* type cast to a pointer to thdata */
    /* do the work */
    printf("Thread %d says %s\n", data->thread_no, data->message);
    pthread_exit(0); /* exit */
}

//*********************************************************
//
// Main Function
//
//*********************************************************

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s num_threads\n", argv[0]);
        exit(1);
    }

    const int n = atoi(argv[1]);

    pthread_t threads[n]; /* thread array */
    thdata data[n]; /* array of structs to be passed to threads */

    /* initialize data to pass to threads */
    for (int i = 0; i < n; i++) {
        data[i].thread_no = i + 1;
        if ((i + 1) % 2 == 0) {
            strcpy(data[i].message, "Hi!");
        } else {
            strcpy(data[i].message, "Hello!");
        }
    }

    /* create threads */
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, (void *) &print_message_function, (void *) &data[i]);
    }

    /* main block now waits for all threads to terminate, before it exits */
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    /* exit */
    exit(0);
}
