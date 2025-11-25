#include <iostream>
#include <vector>

using namespace std;

class Vertex{
    private: 
        unsigned int index;
        int value;
        vector <unsigned int> indices_connected_to;

    public: 
        Vertex(unsigned int index, int value, const vector<unsigned int>& indices_connected_to);
        void print_vertex();
};

/*
indices is passed by const reference, so no copy is made when passing it into the constructor.
But inside the constructor the line
  this->indices_connected_to = indices_connected_to;
performs a copy of the entire vector into the connected_indices member variable.
So connected_indices becomes a separate object, with its own dynamically allocated internal array, 
holding the same integer values as indices, but at a different memory location.
*/
Vertex::Vertex(unsigned int index, int value, const vector<unsigned int>& indices_connected_to) {
    this->index = index;
    this->value = value;
    this->indices_connected_to = indices_connected_to; // This performs a copy
    cout<<"\n";
    cout<<"Vertex constructor: index= "<<index <<", value ="<< value << "\n";
    cout<<"Vertex constructor: &indices_connected_to : " << &indices_connected_to << "\n";
    cout<<"Vertex constructor: &this->indices_connected_to : " << &this->indices_connected_to << "\n";
}

void Vertex::print_vertex() {
    cout<<"\n";
    cout<<"print_vertex: index = "<< this->index << ", value ="<< this->value << ", indices_connected_to:{";
    for (unsigned int index_connected_to : this->indices_connected_to) {
            cout << index_connected_to << ", ";
        }
    cout << "} \n";
}


int main() {      
    cout<<"\n PASS BY REFERENCE: notice that &connections(main) and &indices_connected_to(constructor) are the same, \n\
    But &indices_connected_to(constructor) and &this->indices_connected_to(constructor) have different addresses . \n\
    This is because when passing, the same value/address location i.e. a reference is passed. \n\
    But inside the constructor a copy is made \n";

    cout<< "\n Note: By default, if you don't need to modify the passed set of vectors, pass by const reference is the preferred way to pass vectors \n"; 

    vector<unsigned int> connections = {1, 2};
    cout<<"\n &connections : " << &connections  << "\n";
    Vertex v1(0, 0, connections);
    v1.print_vertex();

    return 0;

}