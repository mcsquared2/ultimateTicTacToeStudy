#include "MonteCarloAgent.h"
#include <iostream> 

void playGame(Agent *p1, Agent *p2, int &p1_wins, int &p2_wins, int &ties, bool displayGame) {
    Board board;
    while ( board.CheckGlobalBoardForWin() == UNFILLED ) {
        // std::cout << board.DisplayString() << std::endl;
        Move nextMove ;
        if ( board.GetTurn() % 2 == 1 ) {
            nextMove = p1->getNextMove(&board) ;
        } else {
            nextMove = p2->getNextMove(&board) ;
        }
        board.ApplyMove(nextMove) ;
        if (displayGame) std::cout << board.DisplayString() ;
    }

    // if (displayGame) std::cout << board.DisplayString() ;
    // std::cout << "The winner is " << board.CheckGlobalBoardForWin() << "\n";
    // std::cout << "The winner is " << board_state_char[board.CheckGlobalBoardForWin()] << "\n";
    switch (board.CheckGlobalBoardForWin()) {
        case X:
            p1_wins ++ ;
            break;
        case O:
            p2_wins++ ;
            break;
        case TIE:
            ties++ ;
            break;
        default:
            std::cout << "Somewhere something went wrong. We got an invalid win state when checking.";
    }
}

void testAgainstRandom(Agent * monte, int games, bool display) {
    int p1wins = 0,
        p2wins = 0,
        ties = 0 ;
    Agent * randA = new RandomAgent();
    std::cout << "Monte goes first" << std::endl ;
    for (int i = 0; i<games; i++) {
        playGame(monte, randA, p1wins, p2wins, ties, display) ;
    }
    std::cout << "w: " << p1wins << " l: " << p2wins << " t: " << ties << std::endl ;
    std::cout << "Monte goes second" << std::endl ;
    p1wins = p2wins = ties = 0 ;
    for (int i = 0; i<games; i++) {
        playGame(randA, monte, p1wins, p2wins, ties, display) ;
    }
    std::cout << "w: " << p2wins << " l: " << p1wins << " t: " << ties << std::endl ;
    delete randA ;

}

int main(int argc, char * argv[]) {
    
    srand( time(0) );
    bool display = false;
    int games = 1 ;
    for (int i = 0; i < argc; i++) {
        std::string a(argv[i]);
        if (a == "-g") {
            i++ ;
            games = atoi(argv[i]) ;
        } else if (a == "-dg") {
            display = true ;
        }
    }

    // play where Monte carlo goes first
    Agent * monte = new MonteCarloAgent() ;
    testAgainstRandom(monte, games, display) ;
    delete monte ;
    return 0;
}