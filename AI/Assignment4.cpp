#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
using namespace std;

struct Node {
    int x, y;
    int g, h, f;
    Node* parent;
    Node(int x, int y, int g, int h, Node* p=nullptr)
        : x(x), y(y), g(g), h(h), f(g+h), parent(p) {}
};

// Manhattan Distance Heuristic
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* Algorithm
bool aStarSearch(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    auto cmp = [](Node* a, Node* b) { return a->f > b->f; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> open(cmp);

    vector<vector<bool>> closed(rows, vector<bool>(cols, false));

    Node* start = new Node(0, 0, 0, heuristic(0, 0, rows-1, cols-1));
    open.push(start);

    vector<pair<int,int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

    while (!open.empty()) {
        Node* current = open.top();
        open.pop();

        int x = current->x, y = current->y;

        // Reached goal
        if (x == rows-1 && y == cols-1) {
            cout << "Path found:\n";
            stack<pair<int,int>> path;
            while (current) {
                path.push({current->x, current->y});
                current = current->parent;
            }
            while (!path.empty()) {
                cout << "(" << path.top().first << "," << path.top().second << ") ";
                path.pop();
            }
            cout << endl;
            return true;
        }

        closed[x][y] = true;

        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx>=0 && ny>=0 && nx<rows && ny<cols && grid[nx][ny]==0 && !closed[nx][ny]) {
                int gNew = current->g + 1;
                int hNew = heuristic(nx, ny, rows-1, cols-1);
                Node* neighbor = new Node(nx, ny, gNew, hNew, current);
                open.push(neighbor);
            }
        }
    }

    cout << "No path found!" << endl;
    return false;
}

// Example usage
int main() {
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };

    aStarSearch(grid);

    return 0;
}
