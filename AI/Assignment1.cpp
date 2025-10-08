#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

const int N = 3;
int goal[N][N] = {{1,2,3},{4,5,6},{7,8,0}};

struct Node {
    int board[N][N];
    vector<vector<vector<int>>> path;
};


string boardToString(int b[N][N]) {
    string s = "";
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            s += to_string(b[i][j]);
    return s;
}

bool is_goal(int board[N][N]) {
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            if (board[i][j] != goal[i][j]) return false;
    return true;
}

// Copies the contents of one 2D board to another.
void copyBoard(int src[N][N], int dest[N][N]) {
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            dest[i][j] = src[i][j];
}

vector<Node> get_neighbors(Node &curr) {
    int x,y;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            if (curr.board[i][j]==0) { x=i; y=j; }

    int dx[4]={-1,1,0,0};
    int dy[4]={0,0,-1,1};
    vector<Node> neighbors;

    for (int k=0;k<4;k++) {
        int nx=x+dx[k], ny=y+dy[k];
        if(nx>=0 && ny>=0 && nx<N && ny<N) {
            Node next;
            copyBoard(curr.board,next.board);
            swap(next.board[x][y], next.board[nx][ny]);
            next.path = curr.path;
            vector<vector<int>> step(N, vector<int>(N));
            for (int i=0;i<N;i++)
                for (int j=0;j<N;j++)
                    step[i][j]=curr.board[i][j];
            next.path.push_back(step);
            neighbors.push_back(next);
        }
    }
    return neighbors;
}

void print_solution(Node &curr) {
    cout << "Solution Path (" << curr.path.size() << " steps):\n";
    for (size_t s=0;s<curr.path.size();s++) {
        cout << "Step " << s << ":\n";
        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) cout << curr.path[s][i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
    cout << "Final State:\n";
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) cout << curr.board[i][j] << " ";
        cout << endl;
    }
}

void bfs(int start[N][N]) {
    queue<Node> q;
    set<string> visited;

    Node startNode;
    copyBoard(start,startNode.board);
    q.push(startNode);

    while(!q.empty()) {
        Node curr=q.front(); q.pop();
        string key=boardToString(curr.board);
        if(visited.count(key)) continue;
        visited.insert(key);

        if(is_goal(curr.board)) {
            cout<<"BFS Solution Found! 🥳\n";
            print_solution(curr);
            return;
        }
        for(auto &nbr : get_neighbors(curr)) {
            if(!visited.count(boardToString(nbr.board)))
                q.push(nbr);
        }
    }
    cout<<"BFS: No solution found. 😕\n";
}

void dfs(int start[N][N]) {
    stack<Node> st;
    set<string> visited;

    Node startNode;
    copyBoard(start,startNode.board);
    st.push(startNode);

    while(!st.empty()) {
        Node curr=st.top(); st.pop();
        string key=boardToString(curr.board);
        if(visited.count(key)) continue;
        visited.insert(key);

        if(is_goal(curr.board)) {
            cout<<"DFS Solution Found! 🥳\n";
            print_solution(curr);
            return;
        }
        for(auto &nbr : get_neighbors(curr)) {
            if(!visited.count(boardToString(nbr.board)))
                st.push(nbr);
        }
    }
    cout<<"DFS: No solution found. 😕\n";
}

bool isSolvable(int start[N][N]) {
    vector<int> flat;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(start[i][j]!=0) flat.push_back(start[i][j]);

    int inv = 0;
    for(size_t i = 0; i < flat.size(); i++) {
        for(size_t j = i + 1; j < flat.size(); j++) {
            if(flat[i] > flat[j]) inv++;
        }
    }
    return (inv % 2 == 0);
}

void runExample(int start[N][N]) {
    cout<<"\nRunning BFS...\n";
    bfs(start);

    cout<<"\nRunning DFS...\n";
    dfs(start);
    cout << "----------------------------------\n";
}

int main() {

    int solve[N][N] = {{1,2,3},{4,5,6},{0,7,8}};
    runExample(solve);
    return 0;
}