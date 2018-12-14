#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "debug.h"

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

Board::Board(Board & b) {
    for ( int i = 0; i < 9; i++ ) {
        mGlobal_state[i] = b.mGlobal_state[i];
    }
    for ( int board = 0; board < 9; board++ ) {
        for ( int cell = 0; cell < 9; cell ++ ) {
            mLocal_states[board][cell] = b.mLocal_states[board][cell];
        }
    }

    mTurn = b.mTurn;
    mCurrentPlayer = b.mCurrentPlayer;
    mLast_move = b.mLast_move;
}

Board::Board(char arr[]) {
    int i = 0 ;
    // just for clarification, the i++ return i but increments it by one
    for (int b = 0; b < 9; b++) {
        mGlobal_state[b] = static_cast<BOARD_STATE>(arr[i++]) ;
    }
    for (int g = 0; g < 9; g++) {
        for (int c = 0; c < 9; c++) {
            mLocal_states[g][c] = arr[i++] ;
        }
    }
    mLast_move.board = arr[i++] ;
    mLast_move.cell = arr[i++] ;
    mSecond_last_move.board = arr[i++] ;
    mSecond_last_move.cell = arr[i++] ;
    mTurn = arr[i++] ;
    mCurrentPlayer = arr[i++] ;

}

std::string Board::DisplayString() {
    std::string state = "";
    state += "turn: " + std::to_string(mTurn) + " currentPlayer: " + std::to_string(mCurrentPlayer) + "\n";
    for ( int y = 0; y < 9; y++ ) {
        for ( int x = 0; x < 9; x++ ) {
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
    state += "Global State:\n";
    for (int i = 0; i < 9; i++) {
        state += board_state_char[mGlobal_state[i]] + " ";
        if (i % 3 == 2) {
            state += "\n";
        }
    }
    state += "\n";
    return state;
}

std::string Board::DisplayAvailableMoves() {
    std::string state = "";
    for ( int y = 0; y < 9; y++ ) {
        for ( int x = 0; x < 9; x++ ) {
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
            std::cout << "This char was in a board where it shouldn't: " << c << "\n";
            return LAST_BOARD_STATE;
    }
}

BOARD_STATE IsBoardWon(char board[9]){
    // Check horizontally
    for ( int i = 0; i < 9; i+=3 ) {
        if (board[i] != cell_marks[UNMARKED] && board[i] == board[i+1] && board[i+2] == board[i]){
            // std::cout << "local row " << i << " " << board[i] << "\n";
            return convertCharToState(board[i]);
        }
    }

    // Check Vertically
    for ( int i = 0; i < 3; i++ ) {
        if (board[i] != cell_marks[UNMARKED] && board[i] == board[i+3] && board[i+6] == board[i]){
            // std::cout << "local col " << i << " " <<  board[i] << "\n";
            
            return convertCharToState(board[i]);
        }
    }

    // Check diagonnaly down
    if(board[0] != cell_marks[UNMARKED] && board[0] == board[4] && board[4] == board[8]) {
        // std::cout << "local diag down " <<  board[0] << "\n";
        
        return convertCharToState(board[0]);
    }

    if(board[2] != cell_marks[UNMARKED] && board[2] == board[4] && board[4] == board[6]) {
        // std::cout << "local diag up " <<  board[2] << "\n";
        
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

BOARD_STATE Board::CheckGlobalBoardForWin() const {

     // Check horizontally
    for ( int i = 0; i < 9; i+=3 ) {
        if (
            (mGlobal_state[i] == X || mGlobal_state[i] == O) &&
            mGlobal_state[i] == mGlobal_state[i+1] &&
            mGlobal_state[i+2] == mGlobal_state[i]
        ){
            // std::cout << mGlobal_state[i] << "\n";
            return mGlobal_state[i];
        }
    }

    // Check Vertically
    for ( int i = 0; i < 3; i++ ) {
        if (
            (mGlobal_state[i] == X || mGlobal_state[i] == O) &&
            mGlobal_state[i] == mGlobal_state[i+3] &&
            mGlobal_state[i+6] == mGlobal_state[i]
        ){
            // std::cout << mGlobal_state[i] << "\n";
            
            return mGlobal_state[i];
        }
    }

    // Check diagonnaly down
    if(
        (mGlobal_state[0] == X || mGlobal_state[0] == O) &&
        mGlobal_state[0] == mGlobal_state[4] &&
        mGlobal_state[4] == mGlobal_state[8]
    ) {
            // std::cout << mGlobal_state[0] << "\n";
        
        return mGlobal_state[0];
    }

    if(
        (mGlobal_state[2] == X || mGlobal_state[2] == O) &&
        mGlobal_state[2] == mGlobal_state[4] &&
        mGlobal_state[4] == mGlobal_state[6]
    ) {
            // std::cout << mGlobal_state[2] << "\n";
        
        return mGlobal_state[2];
    }

    int marked_cells = 0;
    for (int i = 0; i < 9; i ++) {
        if (mGlobal_state[i] != UNFILLED) {
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
                if (mGlobal_state[board_index] == UNFILLED){
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
    }
    return moves;
}

bool Board::ApplyMove(Move m) {
    if ( m.board < 0 || m.board > 8 ) {
        std::cout << "Move: ApplyMove: Board " << m.board << " does not exist\n";
        return false;
    }
    if ( m.cell < 0 || m.cell > 8 ) {
        std::cout << "Move: ApplyMove: Cell " << m.cell << " does not exist\n";
        return false;
    }

    if (mGlobal_state[m.board] != UNFILLED) {
        // std::cout << "Move: Board is already filled\n";
        return false;
    }
    if ( mLocal_states[m.board][m.cell] == cell_marks[UNMARKED] ) {
        mLocal_states[m.board][m.cell] = cell_marks[mCurrentPlayer];
        mGlobal_state[m.board] = CheckLocalBoardForWin(m.board);
        mTurn++;
        mCurrentPlayer = (mCurrentPlayer + 1) % 2;
        mSecond_last_move = mLast_move;
        mLast_move = m;
        return true;
    }
    return false;
}

bool Board::UnMove(Move m) {
    if ( m.board < 0 || m.board > 8 ) {
        std::cout << "UnMove: Board " << m.board << " does not exist\n";
        return false;
    }

    if ( m.cell < 0 || m.cell > 8 ) {
        std::cout << "UnMove: Cell " << m.cell << " does not exist\n";
        return false;
    }

    

    if ( mLocal_states[m.board][m.cell] != cell_marks[UNMARKED] ) {
        mLocal_states[m.board][m.cell] = cell_marks[UNMARKED];
        mGlobal_state[m.board] = CheckLocalBoardForWin(m.board);
        mTurn--;
        mCurrentPlayer = (mCurrentPlayer + 1) % 2;
        mLast_move = mSecond_last_move;
        return true;
    }

    std::cout << 
        "Unmove: Position at " << m.board << ", " << m.cell << 
        " is already marked with a " << cell_marks[UNMARKED] << std::endl;
    return false;
}

void Board::UpdateGlobalState() {
    for (int i = 0; i < 9; i++) {
        mGlobal_state[i] = CheckLocalBoardForWin(i);
    }
}

int Board::GetTurn() {
    return mTurn;
}

int Board::GetCurrentPlayer() {
    return mCurrentPlayer ;
}

bool two_of_three (char a, char b, char c, int player) {
    char unmarked = cell_marks[UNMARKED], player_char = cell_marks[player];
    return (
        (
            a == player_char && (
                (a == b && c == unmarked) ||
                (a == c && b == unmarked) 
            )
        ) 
        || 
        (
            a == unmarked && 
            b == player_char && 
            c == b
        )
    );
}

bool two_of_three (BOARD_STATE a, BOARD_STATE b, BOARD_STATE c, int player) {
    BOARD_STATE player_state = static_cast<BOARD_STATE>(player);
    return (
        (
            a == player_state && (
                (a == b && c == UNFILLED) ||
                (a == c && b == UNFILLED) 
            )
        ) 
        || 
        (
            a == UNFILLED && 
            b == player_state && 
            c == b
        )
    );
}

int partials(const char board[9], int player) {
    int partials = 0;
    for (int i = 0; i < 3; i++) {
        if (two_of_three(board[i], board[i+3], board[i+6], player)) {
            partials++;
        }
        int k = 3*i;
        if (two_of_three(board[k], board[k+1], board[k+2], player)) {
            partials++;
        }

    } 
    if (two_of_three(board[0], board[4], board[8], player)) {
        partials++;
    }
    if (two_of_three(board[2], board[4], board[6], player)) {
        partials++;
    }
    return partials;
}

int partials(const BOARD_STATE board[9], int player) {
    int partials = 0;
    for (int i = 0; i < 3; i++) {
        if (two_of_three(board[i], board[i+3], board[i+6], player)) {
            partials++;
        }
        int k = 3*i;
        if (two_of_three(board[k], board[k+1], board[k+2], player)) {
            partials++;
        }

    } 
    if (two_of_three(board[0], board[4], board[8], player)) {
        partials++;
    }
    if (two_of_three(board[2], board[4], board[6], player)) {
        partials++;
    }
    return partials;
}

int Board::boardValue(
    int player, 
    int global_win_weight, 
    int global_partial_weight, 
    int local_partial_weight
) const {
    int global_win_count = 0, 
        global_partial_count = 0,
        local_partial_count = 0;  
    int other_player = (player + 1) % 2;
    BOARD_STATE b = CheckGlobalBoardForWin(); 
    if ( b == player ) {
        // std::cout << "Player gets a winning board!!!!!!\n";
        return 1e6-1; 
    }
    else if (b == other_player) {
        // std::cout << "Opponents is going to get a winning board???????????\n";
        return -1e6+1 ;
    }
    else if (b == TIE){
        return 0;
    }
    // return 0;
    for (int i = 0; i < 9; i++) {
        if (mGlobal_state[i] == player) {
            global_win_count++;
        } else if (mGlobal_state[i] == other_player) {
            global_win_count--;
        } else if (mGlobal_state[i] == UNFILLED) {
            local_partial_count += partials(mLocal_states[i], player);
            local_partial_count -= partials(mLocal_states[i], other_player);
        }
    }
    global_partial_count = partials(mGlobal_state, player);
    local_partial_count -= partials(mGlobal_state, other_player);    
    // std::cout << "Calculating/////////////////////////////////////////////////\n";
    // std::cout << "global_win_weight: " << global_win_count << std::endl;
    // std::cout << "global_win_value " << global_win_weight * global_win_count / global_win_total <<
    //     "\nglobal_partial_value " << global_partial_weight * global_partial_count / partial_total <<
    //     "\nlocal_partial_value " << local_partial_weight * local_partial_count / local_partial_total << "\n";    
    return global_win_weight * global_win_count + 
        global_partial_weight * global_partial_count +
        local_partial_weight * local_partial_count;
}

int Board::getBoardArrSize() {
    // global board state(9) + local board state (81) + last move(2) + second last move (2) + turn(1) + currentplayer (1) = 96
    return 96 ;

}


void Board::Board2Arr(char arr[]) {
    int i = 0 ;
    // just for clarification, the i++ return i but increments it by one
    for (int b = 0; b < 9; b++) {
        arr[i++] = static_cast<char>(mGlobal_state[b]) ;
    }
    for (int g = 0; g < 9; g++) {
        for (int c = 0; c < 9; c++) {
            arr[i++] = mLocal_states[g][c] ;
        }
    }
    arr[i++] = mLast_move.board ;
    arr[i++] = mLast_move.cell ;
    arr[i++] = mSecond_last_move.board ;
    arr[i++] = mSecond_last_move.cell ;
    arr[i++] = mTurn ;
    arr[i++] = mCurrentPlayer ;
}
