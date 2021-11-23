#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>
#include <chrono>
#include "Grid.h"
#include "State.h"
#include "Algorithms.h"
#include "QLearning.h"


using namespace std;

typedef pair<int, int> coord2D;
typedef vector<vector<int>> matrix;

class Controller {
    public:
    Grid* grid=nullptr;
    State* solution=nullptr;
    QLearning* ql = nullptr;
    bool loaded;
    Controller();
    void loadFile(string inputFile);
    void solve();
    void printOptimalSolution();
    private:
    void prune();
    void pruneHallway(int i, int j);
    istringstream nextLine(ifstream &infile, string line);
    coord2D getXY(istringstream &iss);   
};

#endif