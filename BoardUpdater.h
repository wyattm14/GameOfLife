#include "Board.cpp"
using namespace std;

class BoardUpdater
{
    public:
        BoardUpdater(); //default constructor
        ~BoardUpdater(); //destructor

        void UpdateBoard(Board&, int);
        void RandomizeBoard(Board&, double);
        void CopyBoard(Board&, Board&);
        bool AreBoardsSame(Board&, Board&);
        bool DoesCellLive(int, bool);
        void WaitForEnter();
};