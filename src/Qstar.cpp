#include "QStar.h"

initializer_list<QSMove> allQSMoves = { QUP, QDOWN, QRIGHT, QLEFT, ASTAR};

QStar::QStar(State* initialState, double alpha, double gamma, double epsilon, double decayFactor){
    this->initialState = initialState;
    this->alpha = alpha;
    this->gamma = gamma;
    this->epsilon = epsilon;
    this->decayFactor = decayFactor;
    this->random = Random();
}

double QStar::getReward(State* state, Action* action){
    State* nextState =  action->getQSState(state);
    QState* qstate = new QState(state,action);
    string id = qstate->getId();
    if(visited.count(id) > 0) return -1.0;
    if((!nextState->equals(state))){
        if(nextState->isAnyBoxInDeadlock()) return -10.0;
        if (nextState->isGoal()) return 100.0;
        if (Heuristic::getNBoxes(state) > Heuristic::getNBoxes(nextState)) return 20.0;
        //if(nextState->movedBox && state->movedBox) return 10.0;
        if(nextState->movedBox) return 5.0;
        //if (Heuristic::getValue(state,2,1) > Heuristic::getValue(nextState,2,1)) return 10.0; // this does not guarantee pushing a box
        return -10.0;
    }
    return -1.0;
}

void QStar::getValidActionsAndRewards(State* state){
    this->validActions.clear();
    for (QSMove move: allQSMoves){
        Action* a = new Action(move);
        double reward = getReward(state,a);
        if (reward != -1.0) {
            this->validActions.push_back(make_pair(a, reward));
        }
    }
}

actR QStar::chooseActionWithPolicy(State* state){
    double maxQ = -100000000;
    actR next;
    for(actR a: this->validActions){
        QState* qstate = new QState(state, a.first);
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

actR QStar::getAction(State* state, double epsilon, double decayFactor){
    double probablity = random.getProbablity();
    double greedy = epsilon * pow(decayFactor, epoch);
    if (probablity < greedy){
        int index = random.getBetweenRange(0,validActions.size()-1);
        return this->validActions[index];
    }

    return chooseActionWithPolicy(state);
}

State* QStar::takeAction(State* state){
    actR actionNreward = getAction(state,epsilon,decayFactor);
    Action* action = actionNreward.first;
    double reward = actionNreward.second;
    if (reward == 0.0) inactiveCounter++;
    else inactiveCounter = 0;
    State* nextState = action->getQSState(state);
    getValidActionsAndRewards(nextState);
    if (validActions.size() == 0) return state;
    double nextMaxQ = getNextMaxQ(nextState);
    
    QState* qstate = new QState(state,action);
    string id = qstate->getId();
    visited.insert(id);
    qtable[id] = qtable[id] + alpha * (reward + gamma * nextMaxQ - qtable[id]);
    
    if (qtable[id] > normalizer) normalizer = qtable[id];
    
    return nextState;
}

State* QStar::takeSuboptimalAction(State* state){
    getValidActionsAndRewards(state);
    Action* action = chooseActionWithPolicy(state).first;
    State* nextState = action->getQSState(state);
    return nextState;
}

double QStar::getNextMaxQ(State* nextState){
    double maxQ = -1000000;
    for(actR actionsNRewards: validActions){
        QState* qs = new QState(nextState,actionsNRewards.first);
        string id = qs->getId();
        if (!qtable.count(id)){
            qtable[id] = 0.0;
        }
        if(maxQ < qtable[id]) maxQ = qtable[id];
    }
    return maxQ;
}

bool QStar::executeEpisode(State* initialState, int nMaxMoves){
    State* currentState = initialState;
    int moves = 0; 
    inactiveCounter = 0;
    visited.clear();
    getValidActionsAndRewards(currentState);
    while((!currentState->isGoal()) && (moves < nMaxMoves)){
        State* nextState = takeAction(currentState);
        if (nextState->equals(currentState)) break;
        currentState = nextState;
        if (currentState->isAnyBoxInDeadlock()) {
            break;
        }
        moves ++;
    }
    //currentState->printGrid();

    return currentState->isGoal();
}

void QStar::normalizeQ(){
    for (pair<string,double> qpair: qtable){
        qtable[qpair.first] = qpair.second / normalizer;
    }
}

void QStar::train(int nEpochs, int nMaxSteps){
    bool found = false;
    for (int i = 0; i < nEpochs; i++){
        found = executeEpisode(initialState, nMaxSteps);
        if (found){
            this->epoch = this->epoch+1;
            cout << "EPISODE " << i << ": I WON" << endl;
            this->consecutiveWins+=1;
        } else{
            consecutiveWins = 0;
        }
        if ((i % 100 == 0)){
            cout << "EPISODE " << i << endl;
        }
        if (consecutiveWins > 5) break;
    }
    //normalizeQ();
}

bool QStar::thereIsASolution(int nMaxSteps){
    State* currentStep = initialState;
    int steps = 0;
    while(!currentStep->isGoal()){
        currentStep = takeSuboptimalAction(currentStep);
        steps++;
        if (steps > nMaxSteps) return false;
    }
    return true;
}


