#include <iostream>
#include <vector>

using namespace std;

const int DIRS = 4;
const int dx[DIRS] = {0, 1, 0, -1};
const int dy[DIRS] = {1, 0, -1, 0};

bool isValidMove(int x, int y, const vector<vector<int>>& maze, const vector<vector<bool>>& visited) {
    int n = maze.size();
    int m = maze[0].size();
    return (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y]);
}

bool dfs(int x, int y, const vector<vector<int>>& maze, vector<vector<bool>>& visited, vector<pair<int, int>>& path) {
    if (x == maze.size() - 1 && y == maze[0].size() - 1) {
        path.emplace_back(x, y);
        return true;
    }

    visited[x][y] = true;
    path.emplace_back(x, y);

    for (int i = 0; i < DIRS; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (isValidMove(newX, newY, maze, visited)) {
            if (dfs(newX, newY, maze, visited, path)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

vector<pair<int, int>> solveMaze(const vector<vector<int>>& maze) {
    vector<pair<int, int>> path;
    int n = maze.size();
    int m = maze[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    if (dfs(0, 0, maze, visited, path)) {
        return path;
    } else {
        return {}; // No path found
    }
}

void printMaze(const vector<vector<int>>& maze) {
    for (const auto& row : maze) {
        for (int cell : row) {
            cout << (cell == 1 ? '#' : '*');
        }
        cout << endl;
    }
}

void printPath(const vector<pair<int, int>>& path) {
    for (const auto& step : path) {
        cout << "(" << step.first << ", " << step.second << ") ";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> maze = {
            {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
            {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
            {0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 0}
    };

    cout << "Maze:" << endl;
    printMaze(maze);

    vector<pair<int, int>> path = solveMaze(maze);

    if (!path.empty()) {
        cout << "Path found:" << endl;
        printPath(path);
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
