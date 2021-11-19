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
    {"VOID", 0},
    {"NEW_WALL", 1},
    {"BOX", 2},
    {"STORAGE", 3},
    {"PLAYER", 4},
    {"PLAYERNSTG", 5},
    {"BOXNSTG", 6}
};

matrix grid;
vector <coord2D> nWallSquares, nBoxes, nStorageLocations;
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
            else if (e == tile["PLAYERNSTG"]) cout << "🛌";
            else if (e == tile["BOXNSTG"]) cout << "🎁";
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

bool Grid::isWall(coord2D coord) {
    return (grid[coord.first][coord.second] == tile["WALL"]) || (grid[coord.first][coord.second] == tile["NEW_WALL"]);
}
bool Grid::isBox(coord2D coord) {
    return (grid[coord.first][coord.second] == tile["BOX"]) || (grid[coord.first][coord.second] == tile["BOXNSTG"]);
}

bool Grid::isCorner(coord2D coord) { //no tenemos en cuenta esquinas formadas por otras cajas!
    int i = coord.first; 
    int j = coord.second;
    bool a = (isWall(i-1,j) && (isWall(i,j-1) || isWall(i,j+1)));
    bool b = (isWall(i+1,j) && (isWall(i,j-1) || isWall(i,j+1)));
    return a || b;
}

bool Grid::isAnyBoxInFreeCorner(){
    for (coord2D coord : nBoxes){
        if(isBoxInFreeCorner(coord)) return true;
    }
    return false;
}


bool Grid::isBoxInFreeCorner(coord2D coord) {
    if (!isBox(coord)) return false;
    int i = coord.first; 
    int j = coord.second;
    if (grid[i][j] == tile["BOXNSTG"]) return false;
    
    return isCorner(coord);
}

bool Grid::isBoxInStorage(coord2D coord){
    if (!isBox(coord)) return false;
    return grid[coord.first][coord.second] == tile["BOXNSTG"];
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

void Grid::moveBox(coord2D from, coord2D to){
    for (int i = 0; i < nBoxes.size(); i++){
        if (nBoxes[i] == from){
            nBoxes[i] = to;
            break;
        } 
    }
    
    if (grid[from.first][from.second] == tile["BOXNSTG"]) grid[from.first][from.second] = tile["STORAGE"];
    else grid[from.first][from.second] = tile["VOID"];
    
    if (grid[to.first][to.second] == tile["STORAGE"]) grid[to.first][to.second] = tile["BOXNSTG"];
    else grid[to.first][to.second] = tile["BOX"];
    
}
void Grid::movePlayer(coord2D from, coord2D to){
    player = to;

    if (grid[from.first][from.second] == tile["PLAYERNSTG"]) grid[from.first][from.second] = tile["STORAGE"];
    else grid[from.first][from.second] = tile["VOID"];
    
    if (grid[to.first][to.second] == tile["STORAGE"]) grid[to.first][to.second] = tile["PLAYERNSTG"];
    else grid[to.first][to.second] = tile["PLAYER"];
}


