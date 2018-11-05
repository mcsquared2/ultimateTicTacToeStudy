#pragma once
#include "Agent.h"

class MonteCarloAgent: public Agent {
public:
    MonteCarloAgent() ;
    Move getNextMove(Board * board) ;
    size_t chooseRandomMove(size_t ceil) ;
    BOARD_STATE randomGame(Board * board) ;
private:
    int games_per_move ;
    std::default_random_engine generator ;
} ;
 