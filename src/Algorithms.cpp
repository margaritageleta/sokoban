#include "Algorithms.h"
#include <iostream>


using namespace std;
typedef pair<int, int> coord2D;



State Algorithms::AStar(State state){
    
    if (state.isGoal()) return state;
    
    PriorityQueue frontier = PriorityQueue();
    set<string> visited;
    frontier.push(state);
    while (!frontier.empty()){
        state = frontier.pop();
        visited.insert(state.getId());
        //debug
        //do{} while (cin.get() != '\n');
        state.printGrid();
        if (state.isGoal()) return state;
        vector<State> children = Action::getNextStates(state);
        for (int i=0; i<children.size();i++){
            State child = State::create(children[i], &state);
        
            if ((visited.count(child.getId()) == 0) && (!child.equals(state)) && (!child.isAnyBoxInFreeCorner())){
                frontier.push(child);
            } else {
                //debug
                //if ((visited.count(child.getId()) != 0)) cout << "branch pruned:: already visited" << endl;
                //else if (child.equals(state)) cout << "branch pruned:: not moving" << endl;
                //else if (child.isAnyBoxInFreeCorner())cout << "branch pruned:: box going to corner" << endl;
            }
        }

    }
    State null;
    return null;

}