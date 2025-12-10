/* Adjacency List Implementation of Undirected Graph : using vector<vector<int>>
Key takeaways:
i)   use initalization list in constructor
ii)  avoid copying large vectors . use references whenever possible
iii) use references for modifying individual numbers in a vector
iv)  wisely use find, count, remove from <algorithm>
v)   delete node requires the shifting of numbers in this implementation
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// UGraph is an Undirected Graph
class UGraph {
private:
  vector<vector<size_t>> graph;

public:
  UGraph(const vector<vector<size_t>> &g);
  void add_node(size_t new_node_num, const vector<size_t> &neighbors);
  void delete_node(size_t delete_node_num);
  void add_edge(size_t idx1, size_t idx2);
  void delete_edge(size_t idx1, size_t idx2);
  void print();
};

// Use initialization list in constructor
UGraph::UGraph(const vector<vector<size_t>> &g) : graph(g) {}

void UGraph::add_node(size_t new_node, const vector<size_t> &neighbors) {
  if (new_node != graph.size()) {
    cout << "Cannot add node. Invalid idx:" << new_node << ". ";
    cout << "Graph size is: " << graph.size()
         << ". Max graph idx = " << graph.size() - 1 << "\n";
    return;
  }

  // Ensure that all the new node's neighbors exist
  // Note : That the node can be its own neighbor i.e. self loop
  for (size_t n : neighbors) {
    if (n > graph.size()) {
      cout << "Cannot add node: neighbor " << n << " does not exist\n";
      return;
    }
  }
  // Add the new index as a connection to the other nodes that it is connected
  // to
  for (int idx_connected_to : neighbors) {
    graph[idx_connected_to].push_back(new_node);
  }
  // Add the new nodes with its connections as the latest entry into the
  // adjacency list
  graph.push_back(neighbors);
}

/* When deleting a node
i) delete the row of that node
ii) in all other rows delete every occurence of that node as a neighbor
iii) in all other rows , indices greater than the node, should be reduced by 1
*/
void UGraph::delete_node(size_t delete_node) {
  if (delete_node >= graph.size()) {
    cout << "Cannot delete node. Invalid idx:" << delete_node << ". ";
    cout << "Graph size is: " << graph.size()
         << ". Max graph idx = " << graph.size() - 1 << "\n";
    return;
  }

  // i) Delete the node at its index position. This deletes the entire row
  graph.erase(graph.begin() + delete_node);

  // Delete the node as a connection from other indices
  for (auto &vect : graph) {
    // Delete the node occurence in every row.
    vect.erase(remove(vect.begin(), vect.end(), delete_node), vect.end());

    // Shift numbers
    for (auto &v : vect) {
      if (v > delete_node) {
        --v;
      }
    }
  }
}

void UGraph::add_edge(size_t idx1, size_t idx2) {
  // Check for validity of indices
  if (idx1 >= graph.size() || idx2 >= graph.size()) {
    cout << "Cannot add edge. One or more invalid indices:" << idx1 << ","
         << idx2 << ". ";
    cout << "Graph size is: " << graph.size()
         << ". Max graph idx = " << graph.size() - 1 << "\n";
    return;
  }

  // For idx1, check if idx2 is a prexisting connection.
  // If the connection doesnt exist , add it
  if (!count(graph[idx1].begin(), graph[idx1].end(), idx2)) {
    graph[idx1].push_back(idx2);
  }

  // For idx2, check if idx1 is a prexisting connection.
  // If the connection doesnt exist , add it
  if (!count(graph[idx2].begin(), graph[idx2].end(), idx1)) {
    graph[idx2].push_back(idx1);
  }
}

void UGraph::delete_edge(size_t idx1, size_t idx2) {
  // Check for validity of indices
  if (idx1 >= graph.size() || idx2 >= graph.size()) {
    cout << "Cannot delete edge. One or more invalid indices:" << idx1 << ","
         << idx2 << ". ";
    cout << "Graph size is: " << graph.size()
         << ". Max graph idx = " << graph.size() - 1 << "\n";
    return;
  }

  // For idx1, check if idx2 is a prexisting connection.
  // If the connection exists, delete it
  graph[idx1].erase(remove(graph[idx1].begin(), graph[idx1].end(), idx2),
                    graph[idx1].end());

  // For idx2, check if idx1 is a prexisting connection.
  // If the connection exists, delete it
  graph[idx2].erase(remove(graph[idx2].begin(), graph[idx2].end(), idx1),
                    graph[idx2].end());
}

void UGraph::print() {
  size_t i = 0;
  for (const auto &vect : graph) {
    cout << i << ":";
    for (const auto &x : vect) {
      cout << x << ",";
    }
    cout << "\n";
    i++;
  }
}

int main() {
  vector<vector<size_t>> v = {{1}, {0, 2}, {1, 3}, {2}};
  UGraph g(v);
  cout << "Graph at start:\n";
  g.print();

  // Add Node
  cout << "\n Add invalid node : 3 \n";
  g.add_node(3, {0, 1});
  cout << "\n Add valid node : 4 connected to 0 and 1 \n";
  g.add_node(4, {0, 1});
  g.print();
  cout << "\n Add a valid node : 5 connected to none, 6 connected to 0 \n";
  g.add_node(5, {});
  g.add_node(6, {0});
  g.print();

  // Add Edge
  cout << "\n Add invalid edge : between 0 and 7 \n";
  g.add_edge(0, 7);
  cout << "\n Add valid edge : between 0 and 3 \n";
  g.add_edge(0, 3);
  g.print();

  // Delete Edge
  cout << "\n Delete invalid edge : between 0 and 7 \n";
  g.delete_edge(0, 7);
  cout << "\n Delete valid edge : between 1 and 2 \n";
  g.delete_edge(1, 2);
  g.print();
  cout << "\n Delete edge that doesnt exist: between 0 and 2 (no change in "
          "graph)\n";
  g.delete_edge(0, 2);
  g.print();

  // Delete Node
  cout << "\n Delete invalid node : 7 \n";
  g.delete_node(7);
  cout
      << "\n Delete valid node: 2, ensure that indices > 2 are shifted by 1 \n";
  g.delete_node(2);
  g.print();
  cout
      << "\n Delete valid node: 4, ensure that indices > 4 are shifted by 1 \n";
  g.delete_node(4);
  g.print();
}
