#include "Board.h"
#include <iostream>

Board::Board() {
    for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            local_states[i][j] = marks[UNMARKED];
        }
    }
    for(int j = 0; j < 9; j++) {
        global_state[j] = marks[UNMARKED];
    }
}

std::string Board::DisplayString() {
    std::string state = "";
    for ( int y = 0; y < 9; y++ ) {
        for ( int x = 0; x < 9; x++ ) {
            // std::cout << local_states[y/3 + x/3][3*(y%3) + x%3];
            state += std::string(1, local_states[y/3 + x/3][3*(y%3) + x%3]) + " ";
            if (x%3 == 2) {
                state += " ";
            }
        }
        state += "\n" ;
        if (y%3 == 2){
            state += "\n";
        }
    }
    return state;
}

// char IsBoardWon(char board*){
//     // Check horizontally
//     for ( int i = 0; i < 9; i+=3 ) {
//         if (board[i] != marks[UNMARKED] && board[i] == board[i+1] && board[i+2] == board[i]){
//             return board[i];
//         }
//     }

//     // Check Vertically
//     for ( int i = 0; i < 3; i++ ) {
//         if (board[i] != marks[UNMARKED] && board[i] == board[i+3] && board[i+6] == board[i]){
//             return board[i];
//         }
//     }

//     // Check diagonnaly down
//     if(board[0] != marks[UNMARKED] && board[0] == board[5] && board[5] == board[8]) {
//         return board[0];
//     }

//     if(board[2] != marks[UNMARKED] && board[0] == board[5] && board[5] == board[6]) {
//         return board[2];
//     }
//     return marks[UNMARKED];
// }

char CheckLocalBoardForWin(int local_board_position) {
    
}