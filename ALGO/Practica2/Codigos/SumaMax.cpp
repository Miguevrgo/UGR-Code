#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <cstring>
#include <chrono>
using namespace std;


/**
 * @brief Kadane's algorithm to find the maximum subarray sum implementation
 * 
 * 
 * @param arr array of integers
 * @param low start index
 * @param high end index
 * @return maximum subarray sum
 */
int kadane(const int * const arr, int low, int high) {
    int max_global = arr[low];
    int max_current = arr[low];

    for (int i = low + 1; i <= high; ++i) {
        max_current = max(arr[i], max_current + arr[i]);
        if (max_current > max_global) {
            max_global = max_current;
        }
    }
    return max_global;
}


/**
 * @brief Calculates the maximum subarray sum using the divide and conquer 
 * approach applying the Kadane's algorithm to the left and right subarrays
 * and the sum of the maximum subarrays that cross the middle of the array.
 * 
 * @note Note that the functionality of crossLeftSum and crossRightSum is
 * to find the biggest sum of the subarray that crosses the middle of the array,
 * note that this sum does not skip the middle element. For example:
 * 
 * arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
 *                  |___________|
 * Maximum subarray can only calculate intervals of the form provided above.
 * 
 * @param arr array of integers
 * @param low start index 
 * @param high end index
 * @param threshold "UMBRAL" to apply Kadane's algorithm
 * @return maximum subarray sum
 */
int maxSubArray(const int * const arr, int low, int high, int threshold) {
    if (high - low + 1 <= threshold) {
        return kadane(arr, low, high);
    }

    int mid = low + (high - low) / 2;

    int leftSum = maxSubArray(arr, low, mid, threshold);
    int rightSum = maxSubArray(arr, mid + 1, high, threshold);

    int crossLeftSum = numeric_limits<int>::min();
    int crossRightSum = numeric_limits<int>::min();
    int sum = 0;

    for (int i = mid; i >= low; --i) {
        sum += arr[i];
        crossLeftSum = max(crossLeftSum, sum);
    }

    sum = 0;
    for (int i = mid + 1; i <= high; ++i) {
        sum += arr[i];
        crossRightSum = max(crossRightSum, sum);
    }

    int crossSum = crossLeftSum + crossRightSum;

    return max({leftSum, rightSum, crossSum});
}


int main(int argc, char *argv[]) {
    int TAM= atoi(argv[1]);
    int UMBRAL=atoi(argv[3]);
    srandom(TAM);
    int *v = new int [TAM];
    for (int i=0; i <TAM; i++){
        v[i] = rand() % 10 - (rand() % 10);
    }
    
    if (strcmp(argv[2], "1") == 0) { // Time Test Kadane

        auto start = chrono::high_resolution_clock::now();
        kadane(v, 0, TAM-1);
        auto end = chrono::high_resolution_clock::now();
        std::cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()<<endl;

    } 
    else if (strcmp(argv[2], "2") == 0) { // Time Test DyV
        auto start = chrono::high_resolution_clock::now();
        maxSubArray(v, 0, TAM-1,UMBRAL);
        auto end = chrono::high_resolution_clock::now();
        std::cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()<<endl;
    } 
    else{ // Correctness Test
        int *kadaneVector = new int[TAM];
        for (int i = 0; i < TAM; i++) {
            kadaneVector[i] = v[i];
        }

        int res1 = maxSubArray(v, 0, TAM-1, UMBRAL);
        int res2 = kadane(kadaneVector, 0, TAM-1);
        if (res1 != res2) {
            std::cout << "Error [" << TAM << "]: " << res1 << " != " << res2 << endl;
        }
        
    }
    return 0;
}
