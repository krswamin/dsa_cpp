#include <iostream>
#include <vector>

using namespace std;

void reverse(vector<int> &arr, int start_idx, int end_idx);
void right_rotate(vector<int> &arr, int k);
void print_array(const vector<int> &arr);

int main() {
  vector<vector<int>> arrs = {{-1, 10, 8, 7, -6, 6}, {2, 3, -8, 7, -1, 2}};

  vector<int> right_rots = {2, 5};

  auto it1 = arrs.begin();
  auto it2 = right_rots.begin();

  while (it1 != arrs.end() && it2 != right_rots.end()) {
    cout << "\n\n Array before rotation:";
    print_array(*it1);

    right_rotate(*it1, *it2);
    cout << "\n Array after rotation by " << *it2 << " steps: ";
    print_array(*it1);

    it1++;
    it2++;
  }
}

void reverse(vector<int> &arr, int start_idx, int end_idx) {
  int temp;
  while (start_idx < end_idx) {
    // Swap the left and right index elements
    temp = arr[start_idx];
    arr[start_idx] = arr[end_idx];
    arr[end_idx] = temp;
    start_idx++;
    end_idx--;
  }
}

void right_rotate(vector<int> &arr, int k) {
  // handle when no rotation is needed
  if (k <= 0 || arr.size()) {
    return;
  }
  // handle if k > array size
  k = k % arr.size();

  reverse(arr, 0, arr.size() - 1);
  reverse(arr, 0, k - 1);
  reverse(arr, k, arr.size() - 1);
}

void print_array(const vector<int> &arr) {
  for (int x : arr) {
    cout << x << ",";
  }
  cout << "\n";
}
