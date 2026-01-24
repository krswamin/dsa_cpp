/*
547. Number of Provinces

There are n cities. Some of them are connected, while some are not. 
If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where 
isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

As per the below adjacency matrixS convention a node is connected to itseld. hence isConnected[i][i] = 1 always. i.e. the diagonal is 1 always

Example 1: 3 nodes {1,2,3}. Node 1 and 2 are connected . Node 3 is stand alone
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2


Example 2: 3 nodes {1,2,3}. Node 1, 2 and 3 are all stand alone
Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
 

Constraints:
1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] is 1 or 0.
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]

*/

/* KSW do a BFS or DFS on a graph with disconnected components. 
Check the number of times the while-BFS-loop or the while-DFS-loop is called so that all nodes are visited*/

# include <iostream>
# include <vector>
# include <queue>
using namespace std;
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        
       int num_nodes = isConnected.size();
       int num_provinces = 0;
       queue<int> bfs_q;
       vector<int> visited(num_nodes, 0);
       
       for( int root =0; root<num_nodes; root++) {
        if(visited[root]==1){
            continue;
        } 

        num_provinces++;
        bfs_q.push(root);
        visited[root] = 1;
        while(!bfs_q.empty()){
            int current = bfs_q.front();
            bfs_q.pop();
            for( int child =0; child<num_nodes; child++) {
                if (isConnected[current][child] ==1 && visited[child]==0){
                    bfs_q.push(child);
                    visited[child] = 1;
                }
            }
        }
        
       }

       return num_provinces;

    }
};

int main(){
    Solution sol;
    vector<vector<int>> isConnected = {{1,1,0},{1,1,0},{0,0,1}};
    int num_provinces ;

    num_provinces = sol.findCircleNum(isConnected);
    cout<<"\n Case1: num_provinces ="<<num_provinces;
    
    isConnected = {{1,0,0},{0,1,0},{0,0,1}};
    num_provinces = sol.findCircleNum(isConnected);
    cout<<"\n Case2: num_provinces ="<<num_provinces;
    cout<<"\n";
}


