/* Note
1) using arrays is not recommended. Using vectors is preferred
This code is in place because educative.io expects arrays and not vectors

2) observe how new and delete are used
Every new is accompanied by a delete. The variable new_arr is created using new
in remove_even function It is deleted in the main , even though it was created
inside new_arr. This is because remove_even was created on the heap using new
and delete in this manner is not recommended in modern c++
*/

#include <cmath>
#include <iostream>
#include <string>

int *remove_even(int *arr, int &size) {
  int j = 0;
  // Replace this placeholder return statement with your code
  for (int i = 0; i < size; i++) {
    if (arr[i] % 2 != 0) {
      j++;
    }
  }
  int *new_arr = new int[j];
  j = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] % 2 != 0) {
      new_arr[j] = arr[i];
      j++;
    }
  }
  size = j;
  return new_arr;
}

int main() {
  int inputs[][10] = {{3, 2, 41, 3, 34},
                      {-5, -4, -3, -2, -1},
                      {-1, 2, 3, -4, -10},
                      {1, 2, 3, 7},
                      {2, 4, 6, 8, 10}};

  int sizes[] = {4, 5, 5, 1, 5};
  int *result;
  for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); ++i) {
    std::cout << i + 1 << ".\tArray: [";
    for (int j = 0; j < sizes[i]; ++j) {
      if (j == sizes[i] - 1)
        std::cout << inputs[i][j];
      else
        std::cout << inputs[i][j] << ", ";
    }
    std::cout << "]" << std::endl;

    result = remove_even(inputs[i], sizes[i]);

    std::cout << "\n\tResult: [";
    for (int j = 0; j < sizes[i]; ++j) {
      if (j == sizes[i] - 1)
        std::cout << result[j];
      else
        std::cout << result[j] << ", ";
    }
    std::cout << "]" << std::endl;

    delete[] result;

    std::cout << std::string(100, '-') << std::endl;
  }

  return 0;
}