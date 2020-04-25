#include "BoardUpdater.cpp"

using namespace std;

class ReadFile{
public:
  ReadFile();
  //overloaded
  ReadFile(int);
  ~ReadFile();

  //functions
  void option();
  void argRead(int argc, char** argv);


  //variables using
  string file = "";
  fstream f;
  bool boardPiece = false;
  string width = "";
  string length = "";
  int number = 0;


};
