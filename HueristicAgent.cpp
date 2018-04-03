#include "HueristicAgent.h"
#include <iostream>
#include <random>
HueristicAgent::HueristicAgent(int player, int depth, double global_win_weight, double global_partial_weight, double local_partial_weight)
    :mPlayer(player), 
    mDepth(depth), 
    mGlobal_win_weight(global_win_weight), 
    mGlobal_partial_weight(global_partial_weight), 
    mLocal_partial_weight(local_partial_weight),
    mTime(0.0) 
{

}

Move HueristicAgent::getNextMove(Board *board) {
    clock_t t0 = clock( );
    Move m = alpha_beta_search(board, mPlayer);
    clock_t t1 = clock( );
    mTime += (double)(t1 - t0) / CLOCKS_PER_SEC;
    return m;
}

Move HueristicAgent::alpha_beta_search(Board *board, int player) {
    Move m;
    max_value(*board, player, mDepth, -1e6, 1e6, m);
    // std::cout << "Move to apply: " << m.board << "->" << m.cell << std::endl;
    return m;
}


double HueristicAgent::max_value(Board & board, int player, int depth, double alpha, double beta, Move & move_delta ){
    if (terminal_test(board, player) || depth <= 0) {
        if (depth == 5) {
            std::cout << "Are we getting to the end?\n";
        }
        return utility(board, player);
    }
    Board b(board);
    std::vector<Move> moves = b.GetCurrentMoves();
    // if (player == 1){
    //     std::sort(moves.begin(), moves.end(), sortMax);
    // } else {
    //     std::sort(moves.begin(), moves.end(), sortMin);
    // }
    double best_heuristic = -1e6;
    std::vector<size_t> lowest_moves;
    for (size_t i= 0; i < moves.size(); i++) {
        b.ApplyMove(moves[i]);
        double new_heuristic = min_value(b, player, depth - 1, alpha, beta);
        b.UnMove(moves[i]);
        if (new_heuristic > best_heuristic) {
            move_delta = moves[i];
            best_heuristic = new_heuristic;
            lowest_moves.clear();
            lowest_moves.push_back(i);
        }
        else if (new_heuristic == best_heuristic) {
            lowest_moves.push_back(i);
        }

        if (best_heuristic >= beta ) {
            // std::cout << "size: " << lowest_moves.size() << std::endl;
            size_t r = rand() % lowest_moves.size();
            // // std::cout << i << " " << moves.size() << " " << lowest_moves[r] <<  std::endl;
            move_delta = moves[lowest_moves[r]];
            
            return best_heuristic;
        }
        alpha = alpha < best_heuristic ? alpha : best_heuristic;

    }
    move_delta = moves[lowest_moves[rand() % lowest_moves.size()]];
    return best_heuristic;
}

double HueristicAgent::min_value(Board &board, int player, int depth, double alpha, double beta){

    if (terminal_test(board, player) || depth <= 0) {
        return utility(board, player);
    }
    //   int otherPlayer = player == 1 ? 0 : 1;
    Board b(board);
    std::vector<Move> moves = b.GetCurrentMoves();

    //   if (otherPlayer == 1){
    //       std::sort(moves.begin(), moves.end(), sortMax);
    //   } else {
    //       std::sort(moves.begin(), moves.end(), sortMin);
    //   }

    double best_heuristic = 1e6;
    for (size_t i= 0; i < moves.size(); i++) {
        b.ApplyMove(moves[i]);
        Move move;
        double new_heuristic = max_value(b, player, depth - 1, alpha, beta, move);
        b.UnMove(moves[i]);
        best_heuristic = new_heuristic > best_heuristic ? best_heuristic : new_heuristic;

        if (best_heuristic <= alpha) {
            return best_heuristic;
        }
        beta = beta < best_heuristic ? beta : best_heuristic;

    }
    return best_heuristic;
}


double HueristicAgent::utility(const Board & board, int player) {
    double p = board.boardValue(player, mGlobal_win_weight, mGlobal_partial_weight, mLocal_partial_weight); 
    // std::cout << p << std::endl;
    return p;
}
bool HueristicAgent::terminal_test(const Board & board, int player) {
    return board.CheckGlobalBoardForWin() != UNFILLED;
}

