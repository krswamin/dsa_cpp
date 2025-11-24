/* Note 
1) using arrays is not recommended. Using vectors is preferred
This code is in place because educative.io expects arrays and not vectors

2) observe how new and delete are used
Every new is accompanied by a delete. The variable new_arr is created using new in remove_even function
It is deleted in the main , even though it was created inside new_arr. This is because remove_even was created on the heap
using new and delete in this manner is not recommended in modern c++
*/

#include<iostream>
using namespace std;

int * findProduct(int arr[], int size) {
    
    int left_product[size];
    int right_product[size];
    int *product = new int[size];

    left_product[0]= 1;
    right_product[size-1] = 1;
    for(int i=1; i<size; i++){
        left_product[i] = arr[i-1]*left_product[i-1];
        right_product[size-1-i] = arr[size-i]*right_product[size-i];
    }

    for(int i=0; i<size; i++){
        product[i] = left_product[i]*right_product[i];
    }
    
    return product;
}


int main() {
    int inputs[][10] = {
        {1, 2, 3, 4},
        {5, -3, 1, 2},
        {2, 2, 2, 0},
        {0, 0, 0, 0},
        {-1, -2, -4}
    };
    int sizes[] = {4, 4, 4, 4, 3};

    for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
        cout << i + 1 << ".\tArray: [";
        for (int j = 0; j < sizes[i]; j++) {
            cout << inputs[i][j];
            if (j != sizes[i] - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;

        int* result = findProduct(inputs[i], sizes[i]);
        cout << "\n\tList of products: [";
        for (int k = 0; k < sizes[i]; k++) {
            
            cout << result[k];
            if (k != sizes[i] - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;

        cout << "-" << string(70, '-') << endl;

        // Free memory allocated for the product array
        delete[] result;
    }

    return 0;
}
