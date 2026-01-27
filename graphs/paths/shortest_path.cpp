/*
Shortest path between 2 nodes in a graph
This is BFS with parent
*/

#include<queue>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<iostream>
#include<cassert>
using namespace std;

class Solution{
    public:
    vector<int> shortest_path(unordered_map<int, vector<int>> graph, int node1, int node2);
    void test(int node1, int node2, vector<int> expected_ouput, vector<int> code_output);
};

// Shortest Path is BFS with Parent
vector<int> Solution :: shortest_path(unordered_map<int, vector<int>> graph, int node1, int node2){    

    vector<int> sp = {};
    if(graph.find(node1) == graph.end() || graph.find(node2) == graph.end()){
        return sp;
    }

    queue<int> bfs_q; //<node,parent>
    unordered_set<int> visited;
    unordered_map<int,int> parent;
    
    bfs_q.push(node1);
    visited.emplace(node1);
    parent[node1]= -1;
    bool path_found = false;

    while(!bfs_q.empty()){
        int current = bfs_q.front();
        bfs_q.pop();
        for (int child: graph[current]){
             // if node has not yet been visited
             if(visited.find(child) == visited.end()){
                bfs_q.push(child);
                visited.emplace(child);
                parent[child] = current;
                if (child == node2){
                    path_found = true;
                    break;
                }
             }
        }
    }

    if(path_found){                
        int current = node2;
        while(current != -1){
            sp.push_back(current);
            current = parent[current];
        }        
        reverse(sp.begin(), sp.end());
    }
    return sp;  
}

void Solution::test(int node1, int node2, vector<int> expected_output, vector<int> code_output){
    cout<<"\n";
    cout<<"\n Node1: "<<node1 <<", Node2: "<<node2;
    cout<<"\n Expected output: ";
    for(int x: expected_output){
        cout<<x<<", ";
    }
    cout<<"\n Code output: ";
    for(int x: code_output){
        cout<<x<<", ";
    }
    cout<<"\n";

    assert(code_output == expected_output && "code output and expected output should match");

}


void test_directed_graph(){
    Solution sol;
    vector<int> code_path ;
    vector<int> expected_path ;
    int node1, node2;

    unordered_map<int, vector<int>> directed_graph = {
        {0,{1,3}},
        {1,{2,4}},
        {2,{10}},
        {3,{4,8}},
        {4,{5,6}},
        {5,{}},
        {6,{}},
        {7,{1,2}},
        {8,{9}},
        {9,{6,11}},
        {10,{4,12}},
        {11,{}},
        {12,{}}
    };
    
    // test 1
    node1 = 3;
    node2 = 6;
    expected_path = {3,4,6};
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 2
    node1 = 0;
    node2 = 11;
    expected_path = {0,3,8,9,11};
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 3
    node1 = 0;
    node2 = 5;
    expected_path = {0,1,4,5};
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 4
    node1 = 0;
    node2 = 7;
    expected_path = {}; // no path exists
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 5
    node1 = 5;
    node2 = 6;
    expected_path = {}; // no path exists
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);


    // test 6
    node1 = 13;
    node2 = 7;
    expected_path = {}; // no path exists, node1 doesnt exist
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 7
    node1 = 4;
    node2 = 14;
    expected_path = {}; // no path exists, node2 doesnt exist
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 8
    node1 = 13;
    node2 = 14;
    expected_path = {}; // no path exists, node1 & node2 neither exist
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 8
    node1 = 0;
    node2 = 0;
    expected_path = {}; // no path exists, both nodes are same and there isnt a self path
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 9
    node1 = 12;
    node2 = 7;
    expected_path = {}; // no path exists, both nodes are same and there isnt a self path
    code_path = sol.shortest_path(directed_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

}



void test_undirected_graph(){
    Solution sol;
    vector<int> code_path ;
    vector<int> expected_path ;
    int node1, node2;

    unordered_map<int, vector<int>> undirected_graph = {
        {0,{1,3}},
        {1,{0,2,4,7}},
        {2,{1,7,10}},
        {3,{0,4,8}},
        {4,{1,3,5,6,10}},
        {5,{4}},
        {6,{4,9}},
        {7,{1,2}},
        {8,{3,9}},
        {9,{6,8,11}},
        {10,{2,4,12}},
        {11,{9}},
        {12,{10}}
    };
    
    // test 1
    node1 = 3;
    node2 = 6;
    expected_path = {3,4,6};
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 2
    node1 = 0;
    node2 = 11;
    expected_path = {0,3,8,9,11};
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 3
    node1 = 0;
    node2 = 5;
    expected_path = {0,1,4,5};
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 4
    node1 = 0;
    node2 = 7;
    expected_path = {0,1,7}; 
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 5
    node1 = 5;
    node2 = 6;
    expected_path = {5,4,6}; 
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);


    // test 6
    node1 = 13;
    node2 = 7;
    expected_path = {}; // no path exists, node1 doesnt exist
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 7
    node1 = 4;
    node2 = 14;
    expected_path = {}; // no path exists, node2 doesnt exist
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 8
    node1 = 13;
    node2 = 14;
    expected_path = {}; // no path exists, node1 & node2 neither exist
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 8
    node1 = 0;
    node2 = 0;
    expected_path = {}; // no path exists, both nodes are same and there isnt a self path
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

    // test 9
    node1 = 12;
    node2 = 7;
    expected_path = {12,10,2,7}; 
    code_path = sol.shortest_path(undirected_graph, node1,node2);
    sol.test(node1, node2, expected_path, code_path);

}




int main(){
    cout<<" \n\n------ Test on Directed Graph -----------";
    test_directed_graph() ;

    cout<<" \n\n------ Test on UnDirected Graph -----------";
    test_undirected_graph();                                              
}