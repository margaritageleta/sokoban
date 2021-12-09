#include <random>

using namespace std;

class Random{
    public:
    mt19937 rng;
    uniform_real_distribution<double> r;
    Random();
    double getProbablity();
    int getBetweenRange(int from, int to);
};

