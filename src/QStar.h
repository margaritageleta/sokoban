#ifndef QSTAR_H
#define QSTAR_H

#include <map>
#include <string>
#include <chrono>
#include <unordered_map>

#include "Grid.h"
#include "State.h"
#include "Heuristic.h"
#include "Action.h"
#include "QState.h"

using namespace std;

class QStar{
    public:
    unordered_map<string, double> qtable;
    double alpha, gamma, epsilon, normalizer, decayFactor;
    State* initialState;
    int epoch=0;
    Random random;
    int inactiveCounter = 0;
    QStar(State* initialState, double alpha, double gamma, double epsilon, double decayFactor);
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