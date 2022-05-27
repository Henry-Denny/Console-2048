#ifndef GRID_H
#define GRID_H

#define ROWS 4
#define COLS 4

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "Tiles.h"

typedef enum Direction Direction;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

static int GetRandomCell(int grid[ROWS][COLS]);
static bool MergeRow(int *row[COLS]);
static bool CanMove(int col, int spaces, int *row[COLS], bool merged);
static bool MoveCell(int col, int *rows[COLS], bool *merged);
void InitialiseGrid(int grid[ROWS][COLS]);
bool MoveCells(int grid[ROWS][COLS], Direction dir);
void SpawnCell(int grid[ROWS][COLS], int rank);
void PrintGridBasic(int grid[ROWS][COLS]);
void PrintGrid(int grid[ROWS][COLS], char _squares[NUM_SQUARES][SQUARE_HEIGHT][SQUARE_WIDTH], char _colours[NUM_SQUARES][COLOR_BUFFER]);
bool HasLost(int grid[ROWS][COLS]);


#endif