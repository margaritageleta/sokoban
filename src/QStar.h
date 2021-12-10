#ifndef QSTAR_H
#define QSTAR_H

#include <string>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

#include "Grid.h"
#include "State.h"
#include "Heuristic.h"
#include "Action.h"
#include "QState.h"

using namespace std;
typedef pair<Action*, double> actR;

class QStar{
    public:
    unordered_map<string, double> qtable;
    unordered_set<string> visited;
    vector <actR> validActions; 
    double alpha, gamma, epsilon, normalizer, decayFactor;
    State* initialState;
    int epoch=0;
    int consecutiveWins = 0;
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
    actR getAction(State* state, double epsilon, double decayFactor);
    void getValidActionsAndRewards(State* state);
    actR chooseActionWithPolicy(State* state);
    double getNextMaxQ(State* nextState);
    void normalizeQ();
    bool getSolutionSteps();
    bool isLoop(State* state, Action* action);
    
    
};

#endif