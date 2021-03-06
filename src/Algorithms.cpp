#include "Algorithms.h"

State* Algorithms::AStar(State* state, int W){

    if (state->isGoal()) return state;
    state->W = W;
    PriorityQueue frontier = PriorityQueue();
    set<string> visited;
    frontier.push(state);

    while (!frontier.empty()){
        State* currentState = frontier.pop();
        visited.insert(currentState->getId());
        
        if (currentState->isGoal()) return currentState;
        vector<State*> children = Action::getNextStates(currentState);
        for (int i=0; i<children.size();i++){
            State* child = children[i];
        
            if ((visited.count(child->getId()) == 0) && (!child->equals(currentState)) && (!child->isAnyBoxInDeadlock())){
                frontier.push(child);
            }
        }

    }
    return nullptr;

}

State* Algorithms::AStarSubRoutine(State* state, int W){
    if (state->isGoal()) return state;
    state->W = W;
    PriorityQueue frontier = PriorityQueue();
    set<string> visited;

    frontier.push(state);
    int currentBoxes = Heuristic::getNBoxes(state);

    while (!frontier.empty()){
        State* currentState = frontier.pop();
        visited.insert(currentState->getId());
        
        if (currentState->isSubGoal(currentBoxes)){
            if (Algorithms::isGoodStep(currentState, W)) return currentState;
        }
        vector<State*> children = Action::getNextStates(currentState);
        for (int i=0; i<children.size();i++){
            State* child = children[i];
        
            if ((visited.count(child->getId()) == 0) && (!child->equals(currentState)) && (!child->isAnyBoxInDeadlock())){
                frontier.push(child);
            }
        }

    }
    return nullptr;
}

bool Algorithms::isGoodStep(State* state, int W){
    if (state->isGoal()) return true;
    state->W = W;
    PriorityQueue frontier = PriorityQueue();
    set<string> visited;

    frontier.push(state);
    int currentBoxes = Heuristic::getNBoxes(state);

    while (!frontier.empty()){
        State* currentState = frontier.pop();
        visited.insert(currentState->getId());
        
        if (currentState->isSubGoal(currentBoxes)){
            return true;
        }
        vector<State*> children = Action::getNextStates(currentState);
        for (int i=0; i<children.size();i++){
            State* child = children[i];
        
            if ((visited.count(child->getId()) == 0) && (!child->equals(currentState)) && (!child->isAnyBoxInDeadlock())){
                frontier.push(child);
            }
        }

    }
    return false;
}

QLearning* Algorithms::QLearningAlg(State* state, double alpha,double gamma,double epsilon){
    double decayFactor = 0.999;
    QLearning* ql = new QLearning(state, alpha, gamma, epsilon, decayFactor);
    int iterations = 0;
    while(!ql->thereIsASolution(100) && iterations < 1000){
        //cout << "NO SOLUTION YET" << endl;
        ql->train(1000,1000);
        iterations += 1;
    }
    
    return ql;
}

QStar* Algorithms::QStarAlg(State* state, int W, double alpha,double gamma,double epsilon){
    double decayFactor = 0.999;
    QStar* qs = new QStar(state, alpha, gamma, epsilon, decayFactor);
    int iterations = 0;
    bool solutionYet = false;
    while(!solutionYet && iterations < 1000){
        qs->train(1000,1000);
        iterations += 1;
        solutionYet = qs->thereIsASolution(100);
        //if (!solutionYet) cout << "NO SOLUTION YET" << endl;
    }
    
    return qs;
}
