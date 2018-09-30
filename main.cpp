/*
Ryan Kassab
2296707
Worked with: Ademir Vila
rkassab@chapman.edu
CPSC350-01
Assignment #2
*/
#include "Game.h"

using namespace std;

int main(int argc, char** argv)
{
  UserInput input;

  cout << "Welcome to the Game of Life." << endl;
  bool type = input.gameType();
  string mode = input.gameMode();

  if(type == false)
  {
    Board board;

    int height = board.getHeight();
    int width = board.getWidth();
    double density = board.getDensity();

    if(mode == "classic")
    {
      Classic classic;
      classic.playClassic(height, width, density);
    }
    else if(mode == "doughnut")
    {
      Doughnut doughnut;
      doughnut.playDoughnut(height, width, density);
    }
    else if(mode == "mirror")
    {
      cout << "Sorry this function is currently unavaliable" << endl;
    }
    else
    {
      cout << "Invalid Mode Entered" << endl;
    }
  }
  else
  {
    cout << "Sorry that function isn't working at the momemt" << endl;
  }
}
