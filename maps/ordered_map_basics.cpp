#include <iostream>
#include <map>

using namespace std;

int main() {
  map<int, string> map1 = {
      {11, "Krithika"}, {53, "random"}, {17, "Vasanthi"}, {23, "Swaminathan"}};

  cout << "\n Map: before modifications (notice that it is sorted in ascending "
          "order)  \n";
  for (auto x : map1) {
    cout << x.first << ":" << x.second << "\n";
  }
  // i) Search : key not found
  auto it = map1.find(9);
  if (it != map1.end()) {
    cout << "\n Map: Saumil found:" << it->first << "," << it->second << "\n";
  } else {
    cout << "\n Map: Saumil not found";
  }

  // ii) Deletion
  map1.erase(53);

  // iii) Add using emplace
  // Emplace is better than insert. More efficient
  map1.emplace(6, "Pranav");
  map1.emplace(1, "Soumya");

  // iv) Add using insert
  // Insert expects a pair. If you have the data ready insert might be
  // preferable But emplace is generally preferable
  map1.insert({9, "Saumil"});

  cout << "\n\n Map: after modifications (notice that it is sorted in "
          "ascending order) \n";
  for (auto x : map1) {
    cout << x.first << ":" << x.second << "\n";
  }

  // v) Search : key found
  it = map1.find(9);
  if (it != map1.end()) {
    cout << "\n Map: Saumil found:" << it->first << "," << it->second << "\n";
  } else {
    cout << "\n Map: Saumil not found: \n";
  }

  return 0;
}
