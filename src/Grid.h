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
        Grid() = default;
        void addWall(coord2D coord);

        void addBox(coord2D coord);

        void addStorage(coord2D coord);

        void setPlayerPosition(coord2D coord);

        void printGrid();

        bool isTrap(int i, int j);

        void toWall(int i, int j);

        bool isWall(int i, int j);

        coord2D getDoor(int i, int j);

        bool thereIsWayOut(int i, int j);

};

#endif