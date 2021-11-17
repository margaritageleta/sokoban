#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>

#include "Grid.h"

using namespace std;

typedef pair<int, int> coord2D;
typedef vector<vector<int>> matrix;

class Controller {
    public:
    Grid grid;
    Controller(Grid grid);
    void prune();
    void pruneHallway(int i, int j);
    
    
};

#endif