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


struct SumaData{
    int  max_izq;
    int  max_dch;
    int  sum;
    int  max_sub;
};



// 5 6 -1 1 1 -5 9 1 -5 -2 
SumaData SumaMax (int *v, int inicio, int final){
    SumaData result, d1, d2;
    if (inicio==final){
        result.max_izq = v[inicio];
        result.max_dch = v[inicio];
        result.sum = v[inicio];
        result.max_sub = v[inicio];
        return (result);
    }

    int mid = (final+inicio)/2;
    (d1)=SumaMax(v, inicio, mid);
    (d2)=SumaMax(v, mid+1, final);
    
    result.max_izq = max(d1.max_izq, d1.sum+d2.max_izq);
    result.max_dch = max(d2.max_dch, d2.sum+d1.max_dch);
    result.sum = d1.sum + d2.sum;
    int max_cross = d1.max_dch + d2.max_izq;
    result.max_sub = max(max(max_cross, d1.max_sub), d2.max_sub);
    return (result);
}
 
int kadane(int *a, int size){
    int max_global = a[0];
    int max_current = a[0];

    for (int i = 1; i < size; i++) {
        max_current = max(a[i], max_current + a[i]);
        if (max_current > max_global) {
            max_global = max_current;
        }
    }
    return max_global;
}

int main(int argc, char *argv[]) {
    int TAM= atoi(argv[1]);
    srandom(TAM);
    int *v = new int [TAM];
    for (int i=0; i <TAM; i++){
        v[i] = rand() % 10 - (rand() % 10);
    }
    
    if (strcmp(argv[2], "1") == 0) { // Time Test
        auto start = chrono::high_resolution_clock::now();
        SumaMax(v, 0, TAM-1);
        auto end = chrono::high_resolution_clock::now();
        std::cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    } 
    else{ // Correctness Test
        int *kadaneVector = new int[TAM];
        for (int i = 0; i < TAM; i++) {
            kadaneVector[i] = v[i];
        }
        int res1 = SumaMax(v, 0, TAM-1).max_sub;
        int res2 = kadane(kadaneVector, TAM);
        
        if (res1 != res2) {
            std::cout << "Error [" << TAM << "]: " << res1 << " != " << res2 << endl;
        }
        
    }

    int kadaneResult = kadane(v,TAM);
}