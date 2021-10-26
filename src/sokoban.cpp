#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>
#include "Grid.h"

using namespace std;
typedef pair<int, int> coord2D;
typedef vector<vector<int>> matrix;

std::istringstream nextLine(ifstream &infile, string line);

int main (int argc, char** argv) {

   
   std::ifstream infile (argv[1]);
   int sizeH, sizeV;
   string line;
   istringstream iss;

   if (infile.is_open()){
      nextLine(infile, line) >> sizeH >> sizeV;
      Grid grid(sizeH, sizeV);
      
      int nval;
      iss = nextLine(infile, line);
      iss >> nval;

      for (int i = 0; i < nval; i++) {
         grid.addWall(iss);
      }
      iss = nextLine(infile, line);
      iss >> nval;
      for (int i = 0; i < nval; i++) {
         grid.addBox(iss);
      }
      iss = nextLine(infile, line);
      iss >> nval;
      for (int i = 0; i < nval; i++) {
         grid.addStorage(iss);
      }
      iss = nextLine(infile, line);

      grid.setPlayerPosition(iss);

      grid.printGrid();

   }

}

std::istringstream nextLine(ifstream &infile, string line){
   getline(infile, line);
   istringstream iss(line);
   return iss;
}