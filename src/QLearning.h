#ifndef QLEARNING_H
#define QLEARNING_H

#include <map>
#include<string>
#include "QState.h"
#include "State.h"
#include "Heuristic.h"
#include <chrono>

using namespace std;

class QLearning{
    public:
    map<string, double> qtable;
    double alpha, gamma, epsilon, normalizer;
    State* initialState;
    QLearning(State* initialState, double alpha, double gamma, double epsilon);
    double getReward(State* state, Action* action);
    State* takeAction(State* state);
    bool executeEpisode(State* initialState, int nMaxMoves);
    void train();
    State* takeSuboptimalAction(State* state);
    private:
    Action* getAction(State* state, double epsilon);
    vector<Action*> getValidActions(State* state);
    Action* chooseActionWithPolicy(State* state, vector<Action*> actions);
    double getNextMaxQ(State* nextState);
    void normalizeQ();
    
    
};

#endif