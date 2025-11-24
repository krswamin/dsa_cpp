#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void delete_even_numbers(vector<int> &arr);
void print_array(const vector<int> &arr);

int main(){
    
    vector<vector<int>> arrs = {
        {-2,-4,1,8,13,27,8},
        {-6,6,0},
        {1,9,3}};
    
    //KSW: deliberately using 3 for loops to demonstrate the utility of using references with auto
    cout<<"\n\n Original Array:\n";
    for(auto &arr:arrs){
        print_array(arr);
    }

    for(auto &arr:arrs){      
        delete_even_numbers(arr);
    }
    
    cout<<"\n Array after deleting even numbers:\n";
    for(auto &arr:arrs)  {       
        print_array(arr);
    }

    // Test using remove_if
    arrs = {
        {-2,-4,1,8,13,27,8},
        {1,9,3},
        {-6,6,0}};
    
    //KSW: deliberately using 3 for loops to demonstrate the utility of using references with auto
    cout<<"\n------------------\n Original Array:\n";
    for(auto &arr:arrs){
        print_array(arr);
    }

    for(auto &arr:arrs){      
        delete_even_numbers(arr);
    }
    
    cout<<"\n Array after deleting even numbers(using remove if):\n";
    for(auto &arr:arrs)  {       
        print_array(arr);
    }

    }

void delete_even_numbers(vector<int> &arr){
    for(int i=0; i<arr.size();){
        if (arr[i]%2 ==0){
            arr.erase(arr.begin()+i);
        }
        //increment index only if nothing has been deleted
        else{
            i++;
        }
    }
}


void delete_even_numbers_using_remove_if(vector<int> &arr){
    // KSW: remove_if reorders the array inplace. The items to be deleted are at the end
    // It returns the new end index
    auto new_end = remove_if(arr.begin(), arr.end(), [](int x){ return x % 2 == 0; });
    arr.erase(new_end, arr.end());
}

void print_array(const vector<int> &arr){
    for(int x:arr){
        cout<<x<<",";
    }
    cout<<"\n";
}