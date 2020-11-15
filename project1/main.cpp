#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <cblas.h>
#include <cstdlib>
#include <immintrin.h>
//#include <omp.h>
#include <stddef.h>
#include "matrixop.hpp"

int main()
{
    size_t r1 = 8192; //m1 row
    size_t c = 8192;// m1 column and m2 row
    size_t c2 = 8192; // m2 column
	float *m1 = new float[r1*c];
    float *m2 = new float[c*c2];
    float *res = new float[r1*c2];
    float *res2 = new float[r1*c2];
	for(size_t i=0;i<r1*c2;i++) //Need change
	{
	 	m1[i]=0.1+i*128;
	 	m2[i]=0.2+i*0.1;
	 	res[i]=0;
        res2[i]=0;
    }

    auto start2 = std::chrono::steady_clock::now();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, r1, c2, c, 1.0, m1, c, m2,c2 , 0.0, res, c2);
    auto end2 = std::chrono::steady_clock::now();
    std::cout << "The OpenBLAS Matrix product calculations took "
            << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << "mus = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << "ms ="
            << std::chrono::duration_cast<std::chrono::seconds>(end2 - start2).count() << "s.\n";

    auto start = std::chrono::steady_clock::now();
	matmul5(r1,c,c2,m1,m2,res2);
    //matmul6(r1,m1,m2,res2);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Matmul5 Matrix product calculations took "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "mus = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms ="
            << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s.\n";
    matCompare(r1,c2,r1,c2,res,res2);
    

    delete m1;
    delete m2;
    delete res;
    return 0;
}