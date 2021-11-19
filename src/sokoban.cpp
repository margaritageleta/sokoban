#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>
#include "Grid.h"
#include "State.h"
#include "Controller.h"
#include "Action.h"
#include "Algorithms.h"
#include <chrono>

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
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      controller.prune();
      
      State solution = static_cast<State&>(controller.grid);
      solution = State::create(solution, nullptr);
      
      solution = Algorithms::AStar(solution);
      vector<State> moves;
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      cout << "SOLUTION FOUND" << endl;
      cout << "ELAPSED TIME: " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " seconds"  <<endl;
      cout << "ELAPSED TIME: " << std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() << " minutes"  <<endl;

      while (true){
         moves.push_back(solution);
         if (solution.isInitialState()) break;
         solution = *(solution.parent);
      }
      
      for (int i = moves.size()-1; i >= 0; i--){
         do{cout<<"\nPress enter to see next move\n"<<endl;} while (cin.get() != '\n');
         moves[i].printGrid();
      }

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