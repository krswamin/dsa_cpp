// inplace rotate image
#include<iostream>
#include<vector>
using namespace std;

void rotate_image_90_clockwise(vector<vector<int>> & image);
void rotate_image_90_anticlockwise(vector<vector<int>> & image);
void transpose_image(vector<vector<int>> & image);
void reverse_row(vector<vector<int>> & image, int row_num);
void reverse_col(vector<vector<int>> & image, int col_num);
void print_image(const vector<vector<int>> & image);

int main(){
    vector<vector<int>> image = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    cout<<"Original Image:";
    print_image(image);
    cout<<"\n\n Rotate Image 90 degree clockwise:";
    rotate_image_90_clockwise(image);
    print_image(image);
    
    image = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    cout<<"\n\n Rotate Image 90 degree anti clockwise:";
    rotate_image_90_anticlockwise(image);
    print_image(image);
    cout<<"\n";


    image = {{1,2,3}, {5,6,7}, {9,10,11}};
    cout<<"\n\n Original Image:";
    print_image(image);
    cout<<"\n\n Rotate Image 90 degree clockwise:";
    rotate_image_90_clockwise(image);
    print_image(image);
    
    image = {{1,2,3}, {5,6,7}, {9,10,11}};
    cout<<"\n\n Rotate Image 90 degree anti clockwise:";
    rotate_image_90_anticlockwise(image);
    print_image(image);
    cout<<"\n";

    image = {{1}};
    cout<<"\n\n Original Image:";
    print_image(image);
    cout<<"\n\n Rotate Image 90 degree clockwise:";
    rotate_image_90_clockwise(image);
    print_image(image);
    
    image = {{1}};
    cout<<"\n\n Rotate Image 90 degree anti clockwise:";
    rotate_image_90_anticlockwise(image);
    print_image(image);
    cout<<"\n";

}


// In place rotate image 90 degree clockwise 
void rotate_image_90_clockwise(vector<vector<int>> &image){
     transpose_image(image);
     for(size_t row_num=0; row_num<image.size(); row_num++){
        reverse_row(image, row_num);
     }
}

// In place rotate image 90 degree anti clockwise
void rotate_image_90_anticlockwise(vector<vector<int>> &image){
     transpose_image(image);
     for(size_t col_num=0; col_num<image.size(); col_num++){
        reverse_col(image, col_num);
     }
}

// In place transpose image
void transpose_image(vector<vector<int>> & image){
    int temp;
    for( size_t i =0; i<image.size(); i++){
        for( size_t j =i; j<image.size(); j++){
            temp = image[i][j];
            image[i][j] = image[j][i];
            image[j][i] = temp;
        }
    }
}

// In place reverse row
void reverse_row(vector<vector<int>> & image, int row_num){
    int temp;
    size_t i = 0;
    size_t j = image.size() -1;
    while(i<j){
        temp = image[row_num][i];
        image[row_num][i] = image[row_num][j];
        image[row_num][j] = temp;
        i++;
        j--;
    }
}

// In place reverse column
void reverse_col(vector<vector<int>> & image, int col_num){
    int temp;
    size_t i = 0;
    size_t j = image.size() -1;
    while(i<j){
        temp = image[i][col_num];
        image[i][col_num] = image[j][col_num];
        image[j][col_num] = temp;
        i++;
        j--;
    }
}

// Print image
void print_image(const vector<vector<int>> & image){
    for( size_t i =0; i<image.size(); i++){
        cout<<"\n";
        for( size_t j =0; j<image.size(); j++){
            cout<<image[i][j]<<",";
        }        
    }
}


