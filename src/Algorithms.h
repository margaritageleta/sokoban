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
    static State* AStar(State* state, int W);
    static QLearning* QLearningAlg(State* state, double alpha,double gamma,double epsilon);
    static QStar* QStarAlg(State* state,int W, double alpha,double gamma,double epsilon);
    static State* AStarSubRoutine(State* state, int W);
    static bool isGoodStep(State* state, int W);
};

#endif