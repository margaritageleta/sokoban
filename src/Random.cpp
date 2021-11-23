#include "Random.h"

double Random::getProbablity(){
    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<double> r(0,1);
    return r(rng);
}

int Random::getBetweenRange(int from, int to){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<int> i(from,to);
    return i(rng);
}
