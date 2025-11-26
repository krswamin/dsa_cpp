/*
Tree Implementation.
This is not a binary tree. Hence a vertex can have many nodes.

There is no check in this code to check for cyclicity.
So if the user set up the tree like a cyclical graph, there is no check on that.

DFS Traversal: This is a non recursive Depth First Search of a non-binary tree
Preorder Traversal from left to right.
See method for more details
Data Structures used:
Stack 1 stack<Vertex*>      : for Parent. stack of pointers to vertices.
Pointers make it efficient Stack 2 stack<unsigned int> : for
child-index-position Array   vector<Vertex*>     : for visited nodes. stack of
pointers to visited vertices Pointers make it efficient current_vertex: which
tracks the top of the parent stack

*/

#include <iostream>
#include <optional>
#include <stack>
#include <vector>

using namespace std;

class Vertex {
private:
  unsigned int index;
  int value;
  optional<vector<unsigned int>> indices_connected_to;

public:
  Vertex();
  Vertex(unsigned int index, int value,
         const optional<vector<unsigned int>> &indices_connected_to);
  void set_vertex(unsigned int index, int value,
                  const optional<vector<unsigned int>> &indices_connected_to);
  void print_vertex();
  unsigned int get_index();
  int get_value();
  optional<vector<unsigned int>> get_indices_connected_to();
};

// Default constructor
Vertex::Vertex() {}

/*
indices is passed by const reference, so no copy is made when passing it into
the constructor. But inside the constructor the line
  indices_connected_to(indices_connected_to);
performs a copy of the entire vector into the connected_indices member variable.
So connected_indices becomes a separate object, with its own dynamically
allocated internal array, holding the same integer values as indices, but at a
different memory location.
*/
Vertex::Vertex(unsigned int index, int value,
               const optional<vector<unsigned int>> &indices_connected_to)
    : index(index), value(value), indices_connected_to(indices_connected_to) {}

void Vertex::set_vertex(
    unsigned int index, int value,
    const optional<vector<unsigned int>> &indices_connected_to) {
  this->index = index;
  this->value = value;
  this->indices_connected_to = indices_connected_to; // This performs a copy
}

void Vertex::print_vertex() {
  cout << "vertex: index = " << this->index << ", value =" << this->value
       << ", indices_connected_to: ";
  if (indices_connected_to) {
    cout << "{";
    // Because it is optional, you would have to dereference is first
    for (unsigned int index_connected_to : *this->indices_connected_to) {
      cout << index_connected_to << ",";
    }
    cout << "} \n";
  } else {
    cout << "None(nullopt) \n";
  }
}

unsigned int Vertex::get_index() { return this->index; }

int Vertex::get_value() { return this->value; }

optional<vector<unsigned int>> Vertex::get_indices_connected_to() {
  return this->indices_connected_to;
}

class Tree {
private:
  vector<Vertex> vertices;

public:
  Tree();
  Tree(const vector<unsigned int> &indices, const vector<int> &values,
       const vector<optional<vector<unsigned int>>> &connections);
  void print_tree();
  void dfs();
  void print_dfs(const vector<Vertex *> &visited);
};

// If you define any constructor, the compiler does not generate a default
// constructor automatically: Hence if you need a default constructor you would
// have to explicitly define one
Tree::Tree() {}

//  C++ doesn’t support nested heterogeneous containers (like Python does) out
//  of the box. You'd have to create a custom structure or class, or just pass
//  the individual value Hence the need for using 3 vectors to set the vertices
Tree::Tree(const vector<unsigned int> &indices, const vector<int> &values,
           const vector<optional<vector<unsigned int>>> &connections) {
  if (indices.size() != values.size()) {
    throw runtime_error("indices, and values vectors have different sizes!");
  }
  if (indices.size() != connections.size()) {
    throw runtime_error(
        "indices, and connections vectors have different sizes!");
  }

  // Use pre-increment (++i) in C++. This is especially true for iterators
  // Potentially more efficient, especially for complex iterators (e.g., in
  // std::list, std::map, custom iterators). Avoids creating a temporary copy —
  // post-increment (it++) creates a copy of the iterator before incrementing.
  for (size_t i = 0; i < indices.size(); ++i) {
    vertices.emplace_back(Vertex(indices[i], values[i], connections[i]));
  }
}

// This just steps through the vertices stored as a list and prints
// There is no dfs or bfs involved here
void Tree::print_tree() {
  cout << "\n print_tree (as initialized) \n";
  for (auto vertex : this->vertices) {
    vertex.print_vertex();
  }
  cout << "\n";
}

/*
DFS Traversal: This is a non recursive Depth First Search of a non-binary tree
Preorder Traversal from left to right.
See method for more details
Data Structures used:
Stack 1 stack<Vertex*>      : for Parent. stack of pointers to vertices.
Pointers make it efficient Stack 2 stack<unsigned int> : for
child-index-position Array   vector<Vertex*>     : for visited nodes. stack of
pointers to visited vertices Pointers make it efficient current_vertex: which
tracks the top of the parent stack
*/
void Tree::dfs() {
  // Stacks and vectors needed
  stack<Vertex *> parent;
  stack<unsigned int> child_index_position;
  vector<Vertex *> visited;

  Vertex *current_vertex;
  optional<vector<unsigned int>> current_vertex_indices_connected;
  unsigned int child_index;
  unsigned int child_position;

  // Start with root vertex
  parent.push(&this->vertices[0]);

  while (!parent.empty()) {
    // Current vertex is always the parent.top()
    current_vertex = parent.top();
    current_vertex_indices_connected =
        (*current_vertex).get_indices_connected_to();
    // Add the current vertex to visited stack only if it is the first time you
    // are encountering it I.e before checking for children.
    if (child_index_position.size() == parent.size() - 1) {
      visited.push_back(current_vertex);
    }

    // Check for children
    // If vertex is not a leaf i.e  has children add the children to the
    // child_index_position stack
    if (current_vertex_indices_connected) {
      // No child has been visited
      // child index position stack: push the new child
      // parent stack: push the new child
      if (child_index_position.size() == parent.size() - 1) {
        child_position = 0;
        child_index = (*current_vertex_indices_connected)[child_position];
        child_index_position.push(child_position);
        parent.push(&this->vertices[child_index]);
      }
      // Some children have been visited.
      // child index position stack: pop the old child, push the new child
      // parent stack: push the new child
      else if (child_index_position.top() !=
               (*current_vertex_indices_connected).size() - 1) {
        child_position = child_index_position.top() + 1;
        child_index = (*current_vertex_indices_connected)[child_position];
        // Pop the old value
        child_index_position.pop();
        // Push the new value
        child_index_position.push(child_position);
        // Push the child to the parent
        parent.push(&this->vertices[child_index]);
      }
      // all children have been visited
      // i.e. child_index_position.top()
      // ==(*current_vertex_indices_connected).size()-1 parent stack: pop the
      // parent child index position stack: pop the corresponding child index
      // position
      else {
        // Pop the parent stack
        parent.pop();
        // pop the corresponding child_index_position
        child_index_position.pop();
      }
    }
    // if vertex is a leaf. nullopt, pop it from the parent stack
    else {
      // Pop the parent stack. The corresponding child_index_position is empty
      parent.pop();
    }
  }

  // print dfs traversalj
  print_dfs(visited);
}

// print_dfs
// vector<Vertex*> the * indicates you are passing pointers
// & indicates: it is a reference to a vector of Vertex pointers( prevents
// making copies) const indicates that you will not modify anything
void Tree::print_dfs(const vector<Vertex *> &visited) {
  cout << "\n DFS traversal nodes \n";
  for (auto vertex : visited) {
    (*vertex).print_vertex();
  }
  cout << "\n";
}

int main() {
  vector<unsigned int> indices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  vector<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  // {1, 2} is not automatically understood as an optional<vector<unsigned int>>
  // it needs explicit optional construction in some cases.
  vector<optional<vector<unsigned int>>> connections = {
      vector<unsigned int>{1, 5},      // 0 index connections
      vector<unsigned int>{2, 3, 4},   // 1 index connections
      nullopt,                         // 2 index connections
      vector<unsigned int>{12},        // 3 index connections
      nullopt,                         // 4 index connections
      vector<unsigned int>{6, 7},      // 5 index connections
      vector<unsigned int>{8},         // 6 index connections
      vector<unsigned int>{9, 10, 11}, // 7 index connections
      nullopt,                         // 8 index connections
      nullopt,                         // 9 index connections
      nullopt,                         // 10 index connections
      nullopt,                         // 11 index connections
      nullopt                          // 12 index connections
  };

  Tree tr1(indices, values, connections);
  tr1.print_tree();

  tr1.dfs();

  return 0;
}