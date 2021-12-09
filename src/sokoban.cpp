#include <iostream>
#include <string>

#include "Grid.h"
#include "State.h"
#include "Action.h"
#include "QLearning.h"
#include "Algorithms.h"
#include "Controller.h"
#include "Heuristic.h"
#include "PriorityQueue.h"
#include "QStar.h"
#include "QState.h"




using namespace std;

int main (int argc, char** argv) {

   Controller* controller = new Controller();

   while (!controller->loaded){
      cout << "Write a valid input file path: ";
      string inputFile;
      getline(cin,inputFile);
      controller->loadFile(inputFile);
   }
   controller->solve("qstar");
   controller->printSolution("qstar");
}