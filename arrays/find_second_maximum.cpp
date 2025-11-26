/*
key learning. Think of max and smax being on a number line
Handle the case when xmax=smax and then the number you are examining is above or
below that
*/
#include <iostream>
#include <vector>
using namespace std;

bool second_maximum(const vector<int> &arr, int &smax);
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
                              {-3, -2},
                              {}};

  int smax;

  for (auto &arr : arrs) {
    cout << "\n Array:";
    print_array(arr);

    if (second_maximum(arr, smax)) {
      cout << "Second maximum: " << smax << "\n";
    } else {
      cout << "Second Maximum absent \n";
    }
  }
}

bool second_maximum(const vector<int> &arr, int &smax) {
  int max;

  if (arr.size() < 2) {
    return false;
  }

  max = arr[0];
  smax = arr[0];

  for (auto x : arr) {
    if (x > max) {
      smax = max;
      max = x;
    } else if (x < max && x > smax) {
      smax = x;
    }
    // note x<smax condition here is redundant because it would reach here only
    // if x<smax
    else if (max == smax) {
      smax = x;
    }
  }
  if (smax == max) {
    return false;
  } else {
    return true;
  }
}

void print_array(const vector<int> &arr) {
  for (int x : arr) {
    cout << x << ",";
  }
  cout << "\n";
}