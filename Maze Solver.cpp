#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
using namespace std;

const int N = 5; 
char maze[N][N] = {
    {'S', '.', '.', '#', '.'},
    {'#', '#', '.', '#', '.'},
    {'.', '.', '.', '.', '.'},
    {'.', '#', '#', '#', '.'},
    {'.', '.', '.', '#', 'E'}
};

bool visited[N][N];
pair<int,int> parent[N][N]; 
int dx[4] = {-1, 1, 0, 0}; 
int dy[4] = {0, 0, -1, 1};


bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] != '#' && !visited[x][y]);
}

bool bfs(int sx, int sy, int ex, int ey) {
    queue<pair<int,int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    parent[sx][sy] = {-1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        if (x == ex && y == ey) return true;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }
    return false;
}

bool dfs(int x, int y, int ex, int ey) {
    if (x == ex && y == ey) return true;
    visited[x][y] = true;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny)) {
            parent[nx][ny] = {x, y};
            if (dfs(nx, ny, ex, ey)) return true;
        }
    }
    return false;
}

void printPath(int ex, int ey) {
    vector<pair<int,int>> path;
    for (pair<int,int> at = {ex, ey}; at.first != -1; at = parent[at.first][at.second])
        path.push_back(at);
    reverse(path.begin(), path.end());

    cout << "\nPath found: ";
    for (auto [x, y] : path) cout << "(" << x << "," << y << ") ";
    cout << "\n";

    
    for (auto [x, y] : path) {
        if (maze[x][y] != 'S' && maze[x][y] != 'E')
            maze[x][y] = '*';
    }

    cout << "\nMaze with Path:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << maze[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    int sx, sy, ex, ey;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (maze[i][j] == 'S') { sx = i; sy = j; }
            if (maze[i][j] == 'E') { ex = i; ey = j; }
        }
    }

    cout << "Maze Solver using BFS & DFS\n";
    cout << "Choose algorithm:\n1. BFS (Shortest Path)\n2. DFS (Exploration)\nEnter choice: ";
    int choice; cin >> choice;

    bool found = false;
    if (choice == 1) found = bfs(sx, sy, ex, ey);
    else if (choice == 2) found = dfs(sx, sy, ex, ey);

    if (found) printPath(ex, ey);
    else cout << "No path found!\n";

    return 0;
}
