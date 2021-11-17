#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include "Grid.h"

using namespace std;

typedef pair<int, int> coord2D;
typedef vector<vector<int>> matrix;
map<string, int> tile = {
    {"WALL", -1},
    {"NEW_WALL", 1},
    {"BOX", 2},
    {"STORAGE", 3},
    {"PLAYER", 4},
    {"VOID", 0}
};

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
    grid[coord.first][coord.second] = tile["WALL"];
}

void Grid::addBox(coord2D coord){
    nBoxes.push_back(coord);
    grid[coord.first][coord.second] = tile["BOX"];
}

void Grid::addStorage(coord2D coord){
    nStorageLocations.push_back(coord);
    grid[coord.first][coord.second] = tile["STORAGE"];
}

void Grid::setPlayerPosition(coord2D coord){
   player = coord;
    grid[coord.first][coord.second] = tile["PLAYER"];
}

void Grid::printGrid(){
    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeV; j++) {
            int e = grid[i][j];
            if (e == tile["NEW_WALL"]) cout << "⛔";
            else if (isWall(i,j)) cout << "🚧";
            else if (e == tile["BOX"]) cout << "📦";
            else if (e == tile["STORAGE"]) cout << "📥";
            else if (e == tile["PLAYER"]) cout << "🧚";
            else cout << "⬛️";
        }
        cout << endl;
    }
}

bool Grid::isTrap(int i, int j) {
    if (grid[i][j] != tile["VOID"]) return false;
    int sum = isWall(i-1,j) + isWall(i+1,j) + isWall(i,j-1) + isWall(i,j+1);
    return sum >= 3;
}

void Grid::toWall(int i, int j) {
    grid[i][j] = tile["NEW_WALL"];
}

bool Grid::isWall(int i, int j) {
    return (grid[i][j] == tile["WALL"]) || (grid[i][j] == tile["NEW_WALL"]);
}

bool Grid::thereIsWayOut(int i, int j){
    return ! (isWall(i-1,j) && isWall(i+1,j) && isWall(i,j-1) && isWall(i,j+1));
}

coord2D Grid::getDoor(int i, int j){
    if (!isWall(i-1, j)) return make_pair(i-1, j);
    else if (!isWall(i+1, j)) return make_pair(i+1, j);
    else if (!isWall(i, j-1)) return make_pair(i, j-1);
    else if (!isWall(i, j+1)) return make_pair(i, j+1);
    else throw std::invalid_argument( "There is no door" );
}


