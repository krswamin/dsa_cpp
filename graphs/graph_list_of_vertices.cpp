#include <iostream>
#include <vector>
#include <optional>

using namespace std;

class Vertex{
    private: 
        unsigned int index;
        int value;
        optional<vector <unsigned int>> indices_connected_to;

    public: 
        Vertex();
        Vertex(unsigned int index, 
               int value, 
               const optional<vector<unsigned int>>& indices_connected_to);
        void set_vertex(unsigned int index,
                        int value, 
                        const optional<vector<unsigned int>>& indices_connected_to);
        void print_vertex();
};

Vertex::Vertex() {}

/*
indices is passed by const reference, so no copy is made when passing it into the constructor.
But inside the constructor the line
  indices_connected_to(indices_connected_to);
performs a copy of the entire vector into the connected_indices member variable.
So connected_indices becomes a separate object, with its own dynamically allocated internal array, 
holding the same integer values as indices, but at a different memory location.
*/
Vertex::Vertex(unsigned int index, 
               int value, 
               const optional<vector<unsigned int>>& indices_connected_to):
               index(index), value(value), indices_connected_to(indices_connected_to) {}

void Vertex::set_vertex(unsigned int index,
                        int value, 
                        const optional<vector<unsigned int>>& indices_connected_to) {
    this->index = index;
    this->value = value;
    this->indices_connected_to = indices_connected_to; // This performs a copy
}

void Vertex::print_vertex() {
    cout<<"vertex: index = "<< this->index << ", value ="<< this->value << ", indices_connected_to: ";
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

class Graph{
    private:
    vector <Vertex> vertices;

    public:
    Graph(); 
    Graph(const vector<unsigned int>& indices,
          const vector<int>& values,
          const vector<optional<vector<unsigned int>>>&  connections);
    void print_graph();
};

// If you define any constructor, the compiler does not generate a default constructor automatically:
// Hence if you need a default constructor you would have to explicitly define one
Graph::Graph(){  
}

//  C++ doesn’t support nested heterogeneous containers (like Python does) out of the box.
//  You'd have to create a custom structure or class, or just pass the individual value
//  Hence the need for using 3 vectors to set the vertices
Graph::Graph(const vector<unsigned int>& indices, 
             const vector<int>& values, 
             const vector<optional<vector<unsigned int>>>&  connections){
    if (indices.size() != values.size() ) {
        throw runtime_error("indices, and values vectors have different sizes!");
    }
    if (indices.size() != connections.size() ) {
        throw runtime_error("indices, and connections vectors have different sizes!");
    }

   
    // Use pre-increment (++i) in C++. This is especially true for iterators
    // Potentially more efficient, especially for complex iterators (e.g., in std::list, std::map, custom iterators).
    // Avoids creating a temporary copy — post-increment (it++) creates a copy of the iterator before incrementing.
    for (size_t i = 0; i < indices.size(); ++i) {
        vertices.emplace_back(Vertex(indices[i], values[i], connections[i]));
    }
}


void Graph::print_graph(){
    for (auto vertex: this->vertices){
        vertex.print_vertex();
    }
}


int main() {      
    vector<unsigned int> indices = {0,1,2,3};
    vector<int> values = {0,1,2,3};

    // {1, 2} is not automatically understood as an optional<vector<unsigned int>> 
    // it needs explicit optional construction in some cases.
    vector<optional<vector<unsigned int>>> connections = {
        vector<unsigned int>{1, 2},
        vector<unsigned int>{3},
        vector<unsigned int>{3},
        nullopt
    };

    Graph g(indices, values, connections);
    g.print_graph();

    return 0;
}