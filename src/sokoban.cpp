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

#include <stdlib.h>


using namespace std;

int main (int argc, char** argv) {

   Controller* controller = new Controller();

   string inputFile = argv[1];
   string algo = argv[2];
   int W = atof(argv[3]);
   double alpha = atof(argv[4]);
   double gamma = atof(argv[5]);
   double epsilon = atof(argv[6]);

   while (!controller->loaded){
      controller->loadFile(inputFile);
   }
   controller->solve(algo,W,alpha,gamma,epsilon);
   //controller->printSolution(algo);
}