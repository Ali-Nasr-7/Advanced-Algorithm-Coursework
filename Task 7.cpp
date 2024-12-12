#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
using namespace std;

typedef pair<int, int> Vertex;

bool isValid(int x, int y, const vector<vector<int>>& maze) {
    return x >= 0 && y >= 0 && x < maze.size() && y < maze[0].size() &&
        (maze[x][y] == 0 || maze[x][y] == 2 || maze[x][y] == 3);
}

int getIndex(int x, int y, int cols) {
    return x * cols + y;
}

string classifyVertex(int x, int y, const vector<vector<int>>& maze, const vector<pair<int, int>>& directions) {
    int degree = 0;
    for (auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        if (isValid(nx, ny, maze)) degree++;
    }

    if (maze[x][y] == 3) return "Start";       
    if (maze[x][y] == 2) return "Finish";      
    if (degree == 1) return "Dead End";        
    if (degree > 2) return "Junction";         
    return "Path";                             
}


unordered_map<int, vector<int>> buildGraph(const vector<vector<int>>& maze, vector<pair<int, string>>& classifiedVertices) {
    unordered_map<int, vector<int>> graph;
    int rows = maze.size();
    int cols = maze[0].size();

    
    vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 0 || maze[i][j] == 2 || maze[i][j] == 3) {
                string vertexType = classifyVertex(i, j, maze, directions);
                classifiedVertices.emplace_back(getIndex(i, j, cols), vertexType);

                int index = getIndex(i, j, cols);
                graph[index] = {};
                for (auto& dir : directions) {
                    int nx = i + dir.first;
                    int ny = j + dir.second;
                    while (isValid(nx, ny, maze)) {
                        if (classifyVertex(nx, ny, maze, directions) != "Path") {
                            graph[index].push_back(getIndex(nx, ny, cols));
                            break;
                        }
                        nx += dir.first;
                        ny += dir.second;
                    }
                }
            }
        }
    }

    return graph;
}

void BFS(int start, const unordered_map<int, vector<int>>& graph, const vector<pair<int, string>>& classifiedVertices) {
    unordered_map<int, bool> visited;
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal (Starting from vertex " << start << "):\n";

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        auto it = find_if(classifiedVertices.begin(), classifiedVertices.end(),
            [current](const pair<int, string>& vertex) { return vertex.first == current; });
        if (it != classifiedVertices.end()) {
            cout << "Visited Vertex " << current << " (" << it->second << ")\n";
        }
        else {
            cout << "Visited Vertex " << current << " (Unknown Type)\n";
        }

        if (graph.find(current) != graph.end()) {
            for (int neighbor : graph.at(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
}

void DFS(int start, const unordered_map<int, vector<int>>& graph, const vector<pair<int, string>>& classifiedVertices) {
    unordered_map<int, bool> visited;
    stack<int> s;

    visited[start] = true;
    s.push(start);

    cout << "DFS Traversal (Starting from vertex " << start << "):\n";

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        auto it = find_if(classifiedVertices.begin(), classifiedVertices.end(),
            [current](const pair<int, string>& vertex) { return vertex.first == current; });
        if (it != classifiedVertices.end()) {
            cout << "Visited Vertex " << current << " (" << it->second << ")\n";
        }
        else {
            cout << "Visited Vertex " << current << " (Unknown Type)\n";
        }

        if (graph.find(current) != graph.end()) {
            for (int neighbor : graph.at(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> maze = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, // 2 = End
        {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 3 = Start
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    vector<pair<int, string>> classifiedVertices;
    auto graph = buildGraph(maze, classifiedVertices);

    cout << "Classified Vertices:\n";
    for (auto& vertex : classifiedVertices) {
        cout << "Vertex " << vertex.first << " (" << vertex.second << ")\n";
    }

    cout << "\nGraph Representation (Adjacency List):\n";
    for (const auto& pair : graph) {
        int index = pair.first;
        const auto& neighbors = pair.second;
        cout << "Vertex " << index << " is connected to: ";
        for (int neighbor : neighbors) {
            cout << neighbor << " ";
        }
        cout << endl;
    }

    int startIndex = getIndex(13, 0, maze[0].size());
    BFS(startIndex, graph, classifiedVertices);

    cout << "\n";
    DFS(startIndex, graph, classifiedVertices);

    return 0;
}
