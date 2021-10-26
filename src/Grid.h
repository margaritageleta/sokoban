#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>

using namespace std;

typedef pair<int, int> coord2D;
typedef vector<vector<int>> matrix;

class Grid {
    public:
        matrix grid;
        vector<coord2D> nWallSquares, nBoxes, nStorageLocations;
        coord2D player;
        int sizeH, sizeV, x, y;

        Grid(int sizeH, int sizeV);

        void addWall(istringstream &iss);

        void addBox(istringstream &iss);

        void addStorage(istringstream &iss);

        void setPlayerPosition(istringstream &iss);

        void printGrid();

};

#endif