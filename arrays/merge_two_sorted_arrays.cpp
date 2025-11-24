/*
Learning: 
1) read the order of size checks in merge array
2) compare merge_arrays_v1 and merge_arrays_v2 to see how code has been improved
*/
#include<iostream>
#include<vector>
using namespace std;

vector<int> merge_arrays_v1(const vector<int> &x1, const vector<int> &x2);
vector<int> merge_arrays_v2(const vector<int> &x1, const vector<int> &x2);

void print_array(const vector<int> &arr);
int main (){
    /*
    vector<int> a1 = {10,13,13,21,37};
    vector<int> a2 = {10,10,15,19,23,37,39};

    vector<int> a1 = {6,7,8,9,10} ;
    vector<int> a2 = {1,2,3,4,5}  ;

    vector<int> a1 = {-1,3} ;
    vector<int> a2 = {-1,-1,0,0,1,2}  ;

    */

    vector<int> a1 = {0,1,4,9};
    vector<int> a2 = {-111,-20,-5,5,11,20};

    vector<int> a3, a4;

    cout<<"\n parent array 1: ";
    print_array(a1);
    cout<<"\n parent array 2: ";
    print_array(a2);
    
    cout<<"\n merged array v1  : ";
    a3 = merge_arrays_v1(a1, a2);
    print_array(a3);
    
    cout<<"\n merged array v2  : ";
    a4 = merge_arrays_v2(a1, a2);
    print_array(a4);

}

vector<int> merge_arrays_v1(const vector<int> &x1, const vector<int> &x2){
    vector<int> x3(x1.size()+x2.size());

    int i =0;
    int j =0;
    int k =0;
    while(k<x1.size()+x2.size()){
        // KSW: important learning. the order of size checks here matter a lot
        // Swapping the condition orders could cause out of bound conditions
        if(j>=x2.size() || (i<x1.size() && x1[i]<x2[j])){
            x3[k] = x1[i];
            i++;
            
        }
        else {
            x3[k] = x2[j];
            j++;
        }
        k++;
    }

    return x3;

}
/* better improved version 
i) elminates k
ii) uses vector reserve to reserve space and pushback*/
vector<int> merge_arrays_v2(const vector<int> &x1, const vector<int> &x2){
    vector<int> x3;
    x3.reserve(x1.size()+x2.size());

    int i =0;
    int j =0;
    while(i<x1.size() && j<x2.size()){
        // KSW: important learning. the order of size checks here matter a lot
        // Swapping the condition orders could cause out of bound conditions
        if(x1[i]<x2[j]){
            x3.push_back(x1[i]);
            i++;
            
        }
        else {
            x3.push_back(x2[j]);
            j++;
        }
    }

    //Push the remaining elements of x1
    while(i<x1.size()){
        x3.push_back(x1[i]);
        i++;
    }

    //Push the remaining elements of x2
    while(j<x2.size()){
        x3.push_back(x2[j]);
        j++;
    }

    return x3;
}

void print_array(const vector<int> &arr){
    for(int x:arr){
        cout<<x<<",";
    }
    cout<<"\n";
}