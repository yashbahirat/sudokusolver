#include <stdio.h>
#include <stdbool.h>

// Define constants for the Sudoku grid
#define GRID_SIZE 9

// Function to print the Sudoku grid
void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    printf("\n  Sudoku Grid:\n");
    printf("  -------------------------------\n");
    for (int row = 0; row < GRID_SIZE; row++) {
        printf("%d |", row + 1);
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0)
                printf(" . ");
            else
                printf(" %d ", grid[row][col]);
            if ((col + 1) % 3 == 0 && col < GRID_SIZE - 1)
                printf("|");
        }
        printf("|\n");
        if ((row + 1) % 3 == 0 && row < GRID_SIZE - 1)
            printf("  |---------+---------+---------|\n");
    }
    printf("  -------------------------------\n");
    printf("    1  2  3   4  5  6   7  8  9  (Column)\n");
}

// Function to check if a number can be placed in the given position
bool isSafe(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    for (int x = 0; x < GRID_SIZE; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    bool isEmpty = false;
    for (row = 0; row < GRID_SIZE; row++) {
        for (col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
            break;
    }

    if (!isEmpty)
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

// Function to read grid from input
void readGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    printf("Enter the Sudoku grid (9 rows, 9 numbers per row, use 0 for empty cells):\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int value;
            scanf("%d", &value);
            if (value < 0 || value > 9) {
                printf("Invalid value %d at (%d, %d). Using 0 instead.\n", value, i + 1, j + 1);
                value = 0;
            }
            grid[i][j] = value;
        }
    }
}

int main() {
    int grid[GRID_SIZE][GRID_SIZE] = {0};
    char command;

    printf("Sudoku Solver\n");
    printf("Choose mode:\n");
    printf("  1 : Enter grid and solve immediately\n");
    printf("  2 : Interactive mode (commands: i, s, c, q)\n");
    printf("Enter choice (1 or 2): ");
    scanf(" %c", &command);

    if (command == '1') {
        char again;
        do {
            readGrid(grid);
            printGrid(grid);
            if (solveSudoku(grid)) {
                printf("Puzzle solved!\n");
                printGrid(grid);
            } else {
                printf("No solution exists!\n");
            }

            printf("Solve another puzzle? (y/n): ");
            scanf(" %c", &again);
        } while (again == 'y' || again == 'Y');
    } else if (command == '2') {
        printf("Commands:\n");
        printf("  i <row> <col> <value> : Insert value (1-9) at row, col (1-9)\n");
        printf("  s : Solve the puzzle\n");
        printf("  c : Clear the grid\n");
        printf("  q : Quit\n");

        while (1) {
            printGrid(grid);
            printf("Enter command (i/s/c/q): ");
            scanf(" %c", &command);

            if (command == 'q') {
                printf("Exiting...\n");
                break;
            } else if (command == 'i') {
                int row, col, value;
                printf("Enter row (1-9), col (1-9), value (0-9): ");
                scanf("%d %d %d", &row, &col, &value);
                if (row < 1 || row > 9 || col < 1 || col > 9 || value < 0 || value > 9) {
                    printf("Invalid input! Row and col must be 1-9, value 0-9.\n");
                } else {
                    row--; col--;
                    if (value == 0 || isSafe(grid, row, col, value)) {
                        grid[row][col] = value;
                    } else {
                        printf("Cannot place %d at (%d, %d). Invalid move!\n", value, row + 1, col + 1);
                    }
                }
            } else if (command == 's') {
                int tempGrid[GRID_SIZE][GRID_SIZE];
                for (int i = 0; i < GRID_SIZE; i++)
                    for (int j = 0; j < GRID_SIZE; j++)
                        tempGrid[i][j] = grid[i][j];
                if (solveSudoku(tempGrid)) {
                    for (int i = 0; i < GRID_SIZE; i++)
                        for (int j = 0; j < GRID_SIZE; j++)
                            grid[i][j] = tempGrid[i][j];
                    printf("Puzzle solved!\n");
                } else {
                    printf("No solution exists!\n");
                }
            } else if (command == 'c') {
                for (int i = 0; i < GRID_SIZE; i++)
                    for (int j = 0; j < GRID_SIZE; j++)
                        grid[i][j] = 0;
                printf("Grid cleared.\n");
            } else {
                printf("Invalid command! Use i, s, c, or q.\n");
            }
        }
    } else {
        printf("Invalid choice! Exiting...\n");
    }

    return 0;
}
