#include<iostream>
#include<vector>
using namespace std;

void rearrange_pos_neg(vector<int> &arr);
void print_array(const vector<int> &arr);
int main(){
    vector <vector<int>> arrs = {
        {5,-2,7,3,0,8,0,-6},
        {-1,10,8,7,-6,-6},
        {-2,-3,-8,7,-1,2},
        {0,1,-2,-3,-4,-5,-6,-7}};
    
    // KSW: L1
    // Deliberately using three for loops to demonstrate the need to use references with auto
    cout<<"\n\nArrays before rearrange(auto deduces by value): \n";
    for (auto arr: arrs) {       
        print_array(arr);
    }
    for (auto arr: arrs) {
        rearrange_pos_neg(arr);
    }
    cout<<"Array after rearrange: (nothing has been rearranged since auto deduces by value)\n";
    for (auto arr: arrs) {
        print_array(arr);
    }

    // KSW: L1
    // Deliberately using three for loops to demonstrate the need to use references with auto
    cout<<"\n\nArray before rearrange(use reference with auto): \n";
    for (auto &arr: arrs) {
        
        print_array(arr);
    }
    for (auto &arr: arrs) {
        rearrange_pos_neg(arr);
    }
    cout<<"Array after  rearrange: (array has been rearranged since auto uses reference)\n";
    for (auto &arr: arrs) {
        print_array(arr);
    }
}

void rearrange_pos_neg(vector<int> &arr){
    int next_neg_index = 0;
    int temp;
    for (int i=0; i<arr.size(); i++){
        if(arr[i]< 0) {
            // no need to swap if i and the next_neg_index are the same
            if (i!=next_neg_index){
            temp = arr[next_neg_index];
            arr[next_neg_index] = arr[i];
            arr[i] = temp;
            }
            next_neg_index ++;
        }  
    }
}

void print_array(const vector<int> &arr){
    for(int x:arr){
        cout<<x<<",";
    }
    cout<<"\n";
}