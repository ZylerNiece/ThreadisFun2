# Programming with Ptheads
## Operating Systems

---

## Thread Arrays (20 points)
Type in the attached program that uses pthreads and verify that it compiles and executes correctly. Modify the program to use a thread array rather than individual thread variables. Pass into your program the number of threads to create via command line arguments. The name of this program should be `threadarray.c`.  Here is an example:
```text
mscherger@lovelace:OS-threadfun2$ ./threadarray 8
Thread 1 says Hello!
Thread 2 says Hi!
Thread 4 says Hi!
Thread 5 says Hello!
Thread 7 says Hello!
Thread 8 says Hi!
Thread 6 says Hi!
Thread 3 says Hello!
mscherger@lovelace:OS-threadfun2$
```

---

## Threaded Statistics Calculator (20 points)
Write a multithreaded program (using pthreads) that performs various statistical operations. The main thread will read integers from the command line and store them in an array. Separate threads will be created each will compute the following operations respectively: min, max, mean, median, mode, sample standard deviation. Each thread will compute their respective functions and return the result back to the main thread. The main thread will then print out the results in the order shown below. The name of this program should be `pthreadstatcalc.c` or `.cpp`. Here is an example:
```text
mscherger@lovelace:OS-threadfun2$ ./pthreadstatcalc 1 20 300 41 51 68 79 80 81
MIN:        1
MAX:        300
MEAN:       80.111
MEDIAN:     68
MODE:       NO MODE
STD. DEV.:  87.141
mscherger@lovelace:OS-threadfun2$
```

---

## Token Identifier (20 points)
Write a program that accepts an unspecifed number of tokens (strings of characters) of unspecifed length on the command line. The main() function in this program will create four threads each running separate thread functions (uppercase, lowercase, number, and other). The threads should take turns printing their respective tokens supplied on the command line. The uppercase thread should print all tokens that start with an uppercase letter. The lowercase thread should print all tokens that start with a lowercase letter. The number thread should print out all tokens that are positive or negative integers. The other thread should print out other remaining tokens. Note that the main thread will output nothing - the output will be performed by the threads that `main()` creates. The output order of tokens/words must be the same as the input order on the command line.Your program should work for any phrase of any reasonable length, not just the one given in the example. Here is an example:
```text
mscherger@lovelace:OS-threadfun2$ ./tokenid TCU Mens basketball overall standings is (18) wins !and! 9 losses. 42 - -42 = +84 -34a
UPPER:  TCU
UPPER:  Mens
LOWER:  basketball
LOWER:  overall
LOWER:  standings
LOWER:  is
PUNCT:  (18)
LOWER:  wins
PUNCT:  !and!
NUMBER: 9
LOWER:  losses.
NUMBER: 42
OTHER:  -
NUMBER: -42
OTHER:  =
NUMBER: +84
OTHER: -34a
mscherger@lovelace:OS-threadfun2$
```
Note: I will not test your program with apostrophes, but (double) quoted strings will be tested.

Note: For this problem you are *not permitted* to use synchronization primitives such as mutexes or semaphores for thread coordination. You can use `sched_yield()` to relinquish control of the CPU. 

The name of your program must be `tokenid.c` or `.cpp`.

---

## Sudoku Solution Validator (20 points)
A sudoku puzzle uses a 9 x 9 grid in which each column and row , as well as eah of the nine 3 x 3 subgrids, must contain all the digits 1..9.  You will write a multithreaded program that determines whether the solution to a sudoku puzzle is valid.

For this program, your solution must include:
+ Nine separate threads and each thread will check one column that it contains the digits 1..9.
+ Nine separate threads and each thread will check one row that it contains the digits 1..9.
+ Nine separate threads and each thread will check one 3 x 3 subgrid that it contains the digits 1..9.

### Passing Parameters to Each Thread
The parent thread will create the worker threads, passing each worker the location that it must check in the sudoku grid.  This step will require passing several parameters to each thread.  The easiest approach is to create a data structure using a `struct`.  For ecample, a structure to pass the row and column where the thread must begin validating would appear as follows:
```c
// structure for passing data to threads
typedef struct{
    int row;
    int col;
} Parameters;

// variable declarations
Parameters *data;

// allocate storage for data and assign sudoku block 5 to row and column.
data = (Parameters *) malloc(sizeof(Parameters));
data->row = 3;
data->col = 3;
```  

### Returning Results Back to the Parent Thread
Each worker thread is assigned the task of determining the validity of a particular region of the sudoku puzzle.  Once a worker has performed this check, it must pass its results back to the parent.  One good way to handle this is to create an array of boolean values that is visible to each thread (i.e. a global variable).  The ith index in this array corresponds to the ith worker thread.  Each worker thread would set the ith position in the array to true or false.  When all worker threads have completed, the parent thread checks each entry in the result array to determine if the sudoku puzzle is valid.

### Program Input and Output
A single sudoku puzzle will be stored in a file; nine separate integers, one space apart, for nine lines.  Here is an example:
```text
6 2 4 5 3 9 1 8 7
5 1 9 7 2 8 6 3 4
8 3 7 6 1 4 2 9 5
1 4 3 8 6 5 7 2 9
9 5 8 2 4 7 3 6 1
7 6 2 3 9 1 4 5 8
3 7 1 9 5 6 8 4 2
4 9 6 1 8 2 5 7 3
2 8 5 4 7 3 9 1 6
```
The output will be the string "FALSE" or "TRUE".  Here is an example:

```text
mscherger@lovelace:OS-threadfun2$ ./sudokuvalidator one.txt
TRUE
mscherger@lovelace:OS-threadfun2$
```

The name of your program must be `sudokuvalidator.c` or `.cpp`.

---

## Makefile (10 points)
Develop a Makefile that is capable of building all four of your programs with just a single `make` command.  Also include a `clean` target to remove all executables and object files.

---

## Documentation (10 points)
Make sure each of your programs are well documented.  Follow the documentation standard as posted on TCU Online.

---

## Other
+ This is an individual project.
+ Your programs will be compared with each other using MOSS.
+ You will have to create your own test data.
+ I will test your programs on `lovelace.cs.tcu.edu`.
+ This project is worth 100 points.
+ Be sure to update your git repo regularly!!!  No excuses.