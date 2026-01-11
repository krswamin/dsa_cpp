/*
Leet code 994. Rotting Oranges
https://leetcode.com/problems/rotting-oranges/description/?envType=study-plan-v2&envId=leetcode-75

You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

Example 1:
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:
Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:
Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
-------------

Learner Thought Process
1) Need a bfs_q, visited_set, traversal_order for textbook bfs
2) The graph implementation itself is a 2D matrix and not an unordered set. so how would that affect,
   how would the visited set be. should be a matrix or a unordered set . Turns out no visited set was needed. 
   The grid itself functioned as one
3) ones closest to the 2 should rot parallelly: so how would that work ???
   Answer: BFS is parallel in nature. Multisource BFS should take care of this

*/ 

#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <cassert>
using namespace std;

class rotting_oranges {
    private: 
        vector<vector<int>> grid; 
        int expected_minutes; 

    public:
        rotting_oranges(vector<vector<int>> grid, int expected_minutes);
        void update(vector<vector<int>> grid, int expected_minutes);
        void print_grid() const;
        int bfs();
        void test();

};

rotting_oranges:: rotting_oranges(vector<vector<int>> grid, int expected_minutes) : 
                  grid(grid), expected_minutes(expected_minutes){};

void rotting_oranges:: update(vector<vector<int>> grid, int expected_minutes) {
    this->grid = grid;
    this->expected_minutes = expected_minutes;
}
                  

void rotting_oranges::print_grid() const {
    for( auto & row: grid){
        for(auto & x: row){
            cout<<x<<",";
        }
        cout<<"\n";
    }
}

int rotting_oranges:: bfs(){
    /* Golden Rule : 
    i)  Push to Queue:  Add to visited set
    ii) Pop from Queue: Add to traversal order
    */
    queue<pair<size_t,size_t>> bfs_q ; 
    queue<int> bfs_q_rot_time ; 
    vector<pair<int,int>> initial_rotten_positions;
    int num_good_oranges =0;
    int max_number_of_minutes =0 ; 

    for (size_t i=0; i<grid.size(); i++) {
        for(size_t j =0; j<grid[i].size(); j++) {
            if (grid[i][j] == 2)  {
                // add all rotten oranges to bfs_q
                bfs_q.push({i,j});
                bfs_q_rot_time.push(0);
            } else if (grid[i][j] == 1)  {
                //good orange
                num_good_oranges++;
            }
        }
    }
    
    // There were no good oranges to start with
    if(num_good_oranges ==0){
        return max_number_of_minutes; //which should be zero here
    }
    

    // BFS Traversal
    while (bfs_q.size() !=0) {
        auto current_cell = bfs_q.front(); 
        bfs_q.pop();
        auto curr_rot_time = bfs_q_rot_time.front(); 
        bfs_q_rot_time.pop();


        size_t i = current_cell.first;
        size_t j = current_cell.second;
        //Check for neighbours
        //Neighbor on the top
        if(i !=0 && grid[i-1][j] ==1 ){
            bfs_q.push({i-1,j});
            bfs_q_rot_time.push(curr_rot_time+1);
            max_number_of_minutes = curr_rot_time+1;
            grid[i-1][j]    = 2; // mark as rotten
            num_good_oranges--;
        }
        // Neighbor on the bottom
        if(i <grid.size()-1 && grid[i+1][j] ==1){
            bfs_q.push({i+1,j});
            bfs_q_rot_time.push(curr_rot_time+1);
            max_number_of_minutes = curr_rot_time+1;
            grid[i+1][j]    = 2; // mark as rotten
            num_good_oranges--;
        }
        // Neighbor on the left
        if(j !=0 && grid[i][j-1] ==1){
            bfs_q.push({i,j-1});
            bfs_q_rot_time.push(curr_rot_time+1);
            max_number_of_minutes = curr_rot_time+1; 
            grid[i][j-1]    = 2; // mark as rotten
            num_good_oranges--;
        }
        // Neighbor on the right
        if(j <grid[i].size()-1 && grid[i][j+1] ==1){
            bfs_q.push({i,j+1});
            bfs_q_rot_time.push(curr_rot_time+1);
            max_number_of_minutes = curr_rot_time+1;
            grid[i][j+1]    = 2; // mark as rotten
            num_good_oranges--;
        }           
        
        // Check for number of good oranges at the end of every cell expansion
        if(num_good_oranges ==0){
            return max_number_of_minutes; 
        }
    }
    
    // Final check for number of good oranges left
    if(num_good_oranges ==0){
        return max_number_of_minutes; 
    } else{
        return -1; // impossible
    }

}

void rotting_oranges:: test(){
    cout<<"\nGrid at Start \n";
    print_grid();
    int num_minutes = this->bfs();
    cout<<"\nGrid at End\n";
    print_grid();
    cout<<"Num of Minutes Taken:"<<num_minutes;
    cout<<"\nExpected Minutes:"<<expected_minutes;
    assert((num_minutes==expected_minutes) && "num minutes should match expected output");
}



int main(){
    
    cout<<"\n\n-------------Example 1-------------";
    vector<vector<int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
    int expected_num_minutes = 4;
    rotting_oranges ro(grid, expected_num_minutes);
    ro.test();
    
    cout<<"\n\n-------------Example 2-------------";
    grid = {{2,1,1},{0,1,1},{1,0,1}};
    expected_num_minutes =  -1;
    ro.update(grid, expected_num_minutes);
    ro.test();

    cout<<"\n\n-------------Example 3-------------";
    grid = {{0,2}};
    expected_num_minutes =  0;
    ro.update(grid, expected_num_minutes);
    ro.test();
 
    cout<<"\n\n-------------Example 4-------------";
    cout<<"\nCheck that isolated group of oranges never rot";
    grid = {{2,1,1,0,0,0},{1,1,2,1,1,1},{0,1,1,1,0,0},{0,0,1,0,0,2},{0,0,0,0,0,0},{1,1,1,0,0,0}};
    expected_num_minutes =  -1;
    ro.update(grid, expected_num_minutes);
    ro.test();

    cout<<"\n\n-------------Example 5-------------";
    grid = {{2,1,1,0,0,0},{1,1,2,1,1,1},{0,1,1,1,0,0},{0,0,1,0,0,2},{0,0,0,0,0,0},{0,0,0,0,0,0}};
    expected_num_minutes =  3;
    ro.update(grid, expected_num_minutes);
    ro.test();

    cout<<"\n\n-------------Example 6-------------";
    cout<<"\nCheck that multisource bfs works properly . The oranges closest to the 2 should rot simultaneously";
    grid = {{2,1,1},{1,1,2}};
    expected_num_minutes =  1;
    ro.update(grid, expected_num_minutes);
    ro.test();
    
    cout<<"\n";


}


    



