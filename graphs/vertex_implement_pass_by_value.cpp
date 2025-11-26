#include <iostream>
#include <vector>

using namespace std;

class Vertex {
private:
  unsigned int index;
  int value;
  vector<unsigned int> indices_connected_to;

public:
  Vertex(unsigned int index, int value,
         vector<unsigned int> indices_connected_to);
  void print_vertex();
};

Vertex::Vertex(unsigned int index, int value,
               vector<unsigned int> indices_connected_to) {
  this->index = index;
  this->value = value;
  this->indices_connected_to = indices_connected_to; // This performs a copy
  cout << "\n";
  cout << "Vertex constructor: index= " << index << ", value =" << value
       << "\n";
  cout << "Vertex constructor: &indices_connected_to : "
       << &indices_connected_to << "\n";
  cout << "Vertex constructor: &this->indices_connected_to : "
       << &this->indices_connected_to << "\n";
}

void Vertex::print_vertex() {
  cout << "\n";
  cout << "print_vertex: index = " << this->index << ", value =" << this->value
       << ", indices_connected_to:{";
  for (unsigned int index_connected_to : this->indices_connected_to) {
    cout << index_connected_to << ", ";
  }
  cout << "} \n";
}

int main() {
  cout << "\n PASS BY VALUE: notice that &connections(main), \
    &indices_connected_to(constructor), &this->indices_connected_to(constructor), \
    all have different addresses . \n This is because at every stage a copy is made .\n";

  cout << "\n Note: By default, if you don't need to modify the passed set of "
          "vectors, pass by const reference is the preferred way to pass "
          "vectors \n";

  vector<unsigned int> connections = {1, 2};
  cout << "\n &connections : " << &connections << "\n";
  Vertex v1(0, 0, connections);
  v1.print_vertex();

  return 0;
}