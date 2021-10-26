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

void Grid::addWall(istringstream &iss){
    iss >> x >> y;
    x--; y--;
    nWallSquares.push_back(make_pair(x,y));
    grid[x][y] = 1;
}

void Grid::addBox(istringstream &iss){
    iss >> x >> y;
    x--; y--;
    nBoxes.push_back(make_pair(x,y));
    grid[x][y] = 2;
}

void Grid::addStorage(istringstream &iss){
    iss >> x >> y;
    x--; y--;
    nStorageLocations.push_back(make_pair(x,y));
    grid[x][y] = 3;
}

void Grid::setPlayerPosition(istringstream &iss){
    iss >> x >> y;
    x--; y--;
    player = make_pair(x,y);
    grid[x][y] = 4;
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
