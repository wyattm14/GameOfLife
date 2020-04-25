//https://www.youtube.com/watch?v=fwYlzznrId4
//https://www.cplusplus.com/reference/cstdlib/rand/
//Assignment 1

#include "Board.h"

//default constructor
Board::Board()
{
    height = 5;

    width = 5;

//classic
    boardArray = new bool*[height];
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            boardArray[i] = new bool [width];
        }
    }

//new
    //     boardArray = new bool*[width];
    // for (int i = 0; i < height; ++i)
    // {
    //     for (int j = 0; j < width; ++j)
    //     {
    //         boardArray[i] = new bool [height];
    //     }
    // }

    //initialize array
//classic
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
           *(*(boardArray+i)+j) = false;//random cells
        }
        cout << endl;
    }

//new
    // for (int i = 0; i < width; ++i)
    // {
    //     for (int j = 0; j < height; ++j)
    //     {
    //         boardArray[j][i] = false;//random cells
    //     }
    //     cout << endl;
    // }

}

Board::Board(int xSizeInput, int ySizeInput)
{



    width = xSizeInput;

    height = ySizeInput;

    boardArray = new bool*[height];
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            boardArray[i] = new bool [width];
            deblog("success");
        }
    }

    //initialize array

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
           //*(*(boardArray+i)+j) = false;//random cells
           boardArray[j][i] = false;
        }
        cout << endl;
    }

}

Board::~Board()
{

}


void Board::printBoard()
    {
        deblog("Starting outer loop");
        for (int y = 0; y < height; ++y)
        {
            //deblog("Starting inner loop");
            for (int x = 0; x < width; ++x)
            {

                 if (isCellAlive(x, y))
                {
                    cout << "X";
                } else cout << "-";
             }
            cout << endl;
        }

        cout << endl;

    }

    bool Board::isCellAlive(int xPosition, int yPosition)
    {
        return boardArray[yPosition][xPosition];
    }

    void Board::setCellState(int xPosition, int yPosition, bool isAlive)
    {
        boardArray[yPosition][xPosition] = isAlive;
    }

    bool Board::isInBounds(int xPosition, int yPosition)
    {
        if ((xPosition < 0) || (yPosition < 0))
            return false;
        else if((xPosition >= width) || (yPosition >= height))
            return false;
        else
            return true;
    }

    bool  Board::IsBoardEmpty()
{
     for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j <width; ++j)
        {
           if (boardArray[i][j] == true)
           {
               return false;
           }
        }
    }

    return true;
}

string Board::GetBoardAsString()
{

    string boardValues = "";

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            if (boardArray[y][x])
            {
                boardValues += "X";
            }
            else
            {
                boardValues += "-";
            }

        }
        boardValues += '\n';
    }
    for(int y = 0; y < height; ++y)
    {
        boardValues += '\n';
    }

    return boardValues;
}
