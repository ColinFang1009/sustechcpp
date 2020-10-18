//vecdot.cpp vector dot product calculator
//Name: Weike Fang (22010055)
#include <cblas.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <cstdlib>

using namespace std;
float dot(int index, float *v1, float *v2)
{
    float dot1;
    float dot2;
    float dot3;
    float dot4;
    float result;
    for (int i = 0; i < index; i+=4)
    {
        dot1 += v1[i] * v2[i];
        dot2 += v1[i+1] * v2[i+1];
        dot3 += v1[i+2] * v2[i+2];
        dot4 += v1[i+3] * v2[i+3];
    }
    result = dot1 + dot2 + dot3 + dot4;
    return result;
}
int main()
{
    srand(static_cast<unsigned>(time(0))); //set seed
    int n = 200000000;
    float *v1 = new float[n];
    float *v2 = new float[n];
    for (int i = 0; i < n; i++)
    {
        float r2 = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
        float r1 = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
        //float r1 = 1.0;
        //float r2 = 1.0;
        v1[i] = r1;
        v2[i] = r2;
    }
    //int M = 1;
    //int N = 1; 
    //int K = n; 
    //double alpha = 1.0;
    //double beta = 0.0;
    float result;

    auto start = std::chrono::steady_clock::now();
    result = cblas_sdot(n, v1, 1, v2, 1);
    //the below is for matrix multiplication
    //cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, v1, K, v2, N, beta, result, N);
    auto end = std::chrono::steady_clock::now();
    cout << "Using OpenBLAS lib: \n";
    cout << "The dot product is " << result << endl;
    std::cout << "Dot product calculations took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "mus = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms ="
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s.\n\n";
              
    auto start2 = std::chrono::steady_clock::now();
    float result2 = dot(n, v1, v2);
    auto end2 = std::chrono::steady_clock::now();
    cout << "Using my dot-product function: \n";
    cout << "The dot product2 is " << result2 << endl;
    std::cout << "Dot product calculations took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << "mus = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << "ms ="
              << std::chrono::duration_cast<std::chrono::seconds>(end2 - start2).count() << "s.\n\n";
              
    delete[] v1;
    delete[] v2;
}
