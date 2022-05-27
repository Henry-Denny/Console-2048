#include "Grid.h"

static int GetRandomCell(int grid[ROWS][COLS])
{
    int numFreeCells = 0;
    int freeTiles[ROWS * COLS];
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            if (grid[row][col] == 0)
            {
                freeTiles[numFreeCells] = (row * COLS) + col;
                ++numFreeCells;
            }
        }
    }
    if (numFreeCells == 0) return -1;

    int randIndex = rand() % numFreeCells;
    return freeTiles[randIndex];
}

static bool MergeRow(int *row[COLS])
{
    bool moved = false;
    bool merged = false;
    for (int col = 1; col < COLS; ++col)
    {
        if (*row[col])
        {
            bool cellMoved = MoveCell(col, row, &merged);
            moved = cellMoved || moved;
        }
    }

    return moved;
}

static bool MoveCell(int col, int *rows[COLS], bool *merged)
{
    int left = 0;
    while(CanMove(col, left+1, rows, *merged) && (left == 0 || *rows[col - left] != *rows[col]))
    {
        left++;
    }

    // The cell was moved
    if (left)
    {
        if (*rows[col - left] == *rows[col])
        {
            // The cells are matching
            *merged = true;
            (*rows[col - left])++;
        }
        else
        {
            // Moving to a zero cell
            *merged = false;
            (*rows[col - left]) = *rows[col];
        }
        
        *rows[col] = 0;
        return true;
    }

    // The cell wasn't moved
    *merged = false;
    return false;
}

static bool CanMove(int col, int spaces, int *row[COLS], bool merged)
{
    if (col - spaces < 0) return false;
    else
    {
        return (*row[col - spaces] == 0 || ((*row[col - spaces] == *row[col]) && !merged));
    }
}

void InitialiseGrid(int grid[ROWS][COLS])
{
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            grid[row][col] = 0;
        }
    }
}

bool MoveCells(int grid[ROWS][COLS], Direction dir)
{
    // Create aligned grid
    int *alignGrid[ROWS][COLS];

    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            switch (dir)
            {
                case UP:
                    alignGrid[row][col] = &grid[col][row];
                    break;
                case DOWN:
                    alignGrid[row][col] = &grid[COLS - col - 1][row];
                    break;
                case LEFT:
                    alignGrid[row][col] = &grid[row][col];
                    break;
                case RIGHT:
                    alignGrid[row][col] = &grid[row][COLS - col - 1];
                    break;
            }
        }
    }

    // Merge cells
    bool moved = false;
    for (int row = 0; row < ROWS; ++row)
    {
        if (MergeRow(alignGrid[row])) moved = true;
    }

    return moved;
}

void SpawnCell(int grid[ROWS][COLS], int rank)
{
    int cellID = GetRandomCell(grid);
    int row = cellID / COLS;
    int col = cellID % COLS;
    
    grid[row][col] = rank;
}

void PrintGridBasic(int grid[ROWS][COLS])
{
    system("cls");
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            printf("%i", grid[row][col]);
        }
        printf("\n");
    }
}

void PrintGrid(int grid[ROWS][COLS], char _squares[NUM_SQUARES][SQUARE_HEIGHT][SQUARE_WIDTH], char _colours[NUM_SQUARES][COLOR_BUFFER])
{
    for (int row = 0; row < ROWS; ++row)
    {
        char lines[SQUARE_HEIGHT][SQUARE_WIDTH * COLS + COLS * (2 * COLOR_BUFFER)] = {};
        for (int col = 0; col < COLS; ++col)
        {
            int rank = grid[row][col];
            char colour[COLOR_BUFFER];
            strcpy(colour, _colours[rank]);
            for (int i = 0; i < SQUARE_HEIGHT; ++i)
            {
                strcat(lines[i], colour);
                strcat(lines[i], _squares[rank][i]);
                strcat(lines[i], CLEAR);
            }
        }
        for (int i = 0; i < SQUARE_HEIGHT; ++i)
        {
            printf(lines[i]);
            printf("\n");
        }
    }
    printf("\n");
}

bool HasLost(int grid[ROWS][COLS])
{
    return false;
}