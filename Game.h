/*
Ryan Kassab
2296707
Worked with: Ademir Vila
rkassab@chapman.edu
CPSC350-01
Assignment #2
*/
#include <iostream>

using namespace std;

class UserInput
{
public:
  string gameMode();
  bool gameType();
  bool gamePause();
  string outputFile();
  bool checkOutFile();
};

class Board
{
public:
  char** createBoard(int height, int width);
  int getHeight();
  int getWidth();
  double getDensity();
  char** fillBoard(char** gameBoard, int height, int width, double density);
  int randRow(int width);
  int randCol(int height);
  char** copyBoard(char** gameBoard, int height, int width);
  bool checkIfEmpty(char** gameBoard, int height, int width);
  bool checkIfFull(char** gameBoard, int height, int width);
  bool checkIfStable(char** copyBoard, char** nextGeneration, int height, int width);
  string printBoard(char** gameBoard, int height, int width);
};

class Classic
{
public:
    int checkNeightbors(char** gameBoard, int a, int b);
    char** nextGeneration(char** gameBoard, int a, int b);
    void playClassic(int height, int width, int density);

};

class Doughnut
{
public:
  int checkNeightbors(char** gameBoard,int a, int b, int height, int width);
  char** nextGeneration(char** gameBoard, int a, int b, int height, int width);
  void playDoughnut(int height, int width, double density);
};

class Mirror
{
public:
  int checkNeightbors(char** gameBoard,int a, int b, int height, int width);
  char** nextGeneration(char** gameBoard, int a, int b, int height, int width);
  void playDoughnut(int height, int width, double density);

};
