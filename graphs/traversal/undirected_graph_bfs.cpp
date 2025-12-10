/* Adjacency List Implementation of Undirected Graph : using unordered_map &
 * unordered_set
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

enum class State : int {
  UNVISITED = -1,
  LANDED = 0,
  VISITED = 1,
};

// UGraph is an Undirected Graph
class UGraph {
private:
  unordered_map<int, unordered_set<int>> graph;

public:
  UGraph(vector<int> nodes, vector<unordered_set<int>> neighbors);
  vector<int> bfs_with_status_map(int start_node);
  vector<int> bfs_with_color_sets(int start_node);
  vector<int> bfs_standard(int start_node);
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

vector<int> UGraph::bfs_with_status_map(int start_node) {

  queue<int> bfs_q;
  vector<int> order;
  unordered_map<int, State> status;
  for (auto x : graph) {
    status.insert({x.first, State::UNVISITED});
  }

  bool unvisited_nodes_exist = true;

  // As long as there are unvisited_nodes continue traversing
  // There could be disconnected nodes
  while (unvisited_nodes_exist) {

    bfs_q.push(start_node);
    int current;
    // As long as the queue is not empty continue traversing
    while (bfs_q.size() != 0) {
      current = bfs_q.front();
      bfs_q.pop();
      order.push_back(current);
      status[current] = State::VISITED;
      auto &neighbors = graph[current];
      for (int neighbor : neighbors) {
        if (status[neighbor] == State::UNVISITED) {
          bfs_q.push(neighbor);
          status[neighbor] = State::LANDED;
        }
      }
    }
    // Find the next unvisited node
    unvisited_nodes_exist = false;
    for (auto &x : status) {
      if (x.second == State::UNVISITED) {
        start_node = x.first;
        unvisited_nodes_exist = true;
        break;
      }
    }
  }

  return order;
}

vector<int> UGraph::bfs_with_color_sets(int start_node) {

  queue<int> bfs_q;
  vector<int> order;
  unordered_set<int> white; // unvisited
  unordered_set<int> grey;  // visited but not explored
  unordered_set<int> black; // explored

  // Create an ordered set of the nodes
  for (auto x : graph) {
    white.insert(x.first);
  }

  // As long as there are unvisited_nodes continue traversing
  // There could be disconnected nodes
  while (white.size() != 0) {
    // i) push it to the bfs_queue.
    // ii) move it from white to grey
    bfs_q.push(start_node);
    white.erase(start_node);
    grey.insert(start_node);

    int current;
    while (bfs_q.size()) {
      // i) pop it from the bfs_queue.
      // ii) move it from grey to black
      // iii) add to traversal order
      current = bfs_q.front();
      bfs_q.pop();
      grey.erase(current);
      black.insert(current);
      order.push_back(current);
      // Check for neighbors and add them to the queue
      auto &neighbors = graph[current];
      for (auto neighbor : neighbors) {
        // If neighbor has not been visited
        if (white.find(neighbor) != white.end()) {
          // i) push it to the bfs_queue.
          // ii) move it from white to grey
          bfs_q.push(neighbor);
          white.erase(neighbor);
          grey.insert(neighbor);
        }
      }
    }

    if (white.size() != 0) {
      start_node = *white.begin();
    }
  }

  return order;
}

vector<int> UGraph::bfs_standard(int start_node) {

  queue<int> bfs_q;
  vector<int> order;
  unordered_set<int> visited; // visited but not necessarily explored

  // As long as there are unvisited_nodes continue traversing
  // There could be disconnected nodes
  bool use_start_node = true;
  for (auto &x : graph) {
    if (visited.count(x.first)) {
      continue;
    }
    if (use_start_node) {
      bfs_q.push(start_node);
      visited.insert(start_node);
      use_start_node = false;
    } else {
      bfs_q.push(x.first);
      visited.insert(x.first);
    }

    while (bfs_q.size() != 0) {
      // i) pop it from the bfs_queue.
      // ii) add to traversal order
      int current = bfs_q.front();
      bfs_q.pop();
      order.push_back(current);
      // Check for neighbors and add them to the queue
      auto &neighbors = graph[current];
      for (auto neighbor : neighbors) {
        // If neighbor has not been visited
        if (visited.count(neighbor) == 0) {
          bfs_q.push(neighbor);
          visited.insert(neighbor);
        }
      }
    }
  }
  return order;
}

int main() {
  vector<int> nodes = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<unordered_set<int>> neighbors = {
      {1, 3, 5}, {0, 2, 3, 4, 6}, {1, 4, 7}, {0, 1, 5, 6}, {1, 2, 6},
      {0, 3, 6}, {3, 4, 5, 7},    {2, 6},    {9},          {8}};
  UGraph g(nodes, neighbors);
  vector<int> order;
  order = g.bfs_with_status_map(0);
  cout << "\n bfs(status map): traversal order: ";
  for (auto x : order) {
    cout << x << ",";
  }
  cout << "\n";

  order = g.bfs_with_color_sets(0);
  cout << "\n bfs(color sets): traversal order: ";
  for (auto x : order) {
    cout << x << ",";
  }
  cout << "\n";

  order = g.bfs_standard(8);
  cout << "\n bfs(standard): traversal order: ";
  for (auto x : order) {
    cout << x << ",";
  }
  cout << "\n";
}
