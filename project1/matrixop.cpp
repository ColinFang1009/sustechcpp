#include <iostream>
//#include <algorithm>
//#include <iomanip>
#include <cstdlib>
#include <immintrin.h> //SIMD intrinsics
#include <omp.h>       //parallel
#include <stddef.h>    //exit

#include "matrixop.hpp"

#define UNROLL 4     //4
#define BLOCKSIZE 64 //32

using namespace std;

void matmul1(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result) // brute force
{
    //m1: r1*c, m2: c*c2, result: r1*c2
    for (int i = 0; i < r1; ++i)
    {
        for (int j = 0; j < c2; ++j)
        {
            for (int k = 0; k < c; ++k)
            {
                result[i * (c2) + j] += m1[i * c + k] * m2[k * c2 + j];
            }
        }
    }
}

void matmul2(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result)
{
    //m1: r1*c, m2: c*c2, result: r1*c2
    float s;
    for (int i = 0; i < r1; ++i)
    {
        for (int k = 0; k < c; ++k)
        {
            s = m1[i * c + k];
            for (int j = 0; j < c2; ++j)
            {
                result[i * (c2) + j] += s * m2[k * (c2) + j];
            }
        }
    }
}

void matmul3(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result)
{
    //m1: r1*c, m2: c*c2, result: r1*c2
    //each _mm256 can store 8 float,(=8*4 byte = 256bit)
    for (size_t i = 0; i < r1; i++) 
    {
        for (size_t j = 0; j < c2; j += 8) 
        {
            __m256 c0 = _mm256_load_ps(result + i * c2 + j); // c0 = Cij
            for (size_t k = 0; k < c; k++)
            {
                c0 = _mm256_add_ps(c0,
                                   _mm256_mul_ps(_mm256_load_ps(m1 + i * c + k),         
                                                 _mm256_broadcast_ss(m2 + k * c2 + j))); 
            }
            _mm256_store_ps(result + i * c2 + j, c0); // Cij = c0 
            ;
        }
    }
}

void matmul4(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result)
{
    for (size_t i = 0; i < r1; i++) 
    {
        for (size_t j = 0; j < c2; j += 8 * UNROLL)
        {
            __m256 ca[UNROLL]; //array containing UNROLL number of __m256 element
            for (int x = 0; x < UNROLL; x++)
            {
                ca[x] = _mm256_load_ps(result + i * c2 + x * 8 + j);
            }
            for (size_t k = 0; k < c; k++)
            {
                __m256 b = _mm256_broadcast_ss(m2 + k * c2 + j);
                for (int x = 0; x < UNROLL; x++)
                {
                    ca[x] = _mm256_add_ps(ca[x],
                                          _mm256_mul_ps(_mm256_load_ps(m1 + i * c + k + x * 8),
                                                        b));
                }
            }
            for (int x = 0; x < UNROLL; x++)
            {
                _mm256_store_ps(result + i * c2 + x * 8 + j, ca[x]);
            }
        }
    }
}
static inline void do_block_f(size_t r1, size_t c, size_t c2, int si, int sj, int sk,
                              float *A, float *B, float *C)
{
    for (int i = si; i < si + BLOCKSIZE; i++) 
    {
        for (int j = sj; j < sj + BLOCKSIZE; j += UNROLL * 8)
        {
            __m256 ca[UNROLL];
            for (int x = 0; x < UNROLL; x++)
            {
                ca[x] = _mm256_load_ps(C + i * c2 + x * 8 + j);
            }
            for (int k = sk; k < sk + BLOCKSIZE; k++)
            {
                __m256 b = _mm256_broadcast_ss(B + k * c2 + j);
                for (int x = 0; x < UNROLL; x++)
                {
                    ca[x] = _mm256_add_ps(ca[x],
                                          _mm256_mul_ps(
                                              _mm256_load_ps(A + k + x * 8 + i * c), b));
                }
            }

            for (int x = 0; x < UNROLL; x++)
            {
                _mm256_store_ps(C + i * c2 + x * 8 + j, ca[x]);
            }
        }
    }
}

void matmul5(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result)
{
    for (int sj = 0; sj < c2; sj += BLOCKSIZE)
    {
        for (int si = 0; si < r1; si += BLOCKSIZE)
        {
            for (int sk = 0; sk < c; sk += BLOCKSIZE)
            {
                do_block_f(r1, c, c2, si, sj, sk, m1, m2, result);
            }
        }
    }
}

void matmul6(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result)
{
#pragma omp parallel for
    for (int sj = 0; sj < c2; sj += BLOCKSIZE)
    {
        for (int si = 0; si < r1; si += BLOCKSIZE)
        {
            for (int sk = 0; sk < c; sk += BLOCKSIZE)
            {
                do_block_f(r1, c, c2, si, sj, sk, m1, m2, result);
            }
        }
    }
}

void matCompare(size_t r1, size_t c1, size_t r2, size_t c2, float *m1, float *m2)
{
    //matrix1: r1*c1 matrix2: r2*c2
    float diff;
    if (c1 != c2 || r1 != r2)
        cout << "The two matrices are not comparable" << endl;
    else
    {
        for (int i = 0; i < r1; i++)
            for (int j = 0; j < c1; j++)
            {
                if (m1[i * c1 + j] > m2[i * c2 + j])
                    diff += (m1[i * c1 + j] - m2[i * c2 + j]) / m1[i * c1 + j];
                else
                    diff += (m2[i * c1 + j] - m1[i * c2 + j]) / m2[i * c2 + j];
            }
        diff = diff / (r1 * c1);
        cout << "The percentage difference is around " << diff << endl;
    }
}