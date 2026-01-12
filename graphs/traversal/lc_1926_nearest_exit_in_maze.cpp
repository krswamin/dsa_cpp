/*


1926. Nearest Exit from Entrance in Maze

https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/description/?envType=study-plan-v2&envId=leetcode-75

You are given an m x n matrix maze (0-indexed) with empty cells (represented as '.') and walls (represented as '+'). 
You are also given the entrance of the maze, where entrance = [entrancerow, entrancecol] denotes the row and column of the cell you are initially standing at.
In one step, you can move one cell up, down, left, or right. 
You cannot step into a cell with a wall, and you cannot step outside the maze. 
Your goal is to find the nearest exit from the entrance. An exit is defined as an empty cell that is at the border of the maze. 
The entrance does not count as an exit.
Return the number of steps in the shortest path from the entrance to the nearest exit, or -1 if no such path exists.

Example 1:
Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
Output: 1
Explanation: There are 3 exits in this maze at [1,0], [0,2], and [2,3].
Initially, you are at the entrance cell [1,2].
- You can reach [1,0] by moving 2 steps left.
- You can reach [0,2] by moving 1 step up.
It is impossible to reach [2,3] from the entrance.
Thus, the nearest exit is [0,2], which is 1 step away.

Example 2:
Input: maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
Output: 2
Explanation: There is 1 exit in this maze at [1,2].
[1,0] does not count as an exit since it is the entrance cell.
Initially, you are at the entrance cell [1,0].
- You can reach [1,2] by moving 2 steps right.
Thus, the nearest exit is [1,2], which is 2 steps away.

Example 3:
Input: maze = [[".","+"]], entrance = [0,0]
Output: -1
Explanation: There are no exits in this maze.

Constraints: 
maze.length == m
maze[i].length == n
1 <= m, n <= 100
maze[i][j] is either '.' or '+'.
entrance.length == 2
0 <= entrancerow < m
0 <= entrancecol < n
entrance will always be an empty cell.
*/

#include<vector>
#include<string>
#include<queue>
#include<utility>
#include<iostream>
#include<cassert>
using namespace std;


class Maze{
    private:
        vector<vector<string>> grid;
    
    public:
        Maze(vector<vector<string>> & grid);
        void update(vector<vector<string>> & grid);
        void print_grid() const;
        vector<int> find_exit(vector<size_t> & entrance);
        void test(vector<size_t> & entrance,vector<int> & expected_exit);
      
};

Maze::Maze(vector<vector<string>> & grid): grid(grid) {}

void Maze::update(vector<vector<string>> & grid) {this->grid=grid;}

void Maze::print_grid() const {
    for(auto row: grid){
        for(auto x: row){
            cout<<x<<",";
        }
        cout<<"\n";
    }
}

vector<int> Maze::find_exit(vector<size_t> & entrance){
    /* 
    This is a BFS implementation
    Returns value in the order {cost, row, column}
    */
    
    vector<int> exit = {-1, -1, -1}; //cost, row, column
    queue<vector<size_t>> bfs_q; //cost, row, column 
    bfs_q.push({0, entrance[0], entrance[1]}); // initial cost is zero
    grid[entrance[0]][entrance[1]] = "x";

    while(bfs_q.size() != 0){
        auto current = bfs_q.front();
        bfs_q.pop();
        
        size_t cost = current[0];
        size_t i = current[1];
        size_t j = current[2];        
        // Check Top Neighbor
        if(i !=0 && grid[i-1][j]=="."){
            grid[i-1][j]= "x";
            // This is a border cell and hence an exit
            if (i-1==0){
               exit = {int(cost+1), int(i-1), int(j)};
               break;
            }
            bfs_q.push({cost+1, i-1, j});
        }

        // Check Bottom Neighbor
        if(i<grid.size()-1 && grid[i+1][j]=="."){
            grid[i+1][j]= "x";
            // This is a border cell and hence an exit
            if (i+1==grid.size()-1){
               exit = {int(cost+1), int(i+1), int(j)};
               break;
            }
            bfs_q.push({cost+1, i+1, j});
        }

        // Check Left Neighbor
        if(j !=0 && grid[i][j-1]=="."){
            grid[i][j-1]= "x";
            // This is a border cell and hence an exit
            if (j-1==0){
               exit = {int(cost+1), int(i), int(j-1)};
               break;
            }
            bfs_q.push({cost+1, i, j-1});
        }
        
        // Check Right Neighbor
        if(j<grid[i].size()-1 && grid[i][j+1]=="."){
            grid[i][j+1]= "x";
            // This is a border cell and hence an exit
            if (j+1==grid[i].size()-1){
               exit = {int(cost+1), int(i), int(j+1)};
               break;
            }
            bfs_q.push({cost+1, i, j+1});
        }        
    }

    return exit;
}

void Maze:: test(vector<size_t> & entrance, vector<int> & expected_exit){
    cout<<"\nMaze at Start \n";
    print_grid();
    cout<<"\nEntrance:"<<entrance[0]<<","<<entrance[1];
    auto actual_exit = this->find_exit(entrance);
    cout<<"\nGrid at End\n";
    print_grid();
    
    cout<<"\n actual  : num_steps :"<<actual_exit[0]<<", exit_cell:"<<actual_exit[1]<<","<<actual_exit[2];
    cout<<"\n expected: num_steps :"<<expected_exit[0]<<", exit_cell:"<<expected_exit[1]<<","<<expected_exit[2];
    assert((actual_exit[0]==expected_exit[0]) && "num steps should match expected output");
    assert((actual_exit[1]==expected_exit[1] && actual_exit[2]==expected_exit[2]) && "exit cell should match expected output");
}



int main(){

    cout<<"\n\n-------------Example 1-------------";
    vector<vector<string>> grid = {{"+","+",".","+"},{".",".",".","+"},{"+","+","+","."}};
    vector<size_t> entrance = {1,2};
    vector<int> expected_exit = {1, 0,2}; // num_steps=1. exit cell = [0,2]
    Maze mz(grid);
    mz.test(entrance, expected_exit);
    
    cout<<"\n\n-------------Example 2-------------";
    grid = {{"+","+","+"},{".",".","."},{"+","+","+"}};
    entrance = {1,0};
    expected_exit = {2,1,2}; // num_steps=2. exit cell = [1,2]
    mz.update(grid);
    mz.test(entrance, expected_exit);

    cout<<"\n\n-------------Example 3-------------";
    grid = {{".","+"}};
    entrance = {0,0};
    expected_exit = {-1,-1,-1}; // There are no exits to this maze
    mz.update(grid);
    mz.test(entrance, expected_exit);

    cout<<"\n";

}