#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>
#include "Grid.h"

using namespace std;

typedef pair<int, int> coord2D;
typedef vector<vector<int>> matrix;

matrix grid;
vector<coord2D> nWallSquares, nBoxes, nStorageLocations;
coord2D player;
int sizeH, sizeV, x, y;



Grid::Grid(int sizeH, int sizeV) {
    this->sizeH = sizeH;
    this->sizeV = sizeV;
    grid = matrix(sizeH, vector<int>(sizeV));
}

void Grid::addWall(coord2D coord){
    nWallSquares.push_back(coord);
    grid[coord.first][coord.second] = 1;
}

void Grid::addBox(coord2D coord){
    nBoxes.push_back(coord);
    grid[coord.first][coord.second] = 2;
}

void Grid::addStorage(coord2D coord){
    nStorageLocations.push_back(coord);
    grid[coord.first][coord.second] = 3;
}

void Grid::setPlayerPosition(coord2D coord){
   player = coord;
    grid[coord.first][coord.second] = 4;
}

void Grid::printGrid(){
    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeV; j++) {
            int e = grid[i][j];
            if (e == 1) cout << "🚧";
            else if (e == 2) cout << "📦";
            else if (e == 3) cout << "📥";
            else if (e == 4) cout << "🧚";
            else cout << "⬛️";
        }
        cout << endl;
    }
}
