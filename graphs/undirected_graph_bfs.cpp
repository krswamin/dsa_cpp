/* Adjacency List Implementation of Undirected Graph : using unordered_map &
 * unordered_set
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

enum class State : int {
  UNVISITED = -1,
  LANDED    =  0,
  VISITED   =  1,
};

// UGraph is an Undirected Graph
class UGraph {
private:
  unordered_map<int, unordered_set<int>> graph;

public:
  UGraph(vector<int> nodes, vector<unordered_set<int>> neighbors);
  void add_node(int new_node_num, const unordered_set<int> &neighbors);
  void delete_node(int delete_node_num);
  void add_edge(int idx1, int idx2);
  void delete_edge(int idx1, int idx2);
  void print();
  vector<int> bfs_with_status_map(int start_node);
  vector<int> bfs_with_color_sets(int start_node); 
};

// Use initialization list in constructor
UGraph::UGraph(vector<int> nodes, vector<unordered_set<int>> neighbors) {
  if (nodes.size() != neighbors.size()) {
    cout << "Mismatch between nodes and neighbor entries. ";
    cout << "nodes size is: " << nodes.size()
         << "neighbors size is: " << neighbors.size() << "\n";
    return;
  }

  for (size_t i = 0; i < nodes.size(); i++) {
    graph.insert({nodes[i], neighbors[i]});
  }
}

void UGraph::add_node(int new_node, const unordered_set<int> &neighbors) {
  // Ensure that the node is not prexsiting
  if (graph.find(new_node) != graph.end()) {
    cout << "Cannot add node. Node already exists:" << new_node << ". ";
    return;
  }

  // Ensure that all the new node's neighbors exist
  for (int n : neighbors) {
    if (graph.find(n) == graph.end()) {
      cout << "Cannot add node: neighbor " << n << " does not exist\n";
      return;
    }
  }

  // Add the new nodes as a connection to the other nodes that it is connected
  // to
  for (int neighbor : neighbors) {
    graph[neighbor].insert(new_node);
  }
  // Add the new nodes with its connections as the latest entry into the
  // adjacency list
  graph.insert({new_node, neighbors});
}

/* When deleting a node
i) delete the row of that node
ii) in all other rows delete every occurence of that node as a neighbor
*/
void UGraph::delete_node(int delete_node) {
  // i) Delete the node at its index position. This deletes the entire row
  graph.erase(delete_node);

  // Delete the node as a connection from other indices
  for (auto &node : graph) {
    // Delete the node occurence in every row.
    node.second.erase(delete_node);
  }
}

void UGraph::add_edge(int idx1, int idx2) {
  // For idx1 add idx2 as a connection.
  // If idx2 is already a connection, it is ignored. unordered_set doesn't
  // support duplicates
  graph.at(idx1).insert(idx2);

  // For idx2 add idx1 as a connection.
  // If idx1 is already a connection, it is ignored. unordered_set doesn't
  // support duplicates
  graph.at(idx2).insert(idx1);
}

void UGraph::delete_edge(int idx1, int idx2) {
  // For idx1, delete idx2.
  graph.at(idx1).erase(idx2);

  // For idx2, delete idx1.
  graph.at(idx2).erase(idx1);
}

void UGraph::print() {
  for (const auto &g : graph) {
    cout << g.first << ":";
    for (const auto &neighbor : g.second) {
      cout << neighbor << ",";
    }
    cout << "\n";
  }
}

vector<int> UGraph::bfs_with_status_map(int start_node){

  queue<int> bfs_q;
  vector<int> traverse; 
  unordered_map<int,State> status;
  for(auto x:graph){
    status.insert({x.first, State::UNVISITED});
  }
  
  bool unvisited_nodes_exist = true; 
  
  // As long as there are unvisited_nodes continue traversing
  // There could be disconnected nodes
  while(unvisited_nodes_exist) {

    bfs_q.push(start_node);  
    int current;
    // As long as the queue is not empty continue traversing
    while(bfs_q.size() !=0){
      current = bfs_q.front();
      bfs_q.pop();    
      traverse.push_back(current);
      status[current] = State::VISITED;
      auto& neighbors = graph[current];
      for (int neighbor: neighbors){
        if (status[neighbor] == State::UNVISITED){
          bfs_q.push(neighbor);
          status[neighbor] = State::LANDED;
        }
      }
    }
    // Find the next unvisited node
    unvisited_nodes_exist = false;
    for(auto& x: status){
      if(x.second == State::UNVISITED){
        start_node = x.first;
        unvisited_nodes_exist = true;
        break;
      }
    }
}

return traverse;
}


int main() {
  vector<int> nodes = {0, 1, 2, 3, 4, 5, 6, 7,8,9};
  vector<unordered_set<int>> neighbors = {{1,3,5},
                                          {0,2,3,4,6}, 
                                          {1,4,7},
                                          {0,1,5,6}, 
                                          {1,2,6}, 
                                          {0,3,6},
                                          {3,4,5,7},
                                          {2,6},
                                          {9},
                                          {8} };
  UGraph g(nodes, neighbors);
  vector<int> traverse;
  traverse = g.bfs_with_status_map(0);
  cout<<"\n bfs: traverse :";
  for(auto x: traverse){
    cout<<x<<",";
  }
  cout<<"\n"; 

}
