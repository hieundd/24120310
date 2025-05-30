#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include<queue>
#include<stack>
#include <climits>
#include <algorithm>

using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong the mo file: " << filename << endl;
        return {};
    }

    int n;
    file >> n;

    vector<vector<int>> adj;
    adj.push_back({ n });  

    for (int i = 0; i < n; i++) {
        vector<int> x;
        int count = 0;
        for (int j = 0; j < n; j++) {
            int val;
            if (!(file >> val)) {
                cerr << "Error \n";
                return {};
            }
            if (val == 1) {
                x.push_back(j);
                count++;
            }
        }
        x.insert(x.begin(), count);
        adj.push_back(x);
    }

    file.close();
    return adj;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong the mo file! \n";
        return {};
    }
    int n;
    file >> n;
    vector<vector<int>> matrix;
    matrix.push_back({ n });

    vector<vector<int>> mtx(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        int count;
        file >> count;
        for (int j = 0; j < count; ++j) {
            int neighbor;
            file >> neighbor;
            mtx[i][neighbor] = 1;
        }
    }

    for (const auto& row : mtx) {
        matrix.push_back(row);
    }

    file.close();
    return matrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (adjMatrix[i][j] != adjMatrix[j][i])
                return true;
    return false;

}

int countVertices(const vector<vector<int>>& adjMatrix) {
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix) {
    int count = 0;
    int n = adjMatrix.size();
    bool directed = isDirected(adjMatrix);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            count += adjMatrix[i][j];
    return directed ? count : count / 2;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
    vector<int> isolated;
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        bool isIsolated = true;
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
                isIsolated = false;
                break;
            }
        }
        if (isIsolated)
            isolated.push_back(i);
    }
    return isolated;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && adjMatrix[i][j] == 0)
                return false;
    return true;
}

bool isBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    for (int start = 0; start < n; ++start) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v) {
                    if (adjMatrix[u][v]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        }
                        else if (color[v] == color[u]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    if (!isBipartite(adjMatrix))
        return false;

    int n = adjMatrix.size();
    vector<int> color(n, -1);
    vector<int> setA, setB;

    for (int start = 0; start < n; ++start) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;
            setA.push_back(start);

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v) {
                    if (adjMatrix[u][v]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                            if (color[v] == 0)
                                setA.push_back(v);
                            else
                                setB.push_back(v);
                        }
                    }
                }
            }
        }
    }

    for (int u : setA) {
        for (int v : setB) {
            if (adjMatrix[u][v] == 0)
                return false;
        }
    }

    for (int u : setA)
        for (int v : setA)
            if (u != v && adjMatrix[u][v] != 0)
                return false;

    for (int u : setB)
        for (int v : setB)
            if (u != v && adjMatrix[u][v] != 0)
                return false;

    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> undirected(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
                undirected[i][j] = 1;
                undirected[j][i] = 1;
            }
        }
    }
    return undirected;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> complement(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && adjMatrix[i][j] == 0) {
                complement[i][j] = 1;
            }
        }
    }
    return complement;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> graph = adjMatrix; 
    stack<int> currPath;
    vector<int> circuit;
    currPath.push(0); 

    while (!currPath.empty()) {
        int currV = currPath.top();
        int nextV = -1;
        for (int v = 0; v < n; v++) {
            if (graph[currV][v] > 0) {
                nextV = v;
                break;
            }
        }
        if (nextV == -1) {
            circuit.push_back(currV);
            currPath.pop();
        }
        else {
            graph[currV][nextV]--;
            graph[nextV][currV]--;
            currPath.push(nextV);
        }
    }

    reverse(circuit.begin(), circuit.end());
    return circuit;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    stack<int> st;
    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                tree[u][v] = 1;
                tree[v][u] = 1;
                st.push(v);
            }
        }
    }
    return tree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                tree[u][v] = 1;
                tree[v][u] = 1;
                q.push(v);
            }
        }
    }
    return tree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        if (curr == v) return true;
        for (int i = 0; i < n; i++) {
            if (adjMatrix[curr][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    return false;
}

vector<int> dijkstraSimple(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        int minDist = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1) break; 
        if (u == end) break;

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            int w = adjMatrix[u][v];
            if (w > 0 && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    vector<int> path;
    if (dist[end] == INT_MAX) return path;
    for (int cur = end; cur != -1; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());
    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX) continue;
            for (int v = 0; v < n; v++) {
                int w = adjMatrix[u][v];
                if (w != 0 && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        if (dist[u] == INT_MAX) continue;
        for (int v = 0; v < n; v++) {
            int w = adjMatrix[u][v];
            if (w != 0 && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    vector<int> path;
    if (dist[end] == INT_MAX) return path; 
    for (int cur = end; cur != -1; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());
    return path;
}

