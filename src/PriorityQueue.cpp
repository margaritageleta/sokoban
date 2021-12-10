#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(){
}

void PriorityQueue::push(State* state){
    pq.push(state);
}

State* PriorityQueue::pop(){
    State* s = pq.top();
    pq.pop();
    //lazyRemoval(s);
    return s;
}

bool PriorityQueue::empty(){
    return pq.empty();
}

void PriorityQueue::lazyRemoval(State* state){
    priority_queue<State*, std::vector<State*>, GreaterCost> pq2;
    while (!pq.empty()){
        State* s = pq.top();
        pq.pop();
        if (! s->equals(state)) pq2.push(s);
    }
    pq = pq2;
}





