#include <iostream>
#include <random>
#include "Agent.h"

Agent::Agent() {

}

RandomAgent::RandomAgent(){

}

Move RandomAgent::getNextMove( Board  *board ) {
    Board b = *board;
    // Board b; 
    std::vector<Move> moves = b.GetCurrentMoves();
    if (moves.size() == 0) {
        exit(1);
    }

    size_t r = rand() % moves.size();
    return moves[r];
}
