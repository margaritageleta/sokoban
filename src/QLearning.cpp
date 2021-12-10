#include "QLearning.h"

initializer_list<Move> allMoves = { UP, DOWN, RIGHT, LEFT};

QLearning::QLearning(State* initialState, double alpha, double gamma, double epsilon, double decayFactor){
    this->initialState = initialState;
    this->alpha = alpha;
    this->gamma = gamma;
    this->epsilon = epsilon;
    this->decayFactor = decayFactor;
    this->random = Random();
}

double QLearning::getReward(State* state, Action* action){
    State* nextState =  action->getState(state);
    if((!nextState->equals(state))){
        if(nextState->isAnyBoxInDeadlock() || inactiveCounter > 20) return 1.0;
        if (nextState->isGoal()) return 100.0;
        if (Heuristic::getNBoxes(state) > Heuristic::getNBoxes(nextState)) return 20.0;
        if(nextState->movedBox && state->movedBox) return 10.0;
        if(nextState->movedBox) return 5.0;
        //if (Heuristic::getValue(state,2,1) > Heuristic::getValue(nextState,2,1)) return 10.0; // this does not guarantee pushing a box
        return 1.0;
    }
    return -1.0;
}

vector<Action*> QLearning::getValidActions(State* state){
    vector<Action*> validActions;
    for (Move move: allMoves){
        Action* a = new Action(move);
        if (getReward(state,a) != -1.0) {
            validActions.push_back(a);
        }
    }
    return validActions;
}

Action* QLearning::chooseActionWithPolicy(State* state, vector<Action*> actions){
    double maxQ = -100000000;
    Action * next;
    for(Action* a: actions){
        QState* qstate = new QState(state, a);
        string id = qstate->getId();
        if (!qtable.count(id)){
            qtable[id] = 0.0;
        }
        if(qtable[id] > maxQ){
            maxQ = qtable[id];
            next = a;
        }
    }
    return next;
}

Action* QLearning::getAction(State* state, double epsilon, double decayFactor){
    vector<Action*> validActions = getValidActions(state);
    double probablity = random.getProbablity();
    double greedy = epsilon * pow(decayFactor, epoch); 
    if (probablity < greedy){
        int index = random.getBetweenRange(0,validActions.size()-1);
        return validActions[index];
    }
    return chooseActionWithPolicy(state, validActions);
}

State* QLearning::takeAction(State* state){
    Action* action = getAction(state,epsilon,decayFactor);
    double reward = getReward(state, action);
    
    if (reward == 1.0) inactiveCounter++;
    else inactiveCounter = 0;
    
    State* nextState = action->getState(state);
    double nextMaxQ = getNextMaxQ(nextState);
    
    QState* qstate = new QState(state,action);
    string id = qstate->getId();
    /*if(visited.count(id) == 0) visited[id] = 1;
    else visited[id] = visited[id] + 1;
    */
    qtable[id] = qtable[id] + alpha * (reward + gamma * nextMaxQ - qtable[id]);
    
    if (qtable[id] > normalizer) normalizer = qtable[id];
    
    return nextState;
}

State* QLearning::takeSuboptimalAction(State* state){
    
    Action* action = getAction(state, 0, 1);
    State* nextState = action->getState(state);
    
    return nextState;
}

double QLearning::getNextMaxQ(State* nextState){
    double maxQ = -1000000;
    for(Action* a: getValidActions(nextState)){
        QState* qs = new QState(nextState,a);
        string id = qs->getId();
        if (!qtable.count(id)){
            qtable[id] = 0.0;
        }
        if(maxQ < qtable[id]) maxQ = qtable[id];
    }
    return maxQ;
}

bool QLearning::executeEpisode(State* initialState, int nMaxMoves){
    State* currentState = initialState;
    int moves = 0; 
    inactiveCounter = 0;
    while((!currentState->isGoal()) && (moves < nMaxMoves)){
        currentState = takeAction(currentState);
        if (currentState->isAnyBoxInDeadlock() or inactiveCounter > 20) {
            break;
        }
        moves ++;
    }
    //currentState->printGrid();

    return currentState->isGoal();
}

void QLearning::normalizeQ(){
    for (pair<string,double> qpair: qtable){
        qtable[qpair.first] = qpair.second / normalizer;
    }
}

void QLearning::train(int nEpochs, int nMaxSteps){
    bool found = false;
    for (int i = 0; i < nEpochs; i++){
        found = executeEpisode(initialState, nMaxSteps);
        if (found){
            this->epoch = this->epoch+1;
            //cout << "EPISODE " << i << ": I WON" << endl;
        }
        if ((i % 100 == 0)){
            //cout << "EPISODE " << i << endl;
        }
    }
    normalizeQ();
}

bool QLearning::thereIsASolution(int nMaxSteps){
    State* currentStep = initialState;
    int steps = 0;
    while(!currentStep->isGoal()){
        currentStep = takeSuboptimalAction(currentStep);
        steps++;
        if (steps > nMaxSteps) return false;
    }
    return true;
}


