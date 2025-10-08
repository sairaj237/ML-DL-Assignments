#include <iostream>
using namespace std;

char board[3][3] = {{'1','2','3'}, {'4','5','6'}, {'7','8','9'}};

void printBoard() {
    cout << "\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
}

bool isMovesLeft() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]!='X' && board[i][j]!='O')
                return true;
    return false;
}

int evaluate() {
    // rows
    for(int row=0; row<3; row++){
        if(board[row][0]==board[row][1] && board[row][1]==board[row][2]){
            if(board[row][0]=='X') return +10;
            else if(board[row][0]=='O') return -10;
        }
    }
    // cols
    for(int col=0; col<3; col++){
        if(board[0][col]==board[1][col] && board[1][col]==board[2][col]){
            if(board[0][col]=='X') return +10;
            else if(board[0][col]=='O') return -10;
        }
    }
    // diagonals
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
        if(board[0][0]=='X') return +10;
        else if(board[0][0]=='O') return -10;
    }
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
        if(board[0][2]=='X') return +10;
        else if(board[0][2]=='O') return -10;
    }
    return 0;
}

int minimax(int depth, bool isMax) {
    int score = evaluate();
    if(score==10) return score-depth;
    if(score==-10) return score+depth;
    if(!isMovesLeft()) return 0;

    if(isMax){
        int best = -1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]!='X' && board[i][j]!='O'){
                    char backup = board[i][j];
                    board[i][j] = 'X';
                    best = max(best, minimax(depth+1, !isMax));
                    board[i][j] = backup;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]!='X' && board[i][j]!='O'){
                    char backup = board[i][j];
                    board[i][j] = 'O';
                    best = min(best, minimax(depth+1, !isMax));
                    board[i][j] = backup;
                }
            }
        }
        return best;
    }
}

pair<int,int> findBestMove() {
    int bestVal = -1000;
    pair<int,int> bestMove;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]!='X' && board[i][j]!='O'){
                char backup = board[i][j];
                board[i][j] = 'X';
                int moveVal = minimax(0, false);
                board[i][j] = backup;
                if(moveVal > bestVal){
                    bestMove = {i,j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    printBoard();
    while(isMovesLeft() && evaluate()==0){
        int move;
        cout << "Enter your move (1-9): ";
        cin >> move;
        int r = (move-1)/3;
        int c = (move-1)%3;
        if(board[r][c]!='X' && board[r][c]!='O'){
            board[r][c] = 'O';
            if(isMovesLeft() && evaluate()==0){
                pair<int,int> bestMove = findBestMove();
                board[bestMove.first][bestMove.second] = 'X';
            }
            printBoard();
        } else {
            cout << "Invalid Move\n";
        }
    }
    int score = evaluate();
    if(score==10) cout << "AI wins!\n";
    else if(score==-10) cout << "You win!\n";
    else cout << "Draw!\n";
}
