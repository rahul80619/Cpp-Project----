#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct Cell {
    int x, y;
    vector<pair<int, int>> path; 
};

bool isValid(int x, int y, int n, int m, vector<vector<int>> &maze, vector<vector<bool>> &visited) {
    return (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y]);
}

void bfsSolver(vector<vector<int>> &maze, pair<int, int> start, pair<int, int> end) {
    int n = maze.size();
    int m = maze[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    queue<Cell> q;
    q.push({start.first, start.second, {{start.first, start.second}}});
    visited[start.first][start.second] = true;

    cout << "\nRunning BFS to find the shortest path...\n";

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        int x = current.x, y = current.y;

        if (x == end.first && y == end.second) {
            cout << "\n✅ Shortest Path Found:\n";
            for (auto &p : current.path)
                cout << "(" << p.first << "," << p.second << ") ";
            cout << "\nPath length: " << current.path.size() << endl;
            return;
        }

        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny, n, m, maze, visited)) {
                visited[nx][ny] = true;
                auto newPath = current.path;
                newPath.push_back({nx, ny});
                q.push({nx, ny, newPath});
            }
        }
    }

    cout << "\n❌ No path found using BFS.\n";
}

void dfsHelper(vector<vector<int>> &maze, int x, int y, pair<int, int> end, vector<vector<bool>> &visited, vector<pair<int, int>> &path, vector<vector<pair<int, int>>> &allPaths) {
    if (x == end.first && y == end.second) {
        allPaths.push_back(path);
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny, maze.size(), maze[0].size(), maze, visited)) {
            visited[nx][ny] = true;
            path.push_back({nx, ny});
            dfsHelper(maze, nx, ny, end, visited, path, allPaths);
            path.pop_back();
            visited[nx][ny] = false;
        }
    }
}

void dfsSolver(vector<vector<int>> &maze, pair<int, int> start, pair<int, int> end) {
    int n = maze.size(), m = maze[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<pair<int, int>> path;
    vector<vector<pair<int, int>>> allPaths;

    visited[start.first][start.second] = true;
    path.push_back(start);
    dfsHelper(maze, start.first, start.second, end, visited, path, allPaths);

    if (allPaths.empty()) {
        cout << "\n❌ No path found using DFS.\n";
        return;
    }

    cout << "\n✅ Paths found using DFS: " << allPaths.size() << "\n";
    int i = 1;
    for (auto &p : allPaths) {
        cout << "Path " << i++ << ": ";
        for (auto &pt : p)
            cout << "(" << pt.first << "," << pt.second << ") ";
        cout << endl;
    }
}

int main() {
    int n, m;
    cout << "Enter maze size (rows cols): ";
    cin >> n >> m;

    vector<vector<int>> maze(n, vector<int>(m));
    cout << "Enter maze grid (0 for open path, 1 for wall):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    pair<int, int> start, end;
    cout << "Enter start position (row col): ";
    cin >> start.first >> start.second;
    cout << "Enter end position (row col): ";
    cin >> end.first >> end.second;

    cout << "\nMaze Representation:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }

    int choice;
    cout << "\nChoose algorithm:\n1. BFS (Shortest Path)\n2. DFS (All Paths)\nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
        bfsSolver(maze, start, end);
    else if (choice == 2)
        dfsSolver(maze, start, end);
    else
        cout << "Invalid choice!" << endl;

    return 0;
}
