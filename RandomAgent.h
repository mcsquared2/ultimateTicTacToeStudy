#include "Agent.h"

class RandomAgent: public Agent {
public:
    RandomAgent();
    void getNextMove(std::vector<Move>& moves);
private:
    std::default_random_engine generator ;
}
