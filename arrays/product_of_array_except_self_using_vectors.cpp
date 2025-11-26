#include <iostream>
#include <vector>
using namespace std;

vector<int> product_except_self(const vector<int> &arr);
void print_array(const vector<int> &arr);

int main() {
  vector<vector<int>> arrs = {{-1, 10, 8, 7, -6, 6}, {2, 3, -8, 7, -1, 2}};

  vector<int> product;
  for (auto &arr : arrs) {
    cout << "\nOriginal Array     :";
    print_array(arr);

    product = product_except_self(arr);
    cout << "Product except self:";
    print_array(product);
  }
}

vector<int> product_except_self(const vector<int> &arr) {
  vector<int> left_product;
  vector<int> right_product(arr.size());
  vector<int> product;

  left_product.reserve(arr.size());
  product.reserve(arr.size());

  left_product.push_back(1);
  right_product[arr.size() - 1] = 1;
  for (size_t i = 1; i < arr.size(); i++) {
    left_product.push_back(arr[i - 1] * left_product[i - 1]);
    right_product[arr.size() - 1 - i] =
        arr[arr.size() - i] * right_product[arr.size() - i];
  }

  for (size_t i = 0; i < arr.size(); i++) {
    product.push_back(left_product[i] * right_product[i]);
  }

  return product;
}

void print_array(const vector<int> &arr) {
  for (int x : arr) {
    cout << x << ", ";
  }
  cout << "\n";
}