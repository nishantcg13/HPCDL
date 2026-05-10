#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>

using namespace std;

void parallelBFS(int src, vector<bool>&vis, vector<vector<int>>&adj){

    queue<int> q;
    q.push(src);
    vis[src] = true;

    while(!q.empty()){

        int frontNode = q.front();
        q.pop();

        cout << frontNode << " ";

        #pragma omp parallel for
        for(int i = 0; i < adj[frontNode].size(); i++){

            int nbr = adj[frontNode][i];

            if(!vis[nbr]){

                vis[nbr] = true;

                #pragma omp critical
                {
                    q.push(nbr);
                }
            }
        }
    }
}

void parallelDFS(int node, vector<bool>&vis, vector<vector<int>>&adj){

    cout << node << " ";
    vis[node] = true;

    #pragma omp parallel for
    for(int i = 0; i < adj[node].size(); i++){

        int nbr = adj[node][i];

        if(!vis[nbr]){
            parallelDFS(nbr, vis, adj);
        }
    }
}

int main(){

    // Hardcoded graph
    vector<vector<int>> graph = {

        {1, 2},    // 0
        {0, 3},    // 1
        {0, 3},    // 2
        {1, 2}     // 3
    };

    vector<bool> visited(4, false);

    cout << "Parallel BFS: ";
    parallelBFS(0, visited, graph);

    fill(visited.begin(), visited.end(), false);

    cout << "\nParallel DFS: ";
    parallelDFS(0, visited, graph);

    return 0;
}