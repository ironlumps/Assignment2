/*
Ryan Kassab
2296707
Worked with: Ademir Vila
rkassab@chapman.edu
CPSC350-01
Assignment #2
*/
#include "Game.h"
#include <fstream>

using namespace std;

string UserInput::gameMode() //Method that retrieves the game mode that will be intialized
{
  string mode;
  cout << "Enter the game mode you wish to play (classic, mirror, doughnut): " << endl;

  // this for loop makes the entry into lower case
  for(int i = 0; i < mode.length(); i++)
  {
    mode[i] = tolower(mode[i]);
  }

  cin >> mode;
  return mode;
}

bool UserInput::gameType() // Method that prompts user and returns whether it wants to be read file or randomly generated
{
  string type;
  cout << "Would you like to read from a file (No defaults to random map): " << endl;

  cin >> type;
  // this for loop makes the entry into lower case
  for(int i = 0; i < type.length(); i++)
  {
    type[i] = tolower(type[i]);
  }
  // if yes return true, if not return false
  if(type == "y" || type == "yes")
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool UserInput::gamePause() // Method that prompts the user to whether he wasnts to pause between each iteration
{
  string pause;
  cout << "Would you like the simulation to pause between generations (y/n): " << endl;

  cin >> pause;
  // this for loop takes the entry and makes it lower case
  for(int i = 0; i < pause.length(); i++)
  {
    pause[i] = tolower(pause[i]);
  }

  // if yes return true, if not return false
  if(pause == "y" || pause == "yes")
  {
    return true;
  }
  else
  {
    return false;
  }
}

string UserInput::outputFile() // method that gets a desired output file if results are to be printed to one
{
  string file;
  cout << "Enter the name of your desired output file: " << endl;

  // this for loop makes the entry lower case
  for(int i = 0; i < file.length(); i++)
  {
    file[i] = tolower(file[i]);
  }

  cin >> file;
  return file;
}

bool UserInput::checkOutFile() // method that checks whether or not the user wants to output the results to a file
{
  string answer;
  cout << "Would you like the simulation to write the results to a file: " << endl;

  cin >> answer;

  // this for loop makes the entry lower case
  for(int i = 0; i < answer.length(); i++)
  {
    answer[i] = tolower(answer[i]);
  }
  // if yes return true, if not returns false
  if(answer == "y" || answer == "yes")
  {
    return true;
  }
  else
  {
    return false;
  }
}

char** Board::createBoard(int height, int width) // this method uses a desired height and width to build the game board
{
  // initialize as single array
  char* gameBoard[width];

  // iterate through array
  for(int i = 0; i < width; i++)
  {
    // for each element, add another array to make a 2d array
    gameBoard[i] = new char[height];
    for(int j = 0; j < height; j++)
    {
      // initializes every element as blank
      gameBoard[i][j] = '-';
    }
  }

  return gameBoard;
}

char** Board::copyBoard(char** gameBoard, int height, int width) // copies the original board to another board to keep track of generations
{
  // initialize single array
  char* copyBoard[width];

  for(int i = 0; i < width; i++)
  {
    // for each element add another array
    copyBoard[i] = new char[height];
    for(int j = 0; j < height; j++)
    {
      // each element of the new array is equal to the other array
      copyBoard[i][j] = gameBoard[i][j];
    }
  }

  return copyBoard;
}

double Board::getDensity() // gets denisty from user prompting
{
  string answer;
  cout << "Enter the population density: " << endl;
  cin >> answer;
  // converts string response into double
  double density = stod(answer);
  return density;
}

int Board::getHeight() // gets user prompted height
{
  string answer;
  cout << "Enter the height: " << endl;
  cin >> answer;
  // converts string response into integer
  int height = stoi(answer);
  return height;
}

int Board::getWidth() // gets user pronmpted width
{
  string answer;
  cout << "Enter the width: " << endl;
  cin >> answer;
  // converts string reponse into integer
  int width = stoi(answer);
  return width;
}

int Board::randRow(int width) // generates a random element in the row, based on the width
{
  return(rand() % width);
}

int Board::randCol(int height) // generates a random element in the column, based on the height
{
  return(rand() % height);
}

char** Board::fillBoard(char** gameBoard, int width, int height, double density) // fills the board with random X's
{
  int count = 0;
  // gets how many X's that need to be filled in
  int pop = (height * width) * density;
  while(count < pop)
  {
    // generates a random cell of 2d array
    int row = Board::randRow(width);
    int col = Board::randCol(height);
    // sets it as X
    gameBoard[row][col] = 'X';
    // iterates count until count is = to population
    count++;
  }

  return gameBoard;
}

bool Board::checkIfFull(char** gameBoard, int height, int width) // checks to see if the game board is full of X's to stop program
{
  int xCount = 0;
  // iterates through 2d array to count amount of X's
  for(int i = 0; i < width; i++)
  {
    for(int j = 0; j < height; j++)
    {
      if(gameBoard[i][j] == 'X')
      {
        xCount++;
      }
    }
  }
  // if count of X's is equal to size of grid, the grid is full of X's
  int size = height * width;
  if(xCount == size)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Board::checkIfEmpty(char** gameBoard, int height, int width) // checks to see if grid is empty to stop the program
{
  int xCount = 0;
  // iterates through 2d array to count X's
  for(int i = 0; i < width; i++)
  {
    for(int j = 0; j < height; j++)
    {
      if(gameBoard[i][j] == 'X')
      {
        xCount++;
      }
    }
  }
  // if the count of X's is 0 the grid is empty
  if(xCount == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Board::checkIfStable(char** copyBoard, char** nextGeneration, int height, int width) // checks to see if the grid has hit a repeating pattern
{
  // iterates through 2d arrays and checks if the previous generation is equal to the next generation
  // if they are the same they have hit a repeating pattern
  for(int i = 0; i < width; i++)
  {
    for(int j = 0; j < height; j++)
    {
      if(copyBoard[i][j] == nextGeneration[i][j])
      {
        return true;
      }
    }
  }

  return false;
}

string Board::printBoard(char** gameBoard, int height, int width) // returns a string form of the board
{
  string result;

  // iterates through array and adds each element to the string
  for(int i = 0; i < width; i++)
  {
    for(int j = 0; j < height; j++)
    {
      result += gameBoard[i][j];
    }
    // after each row, adds a new line element to separate lines
    result += '\n';
  }

  return result;
}

int Classic::checkNeightbors(char** gameBoard, int a, int b) // checks the neightbors for the classic game mode
{
  int neightborCount = 0;

  // iterates through the cells directly surrounding the cell ato count the neightbors
  for(int i = -1; i < 2; i++)
  {
    for(int j = -1; j < 2; j++)
    {
      if(i != 0 && j != 0)
      {
        if(gameBoard[a + i][b + j])
        {
          neightborCount++;
        }
      }
    }
  }

  return neightborCount;
}

char** Classic::nextGeneration(char** gameBoard, int a, int b) // creates the next generation board
{
  // gets neighbor count from previous method
  int neightborCount = checkNeightbors(gameBoard, a, b);
  // fills cell based upon appropriate situation
  if(neightborCount <= 1)
  {
    gameBoard[a][b] = '-';
  }
  else if(neightborCount == 2)
  {
    gameBoard[a][b] = gameBoard[a][b];
  }
  else if(neightborCount == 3)
  {
    gameBoard[a][b] = 'X';
  }
  else
  {
    gameBoard[a][b] = '-';
  }

  return gameBoard;
}

void Classic::playClassic(int height, int width, int density)// this method actually executes the classic game mode
{
  // initializes the class objects
  Board board;
  UserInput input;
  // initializes the necessary variables
  char** gameBoard = board.createBoard(height, width);
  gameBoard = board.fillBoard(gameBoard, height, width, density);
  bool answer = input.gamePause();
  bool output = input.checkOutFile();
  bool empty = board.checkIfEmpty(gameBoard, height, width);
  bool full = board.checkIfFull(gameBoard, height, width);
  char** copyBoard;
  char** nextGeneration;
  bool stable = board.checkIfStable(copyBoard, nextGeneration, height, width);

  if(output == true) // if user wants to ouput to file
  {
    string file = input.outputFile();
    // creates out stream of file
    ofstream writeFile(file);

    while(empty != true || full != true || stable != true)
    {
      // copies the current generation
      copyBoard = board.copyBoard(gameBoard, height, width);

      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          // creates the nextGeneration
          nextGeneration = Classic::nextGeneration(gameBoard, i, j);
        }
      }

      // sets the current generation to the new generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          gameBoard[i][j] = nextGeneration[i][j];
        }
      }

    // These two lines were meant to write to a file but not working great
    //  string board = board.printBoard(gameBoard, height, width);
    //  writeFile << board << endl;

    // Recalulates the boolean variables
      empty = board.checkIfEmpty(gameBoard, height, width);
      full = board.checkIfFull(gameBoard, height, width);
      stable = board.checkIfStable(copyBoard, nextGeneration, height, width);
    }

  }

  else if(answer == true) // if user wants to pause between generations
  {
    while(empty != true || full != true || stable != true)
    {
      //copies current generation to copy board
      copyBoard = board.copyBoard(gameBoard, height, width);
      //creates new generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          nextGeneration = Classic::nextGeneration(gameBoard, i, j);
        }
      }
      // makes current generation the next generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          gameBoard[i][j] = nextGeneration[i][j];
        }
      }
      // pauses the simulation until enter is hit
      system("pause");

      // meant to print results to console, but hit a few snags
      // string result = board.printBoard(gameBoard, height, width);
      // cout << result << endl;

      // Recalulates the boolean variables
      empty = board.checkIfEmpty(gameBoard, height, width);
      full = board.checkIfFull(gameBoard, height, width);
      stable = board.checkIfStable(copyBoard, nextGeneration, height, width);
    }
  }
  else // if neither are true just runs it until it fails
  {
    while(empty != true || full != true || stable != true)
    {
      // copies current generation into other board
      copyBoard = board.copyBoard(gameBoard, height, width);
      // creates the next generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          nextGeneration = Classic::nextGeneration(gameBoard, i, j);
        }
      }
      // makes current generation the next generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          gameBoard[i][j] = nextGeneration[i][j];
        }
      }

      // meant to print results out to console, but hit a few snags
      // string result = board.printBoard(gameBoard, height, width);
      // cout << result << endl;

      // Recalulates the boolean variables
      empty = board.checkIfEmpty(gameBoard, height, width);
      full = board.checkIfFull(gameBoard, height, width);
      stable = board.checkIfStable(copyBoard, nextGeneration, height, width);
    }
  }
}

int Doughnut::checkNeightbors(char** gameBoard,int a, int b, int height, int width) // checks the neightbors for doughnut mode
{
  int neightborCount = 0;

  // checking to see if its on top or bottom row
  if(gameBoard[0][b] == 'X' || gameBoard[height - 1][b] == 'X')
  {
    int tempHeight = height - 1;
    // checking to see if its neighbors are X's
    if(gameBoard[a][b - 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a][b + 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a + 1][b - 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a + 1][b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a + 1][b + 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[tempHeight - a][b - 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[tempHeight - a][b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[tempHeight - a][b + 1] == 'X')
    {
      neightborCount++;
    }
  }
  // checking to see its in the first or last column
  else if(gameBoard[a][0] == 'X' || gameBoard[a][width - 1])
  {
    int tempWidth = width - 1;
    //checking to see if its neighbors are X's
    if(gameBoard[a + 1][tempWidth - b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a + 1][b - 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a + 1][b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a][tempWidth - b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a][b - 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a - 1][tempWidth - b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a - 1][b - 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a - 1][b] == 'X')
    {
      neightborCount++;
    }
  }
  // checking to see if cell is in the corners
  else if(gameBoard[0][0] == 'X' || gameBoard[0][width - 1] == 'X' || gameBoard[height - 1][0] == 'X' || gameBoard[height - 1][width - 1] == 'X')
  {
    int tempHeight = height - 1;
    int tempWidth = width - 1;
    //checking if its neightbors are X's
    if(gameBoard[tempHeight - a][b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a - 1][b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[tempHeight - a][b + 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a - 1][b + 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a][b + 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[tempHeight - a][tempWidth - b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a - 1][tempWidth - b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a][tempWidth - b] == 'X')
    {
      neightborCount++;
    }
  }
  else // checks if the cell is in the middle (which is the same as classic)
  {
    // checks the cells neightbors and if they are X's
    if(gameBoard[a + 1][b + 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a + 1][b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a + 1][b - 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a][b + 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a][b - 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a - 1][b + 1] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a - 1][b] == 'X')
    {
      neightborCount++;
    }
    if(gameBoard[a - 1][b - 1] == 'X')
    {
      neightborCount++;
    }
  }

  return  neightborCount;
}

char** Doughnut::nextGeneration(char** gameBoard, int a, int b, int height, int width) // creates next generation for doughnut mode
{
  // gets neighbor count from previous method
  int neightborCount = checkNeightbors(gameBoard, a, b, height, width);
  // uses the neightbor count to calculate the correct situation and fills accordingly
  if(neightborCount <= 1)
  {
    gameBoard[a][b] = '-';
  }
  else if(neightborCount == 2)
  {
    gameBoard[a][b] = gameBoard[a][b];
  }
  else if(neightborCount == 3)
  {
    gameBoard[a][b] = 'X';
  }
  else
  {
    gameBoard[a][b] = '-';
  }

  return gameBoard;
}

void Doughnut::playDoughnut(int height, int width, double density) // executes the doughnut mode game
{
  // initializes the class objects
  Board board;
  UserInput input;
  // initializes the necessary variables
  char** gameBoard = board.createBoard(height, width);
  gameBoard = board.fillBoard(gameBoard, height, width, density);
  bool answer = input.gamePause();
  bool output = input.checkOutFile();
  bool empty = board.checkIfEmpty(gameBoard, height, width);
  bool full = board.checkIfFull(gameBoard, height, width);
  char** copyBoard;
  char** nextGeneration;
  bool stable = board.checkIfStable(copyBoard, nextGeneration, height, width);
  // if the resutls are supposed to be written to a file
  if(output == true)
  {
    string file = input.outputFile();
    // initialize the ouput file stream
    ofstream writeFile(file);

    while(empty != true || full != true || stable != true)
    {
      // copies the board over to create a previous generation
      copyBoard = board.copyBoard(gameBoard, height, width);
      // creates a next generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          nextGeneration = Doughnut::nextGeneration(gameBoard, i, j, height, width);
        }
      }
      // creates the current generation to be the next generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          gameBoard[i][j] = nextGeneration[i][j];
        }
      }

      //  These two lines are meant to write to the file, but it was acting weird
      //  string board = board.printBoard(gameBoard, height, width);
      //  writeFile << board << endl;

      // Recalulates the boolean variables
      empty = board.checkIfEmpty(gameBoard, height, width);
      full = board.checkIfFull(gameBoard, height, width);
      stable = board.checkIfStable(copyBoard, nextGeneration, height, width);
    }

  }

  else if(answer == true) // if the user wasnt to pause in between generations
  {
    while(empty != true || full != true || stable != true)
    {
      // creates a copy of the current generation to create a previous generation
      copyBoard = board.copyBoard(gameBoard, height, width);
      // creates the next generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          nextGeneration = Doughnut::nextGeneration(gameBoard, i, j, height, width);
        }
      }
      // creates the current generation as the next generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          gameBoard[i][j] = nextGeneration[i][j];
        }
      }
      // pauses the generation until it hits enter
      system("pause");

      // These lines were meant to write the boards to the console, but hit a few snags
      // string result = board.printBoard(gameBoard, height, width);
      // cout << result << endl;

      // Recalulates the boolean variables
      empty = board.checkIfEmpty(gameBoard, height, width);
      full = board.checkIfFull(gameBoard, height, width);
      stable = board.checkIfStable(copyBoard, nextGeneration, height, width);
    }
  }
  else // if the user just wants to run simulation through console
  {
    while(empty != true || full != true || stable != true)
    {
      // copies board over to new array to create a previous generation
      copyBoard = board.copyBoard(gameBoard, height, width);
      // creates a next generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          nextGeneration = Doughnut::nextGeneration(gameBoard, i, j, height, width);
        }
      }
      // sets the current generation as the next generation
      for(int i = 0; i < width; i++)
      {
        for(int j = 0; j < height; j++)
        {
          gameBoard[i][j] = nextGeneration[i][j];
        }
      }

      // These lines were meant to print the board to the console, but hit a few snags
      // string result = board.printBoard(gameBoard, height, width);
      // cout << result << endl;

      // Recalulates the boolean variables
      empty = board.checkIfEmpty(gameBoard, height, width);
      full = board.checkIfFull(gameBoard, height, width);
      stable = board.checkIfStable(copyBoard, nextGeneration, height, width);
    }
  }
}
