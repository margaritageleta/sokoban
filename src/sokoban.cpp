#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>
#include "Grid.h"
#include "Controller.h"

using namespace std;
typedef pair<int, int> coord2D;
typedef vector<vector<int>> matrix;

std::istringstream nextLine(ifstream &infile, string line);
coord2D getXY(istringstream &iss);

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
         grid.addWall(getXY(iss));
      }
      iss = nextLine(infile, line);
      iss >> nval;
      for (int i = 0; i < nval; i++) {
         grid.addBox(getXY(iss));
      }
      iss = nextLine(infile, line);
      iss >> nval;
      for (int i = 0; i < nval; i++) {
         grid.addStorage(getXY(iss));
      }
      iss = nextLine(infile, line);

      grid.setPlayerPosition(getXY(iss));

      grid.printGrid();

      Controller controller(grid);

      controller.prune();

   }

   




}

std::istringstream nextLine(ifstream &infile, string line){
   getline(infile, line);
   istringstream iss(line);
   return iss;
}

coord2D getXY(istringstream &iss){
   int x,y;
   iss >> x >> y;
   x--; y--;
   return make_pair(x,y);
}