#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

//As per Christopher Chang
#ifdef DEBUG
#define deblog(msg) cout << msg << endl
#else
#define deblog(msg) ;
#endif
//As per Christopher Chang

class Board 
{
    public:
        Board(); //default constructor
        Board(int xSize, int ySize); //overloaded constructor
        ~Board(); //destructor
        //functions
        //bool updateBoard();   //updatesBoard to next configuration. Returns true if board was static

        //helper functions
        void printBoard();

        bool isCellAlive(int, int);

        void setCellState(int, int, bool);

        bool isInBounds(int, int);

        bool IsBoardEmpty();

        string GetBoardAsString();

        int height;

        int width;

        bool **boardArray; // boardArray[1][2]
};