#ifndef HEURISTIC_H
#define HEURISTIC_H
#include "State.h"
#include <math.h>
#include <limits>
#include <vector>

using namespace std;
typedef pair<int, int> coord2D;
class State;
class Heuristic { 
    public: 
        static double getValue(State* state, const int p, double W);
        static int getNBoxes(State* state);
    private: 
        static double computeMinkowskiDistance(coord2D x1, coord2D x2, const int p);
};

#endif