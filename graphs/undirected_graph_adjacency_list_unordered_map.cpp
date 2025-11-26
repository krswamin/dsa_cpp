/* Adjacency List Implementation of Undirected Graph : using unordered_map & unordered_set
*/

#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
using namespace std;


// UGraph is an Undirected Graph
class UGraph{
    private:
        unordered_map<int, unordered_set<int>> graph;

    public:
        UGraph(vector<int> nodes, vector<unordered_set<int>> neighbors);
        void add_node(int new_node_num, const unordered_set<int>& neighbors);
        void delete_node(int delete_node_num);
        void add_edge(int idx1, int idx2);
        void delete_edge(int idx1, int idx2);
        void print();
};

// Use initialization list in constructor
UGraph::UGraph(vector<int> nodes, vector<unordered_set<int>> neighbors){
    if(nodes.size() != neighbors.size()){
        cout<<"Mismatch between nodes and neighbor entries. ";
        cout<<"nodes size is: "<< nodes.size()<<"neighbors size is: "<< neighbors.size()<< "\n";
        return; 
    }

    for (size_t i = 0; i < nodes.size(); i++){
        graph.insert({nodes[i],neighbors[i]});
    }
}

void UGraph::add_node(int new_node, const unordered_set<int>& neighbors) {
    // Ensure that the node is not prexsiting
    if (graph.find(new_node) != graph.end()) {
        cout<<"Cannot add node. Node already exists:"<<new_node<<". ";
        return; 
    }
    
    // Ensure that all the new node's neighbors exist
    for (int n : neighbors) {
        if (graph.find(n) == graph.end()) {
            cout << "Cannot add node: neighbor " << n << " does not exist\n";
            return;
        }
    }

    // Add the new nodes as a connection to the other nodes that it is connected to
    for (int neighbor: neighbors){
        graph[neighbor].insert(new_node);
    }
    // Add the new nodes with its connections as the latest entry into the adjacency list
    graph.insert({new_node, neighbors});
}

/* When deleting a node
i) delete the row of that node
ii) in all other rows delete every occurence of that node as a neighbor
*/
void UGraph::delete_node(int delete_node){
    // i) Delete the node at its index position. This deletes the entire row
    graph.erase(delete_node);

    // Delete the node as a connection from other indices
    for (auto &node: graph){
        // Delete the node occurence in every row.
        node.second.erase(delete_node);
    }
}

void UGraph::add_edge(int idx1, int idx2){
    // For idx1 add idx2 as a connection. 
    // If idx2 is already a connection, it is ignored. unordered_set doesn't support duplicates
    graph.at(idx1).insert(idx2);
    
    // For idx2 add idx1 as a connection. 
    // If idx1 is already a connection, it is ignored. unordered_set doesn't support duplicates
    graph.at(idx2).insert(idx1);
}


void UGraph::delete_edge(int idx1, int idx2){
    // For idx1, delete idx2.
    graph.at(idx1).erase(idx2);
    
    // For idx2, delete idx1. 
    graph.at(idx2).erase(idx1);
}

void UGraph::print(){
    for (const auto &g:graph){
        cout<<g.first<<":" ;
        for(const auto &neighbor:g.second){
            cout<<neighbor<<","; 
        }
        cout<<"\n";
    }
}

int main(){
    vector<int> nodes = {0,1,2,3};
    vector<unordered_set<int>> neighbors = {{1},{0,2}, {1,3}, {2}};
    UGraph g(nodes, neighbors);
    cout<<"Graph at start:\n";
    g.print();

    //Add Node
    cout<<"\n Add invalid node : 3 \n";
    g.add_node(3, {0,1});
    cout<<"\n Add valid node : 4 connected to 0 and 1 \n";
    g.add_node(4, {0,1});
    g.print();
    cout<<"\n Add a valid node : 5 connected to none, 6 connected to 0 \n";
    g.add_node(5, {});
    g.add_node(6, {0});
    g.print();

    //Add Edge
    cout<<"\n Add invalid edge : between 0 and 7 \n";
    g.add_edge(0,7);
    cout<<"\n Add valid edge : between 0 and 3 \n";
    g.add_edge(0,3);
    g.print();

    //Delete Edge
    cout<<"\n Delete invalid edge : between 0 and 7 \n";
    g.delete_edge(0,7);
    cout<<"\n Delete valid edge : between 1 and 2 \n";
    g.delete_edge(1,2);
    g.print();
    cout<<"\n Delete edge that doesnt exist: between 0 and 2 (no change in graph)\n";
    g.delete_edge(0,2);
    g.print();

    //Delete Node
    cout<<"\n Delete invalid node : 7 \n";
    g.delete_node(7);
    cout<<"\n Delete valid node: 2 \n";
    g.delete_node(2);
    g.print();
    cout<<"\n Delete valid node: 4 \n";
    g.delete_node(4);
    g.print();
}

