#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <set>
#include <map>
#include <string>
#include <vector>

#include "State.h"
#include "Action.h"
#include "PriorityQueue.h"
#include "QLearning.h"


using namespace std;

typedef pair<int, int> coord2D;


class Algorithms{
    public:
    static State* AStar(State* state);
    static QLearning* QLearningAlg(State* state);
};

#endif