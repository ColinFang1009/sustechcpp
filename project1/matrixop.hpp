#pragma once //make sure this is only included once
#include <cstddef>


void matmul1(size_t r1, size_t c, size_t c2, float * m1, float * m2, float * result); // brute force
void matmul2(size_t r1, size_t c, size_t c2, float * m1, float * m2, float * result); //swap j and k
void matmul3(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result); //using AVX intrinsics to vectorize (dgemm_avx) 
void matmul4(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result); //Unroll, vectorize intrinsics
static inline void do_block_f(size_t r1, size_t c, size_t c2, int si, int sj, int sk,float *A, float *B, float *C); //calculate the block
void matmul5(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result); //cache blocking, divide the matrices into submatrices
void matmul6(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result); //using omp to do parallel calculation, #pragma omp parallel for

void matCompare(size_t r1, size_t c1, size_t r2, size_t c2, float *m1, float *m2); //compare two matrices and print their average percentage difference