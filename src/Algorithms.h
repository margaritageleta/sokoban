#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "State.h"
#include "Action.h"
#include "PriorityQueue.h"
#include <set>
#include <string>


using namespace std;
typedef pair<int, int> coord2D;

class Algorithms{
    public:
    static State AStar(State state);
};

#endif