#include <iostream>
#include <vector>
using namespace std;

void search(int node, const vector<vector<int>>& adj, vector<bool>& visited){
    visited[node]= true;
    for(int i=0; i<(int)adj.size(); i++){
        if(adj[node][i] == 1 && !visited[i]){
            search(i, adj, visited);
        }
    }
}

int countSoloCircuits(const vector<vector<int>>& adj){
    int n= adj.size();
    vector<bool> visited(n, false);
    int soloCircuits= 0;

    for(int i=0; i<n; i++){
        if(!visited[i]){
            search(i, adj, visited);
            soloCircuits++;
        }
    }

    return soloCircuits;
}

int main(){
    int systemNum= 1;
    int n;
    while(cin >> n){
        vector<vector<int>> adj(n, vector<int>(n));
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin >> adj[i][j];
            }
        }
        int soloCircuits =countSoloCircuits(adj);
        cout << "System " << systemNum << " isolated circuits: " << soloCircuits << "\n";
        systemNum++;
    }
    return 0;
}

