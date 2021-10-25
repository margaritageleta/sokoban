#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>

using namespace std;
typedef pair<int, int> coord2D;
typedef vector<vector<int>> matrix;

int main (int argc, char** argv) {
   cout << "Good evening." << endl;

   // Read input file:
   ifstream infile(argv[1]);

   // Def variables:
   int sizeH, sizeV;
   matrix grid;
   vector<coord2D> nWallSquares, nBoxes, nStorageLocations;
   coord2D player;
   
   // Process 5 lines.
   string line;
   int i = 0;
   while (getline(infile, line) && i < 5) {
      cout << i << endl;
      istringstream iss(line);
      int x, y;
      // Line 1: read sizeH and sizeV.
      if (i == 0) {
         iss >> sizeH >> sizeV;
          // Define grid:
         cout << "Define grid of size " << sizeH << "x" << sizeV << "." << endl;
         grid = matrix(sizeH, vector<int>(sizeV));
      } // Line 2,3,4: read coord of wall squares, boxes, storage locations.
      else if (i != 5) {
         cout << "Defining coords." << endl;
         int val;
         iss >> val;
         while (iss >> x >> y) {
            x--; y--;
            if (i == 1) nWallSquares.push_back(make_pair(x,y));
            if (i == 2) nBoxes.push_back(make_pair(x,y));
            if (i == 3) nStorageLocations.push_back(make_pair(x,y));
            cout << "Accessing (" <<  x << "," << y << ") = " << i << "." << endl;
            grid[x][y] = i;
         }
      } // Line 5: player's initial location.
      else {
         iss >> x >> y;
         player = make_pair(x,y);
         grid[x][y] = i;
      }
      i++;
   }

   for (int i = 0; i < sizeH; i++) {
      for (int j = 0; j < sizeV; j++) {
         std::cout << grid[i][j];
      }
      std::cout << std::endl;
   }

}