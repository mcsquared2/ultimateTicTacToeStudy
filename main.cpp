#include <iostream>
#include "Board.h"

int main() {

    // Board b;
    // std::cout << b.DisplayString();
    // std::vector<Move> moves = b.GetCurrentMoves();
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            Board b;
            Move m;
            m.board = y;
            m.cell = x;
            b.ApplyMove(m);
            std::cout << "Applied move " << y << ", " << x << "\n";
            std::cout << b.DisplayString();
        }
    }

    // std::cout << "These are the starting moves: \n\t";
    // for (size_t i = 0; i < moves.size(); i++) {
    //     std::cout << moves[i].board << "," << moves[i].cell << " " ;
    //     if (i % 9 == 8) {
    //         std::cout << "\n\t";
    //     }
    // }
    // Move m;
    // m.board = 1;
    // m.cell = 0;
    // b.ApplyMove(m);
    // moves = b.GetCurrentMoves();
    // std::cout << b.DisplayString();
    // std::cout << "These are the moves after X plays on 1,0: \n\t";
    // for (size_t i = 0; i < moves.size(); i++) {
    //     std::cout << moves[i].board << "," << moves[i].cell << " " ;
    //     if (i % 9 == 8) {
    //         std::cout << "\n\t";
    //     }
    // }
    // for (int i = 0; i < 9; i++) {
    //     int arr[9];
    //     b.GetLocalBoardIndices(i, arr);
    //     std::cout << i << ": ";
    //     for (int j = 0; j < 9; j++) {
    //         std::cout << arr[j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}