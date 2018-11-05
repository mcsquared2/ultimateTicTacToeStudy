#include "MonteCarloAgent.h"

int METHOD = 1 ;

MonteCarloAgent::MonteCarloAgent () {
    // std::random_device rd() ;
    games_per_move = 10 ;
    generator = std::default_random_engine( time( 0 )) ;
}

// char WIN = 0 ;
// char LOSS = 1 ;
// char TIE = 2 ;

Move MonteCarloAgent::getNextMove(Board * board) {
    std::vector<Move> moves = board->GetCurrentMoves() ;
    std::vector<int> winVec ;
    std::vector<int> tieVec ;

    for (size_t i = 0; i < moves.size(); i++) {
        int wins, ties = 0 ;
        Board copy(*board) ;
        copy.ApplyMove(moves[i]) ;
        for (int g = 0; g < games_per_move; g++) {
            BOARD_STATE result = randomGame(&copy) ;
            if (result == board->GetCurrentPlayer()) {
                wins++ ;
            } else if (result == TIE) {
                ties++ ;
            }
        }
        winVec.push_back(wins) ;
        tieVec.push_back(ties) ;
    }
    size_t best = 0;
    for (size_t i = 1; i < winVec.size(); i++) {
        if (
            // There are more wins
            winVec[best] < winVec[i] ||
            // wins for both are the same, but i has more ties.
            ( winVec[best] == winVec[i] && tieVec[best] < tieVec[i] )
        ) {
            best = i ;
        } 
    } 
    return moves[best] ;
}

size_t MonteCarloAgent::chooseRandomMove(size_t ceil) {
    std::uniform_int_distribution<size_t> distribution(0,ceil) ;
    return distribution(generator) ;
}

BOARD_STATE MonteCarloAgent::randomGame(Board * board) {
    Board copy(*board) ;
    std::vector<Move> moves ;
    BOARD_STATE state = copy.CheckGlobalBoardForWin() ;
    while (state == UNFILLED) {
        moves.clear() ;
        moves = copy.GetCurrentMoves() ;
        size_t moveIndex = chooseRandomMove(moves.size()-1) ;
        copy.ApplyMove(moves[moveIndex]) ;
        state = copy.CheckGlobalBoardForWin() ;
    }
    return state ;
} 