#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <queue>
#include "State.h"

using namespace std;

class PriorityQueue {
    public:
    struct SmallerCost{
        bool operator()(State state1, State state2){
            return state1.getG() + state1.getH() < state2.getG() + state2.getH();
        }
    };

    priority_queue<State, std::vector<State>, SmallerCost> pq;
    
    PriorityQueue();
    State pop();
    void push(State state);
    bool empty();

    private:
    void lazyRemoval(State state);
};
#endif