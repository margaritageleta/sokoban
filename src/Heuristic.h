#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "State.h"

class Heuristic { 
    public: 
        static double getValue(State state, const int p);
    private: 
        Heuristic() {};
        static double computeMinkowskiDistance(coord2D x1, coord2D x2, const int p);
};

#endif