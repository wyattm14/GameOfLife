#include "ReadFile.h"

using namespace std;

string file ="";
//default
ReadFile::ReadFile(){
  string width = "";
  string length = "";
  string file = "";
  fstream f;
  bool boardPiece = false;

}
//overloaded
ReadFile::ReadFile(int d){
  string file = "";
  fstream f;
  bool boardPiece = false;

}

ReadFile::~ReadFile(){
  //dont know what to put yet
}
// void ReadFile::option(string path){
//   cout<<"help"<<endl;
//   cout<< "Please choose an option ('1' or '2'): "<< endl;
//   cout << "1) To enter a file path "<<endl;
//   cout << "2) For a random configuration"<<endl;
//   cin >> number;
//   // getline (cin, number);
//   if (number == 1){
//     cout<< argv[0] << endl;
//     FILE* file;
//     std::string fileName(argv[0]);
//     file = fopen( fileName.c_str(), "rb" );
//     cout<<"the above code was ran"<<endl;
//
//     if( file != NULL )
//     cout <<"the file could not be opened"<<endl;
//       std::cout << fileName << std::endl;
//   }
//   else if (number == 2){
//     cout << "this is where lucas enters the random generation code"<< endl;
//   }
//
// }

void ReadFile::argRead(int argc, char** argv){
  cout<<"poopie"<<endl;
  string str;
  file = argv [2];
  f.open(file);

  if (! f.is_open()){
    cout<<"The file could not be opened"<<endl;
  }
  ifstream fin (argv[2]);
  // bool grid [length*width];

  for (int i = 0; i <= 2; i++){
    getline(f,str);
    if (i = 1){
      str = width;
      cout<<"print something please"<<endl;
    }
    if (i=2){
      str = length;
      cout <<length<<endl;
    }
  }
}
