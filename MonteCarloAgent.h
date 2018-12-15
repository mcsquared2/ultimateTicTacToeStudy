#pragma once
#include "Agent.h"

class MonteCarloAgent: public Agent {
public:
    MonteCarloAgent() ;
    Move getNextMove(Board * board) ;
    size_t chooseRandomMove(size_t ceil) ;
    BOARD_STATE randomGame(Board * board) ;
    double gettime() ;
    void resettime() {mtime = 0;};
protected:
    int games_per_move ;
    std::default_random_engine generator ;
    int mtime ;
    // std::uniform_int_distribution distributions[8] ;
} ;
 