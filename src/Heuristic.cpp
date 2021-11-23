#include "Heuristic.h"
#include "State.h"



double Heuristic::computeMinkowskiDistance(coord2D x1, coord2D x2, const int p) {
    return pow(pow(abs(x1.first - x2.first), p) + pow(abs(x1.second - x2.second), p), 1/p);
}

double Heuristic::getValue(State* state, const int p, double W) {

    double smallestDist2Box = double(numeric_limits<int>::max());
    double totalDistBoxStorage = 0.0;
    

    for (auto & box : state->nBoxes) { 
        if (state->isBoxInStorage(box)) continue;
        
        double currDist = Heuristic::computeMinkowskiDistance(box, state->player, p); // Heuristic 1
        if (smallestDist2Box > currDist) smallestDist2Box = currDist;

        int nStorage = 0;
        for (auto & storage : state->nStorageLocations) {
           totalDistBoxStorage +=  Heuristic::computeMinkowskiDistance(box, storage, p); // Heuristic 2
           nStorage++;
        }
        totalDistBoxStorage /= nStorage;
    }
    if (double(numeric_limits<int>::max()) == smallestDist2Box) smallestDist2Box = 0;
    return W*(smallestDist2Box + totalDistBoxStorage);

}

int Heuristic::getNBoxes(State* state) {
    
    int nBoxes = 0;
    for (auto & box : state->nBoxes) { 
        if (state->isBoxInStorage(box)) continue;
        nBoxes++;
    }
    return  nBoxes;

}



