/* Maximum sum sub array
Brute force: Use two nested loops 

Standard approach: Kadane's algorithm
Key Idea: 
Step 1: compare the current sum + x with x
(Do not compare the current number with the next number.)
Step 2: Conmpare the current sum and max sum

under the hood it might be functioning sth like this
Case 1: Current sum is +ve, next integer is +ve: 
Extend the subarray. Since this makes the sum even larger
also change the max array indices

Case 2: Current sum is +ve, next integer is -ve . 
Extend the subarray. since starting a new sum will definitely be negative atleast until the first element
but dont increment the max_end_idx

Case 3: Current sum is -ve, next integer is -ve
Start a new sub array : because If you include the next integer it is going to make the sum worse
but which will be the max sub array, the previous or the current one ??
lets say current sum is -2, next integer is -15. In this case the max sum will be current sum
lets say current sum is -15, next integer is -15. In this case the max sum will be current sum

Case 4: Current sum is -ve, next is +ve.
Start a new sub array: because the new one is better than the old negative one
the max sum will be the next number or a previous max sub array.

Instead of coding such a complicated logic. there is a more succinct way to do this
Check the code

*/

#include<iostream>
#include<vector> 
using namespace std;

vector <int> max_subarray_kadane(const vector<int> &x) ;

int main(){
   vector<vector <int>> arrays = {
      {-1,10,8,7,-6,6},
      {2,3,-8,7,-1,2}};
   vector <int> result ;

   for (vector <int> a: arrays){
      cout<<"\n ----------------";
      cout<<"\n array:";
      for (int x: a){
         cout<<x<<",";
      }
      cout<<"\n";      
      result = max_subarray_kadane(a);
      cout<< "\n Max_sum = " << result[0] << ", start_idx = " << result[1] << ", end_idx =" << result[2];
      cout<< "\n";
   }

}

vector <int> max_subarray_kadane(const vector<int> &x){
    int max_sum = x[0];    
    int max_start_idx = 0;
    int max_end_idx = 0;
    
    int curr_sum = x[0];
    int curr_start_idx = 0;
    int curr_end_idx = 0;

    for( size_t i = 1; i < x.size(); i++){
       
       // Step 1: Compare curr_sum + x and x(the next integer)
       if (curr_sum + x[i] > x[i]) {
        // Extend the current array
        curr_sum = curr_sum +x[i];
        curr_end_idx = i;
       }
       else {
        // Start a new array
        curr_sum = x[i];
        curr_start_idx = i;
        curr_end_idx   = i;
       }

       // Step 2: Compare curr_sum and max_sum
       if (curr_sum > max_sum) {
        // Update max sum and start and end indices
        max_sum = curr_sum ;
        max_start_idx = curr_start_idx;
        max_end_idx = curr_end_idx; 
       }

    }

    vector <int> result = {max_sum, max_start_idx, max_end_idx};
    return result;
}