#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void print_array(const vector<int> &arr);
bool find_two_nums_for_k(vector<int> &arr, int k);

int main(){
   vector<vector <int>> arrs = {
      {-4,-8,0,-7,-3,-10},
      {-1,9,56,12,-13,-6,23,19,71,-56,-14},
      {3,3},
      {49,17,15,22,-45,29,18,-15,11,37,12,-52}
   };
    
    vector<int> k_values = {-15,-44,6,0};

    auto it_arr= arrs.begin();
    auto it_k = k_values.begin();
    bool nums_found; 
    while(it_arr != arrs.end() && it_k != k_values.end()){
        nums_found = find_two_nums_for_k(*it_arr,*it_k);

    }

}

bool find_two_nums_for_k(vector<int> &arr, int k){

}

void print_array(const vector<int> &arr){
    for(int x:arr){
        cout<<x<<",";
    }
    cout<<"\n";
}