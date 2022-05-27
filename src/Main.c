#include <stdio.h>
#include <stdbool.h>

#include "Colours.h"
#include "Menu.h"
#include "Grid.h"
#include "Keys.h"
#include "Tiles.h"

void PlayGame();
void PrintTitle();

int main()
{
    Menu *mainMenu = CreateMenu
    (
        RED
        " .d8888b.   .d8888b.      d8888   .d8888b.  \n"
        "d88P  Y88b d88P  Y88b    d8P888  d88P  Y88b \n"
        "       888 888    888   d8P 888  Y88b. d88P \n"
        "     .d88P 888    888  d8P  888   \"Y88888\"  \n"
        " .od888P\"  888    888 d88   888  .d8P\"\"Y8b. \n"
        "d88P\"      888    888 8888888888 888    888 \n"
        "888\"       Y88b  d88P       888  Y88b  d88P \n"
        "888888888   \"Y8888P\"        888   \"Y8888P\"  \n"
        CLEAR,
        1,
        "New Game"
    );
    LinkFunction(mainMenu, PlayGame, 1);

    RunMenu(mainMenu);
    DeleteMenu(mainMenu);

    
    return 0;
}

void PlayGame()
{
    srand(1);
    int grid[ROWS][COLS];
    InitialiseGrid(grid);

    SpawnCell(grid, 1);
    SpawnCell(grid, 1);

    bool done = false;
    while(!done)
    {
        system("cls");
        PrintTitle();
        PrintGrid(grid, squareTexts, squareCols);
        int ch = getch();
        switch(ch)
        {
            case KEY_UP:
                if (MoveCells(grid, UP)) SpawnCell(grid, 1);
                break;
            case KEY_DOWN:
                if (MoveCells(grid, DOWN)) SpawnCell(grid, 1);
                break;
            case KEY_RIGHT:
                if (MoveCells(grid, RIGHT)) SpawnCell(grid, 1);
                break;
            case KEY_LEFT:
                if (MoveCells(grid, LEFT)) SpawnCell(grid, 1);
                break;
            case KEY_Q:
                done = true;
                break;
            default:
                // printf("%i", ch);
                break;
            
            if (HasLost(grid))      // TODO
            {
                done = true;
            }
        }
    }
}

void PrintTitle()
{
    printf
    (
        YELLOW
        "\t\t .d8888b.   .d8888b.      d8888   .d8888b.  \n"
        "\t\td88P  Y88b d88P  Y88b    d8P888  d88P  Y88b \n"
        "\t\t       888 888    888   d8P 888  Y88b. d88P \n"
        "\t\t     .d88P 888    888  d8P  888   \"Y88888\"  \n"
        "\t\t .od888P\"  888    888 d88   888  .d8P\"\"Y8b. \n"
        "\t\td88P\"      888    888 8888888888 888    888 \n"
        "\t\t888\"       Y88b  d88P       888  Y88b  d88P \n"
        "\t\t888888888   \"Y8888P\"        888   \"Y8888P\"  \n\n"
        CLEAR
    );
}