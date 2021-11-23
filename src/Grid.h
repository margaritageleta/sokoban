#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>

using namespace std;

typedef pair<int, int> coord2D;
typedef vector<vector<int>> matrix;

class Grid {
    public:
        static map<string, int> tile;
        matrix grid;
        vector <coord2D> nWallSquares, nBoxes, nStorageLocations;
        coord2D player;
        int sizeH, sizeV;
        bool movedBox = false;
        Grid(int sizeH, int sizeV);
        Grid(Grid* g1);
        Grid() = default;
        void addWall(coord2D coord);

        void addBox(coord2D coord);

        void addStorage(coord2D coord);

        void setPlayerPosition(coord2D coord);

        void printGrid();

        bool isTrap(int i, int j);

        void toWall(int i, int j);

        bool isWall(int i, int j);
        
        bool isWall(coord2D coord);

        bool isBox(coord2D coord);

        bool isCorner(coord2D coord);

        bool isCorner(int i, int j);

        bool isAnyBoxInFreeCorner();

        bool isAnyBoxInDeadlock();

        bool isBoxInFreeCorner(coord2D coord);

        bool isBoxBetweenCorners(coord2D coord);

        bool isBoxInDeadlock(coord2D coord);

        bool isBoxInStorage(coord2D coord);

        coord2D getDoor(int i, int j);

        bool thereIsWayOut(int i, int j);

        void moveBox(coord2D from, coord2D to);

        void movePlayer(coord2D from, coord2D to);

        bool checkHorizontalDeadlock(int i,int j,int s);

        bool checkHorizontalDeadlock(int i,int j,int s, int o);

        bool checkVerticalDeadlock(int i,int j,int s);

        bool checkVerticalDeadlock(int i,int j,int s, int o);

};

#endif