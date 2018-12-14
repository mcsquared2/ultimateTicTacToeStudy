import itertools

X = "X"
O = "O"
U = "U"

possible_values = [
    X,
    O,
    U
]

# def generateNonWinningBoards():
def threeAreSameAndPlayer(a, b, c):
    if a != U and a == b and a == c:
        return True
    return False

def getIntersections(lines):
    intersections = {}
    for i in range(len(lines)):
        for j in range(i+1, len(lines)):
            values = (lines[i].intersection(lines[j]))
            for v in values:
                intersections[v] = True
    return list(intersections)

def boardIsValid(board):
    px_lines, po_lines = winningLines(board)
    if px_lines and po_lines:
        return False
    elif px_lines:
        if len(px_lines) <= 1:
            return X
        intersections = getIntersections(px_lines)
        if len(intersections) != 1:
            return False
        else:
            return X
    elif po_lines:
        if len(po_lines) <= 1:
            return O
        intersections = getIntersections(po_lines)
        if len(intersections) != 1:
            return False
        else: 
            return O
    else:
        return U

def winningLines(board):
    px_lines = []
    po_lines = []
    for i in range(3):
        if threeAreSameAndPlayer(board[i], board[i+3], board[i+6]):
            if board[i] == X:
                px_lines.append( set([ i, i+3, i+6 ]) )
            elif board[i] == O:
                po_lines.append( set([i, i+3, i+6]) )
            else:
                raise Exception("threeAreSameAndPlayer failed when checking {} on the indecies {}, {}, {}".format(
                    str(board),
                    i, i+3, i+6
                ))
        if threeAreSameAndPlayer(board[ 3*i ], board[ 3*i + 1 ], board[ 3*i + 2 ]):
            if board[3*i] == X:
                px_lines.append( set([ 3*i, 3*i+1, 3*i+2 ]) )
            elif board[3*i] == O:
                po_lines.append( set([ 3*i, 3*i+1, 3*i+2 ]) )
            else:
                raise Exception("threeAreSameAndPlayer failed when checking {} on the indecies {}, {}, {}".format(
                    str(board),
                    3*i, 3*i+1, 3*i+2
                ))

    if threeAreSameAndPlayer(board[0], board[4], board[8]):
        if board[0] == X:
            px_lines.append( set([ 0, 4, 8 ]) )
        elif board[0] == O:
            po_lines.append( set([ 0, 4, 8]))
        else:
            raise Exception("threeAreSameAndPlayer failed when checking {} on the indecies {}, {}, {}".format(
                str(board),
                0, 4, 8
            ))
    if threeAreSameAndPlayer(board[2], board[4], board[6]):
        if board[2] == X:
            px_lines.append( set([ 2, 4, 6 ]) )
        elif board[2] == O:
            po_lines.append( set([ 2, 4, 6]))
        else:
            raise Exception("threeAreSameAndPlayer failed when checking {} on the indecies {}, {}, {}".format(
                str(board),
                2, 4, 6
            ))
    return px_lines, po_lines


invalid_boards = [
    # [X] * 9,
    [O] * 9,
    [
        X, X, X,
        X, O, X,
        X, O, X,
    ],
    [
        X, X, X,
        U, U, U,
        X, X, X,
    ],
    [
        O, O, X,
        O, O, X,
        O, O, X,
    ],
    [
        X, X, X,
        U, X, X,
        U, X, X,
    ],
    [
        O, O, O,
        O, O, X,
        O, O, X,
    ],
]

# for board in invalid_boards:
#     assert not boardIsValid(board), "Board {} did not return False and is invalid".format(board) 

valid_boards = [
    [U]*9,
    [
        O, O, O,
        O, U, U,
        O, U, U,
    ],
    [
        O, O, O,
        O, X, X,
        O, X, X,
    ],
    [
        O, O, O,
        O, U, U,
        O, U, U,
    ],
    [
        O, O, X,
        O, U, X,
        X, X, X,
    ],
    [
        O, U, U,
        O, U, U,
        O, U, U,
    ],
    [
        O, O, X,
        U, U, U,
        X, X, X,
    ],
    [
        U, O, O,
        O, O, O,
        O, O, X,
    ],
    [
        U, X, X,
        X, X, X,
        X, X, U,
    ],
]

for board in valid_boards:
    assert boardIsValid(board), "Board {} returned False and is valid".format(board)

winning_boards = 0
valid_board_count = 0
boards = [b for b in itertools.product(possible_values, repeat=9)]
for board in boards:
    v = boardIsValid(board)
    if v:
        valid_board_count += 1
        if v != U:
            winning_boards += 1

unfilled_board_count = valid_board_count - winning_boards
total_global_boards = 0
winng_boards_per_player = winning_boards//2
global_wins_total = 0
for board in boards:
    v = boardIsValid(board)
    if v:
        state_boards = 1
        global_wins=1
        for b in board:
            if b == U:
                state_boards *= unfilled_board_count
                if v != U:
                    global_wins *= unfilled_board_count    
            else:
                state_boards *= winng_boards_per_player
                if v != U:
                    global_wins *= winng_boards_per_player
        total_global_boards += state_boards
        global_wins_total += global_wins
print("Winning boards are {}".format(winning_boards))
print("unfilled boards are: {}".format(unfilled_board_count))
print("Total valid boards are {}".format(valid_board_count))
print("Total end boards is {:.3E}".format(total_global_boards))
print("Total winning boards is {:.3E}".format(global_wins_total))
    
            
