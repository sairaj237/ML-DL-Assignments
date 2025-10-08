#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node {
    int x, y;
    int g, h; // g = cost from start, h = heuristic to goal
    Node* parent;
    Node(int x, int y, int g=0, int h=0, Node* p=nullptr) : x(x), y(y), g(g), h(h), parent(p) {}
};

// Compare nodes for priority queue
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return (a->g + a->h) > (b->g + b->h);
    }
};

// Heuristic: Manhattan distance
int heuristic(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check valid cell
bool isValid(int x, int y, int rows, int cols){
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

// A* algorithm
vector<pair<int,int>> AStar(vector<vector<int>> grid, pair<int,int> start, pair<int,int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols,false));
    
    priority_queue<Node*, vector<Node*>, CompareNode> pq;
    pq.push(new Node(start.first, start.second, 0, heuristic(start.first,start.second,goal.first,goal.second)));

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    Node* endNode = nullptr;

    while(!pq.empty()){
        Node* current = pq.top(); pq.pop();
        if(visited[current->x][current->y]) continue;
        visited[current->x][current->y] = true;

        if(current->x == goal.first && current->y == goal.second){
            endNode = current;
            break;
        }

        for(int i=0;i<4;i++){
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if(isValid(nx, ny, rows, cols) && !visited[nx][ny] && grid[nx][ny] == 0){
                int g_new = current->g + 1;
                int h_new = heuristic(nx, ny, goal.first, goal.second);
                pq.push(new Node(nx, ny, g_new, h_new, current));
            }
        }
    }

    // Reconstruct path
    vector<pair<int,int>> path;
    while(endNode != nullptr){
        path.push_back({endNode->x, endNode->y});
        endNode = endNode->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

int main(){
    vector<vector<int>> grid = {
        {0,0,0,0,0},
        {1,1,0,1,0},
        {0,0,0,1,0},
        {0,1,1,0,0},
        {0,0,0,0,0}
    };

    pair<int,int> start = {0,0};
    pair<int,int> goal = {4,4};

    vector<pair<int,int>> path = AStar(grid, start, goal);

    if(path.empty()) cout << "No path found!\n";
    else {
        cout << "Path found:\n";
        for(auto p: path) cout << "(" << p.first << "," << p.second << ") ";
        cout << endl;
    }
}
