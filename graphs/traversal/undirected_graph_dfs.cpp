/* DFS : Depth First Search on Undirected Graph
various implementations for comparison
See accompanying README.md
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// UGraph is an Undirected Graph
class UGraph {
private:
  unordered_map<int, unordered_set<int>> graph;

public:
  UGraph(unordered_map<int, unordered_set<int>> const &graph);
  vector<int> dfs_standard_lambda(int start_node);
};

// Use initialization list in constructor
/*
i) Uses const& : constant reference to prevent copying of the entire map input
into the method variable graph_input

*/
UGraph::UGraph(unordered_map<int, unordered_set<int>> const &graph_input)
    : graph(graph_input) {}

// Standard implementation of dfs. It uses a lambda function
vector<int> UGraph::dfs_standard_lambda(int start_node) {
  stack<int> dfs_s;
  vector<int> order;
  unordered_set<int> visited;

  // dfs_connected_nodes is the lambda function
  auto dfs_connected_nodes = [&](int root) {
    dfs_s.push(root);
    order.push_back(root);
    visited.emplace(root);

    while (!dfs_s.empty()) {
      auto current = dfs_s.top();
      bool all_children_traversed = true;

      for (auto &child : graph[current]) {
        auto it = visited.find(child);
        // child has not been visited before
        if (it == visited.end()) {
          all_children_traversed = false;
          dfs_s.push(child);
          order.push_back(child);
          visited.emplace(child);
          break;
        }
      }

      if (all_children_traversed) {
        dfs_s.pop();
      }
    }
  };

  // If start_node is found , only then start dfs from that node
  if (graph.find(start_node) != graph.end()) {
    dfs_connected_nodes(start_node);
  }
  for (auto &node : graph) {
    auto it = visited.find(node.first);
    // Node has not been visited before
    if (it == visited.end()) {
      dfs_connected_nodes(node.first);
    }
  }

  return order;
}

int main() {
  unordered_map<int, unordered_set<int>> map = {
      {0, {1, 3, 5}},    {1, {0, 2, 3, 4, 6}}, {2, {1, 4, 7}},
      {3, {0, 1, 5, 6}}, {4, {1, 2, 6}},       {5, {0, 3, 6}},
      {6, {3, 4, 5, 7}}, {7, {2, 6}},          {18, {19}},
      {19, {18}}};
  UGraph g(map);
  vector<int> order;
  order = g.dfs_standard_lambda(0);
  cout << "\n \n dfs(standard): traversal order: ";
  for (auto x : order) {
    cout << x << ",";
  }
  cout << '\n';
}
