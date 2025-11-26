#include <iostream>
#include <vector>
using namespace std;

int find_min(const vector<int> &arr);
void print_array(const vector<int> &arr);

int main() {

  vector<vector<int>> arrs = {{-2, -4, 1, 8, 13, 27, 8},
                              {-2, -2, -2, -2},
                              {-3, -3, -3, -3, -3, -2},
                              {-10, 10},
                              {-3, -3, -2, -3, -3, -1, -1, -1},
                              {-3, -3, -3, -3, -3, -2},
                              {-2, -2, -2, -2, -2, -3},
                              {-2, -2, -3, -2, -2, -2},
                              {-2, -3},
                              {-6, 6, 0},
                              {7},
                              {-3, -2}};

  int min;

  for (auto &arr : arrs) {
    cout << "\n Array:";
    print_array(arr);

    min = find_min(arr);
    cout << "Minimim: " << min << "\n";
  }
}

int find_min(const vector<int> &arr) {
  int min = arr[0];
  for (int x : arr) {
    if (x < min) {
      min = x;
    }
  }

  return min;
}

void print_array(const vector<int> &arr) {
  for (int x : arr) {
    cout << x << ",";
  }
  cout << "\n";
}