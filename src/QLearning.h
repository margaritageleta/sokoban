#ifndef QLEARNING_H
#define QLEARNING_H

#include <map>
#include<string>
#include "QState.h"
#include "State.h"
#include "Heuristic.h"
#include <chrono>
#include "Random.h"

using namespace std;

class QLearning{
    public:
    map<string, double> qtable;
    double alpha, gamma, epsilon, normalizer, decayFactor;
    State* initialState;
    int epoch=0;
    QLearning(State* initialState, double alpha, double gamma, double epsilon, double decayFactor);
    double getReward(State* state, Action* action);
    State* takeAction(State* state);
    bool executeEpisode(State* initialState, int nMaxMoves);
    void train(int nEpochs, int nMaxSteps);
    State* takeSuboptimalAction(State* state);
    bool thereIsASolution(int nMaxSteps);
    private:
    map<string, double> visited;
    Action* getAction(State* state, double epsilon, double decayFactor);
    vector<Action*> getValidActions(State* state);
    Action* chooseActionWithPolicy(State* state, vector<Action*> actions);
    double getNextMaxQ(State* nextState);
    void normalizeQ();
    bool getSolutionSteps();
    bool isLoop(State* state, Action* action);
    
    
};

#endif