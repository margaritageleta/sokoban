#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <set>
#include <map>
#include <string>
#include <vector>

#include "Grid.h"
#include "State.h"
#include "PriorityQueue.h"
#include "Action.h"
#include "QLearning.h"
#include "QStar.h"


using namespace std;

typedef pair<int, int> coord2D;

class QLearning;
class QStar;
class Algorithms{
    public:
    static State* AStar(State* state);
    static QLearning* QLearningAlg(State* state);
    static QStar* QStarAlg(State* state);
    static State* AStarSubRoutine(State* state);
    static State* QLearningAstar(State* state);
    static bool isGoodStep(State* state);
};

#endif