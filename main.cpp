// #include "Board.cpp"
// http://www.cplusplus.com/forum/beginner/106204/
//https://www.techiedelight.com/convert-string-to-int-cpp/
// https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
#include <chrono>
#include <thread>
#include "ReadFile.cpp"

using namespace std;

int main(int argc, char **argv)

{
  //initializing variabkes

    string path = "";
    int number = 0;
    fstream f;
    string lengthString;
    string widthString;
    int length = 0;
    int width = 0;
    string line = "";
    char grid[length][width];
    int xcount = -1;
    int ycount = -1;
    int randlength = 0;
    int randwidth = 0;
    double percentageAlive = 0.0;
    int mode = 0;
    int iterations = 0;
    int txtfile = 0;
    string outputfile = "";
    int outputMode = 0;
    char ch = '\0';


    //initial option
    cout<< "Please choose an option ('1' or '2'): "<< endl;
    cout << "1) To enter a file path "<<endl;
    cout << "2) For a random configuration"<<endl;
    cin >> number;

    //text file FUNCTIONALITY
    if (number == 1){
      cout << "Please specify the .txt file you would like to run: "<<endl;
      cin >> path;
      cout << "this is the path: "<< path << endl;
      //opening the file
      f.open(path);
      if (!f.is_open()){
        cout<<"the file could not be opened: "<<endl;
        return 0;
      }
      //getting the board width and length
      for (int i = 0; i<=2; ++i){
        if (i == 1){
          getline(f, widthString);
          width = std::stoi(widthString);
          // cout <<"Width: "<< width<<endl;
        }
        else if (i == 2){
          getline(f, lengthString);
          length = std::stoi(lengthString);
          // cout <<"Length: "<<length<< endl;
        }
      }
      //creating the boards of width and length
      Board *myBoard = new Board(width, length);
      Board *prevBoard = new Board(width, length);
      BoardUpdater *myBoardUpdater = new BoardUpdater();


      //creating the board
      for (int i =0; i<length ; ++i){
        getline(f,line);
        // cout<<line<<endl;
        int index = 0;
        xcount += 1;
        ycount = -1;
        // cout << "xcount is:"<< xcount << endl;
        //https://stackoverflow.com/questions/1315041/how-can-i-iterate-through-a-string-and-also-know-the-index-current-position
        for (auto it = line.begin() ; it < line.end(); ++it, ++index){
          ycount += 1;
          // cout << index << ": "<<*it<< endl;
          if (*it == 'X'){
            myBoard->setCellState(ycount, xcount, 1);
          }
          else if (*it == '.'){
            myBoard->setCellState(ycount, xcount, 0);
          }
        }
      }
      cout<<"Here is the original text file board "<< endl;
      myBoard->printBoard();

      f.close();


      //getting the game mode

      cout << "Which mode would you like to play? (1,2,3)"<< endl;
      cout << "0) Classic Mode "<< endl;
      cout << "1) Mirror Mode "<< endl;
      cout << "2) Donut Mode "<< endl;
      cin >> mode;
      // myBoardUpdater -> UpdateBoard (*myBoard, mode);
      if (mode>2){
        cout << "That is not an option, please restart!! "<< endl;
        return 1;
      }
      //seeing what they would like to do
      cout << "Would you like to: "<< endl;
      cout << "1) Output to a .txt file "<< endl;
      cout << "2) Output to the terminal "<< endl;
      cout << "3) Press the ENTER key for each iteration "<< endl;
      cin >> outputMode;


      //txt file FUNCTIONALITY
      if (outputMode == 1)
      {


        cout << "Please name the file you would like to output to (German.txt)"<<endl;
        cin>>outputfile;
        //cout << ".txt"<< endl;
        cout << "How many max iterations would you like"<< endl;
        cin>> iterations;

        ofstream outputFile(outputfile);
        string toAppendToFile = "";

        //main FUNCTIONALITY

        for (int i = 0; i <= iterations; ++i)
        {
          //copying board for repeated state check
          myBoardUpdater -> CopyBoard(*myBoard, *prevBoard);

          toAppendToFile += myBoard->GetBoardAsString();
          myBoardUpdater -> UpdateBoard(*myBoard, mode);

          if (myBoardUpdater -> AreBoardsSame(*prevBoard, *myBoard)){
            // cout << "THIS IS PREV BOARD WHEN STATIC"<<endl;
            prevBoard->printBoard();
            cout<<"The state is static"<<endl;
            break;
          }
          //checking if empty
          if (myBoard->IsBoardEmpty())
          {
            toAppendToFile += myBoard->GetBoardAsString();
            cout<<"Board is empty"<<endl;
            break;
          }
        }

        outputFile << toAppendToFile;
        outputFile.close();

      }
      // outputting to the terminal
      else if (outputMode == 2)
      {
        cout << "How many max iterations would you like"<< endl;
        cin>> iterations;
        int count = 0;
        for (int i = 0; i < iterations; ++i){
          if (myBoard->IsBoardEmpty()){
            myBoard->printBoard();
            cout<<"Board is empty"<<endl;
            break;
          }
          myBoardUpdater -> CopyBoard(*myBoard, *prevBoard);

          std::this_thread::sleep_for(std::chrono::milliseconds(100));
          myBoardUpdater -> UpdateBoard (*myBoard, mode);
          cout << "This is the "<< i+1 << "'th iteration"<< endl;
          myBoard->printBoard();

          if (myBoardUpdater -> AreBoardsSame(*prevBoard, *myBoard)){
            // cout << "THIS IS PREV BOARD WHEN STATIC"<<endl;
            prevBoard->printBoard();
            cout<<"The state is static"<<endl;
            break;
          }
        }
      }
      //outputting from enter button
      else if (outputMode == 3)
      {
        // cout << "please press ENTER for the next generation"<< endl;
        for (int i = 0; i<=1000; ++i){



          myBoardUpdater -> CopyBoard(*myBoard, *prevBoard);
          myBoardUpdater -> UpdateBoard (*myBoard, mode);
          myBoard->printBoard();
          if (myBoardUpdater -> AreBoardsSame(*prevBoard, *myBoard)){
            // cout << "THIS IS PREV BOARD WHEN STATIC"<<endl;
            prevBoard->printBoard();
            cout<<"The state is static"<<endl;
            break;
          }
          if (myBoard->IsBoardEmpty())
          {
            cout<<"Board is empty"<<endl;
            break;
          }
          cout << "Please press ENTER for the next generation" << endl;
          cout << "If you want to exit the program, press the spacebar followed by ENTER" << endl;
          //checking for a spacebar 
          std::cin.get(ch);
          if (ch == ' '){
            break;
          }
        }
      }
     }


// if they would like to create a random board
    else if (number == 2){
      cout << "RANDOM BOARD"<< endl;
      cout << "What width do you want your board? "<< endl;
      cin >> randlength;
      cout << "What length do you want your board? "<< endl;
      cin >> randwidth;
      cout << "What percent of the cells would you like to be alive (1.0 - 0.0)"<<endl;
      cin >> percentageAlive;
      //creating the needed boards

      Board *myBoard = new Board(randlength, randwidth);
      Board *prevBoard = new Board(randlength, randwidth);

      BoardUpdater *myBoardUpdater = new BoardUpdater();
      myBoardUpdater -> RandomizeBoard(*myBoard, percentageAlive);
      myBoard -> printBoard();

      //getting the mode from user

      cout << "Which mode would you like to play? (1,2,3)"<< endl;
      cout << "0) Classic Mode "<< endl;
      cout << "1) Mirror Mode "<< endl;
      cout << "2) Donut Mode "<< endl;
      cin >> mode;
      // myBoardUpdater -> UpdateBoard (*myBoard, mode);
      if (mode>2){
        cout << "That is not an option, please restart!! "<< endl;
        return 1;
      }

      //seeing what they would like to do
      cout << "Would you like to: "<< endl;
      cout << "1) Output to a .txt file "<< endl;
      cout << "2) Output to the terminal "<< endl;
      cout << "3) Press the ENTER key for each iteration "<< endl;
      cin >> outputMode;

      // text file logic
      if (outputMode == 1)
      {


        cout << "Please name the file you would like to output to (German.txt)"<<endl;
        cin>>outputfile;
        //cout << ".txt"<< endl;
        cout << "How many max iterations would you like"<< endl;
        cin>> iterations;

        ofstream outputFile(outputfile);
        string toAppendToFile = "";

        for (int i = 0; i <= iterations; ++i)
        {

          myBoardUpdater -> CopyBoard(*myBoard, *prevBoard);

          toAppendToFile += myBoard->GetBoardAsString();
          myBoardUpdater -> UpdateBoard(*myBoard, mode);

          if (myBoardUpdater -> AreBoardsSame(*prevBoard, *myBoard)){
            // cout << "THIS IS PREV BOARD WHEN STATIC"<<endl;
            prevBoard->printBoard();
            cout<<"The state is static"<<endl;
            break;
          }

          if (myBoard->IsBoardEmpty())
          {
            toAppendToFile += myBoard->GetBoardAsString();
            cout<<"Board is empty"<<endl;
            break;
          }
        }

        outputFile << toAppendToFile;
        outputFile.close();

      }

      //output to terminal logic
      else if (outputMode == 2)
      {
        cout << "How many max iterations would you like"<< endl;
        cin>> iterations;
        int count = 0;
        for (int i = 0; i < iterations; ++i){
          if (myBoard->IsBoardEmpty()){
            myBoard->printBoard();
            cout<<"Board is empty"<<endl;
            break;
          }
          myBoardUpdater -> CopyBoard(*myBoard, *prevBoard);
          // prevBoard = myBoard;//this is the problem
          // cout << "THIS IS PREV BOARD INITIAL"<<endl;
          // prevBoard->printBoard();
          // cout << "this is the first board before the update"<<endl;
          // myBoard->printBoard();


          std::this_thread::sleep_for(std::chrono::milliseconds(100));
          myBoardUpdater -> UpdateBoard (*myBoard, mode);
          cout << "This is the "<< i+1 << "'th iteration"<< endl;
          cout << "this is the second board after the update"<<endl;
          myBoard->printBoard();


          if (myBoardUpdater -> AreBoardsSame(*prevBoard, *myBoard)){
            // cout << "THIS IS PREV BOARD WHEN STATIC"<<endl;
            prevBoard->printBoard();
            cout<<"The state is static"<<endl;
            break;
          }
        }
      }

      //enter key logic
      else if (outputMode == 3)
      {
        // cout << "please press ENTER for the next generation"<< endl;
        while (true){

          myBoardUpdater -> CopyBoard(*myBoard, *prevBoard);
          myBoardUpdater -> UpdateBoard (*myBoard, mode);
          myBoard->printBoard();
          if (myBoardUpdater -> AreBoardsSame(*prevBoard, *myBoard)){
            // cout << "THIS IS PREV BOARD WHEN STATIC"<<endl;
            prevBoard->printBoard();
            cout<<"The state is static"<<endl;
            break;
          }
          if (myBoard->IsBoardEmpty())
          {
            cout<<"Board is empty"<<endl;
            break;
          }
          cout << "Please press ENTER for the next generation" << endl;
          cout << "If you want to exit the program, press the spacebar followed by ENTER" << endl;

          //checking for a space bar
          std::cin.get(ch);
          if (ch == ' '){
            break;
          }


        }

      }


//here



      // int count = 0;
      // for (int i = 0; i < iterations; ++i){
      //   if (myBoard->IsBoardEmpty()){
      //     myBoard->printBoard();
      //     cout<<"Board is empty"<<endl;
      //     break;
      //   }

      //   std::this_thread::sleep_for(std::chrono::milliseconds(100));
      //   myBoardUpdater -> UpdateBoard (*myBoard, mode);
      //   cout << "This is the "<< i+1 << "'th iteration"<< endl;
      //   myBoard->printBoard();
      // }
      // cout << "Would you like to output the final iteration to an .txt file? "<< endl;
      // cout << "0) Yes"<<endl;
      // cout << "1) No"<< endl;
      // cin >> txtfile;
      // if (txtfile == 0){
      //   cout << "Please name the file you would like to output to (German.txt)"<<endl;
      //   cin>>outputfile;
      //   std::ofstream ofs (outputfile, std::ofstream::out);
      //   ofs<< "Wyatt Miller : 2302376"<<endl<<
      //   "Lucas Torti : 2351555"<<endl
      //   ;

      //}
    }






    BoardUpdater *boardUpdater = new BoardUpdater();

//        TO DO LIST
// OUTPUT TO A FILE
// SLEEP OUTPUT
// ENTER FUNCTIONALITY
// . TO -
// DONUT MODE NEEDS FIXING


    return 0;
}
