#include "Board.h"
#include <iostream>
#include <stdlib.h>

Board::Board() {
    for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            mLocal_states[i][j] = cell_marks[UNMARKED];
        }
    }

    for(int j = 0; j < 9; j++) {
        mGlobal_state[j] = UNFILLED;
    }

    mTurn = 1;
    mCurrentPlayer = 0;
}

Board::Board(std::string& board_state) {
    int c_index = 0;
    int b, c;
    for (unsigned int i = 0; i < board_state.size(); i++) {
        if (!isspace(board_state[i])) {
            if (c_index < 81) {
                b = (c_index % 9) / 3 + (c_index / 27) * 3;
                c = (c_index % 3) + ((c_index / 9) % 3 * 3);
                mLocal_states[b][c] = board_state[i];
                c_index ++;
            } else {
                // if (board:state.substr(i, i+3) == "t: ") {
                //     // mTurn = atoi()
                // }
            }

        }

    }

    UpdateGlobalState();

    mTurn = 1;
    mCurrentPlayer = 0;


}

std::string Board::DisplayString() {
    std::string state = "";
    for ( int y = 0; y < 9; y++ ) {
        for ( int x = 0; x < 9; x++ ) {
            // std::cout << mLocal_states[y/3 + x/3][3*(y%3) + x%3];
            state += std::string(1, mLocal_states[(y/3)*3 + x/3][3*(y%3) + x%3]) + " ";
            if (x%3 == 2) {
                state += " ";
            }
        }
        state += "\n" ;
        if (y%3 == 2){
            state += "\n";
        }
    }
    // state += "t: " + std::to_string(mTurn) + " currentPlayer: " + std::to_string(mCurrentPlayer);
    return state;
}

std::string Board::DisplayAvailableMoves() {
    std::string state = "";
    for ( int y = 0; y < 9; y++ ) {
        for ( int x = 0; x < 9; x++ ) {
            // std::cout << mLocal_states[y/3 + x/3][3*(y%3) + x%3];
            state += std::string(1, mLocal_states[y/3 + x/3][3*(y%3) + x%3]) + " ";
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

BOARD_STATE convertCharToState(char c) {
    switch (c) {
        case 'X':
            return X;
        case 'O':
            return O;
        case '-':
            return UNFILLED;
        case 'T':
            return TIE;
        default:
            return LAST_BOARD_STATE;
    }
}

BOARD_STATE IsBoardWon(char board[]){
    // Check horizontally
    for ( int i = 0; i < 9; i+=3 ) {
        if (board[i] != cell_marks[UNMARKED] && board[i] == board[i+1] && board[i+2] == board[i]){
            return convertCharToState(board[i]);
        }
    }

    // Check Vertically
    for ( int i = 0; i < 3; i++ ) {
        if (board[i] != cell_marks[UNMARKED] && board[i] == board[i+3] && board[i+6] == board[i]){
            return convertCharToState(board[i]);
        }
    }

    // Check diagonnaly down
    if(board[0] != cell_marks[UNMARKED] && board[0] == board[5] && board[5] == board[8]) {
        return convertCharToState(board[0]);
    }

    if(board[2] != cell_marks[UNMARKED] && board[0] == board[5] && board[5] == board[6]) {
        return convertCharToState(board[2]);
    }

    int marked_cells = 0;
    for (int i = 0; i < 9; i ++) {
        if (board[i] == cell_marks[X] || board[i] == cell_marks[O]) {
            marked_cells++;
        }
    }
    if (marked_cells == 9) {
        return TIE;
    }

    return UNFILLED;
}

BOARD_STATE Board::CheckLocalBoardForWin(int local_board_position) {
    return IsBoardWon(mLocal_states[local_board_position]);
}

BOARD_STATE Board::CheckGlobalBoardForWin() {
     // Check horizontally
    for ( int i = 0; i < 9; i+=3 ) {
        if (
            (mGlobal_state[i] == X || mGlobal_state[i] == O) &&
            mGlobal_state[i] == mGlobal_state[i+1] &&
            mGlobal_state[i+2] == mGlobal_state[i]
        ){
            return convertCharToState(mGlobal_state[i]);
        }
    }

    // Check Vertically
    for ( int i = 0; i < 3; i++ ) {
        if (
            (mGlobal_state[i] == X || mGlobal_state[i] == O) &&
            mGlobal_state[i] == mGlobal_state[i+3] &&
            mGlobal_state[i+6] == mGlobal_state[i]
        ){
            return convertCharToState(mGlobal_state[i]);
        }
    }

    // Check diagonnaly down
    if(
        (mGlobal_state[0] == X || mGlobal_state[0] == O) &&
        mGlobal_state[0] == mGlobal_state[5] &&
        mGlobal_state[5] == mGlobal_state[8]
    ) {
        return convertCharToState(mGlobal_state[0]);
    }

    if(
        (mGlobal_state[2] == X || mGlobal_state[2] == O) &&
        mGlobal_state[0] == mGlobal_state[5] &&
        mGlobal_state[5] == mGlobal_state[6]
    ) {
        return convertCharToState(mGlobal_state[2]);
    }

    int marked_cells = 0;
    for (int i = 0; i < 9; i ++) {
        if (mGlobal_state[i] == X || mGlobal_state[i] == O) {
            marked_cells++;
        }
    }
    if (marked_cells == 9) {
        return TIE;
    }

    return UNFILLED;
}

std::vector<Move> Board::GetCurrentMoves() {
    std::vector<Move> moves;
    if (mTurn == 1) {
        for (int board_index = 0; board_index < 9; board_index++) {
            for (int cell_index = 0; cell_index < 9; cell_index++) {
                Move m;
                m.board = board_index;
                m.cell = cell_index;
                moves.push_back(m);
            }
        }
    } else {
        if (mGlobal_state[mLast_move.cell] == UNFILLED) {
            for (int cell = 0; cell < 9; cell++) {
                if (mLocal_states[mLast_move.cell][cell] == cell_marks[UNMARKED]) {
                    Move m;
                    m.board = mLast_move.cell;
                    m.cell = cell;
                    moves.push_back(m);
                }
            }
        } else {
           for (int board_index = 0; board_index < 9; board_index++) {
                for (int cell_index = 0; cell_index < 9; cell_index++) {
                    if (mLocal_states[board_index][cell_index] == cell_marks[UNMARKED]) {
                        Move m;
                        m.board = board_index;
                        m.cell = cell_index;
                        moves.push_back(m);
                    }
                }
            }
        }
    }
    return moves;
}

bool Board::ApplyMove(Move m) {
    if (mLocal_states[m.board][m.cell] == cell_marks[UNMARKED]) {
        mLocal_states[m.board][m.cell] = cell_marks[mCurrentPlayer];
        mGlobal_state[m.board] = CheckLocalBoardForWin(m.board);
        mTurn++;
        mCurrentPlayer = (mCurrentPlayer + 1) % 2;
        return true;
    }
    return false;
}

void Board::UpdateGlobalState() {
    for (int i = 0; i < 9; i++) {
        mGlobal_state[i] = CheckLocalBoardForWin(i);
    }
}
