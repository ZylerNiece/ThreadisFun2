//*********************************************************
// Zyler Niece
// Operating Systems
// Programming with Ptheads: Sudoku Solution Validator
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
#include <stdbool.h>
#include <pthread.h>

#define GRID_SIZE 9
#define SUBGRID_SIZE 3

//*********************************************************
//
// Extern Declarations
//
//*********************************************************

typedef struct {
    int row;
    int col;
} Parameters;

int grid[GRID_SIZE][GRID_SIZE];
bool row_valid[GRID_SIZE];
bool col_valid[GRID_SIZE];
bool subgrid_valid[GRID_SIZE];

//*********************************************************
//
// Function Prototypes
//
//*********************************************************

//***************************************************************************
//
// Validate Row Function
//
// This function receives a pointer to a Parameters structure and validates
// a row of a Sudoku grid. It checks whether each number from 1 to GRID_SIZE
// appears exactly once in the row. If a number appears more than once,
// the row is marked as invalid in the row_valid array.
//
// Function Parameters
// -------------------
// param void pointer A pointer to a Parameters structure containing
// the row index of the row to validate.
//
// Local Variables
// ---------------
// data Parameters* A pointer to the Parameters structure passed in
// row int The index of the row to validate
// num_appearances int[] An array that tracks the number of appearances
// of each number in the row.
// num int The number currently being validated in the row.
// i int Loop iteration variable
//
// Global Variables
// ----------------
// grid int[][] The Sudoku grid to validate.
// row_valid bool[] An array that tracks the validity of each row in the grid.
// GRID_SIZE int The size of the Sudoku grid.
//
//***************************************************************************

//***************************************************************************
//
// Validate Column Function
//
// This function receives a pointer to a Parameters structure and validates
// a column of a Sudoku grid. It checks whether each number from 1 to GRID_SIZE
// appears exactly once in the column. If a number appears more than once,
// the column is marked as invalid in the col_valid array.
//
// Function Parameters
// -------------------
// param void pointer A pointer to a Parameters structure containing
// the column index of the column to validate.
//
// Local Variables
// ---------------
// data Parameters* A pointer to the Parameters structure passed in.
// col int The index of the column to validate.
// num_appearances int[] An array that tracks the number of appearances
// of each number in the column.
// num int The number currently being validated in the column.
// i int Loop iteration variable.
//
// Global Variables
// ----------------
// grid int[][] The Sudoku grid to validate.
// col_valid bool[] An array that tracks the validity of each column in the grid.
// GRID_SIZE int The size of the Sudoku grid.
//
//***************************************************************************

//***************************************************************************
//
// Validate Subgrid Function
//
// This function receives a pointer to a Parameters structure and validates
// a subgrid of a Sudoku grid. It checks whether each number from 1 to GRID_SIZE
// appears exactly once in the subgrid. If a number appears more than once,
// the subgrid is marked as invalid in the subgrid_valid array.
//
// Function Parameters
// -------------------
// param void pointer A pointer to a Parameters structure containing
// the row and column index of the top-left corner of the subgrid to validate.
//
// Local Variables
// ---------------
// data Parameters* A pointer to the Parameters structure passed in.
// row int The row index of the top-left corner of the subgrid to validate.
// col int The column index of the top-left corner of the subgrid to validate.
// num_appearances int[] An array that tracks the number of appearances
// of each number in the subgrid.
// num int The number currently being validated in the subgrid.
// i int Loop iteration variable for rows.
// j int Loop iteration variable for columns.
//
// Global Variables
// ----------------
// grid int[][] The Sudoku grid to validate.
// subgrid_valid bool[] An array that tracks the validity of each subgrid in the grid.
// GRID_SIZE int The size of the Sudoku grid.
// SUBGRID_SIZE int The size of each subgrid.
//
//***************************************************************************

//***************************************************************************
//
// Read Input Function
//
// This function reads the Sudoku grid from a file specified by the input
// filename argument. The file should contain a 9x9 grid of integers separated
// by whitespace. The function returns 0 if the input file is read successfully,
// or 1 if an error occurs.
//
// Function Parameters
// -------------------
// filename const char* The name of the input file to read.
//
// Local Variables
// ---------------
// fp FILE* A file pointer to the input file.
// i int Loop iteration variable for row index
// j int Loop iteration variable for column index
//
// Global Variables
// ----------------
// grid int[][] The Sudoku grid to read into.
// GRID_SIZE int The size of the Sudoku grid.
//
//***************************************************************************

//***************************************************************************
//
// Initialize Validation Arrays Function
//
// This function initializes the row_valid, col_valid, and subgrid_valid arrays
// to false. These arrays are used to track the validity of each row, column,
// and subgrid in the Sudoku grid.
//
// Function Parameters
// -------------------
// None
//
// Local Variables
// ---------------
// i int Loop iteration variable
//
// Global Variables
// ----------------
// row_valid bool[] An array that tracks the validity of each row in the grid.
// col_valid bool[] An array that tracks the validity of each column in the grid.
// subgrid_valid bool[] An array that tracks the validity of each subgrid in the grid.
// GRID_SIZE int The size of the Sudoku grid.
// SUBGRID_SIZE int The size of each subgrid in the Sudoku grid.
//
//***************************************************************************

//***************************************************************************
//
// Create Threads Function
//
// This function creates and launches multiple threads to validate the rows,
// columns, and subgrids of a Sudoku grid. It uses the validate_row(),
// validate_col(), and validate_subgrid() functions to validate each
// individual row, column, and subgrid, respectively. It also waits for all
// threads to complete before returning.
//
// Function Parameters
// -------------------
// None
//
// Local Variables
// ---------------
// threads pthread_t[] An array of thread identifiers to be created
// thread_count int A counter to keep track of the number of threads created
// data Parameters* A pointer to a Parameters structure containing the row
// and column indices of the current thread
// i int Loop iteration variable for validating rows and subgrids
// j int Loop iteration variable for validating columns and subgrids
//
// Global Variables
// ----------------
// grid int[][] The Sudoku grid to validate.
// row_valid bool[] An array that tracks the validity of each row in the grid.
// GRID_SIZE int The size of the Sudoku grid.
// SUBGRID_SIZE int The size of each subgrid in the Sudoku grid.
//
//***************************************************************************

//****************************************************************************
//
// Is Sudoku Valid Function
//
// This function checks whether the Sudoku grid is valid by checking if all
// rows, columns, and sub-grids contain all numbers from 1 to GRID_SIZE exactly
// once.
//
// Function Parameters
// -------------------
// None
//
// Local Variables
// ---------------
// is_valid bool A boolean flag to indicate whether the Sudoku grid is valid.
// i int Loop iteration variable
//
// Global Variables
// ----------------
// row_valid bool[] An array that tracks the validity of each row in the grid.
// col_valid bool[] An array that tracks the validity of each column in the grid.
// subgrid_valid bool[] An array that tracks the validity of each sub-grid in the grid.
// GRID_SIZE int The size of the Sudoku grid.
//
//***************************************************************************

void *validate_row(void *param) {
    Parameters *data = (Parameters *)param;
    int row = data->row;

    // Initialize array for tracking number appearances
    int num_appearances[GRID_SIZE] = {0};

    // Iterate over row, updating num_appearances array
    for (int i = 0; i < GRID_SIZE; i++) {
        int num = grid[row][i];
        if (num_appearances[num-1] > 0) {
            row_valid[row] = false;
            pthread_exit(NULL);
        } else {
            num_appearances[num-1]++;
        }
    }

    // If we get here, the row is valid
    row_valid[row] = true;
    pthread_exit(NULL);
}

void *validate_col(void *param) {
    Parameters *data = (Parameters *)param;
    int col = data->col;

    // Initialize array for tracking number appearances
    int num_appearances[GRID_SIZE] = {0};

    // Iterate over column, updating num_appearances array
    for (int i = 0; i < GRID_SIZE; i++) {
        int num = grid[i][col];
        if (num_appearances[num-1] > 0) {
            col_valid[col] = false;
            pthread_exit(NULL);
        } else {
            num_appearances[num-1]++;
        }
    }

    // If we get here, the column is valid
    col_valid[col] = true;
    pthread_exit(NULL);
}

void *validate_subgrid(void *param) {
    Parameters *data = (Parameters *)param;
    int row = data->row;
    int col = data->col;

    // Initialize array for tracking number appearances
    int num_appearances[GRID_SIZE] = {0};

    // Iterate over subgrid, updating num_appearances array
    for (int i = row; i < row + SUBGRID_SIZE; i++) {
        for (int j = col; j < col + SUBGRID_SIZE; j++) {
            int num = grid[i][j];
            if (num_appearances[num-1] > 0) {
                subgrid_valid[row/SUBGRID_SIZE*SUBGRID_SIZE + col/SUBGRID_SIZE] = false;
                pthread_exit(NULL);
            } else {
                num_appearances[num-1]++;
            }
        }
    }

    // If we get here, the subgrid is valid
    subgrid_valid[row/SUBGRID_SIZE*SUBGRID_SIZE + col/SUBGRID_SIZE] = true;
    pthread_exit(NULL);
}

int read_input(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return 1;
    }

    // Read the Sudoku grid from the file
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (fscanf(fp, "%d", &grid[i][j]) != 1) {
                fprintf(stderr, "Invalid input file format\n");
                return 1;
            }
        }
    }

    fclose(fp);
    return 0;
}

void init_validation_arrays() {
    // Initialize validation arrays
    for (int i = 0; i < GRID_SIZE; i++) {
        row_valid[i] = false;
        col_valid[i] = false;
        subgrid_valid[i] = false;
    }
}

void create_threads() {
    pthread_t threads[GRID_SIZE * 3];
    int thread_count = 0;

    // Validate rows
    for (int i = 0; i < GRID_SIZE; i++) {
        Parameters *data = (Parameters *)malloc(sizeof(Parameters));
        data->row = i;
        data->col = 0;
        pthread_create(&threads[thread_count++], NULL, validate_row, data);
    }

    // Validate columns
    for (int j = 0; j < GRID_SIZE; j++) {
        Parameters *data = (Parameters *)malloc(sizeof(Parameters));
        data->row = 0;
        data->col = j;
        pthread_create(&threads[thread_count++], NULL, validate_col, data);
    }

    // Validate subgrids
    for (int i = 0; i < GRID_SIZE; i += SUBGRID_SIZE) {
        for (int j = 0; j < GRID_SIZE; j += SUBGRID_SIZE) {
            Parameters *data = (Parameters *)malloc(sizeof(Parameters));
            data->row = i;
            data->col = j;
            pthread_create(&threads[thread_count++], NULL, validate_subgrid, data);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
}

bool is_sudoku_valid() {
    bool is_valid = true;
    for (int i = 0; i < GRID_SIZE; i++) {
        if (!row_valid[i] || !col_valid[i] || !subgrid_valid[i]) {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

//*********************************************************
//
// Main Function
//
//*********************************************************

int main(int argc, char *argv[]) {
    //Check to make sure there is only one argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    //Read Input File
    if (read_input(argv[1]) != 0) {
        return 1;
    }

    //Initialize arrays used for validation
    init_validation_arrays();

    //Create Threads to validate the sudoku
    create_threads();

    //Check if sudoku is valid or not and print results
    if (is_sudoku_valid()) {
        printf("TRUE\n");
    } else {
        printf("FALSE\n");
    }

    return 0;
}