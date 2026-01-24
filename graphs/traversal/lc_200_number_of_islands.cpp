/*
https://leetcode.com/problems/number-of-islands/description/?envType=study-plan-v2&envId=top-interview-150

Leet Code 200. Number of Islands
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
You may assume all four edges of the grid are all surrounded by water.


Example 1:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1


Example 2:
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

*/

/*
KSW High Level Solution

Perform  bfs or dfs. Find the number of source/ number of times to run bfs/dfs loop/
Number of independent loops.

Key Learnings:
1) to prevent overflow errors: all the .size() should be convereted to int
Example. if(cj<=int(grid[ci].size())-2 && grid[ci][cj+1]=='1')

*/

# include<queue>
# include<utility>
# include<iostream>
#include<cassert>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {

        if (grid.empty()){
            return 0;
        }

        queue<pair<int,int>> bfs_q;        
        int number_of_islands = 0;
        //Outer multisource bfs
        for(int i = 0; i<int(grid.size()); i++){
            if (grid[i].empty()){
                continue;
            }
            for(int j = 0; j<int(grid[i].size()); j++){
                if(grid[i][j] != '1'){
                    continue;
                }
                
                // Single Source BFS
                pair<int,int> root ={i,j};
                bfs_q.push(root);
                grid[i][j] = '2';
                number_of_islands++;
                while(!bfs_q.empty()){
                    auto current = bfs_q.front();
                    int ci = current.first;
                    int cj = current.second;
                    bfs_q.pop();

                    //Check for top neighbor
                    if(ci>=1 && grid[ci-1][cj]=='1') {
                        bfs_q.push({ci-1,cj});
                        grid[ci-1][cj] = '2';
                    }

                    //Check for bottom neighbor
                    if(ci<=int(grid.size())-2 && grid[ci+1][cj]=='1') {
                        bfs_q.push({ci+1,cj});
                        grid[ci+1][cj] = '2';
                    }

                    //Check for left neighbor
                    if(cj>=1 && grid[ci][cj-1]=='1') {
                        bfs_q.push({ci,cj-1});
                        grid[ci][cj-1] = '2';
                    }

                    //Check for right neighbor
                    if(cj<=int(grid[ci].size())-2 && grid[ci][cj+1]=='1') {
                        bfs_q.push({ci,cj+1});
                        grid[ci][cj+1] = '2';
                    }
                }
            }
        }

        return number_of_islands;
   }
};

int main(){

    vector<vector<char>> grid ;
    int expected_output ;
    int code_output;
    Solution sol;

    grid = { 
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}};
    expected_output = 1;
    code_output = sol.numIslands(grid);
    cout<<"\n\n Expected Output ="<< expected_output;
    cout<<"\n Code Output ="<< code_output;
    assert(expected_output == code_output && "expected and code output should match");
    
    grid = { 
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}};
    expected_output = 3;
    code_output = sol.numIslands(grid);
    cout<<"\n\n Expected Output ="<< expected_output;
    cout<<"\n Code Output ="<< code_output;
    assert(expected_output == code_output && "expected and code output should match");
    
    grid = {{'1'}};
    expected_output = 1;
    code_output = sol.numIslands(grid);
    cout<<"\n\n Expected Output ="<< expected_output;
    cout<<"\n Code Output ="<< code_output;
    assert(expected_output == code_output && "expected and code output should match");

    grid = { 
        {'1','1','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}};
    expected_output = 3;
    code_output = sol.numIslands(grid);
    cout<<"\n\n Expected Output ="<< expected_output;
    cout<<"\n Code Output ="<< code_output;
    assert(expected_output == code_output && "expected and code output should match");
  
    grid = { 
        {'1','1','0','0'},
        {'1','1','0','0','0'},
        {},
        {'0','0','0','1','1'}};
    expected_output = 2;
    code_output = sol.numIslands(grid);
    cout<<"\n\n Expected Output ="<< expected_output;
    cout<<"\n Code Output ="<< code_output;
    assert(expected_output == code_output && "expected and code output should match");
    cout<<"\n";

}