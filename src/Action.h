#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <memory>

#include "Grid.h"
#include "State.h"
#include "Algorithms.h"

using namespace std;
typedef pair<int, int> coord2D;

enum Move{ UP=0, DOWN=1, RIGHT=2, LEFT=3, Last};
enum QSMove{ QUP=0, QDOWN=1, QRIGHT=2, QLEFT=3, ASTAR=4, QLast};

class Algorithms;

class Action{
    private:
    static State* getState(State* state, Move m);
    static State* getQSState(State* state, QSMove m);
    static coord2D moveRight(coord2D coord);
    static coord2D moveLeft(coord2D coord);
    static coord2D moveUp(coord2D coord);
    static coord2D moveDown(coord2D coord);
    public:
    static vector<State*> getNextStates(State* state);
    static Move getQSMove(QSMove move);
    coord2D (*action)(coord2D coord);
    Move move = Last;
    QSMove qsmove = QLast;
    Action(Move move);
    Action(QSMove move);
    string getId();
    State* getState(State* state);
    State* getQSState(State* state);
        
};

#endif