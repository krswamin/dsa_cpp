#include<iostream>
#include<set>

using namespace std;

int main(){
     set <string> set1 = {"Krithika",
                          "random",
                          "Vasanthi",
                          "Swaminathan"
                          };
    
    cout<<"\n set: before modifications (notice that it is sorted in ascending order)  \n";
    for (auto x: set1){
        cout<<x<<"\n";
    }
    // i) Search : key not found
    auto it = set1.find("Saumil");
    if (it != set1.end()){
         cout<<"\n set: Saumil found:"<<*it<<"\n";
    } else {
         cout<<"\n set: Saumil not found";
    }
   

    // ii) Deletion
    set1.erase("random");

    // iii) Add using emplace
    // Emplace is better than insert. More efficient    
    set1.emplace("Soumya");
    set1.emplace("Pranav");

    // iv) Add using insert
    // Insert expects a pair. If you have the data ready insert might be preferable
    // But emplace is generally preferable
    set1.insert("Saumil");

    cout<<"\n\n set: after modifications (notice that it is sorted in ascending order) \n";
    for (auto x: set1){
        cout<<x<<"\n";
    }

    // v) Search : key found
    it = set1.find("Saumil");
    if (it != set1.end()){
         cout<<"\n set: Saumil found:"<<*it<<"\n";
    } else {
         cout<<"\n set: Saumil not found:\n";
    }

    return 0;

}
