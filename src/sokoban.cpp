#include <iostream>
#include <string>
#include "Controller.h"

using namespace std;

int main (int argc, char** argv) {

   Controller* controller = new Controller();

   while (!controller->loaded){
      cout << "Write a valid input file path: ";
      string inputFile;
      getline(cin,inputFile);
      controller->loadFile(inputFile);
   }
   controller->solve();
   controller->printOptimalSolution();
}