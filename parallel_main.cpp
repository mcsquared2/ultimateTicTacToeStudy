#include "MonteCarloParallelAgent.h"
#include <iostream> 
#include <mpi.h>
#include <string> 
#define MCW MPI_COMM_WORLD

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

void p2screen(int rank, std::string s) {
    if (rank == 0) std::cout <<  s ;
}

int playParallelGame(
        Agent *p1, 
        Agent *p2, 
        int &p1_wins, 
        int &p2_wins, 
        int &ties, 
        bool displayGame, 
        int rank,
        int size, 
        int & turns
) {
    Board board;
    int finished = 0 ;
    int finishedFlag = 0 ;
    MPI_Status mystatus ;
    int sharedMove[2] ; 
    while ( board.CheckGlobalBoardForWin() == UNFILLED ) {
        // std::cout << board.DisplayString() << std::endl;
        Move nextMove ;
        // MPI_Barrier(MCW) ;
        if ( board.GetTurn() % 2 == 1 ) {
            // p2screen(rank, "We are getting a move from monte!\n") ;
            nextMove = p1->getNextMove(&board) ;
            // p2screen(rank, std::to_string(nextMove.board) + " " + std::to_string(nextMove.cell) + "\n") ;
        } else {
            nextMove = p2->getNextMove(&board) ;
        }
        sharedMove[0] = nextMove.board ;
        sharedMove[1] = nextMove.cell ;
        MPI_Bcast(sharedMove, 2, MPI_INT, 0, MCW) ;
        nextMove.board = sharedMove[0] ;
        nextMove.cell = sharedMove[1] ;
        board.ApplyMove(nextMove) ;
        if (displayGame) p2screen( rank, board.DisplayString() ) ;
    }

    // if (displayGame) std::cout << board.DisplayString() ;
    // std::cout << "The winner is " << board.CheckGlobalBoardForWin() << "\n";
    // std::cout << "The winner is " << board_state_char[board.CheckGlobalBoardForWin()] << "\n";
    turns = board.GetTurn() ;
    if (rank == 0) {
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
                p2screen( rank, "Somewhere something went wrong. We got an invalid win state when checking." ) ;
        }
    }
    return board.CheckGlobalBoardForWin() ;
}

void testAgainstRandom(Agent * monte, int games, bool display) {
    int p1wins = 0,
        p2wins = 0,
        ties = 0 ;
    Agent * randA = new RandomAgent();
    std::cout << "Monte goes first" << std::endl ;
    for (int i = 0; i<games; i++) {
        dynamic_cast<MonteCarloAgent*>(monte)->resettime() ;
        playGame(monte, randA, p1wins, p2wins, ties, display) ;
        std::cout << "monte time " << dynamic_cast<MonteCarloAgent*>(monte)->gettime() << std::endl ;
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


void testAgainstRandom(Agent * monte, int games, bool display, int rank, int size) {
    int p1wins = 0,
        p2wins = 0,
        ties = 0 ;
    Agent * randA = new RandomAgent();
    int turns, winturns, tieturns, lossturns, totalturns = 0 ;
    p2screen(rank, "Monte goes first\n" ) ;
    for (int i = 0; i<games; i++) {
        // dynamic_cast<MonteCarloAgent*>(monte)->resettime() ;
        int result = playParallelGame(monte, randA, p1wins, p2wins, ties, display, rank, size, turns) ;
        switch (result) {
            case X: 
                winturns += turns ;
                break ;
            case O:
                lossturns += turns ;
                break ;
            case TIE:
                tieturns += turns ;
                break ;
            default:
                p2screen(rank, "Result is invalid!\n") ;
        }
        totalturns += turns ;
        // double time = dynamic_cast<MonteCarloAgent*>(monte)->gettime() ;
        // p2screen(rank, "monte time " + std::to_string( time ) + "\n" ) ;
    }
    p2screen(
        rank, 
        "w: " + std::to_string(p1wins) + 
        " l: " + std::to_string(p2wins) + 
        " t: " + std::to_string(ties) + "\n"
    ) ;
    double winturnsAvg, tieturnsAvg, lossturnsAvg = 0 ;
    if (p1wins) winturnsAvg = winturns / double(p1wins) ;
    if (p2wins) lossturnsAvg = lossturns / double(p2wins) ;
    if (ties) tieturnsAvg = tieturns / double(ties) ;
    p2screen(
        rank, 
        "win turn avg: " + std::to_string(winturnsAvg) + 
        " loss turn avg: " + std::to_string(lossturnsAvg) +
        " tie turn avg: " + std::to_string(tieturnsAvg) +
        " total turn avg " + std::to_string(totalturns/games) + "\n"
    ) ;
    p2screen(rank, "Monte goes second\n") ;
    winturns = tieturns = lossturns = totalturns = 0 ;
    p1wins = p2wins = ties = 0 ;
    for (int i = 0; i<games; i++) {
        int result = playParallelGame(randA, monte, p1wins, p2wins, ties, display, rank, size, turns) ;
        switch (result) {
            case 1: 
                winturns += turns ;
                break ;
            case 0:
                lossturns += turns ;
                break ;
            case TIE:
                tieturns += turns ;
                break ;
            default:
                p2screen(rank, "Result is invalid!\n") ;
        }
        totalturns += turns ;
    }
    p2screen(
        rank, 
        "w: " + std::to_string(p2wins) + 
        " l: " + std::to_string(p1wins) + 
        " t: " + std::to_string(ties) + "\n" 
    ) ;
    winturnsAvg = tieturnsAvg = lossturnsAvg = 0 ;
    if (p2wins) winturnsAvg = winturns / double(p2wins) ;
    if (p1wins) lossturnsAvg = lossturns / double(p1wins) ;
    if (ties) tieturnsAvg = tieturns / double(ties) ;
    p2screen(
        rank, 
        "win turn avg: " + std::to_string(winturnsAvg) + 
        " loss turn avg: " + std::to_string(lossturnsAvg) +
        " tie turn avg: " + std::to_string(tieturnsAvg) +
        " total turn avg: " + std::to_string(double(totalturns)/games) + "\n"
    ) ;
    delete randA ;
}

int main(int argc, char * argv[]) {

    int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MCW, &rank);
	MPI_Comm_size(MCW, &size);
    srand( rank );
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
    // Agent * monte = new MonteCarloAgent() ;
    // testAgainstRandom(monte, games, display) ;

    // play where the agent is MonteCarloParallelAgent
    Agent * monteP = new MonteCarloParallelAgent(rank, size) ;
    testAgainstRandom(monteP, games, display, rank, size) ;
    // delete monte ;
    delete monteP ;
    return 0;
}